
package com.terminalx999;

import android.content.Context;
import android.provider.Settings;
import android.os.Build;

import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;

public class KeyAuth {
    private String appname;
    private String ownerid;
    private String version;
    private String url;
    private Context context;
    private String sessionid; // Store session ID

    public KeyAuth(String appname, String ownerid, String version, String url, Context context) {
        this.appname = appname;
        this.ownerid = ownerid;
        this.version = version;
        this.url = url;
        this.context = context;
        this.sessionid = null; // Initialize as null
    }

    public void init() throws Exception {
        String separator = url.endsWith("/") ? "" : "/";
        String initUrl = url + separator + "?type=init&name=" + URLEncoder.encode(appname, "UTF-8") + "&ownerid=" + URLEncoder.encode(ownerid, "UTF-8") + "&ver=" + URLEncoder.encode(version, "UTF-8");
        JSONObject responseJSON = makeApiCall(initUrl);
        if (!responseJSON.getBoolean("success")) {
            throw new Exception(responseJSON.optString("message", "Initialization failed"));
        }
        // Store sessionid from response
        this.sessionid = responseJSON.optString("sessionid", null);
        if (this.sessionid == null || this.sessionid.isEmpty()) {
            throw new Exception("Session ID not provided in init response");
        }
    }

    private String getHWID(Context context) {
        String base = Settings.Secure.getString(
                context.getContentResolver(),
                Settings.Secure.ANDROID_ID
        );

        if (base == null || base.isEmpty()) {
            base = "UNKNOWN_DEVICE";
        }

        base += Build.BOARD
                + Build.BRAND
                + Build.DEVICE
                + Build.ID;

        if (base.length() < 20) {
            base += "HWIDFILLEREXTRA123";
        }

        return base;
    }



    public JSONObject login(String username, String password) throws Exception {
        if (sessionid == null || sessionid.isEmpty()) {
            throw new Exception("Session ID not initialized. Call init first.");
        }

        // ✅ HWID fetch and patch for 20+ characters
//        String rawHwid = Settings.Secure.getString(context.getContentResolver(), Settings.Secure.ANDROID_ID);
//        String hwid = (rawHwid + "-BSC-sec").substring(0, Math.max(20, (rawHwid + "-BSC-sec").length()));

        String hwid = getHWID(context);


        String separator = url.endsWith("/") ? "" : "/";
        String loginUrl = url + separator + "?type=login" +
                "&username=" + URLEncoder.encode(username, "UTF-8") +
                "&pass=" + URLEncoder.encode(password, "UTF-8") +
                "&hwid=" + URLEncoder.encode(hwid, "UTF-8") +
                "&name=" + URLEncoder.encode(appname, "UTF-8") +
                "&ownerid=" + URLEncoder.encode(ownerid, "UTF-8") +
                "&sessionid=" + URLEncoder.encode(sessionid, "UTF-8");

        JSONObject responseJSON = makeApiCall(loginUrl);
        if (!responseJSON.getBoolean("success")) {
            throw new Exception(responseJSON.optString("message", "Login failed"));
        }
        return responseJSON;
    }

    public void upgrade(String username, String key) throws Exception {
        if (sessionid == null || sessionid.isEmpty()) {
            throw new Exception("Session ID not initialized. Call init first.");
        }
        String separator = url.endsWith("/") ? "" : "/";
        String upgradeUrl = url + separator + "?type=upgrade&username=" + URLEncoder.encode(username, "UTF-8") + "&key=" + URLEncoder.encode(key, "UTF-8") + "&name=" + URLEncoder.encode(appname, "UTF-8") + "&ownerid=" + URLEncoder.encode(ownerid, "UTF-8") + "&sessionid=" + URLEncoder.encode(sessionid, "UTF-8");
        JSONObject responseJSON = makeApiCall(upgradeUrl);
        if (!responseJSON.getBoolean("success")) {
            throw new Exception(responseJSON.optString("message", "Upgrade failed"));
        }
    }

    public void license(String key) throws Exception {
        if (sessionid == null || sessionid.isEmpty()) {
            throw new Exception("Session ID not initialized. Call init first.");
        }
        String separator = url.endsWith("/") ? "" : "/";
        String licenseUrl = url + separator + "?type=license&key=" + URLEncoder.encode(key, "UTF-8") + "&name=" + URLEncoder.encode(appname, "UTF-8") + "&ownerid=" + URLEncoder.encode(ownerid, "UTF-8") + "&sessionid=" + URLEncoder.encode(sessionid, "UTF-8");
        JSONObject responseJSON = makeApiCall(licenseUrl);
        if (!responseJSON.getBoolean("success")) {
            throw new Exception(responseJSON.optString("message", "License activation failed"));
        }
    }

    private JSONObject makeApiCall(String apiUrl) throws Exception {
        return makeApiCall(apiUrl, null);
    }

    private JSONObject makeApiCall(String apiUrl, String postData) throws Exception {
        String baseUrl = apiUrl;
        String query = postData;

        if (query == null) {
            String[] parts = apiUrl.split("\\?");
            baseUrl = parts[0];
            query = parts.length > 1 ? parts[1] : "";
        }

        URL url = new URL(baseUrl);
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setRequestMethod("POST");
        connection.setConnectTimeout(15000);
        connection.setReadTimeout(15000);
        connection.setRequestProperty("User-Agent", "Mozilla/5.0 (Linux; Android 10; SM-G973F) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Mobile Safari/537.36");
        connection.setRequestProperty("Accept", "application/json");
        connection.setRequestProperty("X-Requested-With", "com.terminalx999");
        connection.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");
        connection.setRequestProperty("Connection", "keep-alive");
        connection.setDoOutput(true);
        connection.setInstanceFollowRedirects(false); // We handle it manually

        if (!query.isEmpty()) {
            java.io.OutputStream os = connection.getOutputStream();
            os.write(query.getBytes("UTF-8"));
            os.close();
        }

        int responseCode = connection.getResponseCode();

        // Handle Redirects (301, 302, 307, 308)
        if (responseCode == 301 || responseCode == 302 || responseCode == 307 || responseCode == 308) {
            String newUrl = connection.getHeaderField("Location");
            connection.disconnect();
            return makeApiCall(newUrl, query); // Pass the same query data to the new location
        }

        BufferedReader reader;
        if (responseCode >= 200 && responseCode <= 299) {
            reader = new BufferedReader(new InputStreamReader(connection.getInputStream()));
        } else {
            java.io.InputStream errorStream = connection.getErrorStream();
            if (errorStream != null) {
                reader = new BufferedReader(new InputStreamReader(errorStream));
            } else {
                throw new Exception("HTTP error code: " + responseCode);
            }
        }

        StringBuilder response = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            response.append(line);
        }
        reader.close();
        connection.disconnect();

        try {
            JSONObject json = new JSONObject(response.toString());
            if (responseCode != HttpURLConnection.HTTP_OK && json.has("message")) {
                throw new Exception(json.getString("message"));
            }
            return json;
        } catch (org.json.JSONException e) {
            if (responseCode != HttpURLConnection.HTTP_OK) {
                String errorMsg = response.toString();
                if (errorMsg.isEmpty()) {
                    throw new Exception("HTTP error code: " + responseCode);
                } else {
                    if (errorMsg.length() > 100) errorMsg = errorMsg.substring(0, 100) + "...";
                    throw new Exception(errorMsg);
                }
            }
            throw e;
        }
    }

    // Getter for sessionid (optional, for debugging)
    public String getSessionId() {
        return sessionid;
    }
}
