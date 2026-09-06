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

    private final String appName = "Lusquen Aimkill";
    private final String ownerId = "eb3d08ed5e";
    private final String secret = "9dafb080c0b6107dbc6157703819357340592733aab80b7d2bc3147d6a5943c8";
    private final String version = "1.0";
    private final String apiUrl = "https://phxcorp.duckdns.org/KeyAuthZ/api/1.0/";

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

