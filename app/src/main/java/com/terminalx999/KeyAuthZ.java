package com.terminalx999;

import android.content.Context;
import android.os.Build;
import android.provider.Settings;

import org.json.JSONArray;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.util.ArrayList;
import java.util.List;

public class KeyAuthZ {

    public static class SubscriptionData {
        public String name;
        public String key;
        public String expiry;
        public long timeLeft;

        public SubscriptionData(String name, String key, String expiry, long timeLeft) {
            this.name = name;
            this.key = key;
            this.expiry = expiry;
            this.timeLeft = timeLeft;
        }
    }

    public static class UserData {
        public String username = "";
        public String ip = "";
        public String hwid = "";
        public String createDate = "";
        public String lastLogin = "";
        public long timeLeft = 0;
        public List<SubscriptionData> subscriptions = new ArrayList<>();
    }

    private final String name;
    private final String ownerId;
    private final String secret;
    private final String version;
    private final String apiUrl;
    private final Context context;

    private String sessionId = null;
    private String encKey = null;
    private UserData userData = new UserData();

    public KeyAuthZ(String name, String ownerId, String secret, String version, String apiUrl, Context context) {
        this.name = name;
        this.ownerId = ownerId;
        this.secret = secret;
        this.version = version;
        this.apiUrl = apiUrl.endsWith("/") ? apiUrl : apiUrl + "/";
        this.context = context;
    }

    public void init() throws Exception {
        StringBuilder sb = new StringBuilder();
        sb.append("type=").append(URLEncoder.encode("init", "UTF-8"))
          .append("&name=").append(URLEncoder.encode(name, "UTF-8"))
          .append("&ownerid=").append(URLEncoder.encode(ownerId, "UTF-8"))
          .append("&secret=").append(URLEncoder.encode(secret, "UTF-8"))
          .append("&version=").append(URLEncoder.encode(version, "UTF-8"));

        JSONObject response = postRequest(apiUrl, sb.toString());
        boolean success = response.optBoolean("success", false);
        if (!success) {
            String msg = response.optString("message", "Initialization failed");
            throw new Exception(msg);
        }

        this.sessionId = response.optString("sessionid", "");
        this.encKey = response.optString("enckey", "");

        if (this.sessionId.isEmpty()) {
            throw new Exception("Session ID not received from KeyAuthZ server");
        }
    }

    public UserData license(String key) throws Exception {
        if (sessionId == null || sessionId.isEmpty()) {
            init();
        }

        String hwid = getHWID(context);

        StringBuilder sb = new StringBuilder();
        sb.append("type=").append(URLEncoder.encode("license", "UTF-8"))
          .append("&sessionid=").append(URLEncoder.encode(sessionId, "UTF-8"))
          .append("&key=").append(URLEncoder.encode(key, "UTF-8"))
          .append("&hwid=").append(URLEncoder.encode(hwid, "UTF-8"))
          .append("&name=").append(URLEncoder.encode(name, "UTF-8"))
          .append("&ownerid=").append(URLEncoder.encode(ownerId, "UTF-8"));

        JSONObject response = postRequest(apiUrl, sb.toString());
        boolean success = response.optBoolean("success", false);
        if (!success) {
            String msg = response.optString("message", "License validation failed");
            throw new Exception(msg);
        }

        userData = new UserData();
        userData.hwid = hwid;

        JSONObject info = response.optJSONObject("info");
        if (info != null) {
            userData.username = info.optString("username", key);
            userData.ip = info.optString("ip", "");
            userData.hwid = info.optString("hwid", hwid);
            userData.createDate = info.optString("createdate", "");
            userData.lastLogin = info.optString("lastlogin", "");

            JSONArray subs = info.optJSONArray("subscriptions");
            if (subs != null) {
                for (int i = 0; i < subs.length(); i++) {
                    JSONObject subObj = subs.optJSONObject(i);
                    if (subObj != null) {
                        String sName = subObj.optString("subscription", "Default");
                        String sKey = subObj.optString("key", key);
                        String sExpiry = subObj.optString("expiry", "");
                        long sTimeLeft = subObj.optLong("timeleft", 0);
                        if (i == 0) userData.timeLeft = sTimeLeft;
                        userData.subscriptions.add(new SubscriptionData(sName, sKey, sExpiry, sTimeLeft));
                    }
                }
            }
        } else {
            userData.username = key;
        }

        return userData;
    }

    public boolean check() {
        if (sessionId == null || sessionId.isEmpty()) return false;
        try {
            String postData = "type=check&sessionid=" + URLEncoder.encode(sessionId, "UTF-8");
            JSONObject res = postRequest(apiUrl, postData);
            return res.optBoolean("success", false);
        } catch (Exception e) {
            return false;
        }
    }

    public void log(String message) {
        if (sessionId == null || sessionId.isEmpty()) return;
        try {
            String postData = "type=log&sessionid=" + URLEncoder.encode(sessionId, "UTF-8")
                    + "&message=" + URLEncoder.encode(message, "UTF-8")
                    + "&pcuser=" + URLEncoder.encode(Build.MODEL, "UTF-8");
            postRequest(apiUrl, postData);
        } catch (Exception ignored) {}
    }

    public UserData getUserData() {
        return userData;
    }

    public String getSessionId() {
        return sessionId;
    }

    public static String getHWID(Context ctx) {
        try {
            String androidId = "";
            if (ctx != null) {
                androidId = Settings.Secure.getString(ctx.getContentResolver(), Settings.Secure.ANDROID_ID);
            }
            if (androidId == null || androidId.isEmpty()) {
                androidId = "NO_ANDROID_ID";
            }
            String raw = androidId + "_" + Build.BOARD + "_" + Build.BRAND + "_" + Build.DEVICE + "_" + Build.MODEL;
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hash = md.digest(raw.getBytes(StandardCharsets.UTF_8));
            StringBuilder hexString = new StringBuilder();
            for (byte b : hash) {
                String hex = Integer.toHexString(0xff & b);
                if (hex.length() == 1) hexString.append('0');
                hexString.append(hex);
            }
            return hexString.toString();
        } catch (Exception e) {
            return "HWID_" + Build.SERIAL;
        }
    }

    private JSONObject postRequest(String targetUrl, String postData) throws Exception {
        URL url = new URL(targetUrl);
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("POST");
        conn.setConnectTimeout(15000);
        conn.setReadTimeout(15000);
        conn.setDoOutput(true);
        conn.setInstanceFollowRedirects(true);
        conn.setRequestProperty("User-Agent", "KeyAuthZ-Native-Client");
        conn.setRequestProperty("Content-Type", "application/x-www-form-urlencoded; charset=UTF-8");
        conn.setRequestProperty("Accept", "application/json");

        byte[] postBytes = postData.getBytes(StandardCharsets.UTF_8);
        conn.setFixedLengthStreamingMode(postBytes.length);

        try (OutputStream os = conn.getOutputStream()) {
            os.write(postBytes);
            os.flush();
        }

        int responseCode = conn.getResponseCode();
        InputStream is = (responseCode >= 200 && responseCode <= 299) ? conn.getInputStream() : conn.getErrorStream();

        if (is == null) {
            throw new Exception("HTTP Error " + responseCode + ": No response body");
        }

        StringBuilder response = new StringBuilder();
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(is, StandardCharsets.UTF_8))) {
            String line;
            while ((line = reader.readLine()) != null) {
                response.append(line);
            }
        } finally {
            conn.disconnect();
        }

        String body = response.toString().trim();
        if (body.isEmpty()) {
            throw new Exception("HTTP Error " + responseCode + ": Empty server response");
        }

        if (body.equals("KeyAuth_Invalid")) {
            throw new Exception("KeyAuthZ credentials invalid (app name, ownerid, or secret mismatch)");
        }

        try {
            return new JSONObject(body);
        } catch (Exception jsonEx) {
            if (responseCode >= 400) {
                throw new Exception("HTTP " + responseCode + ": " + body);
            }
            throw new Exception("Invalid JSON from server: " + body);
        }
    }
}
