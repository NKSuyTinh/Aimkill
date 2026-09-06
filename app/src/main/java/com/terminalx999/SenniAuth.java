package com.terminalx999;

/* =========================================================================
   🌸 SenniCute Auth SDK - Java (POST + HMAC-SHA256 Anti-Tamper)
   ========================================================================= */
import android.content.Context;
import android.os.Build;
import android.provider.Settings;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.TreeMap;
import java.util.UUID;
import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;

public class SenniAuth {
    public static final String API_URL = "https://txhauth.store/verify.php";
    public static final String OWNER = "namkhanhiusenni";
    public static final String API_NAME = "Aimkill";
    public static final String API_SECRET = "64c198aee174707380d4123b6b1170bc0b4893a7bc088f48c26a5ee24e8a5076";

    public static class VerifyResult {
        public boolean valid;
        public String message;
        public long expiry;
        public String expiryFormatted;
        public String hwid;
        public String rawOutput;

        public VerifyResult(boolean valid, String message, long expiry, String expiryFormatted, String hwid, String rawOutput) {
            this.valid = valid;
            this.message = message;
            this.expiry = expiry;
            this.expiryFormatted = expiryFormatted;
            this.hwid = hwid;
            this.rawOutput = rawOutput;
        }
    }

    public static String getHWID(Context ctx) {
        if (ctx != null) {
            try {
                String androidId = Settings.Secure.getString(
                        ctx.getContentResolver(), Settings.Secure.ANDROID_ID);
                if (androidId != null && !androidId.trim().isEmpty()) {
                    return androidId.trim();
                }
            } catch (Exception ignored) {}
        }
        try {
            Process p = Runtime.getRuntime().exec("wmic csproduct get uuid");
            BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
            br.readLine(); br.readLine();
            String line = br.readLine();
            if (line != null && !line.trim().isEmpty()) return line.trim();
        } catch (Exception ignored) {}
        String envComp = System.getenv("COMPUTERNAME");
        return envComp != null ? envComp : "ANDROID_" + Build.ID;
    }

    public static String getHWID() {
        return getHWID(null);
    }

    private static String computeHMAC(Map<String, String> params, String secret) throws Exception {
        StringBuilder canonical = new StringBuilder();
        for (Map.Entry<String, String> entry : params.entrySet()) {
            if (canonical.length() != 0) canonical.append('&');
            canonical.append(entry.getKey()).append('=').append(URLEncoder.encode(entry.getValue(), "UTF-8"));
        }

        Mac mac = Mac.getInstance("HmacSHA256");
        SecretKeySpec keySpec = new SecretKeySpec(secret.getBytes(StandardCharsets.UTF_8), "HmacSHA256");
        mac.init(keySpec);
        byte[] hash = mac.doFinal(canonical.toString().getBytes(StandardCharsets.UTF_8));
        StringBuilder hex = new StringBuilder();
        for (byte b : hash) hex.append(String.format("%02x", b));
        return hex.toString();
    }

    public static VerifyResult verify(Context ctx, String key) {
        try {
            String hwid = getHWID(ctx);
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
            conn.setRequestProperty("User-Agent", "SenniCuteAndroidClient/1.0");
            conn.setDoOutput(true);
            conn.setConnectTimeout(8000);
            conn.setReadTimeout(8000);

            try (DataOutputStream wr = new DataOutputStream(conn.getOutputStream())) {
                wr.write(postDataBytes);
                wr.flush();
            }

            InputStream is = conn.getResponseCode() >= 400 ? conn.getErrorStream() : conn.getInputStream();
            BufferedReader in = new BufferedReader(new InputStreamReader(is, StandardCharsets.UTF_8));
            String line;
            StringBuilder res = new StringBuilder();
            while ((line = in.readLine()) != null) res.append(line);
            in.close();

            String output = res.toString();
            boolean isValid = output.contains("\"valid\": true") || output.contains("\"valid\":true");
            String msg = isValid ? "Xác thực bản quyền thành công 🌸!" : "Key không hợp lệ!";
            long expiry = 0L;
            String expiryStr = "";

            try {
                JSONObject json = new JSONObject(output);
                if (json.has("valid")) isValid = json.optBoolean("valid", false);
                if (json.has("message")) msg = json.getString("message");
                if (json.has("expiry")) {
                    expiry = json.optLong("expiry", 0L);
                    if (expiry > 2000000000L) {
                        expiryStr = "Lifetime";
                    } else if (expiry > 0) {
                        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss", Locale.US);
                        expiryStr = sdf.format(new Date(expiry * 1000L));
                    }
                }
            } catch (Exception ignored) {}

            return new VerifyResult(isValid, msg, expiry, expiryStr, hwid, output);
        } catch (Exception e) {
            return new VerifyResult(false, "Lỗi kết nối mạng: " + e.getMessage(), 0L, "", "", "");
        }
    }

    public static boolean license(String key) {
        VerifyResult res = verify(null, key);
        return res.valid;
    }
}
