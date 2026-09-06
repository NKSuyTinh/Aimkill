package com.terminalx999;

import android.app.Activity;

import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

public class restart {
    static {
        System.loadLibrary("TERMINALX_MENU");
    }
    
    public static native void disableAll();
    public static native String getNativeString(int key);

    private final Activity context;

    private final String appName = getNativeString(2);
    private final String ownerId = getNativeString(1);
    private final String version = getNativeString(3);
    private final String apiUrl = getNativeString(0);

    private boolean hasRestarted = false;

    public restart(Activity context) {
        this.context = context;
    }

    public void startLoop() {
        new Thread(() -> {
            while (!hasRestarted) {
                try {
                    String serverVersion = fetchServerVersion();
                    if (serverVersion != null && !serverVersion.equals(version)) {
                        try {
                            disableAll();
                        } catch (UnsatisfiedLinkError e) {
                            // Native function not available, continue anyway
                        }
                        hasRestarted = true;
                        fullRestartWithSu(); // 🔥 Root-level full restart
                        break;
                    }
                    Thread.sleep(3000);
                } catch (Exception ignored) {}
            }
        }).start();
    }

    private String fetchServerVersion() {
        try {
            String params = "type=init&name=" + appName + "&ownerid=" + ownerId + "&ver=" + version;
            URL url = new URL(apiUrl);
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setRequestMethod("POST");
            conn.setDoOutput(true);
            conn.getOutputStream().write(params.getBytes("UTF-8"));

            BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));
            StringBuilder response = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) response.append(line);
            reader.close();

            JSONObject json = new JSONObject(response.toString());
            if (!json.getBoolean("success")) {
                return json.getString("message").replace("Invalid version. Expected ", "").trim();
            }
        } catch (Exception ignored) {}
        return version;
    }

    private void fullRestartWithSu() {
        try {
            String packageName = context.getPackageName();
            String restartCommand = "am force-stop " + packageName + " ; " +
                    "sleep 1 ; " +
                    "monkey -p " + packageName + " -c android.intent.category.LAUNCHER 1";

            // Detect which su path is valid
            String suPath = "/system/xbin/su";
            String su1Path = "/system/xbin/WindowSecurity";
            String suToUse;

            if (new java.io.File(su1Path).exists()) {
                suToUse = su1Path;
            } else {
                suToUse = suPath;
            }

            Process process = Runtime.getRuntime().exec(suToUse);
            DataOutputStream os = new DataOutputStream(process.getOutputStream());
            os.writeBytes(restartCommand + "\n");
            os.writeBytes("exit\n");
            os.flush();
            os.close();

            process.waitFor();
        } catch (Exception e) {
            e.printStackTrace(); // Optional logging
        }
    }

}

