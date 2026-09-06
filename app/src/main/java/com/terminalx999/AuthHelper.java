package com.terminalx999;

import android.content.Context;
import android.os.Build;
import android.provider.Settings;

import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;
import java.util.Base64;
import java.util.concurrent.CompletableFuture;

import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;

public class AuthHelper {

    private static final String VALIDATE_URL = "https://terminalx999.com/api/validate.php";
    private static final String SECRET_KEY = "SuperSecretKey987654321";
    private static String initToken = null;

    public static class LoginResult {
        public boolean success;
        public String message;
        public String packageName;
        public String expiryDate;
        public String status;
        public String timeLeft;
        public String hwid;

        public LoginResult(boolean success, String message, String packageName, String expiryDate, String status, String timeLeft, String hwid) {
            this.success = success;
            this.message = message;
            this.packageName = packageName;
            this.expiryDate = expiryDate;
            this.status = status;
            this.timeLeft = timeLeft;
            this.hwid = hwid;
        }
    }

    public interface AuthCallback {
        void onSuccess(LoginResult result);
        void onFailure(String error);
    }

    public interface InitCallback {
        void onSuccess();
        void onFailure(String error);
    }

    public interface PackageValidationCallback {
        void onValidPackage(String packageName);
        void onInvalidPackage(String packageName);
        void onNoPackage();
    }

    public static String getDeviceId(Context context) {
        try {
            String androidId = Settings.Secure.getString(context.getContentResolver(), Settings.Secure.ANDROID_ID);
            return androidId != null ? androidId : "";
        } catch (Exception e) {
            return e.getMessage();
        }
    }

    public static String getProcessorId() {
        try {
            return Build.HARDWARE + "_" + Build.BOARD;
        } catch (Exception e) {
            return e.getMessage();
        }
    }

    private static String base64UrlEncode(byte[] input) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            return Base64.getUrlEncoder().withoutPadding().encodeToString(input);
        } else {
            return android.util.Base64.encodeToString(input,
                    android.util.Base64.URL_SAFE | android.util.Base64.NO_PADDING | android.util.Base64.NO_WRAP);
        }
    }

    private static String base64UrlEncode(String input) {
        return base64UrlEncode(input.getBytes(StandardCharsets.UTF_8));
    }

    private static String hmacSha256(String data, String key) {
        try {
            Mac mac = Mac.getInstance("HmacSHA256");
            SecretKeySpec secretKeySpec = new SecretKeySpec(key.getBytes(StandardCharsets.UTF_8), "HmacSHA256");
            mac.init(secretKeySpec);
            byte[] hash = mac.doFinal(data.getBytes(StandardCharsets.UTF_8));
            return base64UrlEncode(hash);
        } catch (Exception e) {
            return e.getMessage();
        }
    }

    public static String generateJwt(JSONObject payload, String secret) {
        try {
            JSONObject header = new JSONObject();
            header.put("alg", "HS256");
            header.put("typ", "JWT");
            String headerEncoded = base64UrlEncode(header.toString());
            String payloadEncoded = base64UrlEncode(payload.toString());
            String signature = hmacSha256(headerEncoded + "." + payloadEncoded, secret);
            String jwt = headerEncoded + "." + payloadEncoded + "." + signature;
            return jwt;
        } catch (Exception e) {
            return e.getMessage();
        }
    }

    public static void initAlternative(String appId, String secretKey, String version, InitCallback callback) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N) {
            CompletableFuture.runAsync(() -> {
                try {
                    URL url = new URL(VALIDATE_URL);
                    HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                    connection.setRequestMethod("POST");
                    connection.setConnectTimeout(30000);
                    connection.setReadTimeout(30000);
                    connection.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");
                    connection.setRequestProperty("Accept", "application/json");
                    connection.setDoOutput(true);

                    String postData = String.format("app_id=%s&secret_key=%s&version=%s&mode=init",
                            URLEncoder.encode(appId, "UTF-8"),
                            URLEncoder.encode(secretKey, "UTF-8"),
                            URLEncoder.encode(version, "UTF-8"));

                    try (OutputStream os = connection.getOutputStream()) {
                        os.write(postData.getBytes(StandardCharsets.UTF_8));
                        os.flush();
                    }

                    int responseCode = connection.getResponseCode();
                    String responseContent = readResponse(connection);


                    if (responseCode == 200 && !responseContent.trim().startsWith("<")) {
                        JSONObject jsonResponse = new JSONObject(responseContent);
                        String status = jsonResponse.optString("status", "unknown");

                        if ("success".equals(status) && jsonResponse.has("init_token")) {
                            initToken = jsonResponse.getString("init_token");
                            callback.onSuccess();
                            return;
                        }
                    }

                    initOriginal(appId, secretKey, version, callback);

                } catch (Exception e) {
                    initOriginal(appId, secretKey, version, callback);
                }
            });
        } else {
            callback.onFailure("Android version not supported (requires API 24+)");
        }
    }

    // Updated original init method with improved JWT handling
    private static void initOriginal(String appId, String secretKey, String version, InitCallback callback) {
        try {

            JSONObject payload = new JSONObject();
            payload.put("app_id", appId);
            payload.put("secret_key", secretKey);
            payload.put("version", version);
            payload.put("timestamp", System.currentTimeMillis() / 1000); // Add timestamp for token freshness

            String jwtToken = generateJwt(payload, SECRET_KEY);
            if (jwtToken.isEmpty()) {
                callback.onFailure("Failed to generate JWT token");
                return;
            }

            String fullUrl = VALIDATE_URL + "?token=" + jwtToken + "&mode=init";

            URL url = new URL(fullUrl);
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("GET");
            connection.setConnectTimeout(30000);
            connection.setReadTimeout(30000);
            connection.setRequestProperty("Accept", "application/json");
            connection.setRequestProperty("User-Agent", "Android-AuthHelper/2.0");

            int responseCode = connection.getResponseCode();
            String responseContent = readResponse(connection);

            if (responseCode != 200) {
                callback.onFailure("HTTP Error " + responseCode + ": " + responseContent);
                return;
            }

            if (responseContent == null || responseContent.trim().isEmpty()) {
                callback.onFailure("Empty response from server");
                return;
            }

            if (responseContent.trim().startsWith("<")) {
                callback.onFailure("Server returned Error");
                return;
            }

            JSONObject jsonResponse = new JSONObject(responseContent.trim());
            String status = jsonResponse.optString("status", "unknown");
            String message = jsonResponse.optString("message", "No message");

            if (!"success".equals(status)) {
                callback.onFailure(message);
                return;
            }

            if (jsonResponse.has("init_token")) {
                initToken = jsonResponse.getString("init_token");
                callback.onSuccess();
            } else {
                callback.onFailure("Init token not found in server response");
            }

        } catch (Exception e) {
            callback.onFailure(e.getMessage());
        }
    }

    // Main init method - tries alternative first, then original
    public static void init(String appId, String secretKey, String version, InitCallback callback) {
        initToken = null;
        initAlternative(appId, secretKey, version, callback);
    }

    public static void login(Context context, String appId, String secretKey, String username,
                             String password, String version, AuthCallback callback) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N) {
            if (initToken != null && !initToken.isEmpty()) {
                performLogin(context, appId, secretKey, username, password, version, callback);
            } else {
                init(appId, secretKey, version, new InitCallback() {
                    @Override
                    public void onSuccess() {
                        performLogin(context, appId, secretKey, username, password, version, callback);
                    }

                    @Override
                    public void onFailure(String error) {
                        callback.onFailure(error);
                    }
                });
            }
        } else {
            callback.onFailure("Android version not supported");
        }
    }

    private static void performLogin(Context context, String appId, String secretKey, String username,
                                     String password, String version, AuthCallback callback) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N) {
            CompletableFuture.runAsync(() -> {
                try {
                    String deviceId = getDeviceId(context);
                    String processorId = getProcessorId();

                    JSONObject payload = new JSONObject();
                    payload.put("app_id", appId);
                    payload.put("secret_key", secretKey);
                    payload.put("username", username);
                    payload.put("password", password);
                    payload.put("version", version);
                    payload.put("hwid", deviceId);
                    payload.put("processor_id", processorId);
                    payload.put("init_token", initToken);

                    String jwtToken = generateJwt(payload, SECRET_KEY);
                    if (jwtToken.isEmpty()) {
                        callback.onFailure("Failed to generate login");
                        return;
                    }

                    URL url = new URL(VALIDATE_URL + "?token=" + jwtToken);
                    HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                    connection.setRequestMethod("GET");
                    connection.setConnectTimeout(30000);
                    connection.setReadTimeout(30000);
                    connection.setRequestProperty("Accept", "application/json");

                    int responseCode = connection.getResponseCode();
                    String responseContent = readResponse(connection);

                    if (responseCode != 200 || responseContent.trim().startsWith("<")) {
                        callback.onFailure("Server error or invalid response format");
                        return;
                    }

                    JSONObject jsonResponse = new JSONObject(responseContent);
                    String message = jsonResponse.getString("message");
                    String status = jsonResponse.getString("status");

                    if ("success".equals(status)) {
                        final String finalMsg = message;
                        final String initialUsername = username;

                        CompletableFuture.runAsync(() -> {
                            try {
                                String statusUrlStr = "https://terminalx999.com/api/key_status.php?key=" + java.net.URLEncoder.encode(initialUsername, "UTF-8");
                                java.net.URL statusUrl = new java.net.URL(statusUrlStr);
                                java.net.HttpURLConnection statusConn = (java.net.HttpURLConnection) statusUrl.openConnection();
                                statusConn.setRequestMethod("GET");
                                statusConn.setConnectTimeout(8000);
                                statusConn.setReadTimeout(8000);

                                String statusResp = readResponse(statusConn);
                                if (!statusResp.isEmpty() && !statusResp.trim().startsWith("<")) {
                                    JSONObject sJson = new JSONObject(statusResp);
                                    if ("success".equals(sJson.optString("status"))) {
                                        JSONObject kd = sJson.getJSONObject("key");
                                        LoginResult enriched = new LoginResult(true, finalMsg,
                                                kd.optString("package", "AIMCOVER"),
                                                kd.optString("expiry_date", ""),
                                                kd.optString("status", "Active"),
                                                kd.optString("time_left", ""),
                                                kd.optString("hwid", ""));
                                        callback.onSuccess(enriched);
                                        return;
                                    }
                                }
                            } catch (Exception ignored) {}
                            callback.onSuccess(new LoginResult(true, finalMsg, "AIMCOVER", "", "Active", "", ""));
                        });
                        return;
                    } else {
                        callback.onFailure(message);
                    }

                } catch (Exception e) {
                    callback.onFailure(e.getMessage());
                }
            });
        }
    }

    private static String readResponse(HttpURLConnection connection) throws IOException {
        BufferedReader reader = null;
        try {
            InputStream inputStream = connection.getResponseCode() >= 400 ?
                    connection.getErrorStream() : connection.getInputStream();

            if (inputStream == null) return "";

            reader = new BufferedReader(new InputStreamReader(inputStream, StandardCharsets.UTF_8));
            StringBuilder response = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                response.append(line);
            }
            return response.toString();
        } finally {
            if (reader != null) {
                try {
                    reader.close();
                } catch (IOException e) {
                    // Ignore
                }
            }
        }
    }

    public static void clearSession() {
        initToken = null;
    }

    public static void validatePackage(String userPackage, String[] allowedPackages, PackageValidationCallback callback) {
        if (userPackage == null || userPackage.isEmpty()) {
            callback.onNoPackage();
            return;
        }

        for (String allowedPackage : allowedPackages) {
            if (userPackage.equalsIgnoreCase(allowedPackage)) {
                callback.onValidPackage(userPackage);
                return;
            }
        }

        callback.onInvalidPackage(userPackage);
    }

    public static boolean isPackageValid(String userPackage, String requiredPackage) {
        if (userPackage == null || userPackage.isEmpty()) {
            return false;
        }
        return userPackage.equalsIgnoreCase(requiredPackage);
    }

    public static void fetchUserExpiry(Context context, String appId, String secretKey, String username,
                                       String version, final java.util.function.Consumer<String> callback) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N) {
            CompletableFuture.runAsync(() -> {
                try {
                    String deviceId = getDeviceId(context);
                    String processorId = getProcessorId();

                    JSONObject payload = new JSONObject();
                    payload.put("app_id", appId);
                    payload.put("secret_key", secretKey);
                    payload.put("username", username);
                    payload.put("version", version);
                    payload.put("hwid", deviceId);
                    payload.put("processor_id", processorId);
                    payload.put("init_token", initToken);
                    payload.put("mode", "get_user_info");

                    String jwtToken = generateJwt(payload, SECRET_KEY);
                    if (jwtToken.isEmpty()) {
                        if (callback != null) callback.accept("");
                        return;
                    }

                    URL url = new URL(VALIDATE_URL + "?token=" + jwtToken + "&mode=get_user_info");
                    HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                    connection.setRequestMethod("GET");
                    connection.setConnectTimeout(15000);
                    connection.setReadTimeout(15000);
                    connection.setRequestProperty("Accept", "application/json");

                    int responseCode = connection.getResponseCode();
                    String responseContent = readResponse(connection);

                    if (responseCode == 200 && !responseContent.trim().startsWith("<")) {
                        try {
                            JSONObject jsonResponse = new JSONObject(responseContent);
                            String expiryDate = "";

                            // Try multiple possible locations
                            if (jsonResponse.has("expiry_date")) {
                                expiryDate = jsonResponse.getString("expiry_date");
                            } else if (jsonResponse.has("expiry")) {
                                expiryDate = jsonResponse.getString("expiry");
                            } else if (jsonResponse.has("user_data")) {
                                JSONObject userData = jsonResponse.getJSONObject("user_data");
                                if (userData.has("expiry_date")) {
                                    expiryDate = userData.getString("expiry_date");
                                } else if (userData.has("expiry")) {
                                    expiryDate = userData.getString("expiry");
                                }
                            } else if (jsonResponse.has("info")) {
                                try {
                                    JSONObject info = jsonResponse.getJSONObject("info");
                                    if (info.has("subscriptions")) {
                                        org.json.JSONArray subArray = info.getJSONArray("subscriptions");
                                        if (subArray.length() > 0) {
                                            org.json.JSONObject subObject = subArray.getJSONObject(0);
                                            if (subObject.has("expiry")) {
                                                expiryDate = subObject.getString("expiry");
                                            } else if (subObject.has("expiry_date")) {
                                                expiryDate = subObject.getString("expiry_date");
                                            }
                                        }
                                    }
                                } catch (Exception e) {
                                    // Ignore
                                }
                            }

                            if (callback != null) callback.accept(expiryDate);
                        } catch (Exception e) {
                            if (callback != null) callback.accept("");
                        }
                    } else {
                        if (callback != null) callback.accept("");
                    }
                } catch (Exception e) {
                    if (callback != null) callback.accept("");
                }
            });
        } else {
            if (callback != null) callback.accept("");
        }
    }

    public static void loginWithPackageValidation(Context context, String appId, String secretKey,
                                                  String username, String password, String version,
                                                  String[] allowedPackages, AuthCallback callback) {
        login(context, appId, secretKey, username, password, version, new AuthCallback() {
            @Override
            public void onSuccess(LoginResult result) {
                validatePackage(result.packageName, allowedPackages, new PackageValidationCallback() {
                    @Override
                    public void onValidPackage(String packageName) {
                        callback.onSuccess(result);
                    }

                    @Override
                    public void onInvalidPackage(String packageName) {
                        callback.onFailure("Access denied. Your package '" + packageName + "' is not authorized.");
                    }

                    @Override
                    public void onNoPackage() {
                        callback.onFailure("No package assigned to your account. Contact administrator.");
                    }
                });
            }

            @Override
            public void onFailure(String error) {
                callback.onFailure(error);
            }
        });
    }
}
