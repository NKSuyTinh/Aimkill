package com.terminalx999;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.util.Log;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

public class IntegrityChecker {
    // STRICT MODE: Set these hashes after first build - any change will break app
    private static final String EXPECTED_SIGNATURE_HASH = ""; // APK signature hash
    private static final String EXPECTED_DEX_HASH = ""; // classes.dex hash
    private static final String EXPECTED_APK_HASH = ""; // Complete APK file hash
    private static final String EXPECTED_LIB_VED_HASH = ""; // libved.so hash
    private static final String EXPECTED_LIB_ADINEW_HASH = ""; // libadinew.so hash
    private static final long EXPECTED_APK_SIZE = 0; // APK file size in bytes
    /** Hash of har file inside APK (path|sha256). Android Studio se build -> run once -> logcat se copy karke yahan paste karo. */
    private static final String EXPECTED_APK_FILES_HASH = "";
    
    static {
        System.loadLibrary("TERMINALX_MENU");
    }
    
    // Native integrity check methods
    public static native boolean nativeCheckLibraryIntegrity();
    public static native boolean nativeCheckAllLibs(); // Check libved.so (libadinew.so injected later)
    public static native boolean nativeCheckAllLibsWithContext(Context context); // Check both libs with file path
    public static native boolean nativeVerifyLibVed(); // Verify libved.so (from libadinew.so)
    
    // App config verification - checks Client.cpp values against NativeProtections.cpp
    // If mismatch detected, app will be permanently corrupted (only fixable by uninstall)
    public static native boolean nativeVerifyAppConfigValues(Context context);
    public static native void nativeCheckCorruptedState(Context context); // Check if app is corrupted and crash if yes
    public static native void nativeCorruptApp(Context context); // Explicitly corrupt app (for security failures, etc.)
    
    /**
     * Check if app is corrupted (Java side check - shows message before crash)
     * Returns true if corrupted, false if not
     */
    public static boolean isAppCorrupted(Context context) {
        try {
            android.content.SharedPreferences prefs = context.getSharedPreferences("AppCorruptionState", Context.MODE_PRIVATE);
            boolean isCorrupted = prefs.getBoolean("is_corrupted", false);
            if (isCorrupted) {
                Log.e("IntegrityChecker", "App is corrupted - previous crack attempt detected");
            }
            return isCorrupted;
        } catch (Exception e) {
            Log.w("IntegrityChecker", "Failed to check corruption state: " + e.getMessage());
            return false; // On error, assume not corrupted
        }
    }
    
    /**
     * Verify APK signature
     */
    public static boolean verifySignature(Context context) {
        try {
            PackageManager pm = context.getPackageManager();
            PackageInfo packageInfo = pm.getPackageInfo(
                context.getPackageName(), 
                PackageManager.GET_SIGNATURES
            );
            
            if (packageInfo.signatures == null || packageInfo.signatures.length == 0) {
                return false;
            }
            
            Signature signature = packageInfo.signatures[0];
            String signatureHash = getSignatureHash(signature);
            
            // If expected hash is set, compare it
            if (!EXPECTED_SIGNATURE_HASH.isEmpty()) {
                return EXPECTED_SIGNATURE_HASH.equals(signatureHash);
            }
            
            // First run - just verify signature exists
            if (signatureHash != null && !signatureHash.isEmpty()) {
                Log.d("IntegrityChecker", "Signature Hash (first run): " + signatureHash);
                Log.d("IntegrityChecker", "Copy above hash to EXPECTED_SIGNATURE_HASH");
            }
            return signatureHash != null && !signatureHash.isEmpty();
            
        } catch (Exception e) {
            return false;
        }
    }
    
    /**
     * Get signature hash
     */
    private static String getSignatureHash(Signature signature) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] digest = md.digest(signature.toByteArray());
            return bytesToHex(digest);
        } catch (Exception e) {
            return null;
        }
    }
    
    /**
     * Verify DEX file integrity
     * Calculates hash of classes.dex from APK
     */
    public static boolean verifyDexIntegrity(Context context) {
        try {
            String apkPath = context.getApplicationInfo().sourceDir;
            if (apkPath == null) {
                Log.w("IntegrityChecker", "APK path is null");
                return true; // Allow on first run
            }
            
            File apkFile = new File(apkPath);
            if (!apkFile.exists()) {
                Log.w("IntegrityChecker", "APK file does not exist");
                return true; // Allow on first run
            }
            
            // Extract and calculate hash of classes.dex from APK
            String currentDexHash = calculateDexHashFromApk(apkFile);
            
            if (currentDexHash == null || currentDexHash.isEmpty()) {
                Log.w("IntegrityChecker", "DEX hash calculation failed");
                return true; // Allow on first run - hash calculation might fail
            }
            
            // If expected hash is set, compare it
            if (!EXPECTED_DEX_HASH.isEmpty()) {
                boolean isValid = EXPECTED_DEX_HASH.equals(currentDexHash);
                if (!isValid) {
                    Log.e("IntegrityChecker", "DEX hash mismatch! Expected: " + EXPECTED_DEX_HASH.substring(0, 16) + "... Got: " + currentDexHash.substring(0, 16) + "...");
                    return false; // Strict check - hash mismatch
                }
                return true;
            }
            
            // First run - hash calculated successfully
            Log.d("IntegrityChecker", "DEX Hash (first run): " + currentDexHash);
            Log.d("IntegrityChecker", "Copy above hash to EXPECTED_DEX_HASH in IntegrityChecker.java");
            return true;
            
        } catch (Exception e) {
            Log.w("IntegrityChecker", "DEX integrity check exception: " + e.getMessage());
            return true; // Allow on exception - don't block app
        }
    }
    
    /**
     * Calculate hash of classes.dex from APK file
     * APK is a ZIP file, so we extract classes.dex and hash it
     * Uses ZipInputStream for better compatibility
     */
    private static String calculateDexHashFromApk(File apkFile) {
        java.util.zip.ZipInputStream zis = null;
        try {
            FileInputStream fis = new FileInputStream(apkFile);
            zis = new java.util.zip.ZipInputStream(fis);
            
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            java.util.zip.ZipEntry entry;
            
            // Find and hash classes.dex (or classes2.dex, classes3.dex for multidex)
            while ((entry = zis.getNextEntry()) != null) {
                String entryName = entry.getName();
                if (entryName.equals("classes.dex") || 
                    (entryName.startsWith("classes") && entryName.endsWith(".dex"))) {
                    
                    byte[] buffer = new byte[8192];
                    int bytesRead;
                    while ((bytesRead = zis.read(buffer)) != -1) {
                        md.update(buffer, 0, bytesRead);
                    }
                    
                    byte[] digest = md.digest();
                    zis.closeEntry();
                    return bytesToHex(digest);
                }
                zis.closeEntry();
            }
            
            // If no DEX found, fallback to APK hash
            return calculateFileHash(apkFile);
            
        } catch (Exception e) {
            // Fallback: Calculate hash of entire APK
            try {
                return calculateFileHash(apkFile);
            } catch (Exception ex) {
                return null;
            }
        } finally {
            try {
                if (zis != null) {
                    zis.close();
                }
            } catch (IOException e) {
                // Ignore
            }
        }
    }
    
    /**
     * Calculate file hash (SHA-256)
     */
    private static String calculateFileHash(File file) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            FileInputStream fis = new FileInputStream(file);
            byte[] buffer = new byte[8192];
            int bytesRead;
            
            while ((bytesRead = fis.read(buffer)) != -1) {
                md.update(buffer, 0, bytesRead);
            }
            
            fis.close();
            byte[] digest = md.digest();
            return bytesToHex(digest);
            
        } catch (Exception e) {
            return null;
        }
    }
    
    /**
     * Compute a single hash that changes if ANY file inside the APK (ZIP) changes.
     * Process: open APK as ZIP, sort entry names, for each file add "path|sha256(content)\n",
     * then return SHA-256 of that full string. One character change in any file → different hash.
     */
    private static String calculateApkAllFilesHash(File apkFile) {
        ZipFile zip = null;
        try {
            zip = new ZipFile(apkFile, ZipFile.OPEN_READ);
            ArrayList<String> names = new ArrayList<>();
            Enumeration<? extends ZipEntry> entries = zip.entries();
            while (entries.hasMoreElements()) {
                ZipEntry e = entries.nextElement();
                names.add(e.getName());
            }
            Collections.sort(names);
            
            MessageDigest fileDigest = MessageDigest.getInstance("SHA-256");
            StringBuilder combined = new StringBuilder();
            byte[] buf = new byte[8192];
            
            for (String name : names) {
                ZipEntry entry = zip.getEntry(name);
                if (entry == null || entry.isDirectory()) continue;
                InputStream is = zip.getInputStream(entry);
                if (is == null) continue;
                fileDigest.reset();
                int n;
                while ((n = is.read(buf)) != -1) {
                    fileDigest.update(buf, 0, n);
                }
                is.close();
                combined.append(name).append("|").append(bytesToHex(fileDigest.digest())).append("\n");
            }
            
            MessageDigest master = MessageDigest.getInstance("SHA-256");
            byte[] combinedBytes = combined.toString().getBytes(StandardCharsets.UTF_8);
            return bytesToHex(master.digest(combinedBytes));
        } catch (Exception e) {
            Log.w("IntegrityChecker", "APK all-files hash failed: " + e.getMessage());
            return null;
        } finally {
            if (zip != null) {
                try { zip.close(); } catch (IOException ignored) {}
            }
        }
    }
    
    /**
     * Verify that no file inside the APK was modified. Uses hash of every ZIP entry's content.
     * If EXPECTED_APK_FILES_HASH is set, mismatch → false (integrity failed).
     */
    public static boolean verifyApkAllFilesHash(Context context) {
        try {
            String apkPath = context.getApplicationInfo().sourceDir;
            if (apkPath == null) {
                Log.e("IntegrityChecker", "APK path is null - FAIL");
                return false;
            }
            File apkFile = new File(apkPath);
            if (!apkFile.exists()) {
                Log.e("IntegrityChecker", "APK file does not exist - FAIL");
                return false;
            }
            String current = calculateApkAllFilesHash(apkFile);
            if (current == null || current.isEmpty()) {
                Log.e("IntegrityChecker", "APK all-files hash calculation failed - FAIL");
                return false;
            }
            if (!EXPECTED_APK_FILES_HASH.isEmpty()) {
                boolean ok = EXPECTED_APK_FILES_HASH.equals(current);
                if (!ok) {
                    Log.e("IntegrityChecker", "APK FILES MODIFIED! (per-file hash mismatch)");
                    Log.e("IntegrityChecker", "Expected: " + (EXPECTED_APK_FILES_HASH.length() > 32 ? EXPECTED_APK_FILES_HASH.substring(0, 32) + "..." : EXPECTED_APK_FILES_HASH));
                    Log.e("IntegrityChecker", "Got:      " + (current.length() > 32 ? current.substring(0, 32) + "..." : current));
                    return false;
                }
                return true;
            }
            Log.d("IntegrityChecker", "=== FIRST RUN - PER-FILE APK HASH ===");
            Log.d("IntegrityChecker", "EXPECTED_APK_FILES_HASH = \"" + current + "\"");
            Log.d("IntegrityChecker", "Copy above into IntegrityChecker.java, rebuild from Android Studio.");
            return true;
        } catch (Exception e) {
            Log.e("IntegrityChecker", "APK all-files check exception: " + e.getMessage());
            return false;
        }
    }
    
    /**
     * Check if APK is in expected location
     * Made lenient - allows multiple valid paths
     */
    public static boolean checkApkLocation(Context context) {
        try {
            String actualPath = context.getApplicationInfo().sourceDir;
            if (actualPath == null) return false;
            
            // Allow multiple valid installation paths
            String[] validPaths = {
                "/data/app/",
                "/data/app-private/",
                "/mnt/asec/",
                "/mnt/obb/"
            };
            
            boolean isValidPath = false;
            for (String validPath : validPaths) {
                if (actualPath.startsWith(validPath)) {
                    isValidPath = true;
                    break;
                }
            }
            
            // If path is valid, check file exists
            if (isValidPath) {
                File apkFile = new File(actualPath);
                return apkFile.exists();
            }
            
            // For debug builds or other paths, just check file exists
            File apkFile = new File(actualPath);
            return apkFile.exists();
            
        } catch (Exception e) {
            // On error, allow (don't block app)
            return true;
        }
    }
    
    /**
     * Verify complete APK file hash (ALWAYS STRICT - any change detected immediately)
     */
    public static boolean verifyApkHash(Context context) {
        try {
            String apkPath = context.getApplicationInfo().sourceDir;
            if (apkPath == null) {
                Log.e("IntegrityChecker", "APK path is null - FAIL");
                return false; // STRICT: Fail if path null
            }
            
            File apkFile = new File(apkPath);
            if (!apkFile.exists()) {
                Log.e("IntegrityChecker", "APK file does not exist - FAIL");
                return false; // STRICT: Fail if file missing
            }
            
            // Check file size first (fast check) - ALWAYS check if size is set
            if (EXPECTED_APK_SIZE > 0) {
                long currentSize = apkFile.length();
                if (currentSize != EXPECTED_APK_SIZE) {
                    Log.e("IntegrityChecker", "APK size mismatch! Expected: " + EXPECTED_APK_SIZE + " Got: " + currentSize);
                    return false; // STRICT: Size mismatch = fail
                }
            }
            
            // Calculate complete APK hash
            String currentHash = calculateFileHash(apkFile);
            if (currentHash == null || currentHash.isEmpty()) {
                Log.e("IntegrityChecker", "APK hash calculation failed - FAIL");
                return false; // STRICT: Fail if hash can't be calculated
            }
            
            // If expected hash is set, compare STRICTLY
            if (!EXPECTED_APK_HASH.isEmpty()) {
                boolean isValid = EXPECTED_APK_HASH.equals(currentHash);
                if (!isValid) {
                    Log.e("IntegrityChecker", "APK HASH MISMATCH! File modified!");
                    Log.e("IntegrityChecker", "Expected: " + EXPECTED_APK_HASH.substring(0, Math.min(32, EXPECTED_APK_HASH.length())) + "...");
                    Log.e("IntegrityChecker", "Got:      " + currentHash.substring(0, Math.min(32, currentHash.length())) + "...");
                    return false; // STRICT: Always fail on mismatch
                }
                return true;
            }
            
            // First run - log hash for user to copy
            Log.d("IntegrityChecker", "=== FIRST RUN - COPY THESE HASHES ===");
            Log.d("IntegrityChecker", "APK Hash: " + currentHash);
            Log.d("IntegrityChecker", "APK Size: " + apkFile.length());
            Log.d("IntegrityChecker", "Copy above to IntegrityChecker.java constants");
            Log.d("IntegrityChecker", "=====================================");
            return true; // First run - allow (user will set hashes and rebuild)
            
        } catch (Exception e) {
            Log.e("IntegrityChecker", "APK hash check exception: " + e.getMessage());
            return false; // STRICT: Fail on exception
        }
    }
    
    /**
     * Verify native library hash (STRICT)
     */
    public static boolean verifyNativeLibraryHash(Context context, String libName, String expectedHash) {
        if (expectedHash == null || expectedHash.isEmpty()) return true;
        
        try {
            String libPath = context.getApplicationInfo().nativeLibraryDir + "/" + libName;
            File libFile = new File(libPath);
            if (!libFile.exists()) {
                Log.e("IntegrityChecker", "Library not found: " + libName);
                return false;
            }
            
            // Calculate hash
            String currentHash = calculateFileHash(libFile);
            if (currentHash == null || currentHash.isEmpty()) {
                return false;
            }
            
            boolean isValid = expectedHash.equals(currentHash);
            if (!isValid) {
                Log.e("IntegrityChecker", "Library hash mismatch: " + libName);
            }
            return isValid;
            
        } catch (Exception e) {
            return false;
        }
    }
    
    /**
     * STRICT integrity check - any change will break app.
     * NOTE: To actually lock the APK, fill EXPECTED_* constants above from your first release build.
     */
    public static boolean performIntegrityCheck(Context context) {
        // 0. Native lib presence + basic check (libved.so + libadinew.so)
        if (!nativeCheckAllLibsWithContext(context)) {
            Log.e("IntegrityChecker", "NATIVE LIB CHECK FAILED - libved.so or libadinew.so missing/invalid");
            return false;
        }

        // 1. Per-file APK hash (every file inside APK)
        if (!verifyApkAllFilesHash(context)) {
            Log.e("IntegrityChecker", "APK MODIFIED (per-file hash) - Integrity check failed!");
            return false;
        }

        // 2. Whole-APK hash / size (if EXPECTED_APK_HASH / EXPECTED_APK_SIZE set)
        if (!verifyApkHash(context)) {
            Log.e("IntegrityChecker", "APK FILE MODIFIED - Integrity check failed!");
            return false;
        }

        // 3. Signature check (STRICT if EXPECTED_SIGNATURE_HASH set)
        if (!verifySignature(context)) {
            Log.e("IntegrityChecker", "SIGNATURE VERIFICATION FAILED");
            return false;
        }

        // 4. DEX hash check (STRICT if EXPECTED_DEX_HASH set)
        if (!verifyDexIntegrity(context)) {
            Log.e("IntegrityChecker", "DEX FILE MODIFIED - Integrity check failed!");
            return false;
        }

        // 5. Native library hash checks (STRICT if EXPECTED_LIB_* set)
        if (!EXPECTED_LIB_VED_HASH.isEmpty()) {
            if (!verifyNativeLibraryHash(context, "libved.so", EXPECTED_LIB_VED_HASH)) {
                Log.e("IntegrityChecker", "NATIVE LIBRARY MODIFIED: libved.so");
                return false;
            }
        }
        if (!EXPECTED_LIB_ADINEW_HASH.isEmpty()) {
            if (!verifyNativeLibraryHash(context, "libadinew.so", EXPECTED_LIB_ADINEW_HASH)) {
                Log.e("IntegrityChecker", "NATIVE LIBRARY MODIFIED: libadinew.so");
                return false;
            }
        }

        // 6. APK location check (must be expected path)
        if (!checkApkLocation(context)) {
            Log.e("IntegrityChecker", "APK LOCATION CHECK FAILED");
            return false;
        }

        return true;
    }
    
    /**
     * Convert bytes to hex string
     */
    private static String bytesToHex(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }
}

