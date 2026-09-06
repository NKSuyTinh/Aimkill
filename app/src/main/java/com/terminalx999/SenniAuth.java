package com.terminalx999;

/* =========================================================================
   🌸 SenniCute Auth SDK - Java (POST + HMAC-SHA256 Anti-Tamper)
   ========================================================================= */
import android.content.Context;
import android.os.Build;
import android.provider.Settings;

import org.json.JSONObject;

import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;
import java.text.SimpleDateFormat;
import java.util.*;
import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;

public class SenniAuth {
    private static final String API_URL = "https://txhauth.store/verify.php";
    private static final String OWNER = "namkhanhiusenni";
    private static final String API_NAME = "Aimkill";
    private static final String API_SECRET = "64c198aee174707380d4123b6b1170bc0b4893a7bc088f48c26a5ee24e8a5076";

    public static class VerifyResult {
        public boolean valid;
        public String message;
        public long expiry;
        public String expiryStr;
        public String hwid;
        public String rawResponse;

        public VerifyResult(boolean valid, String message, long expiry, String expiryStr, String hwid, String rawResponse) {
            this.valid = valid;
            this.message = message;
            this.expiry = expiry;
            this.expiryStr = expiryStr;
            this.hwid = hwid;
            this.rawResponse = rawResponse;
        }
    }

    public static String getHWID(Context context) {
        if (context != null) {
            try {
                String androidId = Settings.Secure.getString(context.getContentResolver(), Settings.Secure.ANDROID_ID);
                if (androidId != null && !androidId.trim().isEmpty()) {
                    return androidId.trim();
                }
            } catch (Exception ignored) {}
        }
        try {
            String hw = HWID.getHWID();
            if (hw != null && !hw.trim().isEmpty()) return hw.trim();
        } catch (Exception ignored) {}
        try {
            Process p = Runtime.getRuntime().exec("wmic csproduct get uuid");
            BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
            br.readLine(); br.readLine();
            String res = br.readLine();
            if (res != null && !res.trim().isEmpty()) return res.trim();
        } catch (Exception ignored) {}
        try {
            String name = System.getenv("COMPUTERNAME");
            if (name != null && !name.trim().isEmpty()) return name.trim();
        } catch (Exception ignored) {}
        return "ANDROID_" + Build.BOARD + "_" + Build.SERIAL;
    }

    public static String getHWID() {
        return getHWID(null);
    }

    private static String computeHMAC(Map<String, String> params, String secret) throws Exception {
        List<String> parts = new ArrayList<>();
        for (Map.Entry<String, String> entry : params.entrySet()) {
            parts.add(entry.getKey() + "=" + URLEncoder.encode(entry.getValue(), "UTF-8"));
        }
        String canonical = String.join("&", parts);

        Mac mac = Mac.getInstance("HmacSHA256");
        SecretKeySpec keySpec = new SecretKeySpec(secret.getBytes(StandardCharsets.UTF_8), "HmacSHA256");
        mac.init(keySpec);
        byte[] hash = mac.doFinal(canonical.getBytes(StandardCharsets.UTF_8));
        StringBuilder hex = new StringBuilder();
        for (byte b : hash) hex.append(String.format("%02x", b));
        return hex.toString();
    }

    public static VerifyResult verify(Context context, String key) {
        try {
            String hwid = getHWID(context);
            String timestamp = String.valueOf(System.currentTimeMillis() / 1000L);
            String nonce = UUID.randomUUID().toString().replace("-", "");

            Map<String, String> params = new TreeMap<>();
            params.put("api", API_NAME);
            params.put("hwid", hwid);
            params.put("key", key);
            params.put("nonce", nonce);
            params.put("owner", OWNER);
            params.put("timestamp", timestamp);

            String signature = computeHMAC(params, API_SECRET);
            params.put("signature", signature);

            StringBuilder postData = new StringBuilder();
            for (Map.Entry<String, String> param : params.entrySet()) {
                if (postData.length() != 0) postData.append('&');
                postData.append(URLEncoder.encode(param.getKey(), "UTF-8"));
                postData.append('=');
                postData.append(URLEncoder.encode(param.getValue(), "UTF-8"));
            }
            byte[] postDataBytes = postData.toString().getBytes(StandardCharsets.UTF_8);

            URL url = new URL(API_URL);
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setRequestMethod("POST");
            conn.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");
            conn.setRequestProperty("Content-Length", String.valueOf(postDataBytes.length));
            conn.setDoOutput(true);
            conn.setConnectTimeout(8000);
            conn.setReadTimeout(8000);

            try (DataOutputStream wr = new DataOutputStream(conn.getOutputStream())) {
                wr.write(postDataBytes);
            }

            InputStream is = conn.getResponseCode() >= 400 ? conn.getErrorStream() : conn.getInputStream();
            BufferedReader in = new BufferedReader(new InputStreamReader(is, StandardCharsets.UTF_8));
            String line; StringBuilder res = new StringBuilder();
            while ((line = in.readLine()) != null) res.append(line);
            in.close();

            String output = res.toString();
            boolean isValid = false;
            String msg = "Không nhận được phản hồi hợp lệ từ máy chủ";
            long expiry = 0L;
            String expiryStr = "Lifetime";

            try {
                JSONObject json = new JSONObject(output);
                if (json.has("valid")) isValid = json.optBoolean("valid", false);
                if (json.has("message")) msg = json.getString("message");
                if (json.has("expiry")) {
                    expiry = json.optLong("expiry", 0L);
                    if (expiry > 2000000000L || expiry == 0L) {
                        expiryStr = "Lifetime";
                    } else if (expiry > 0L) {
                        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss", Locale.US);
                        expiryStr = sdf.format(new Date(expiry * 1000L));
                    }
                }
            } catch (Exception ignored) {
                if (output.contains("\"valid\": true") || output.contains("\"valid\":true")) {
                    isValid = true;
                    msg = "Xác thực bản quyền thành công 🌸!";
                }
            }

            return new VerifyResult(isValid, msg, expiry, expiryStr, hwid, output);
        } catch (Exception e) {
            return new VerifyResult(false, "Lỗi kết nối mạng: " + e.getMessage(), 0L, "", "", "");
        }
    }

    public static boolean license(String key) {
        VerifyResult res = verify(null, key);
        return res.valid;
    }

    public static boolean license(Context context, String key) {
        VerifyResult res = verify(context, key);
        return res.valid;
    }
}
