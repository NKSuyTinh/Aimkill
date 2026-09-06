package com.terminalx999;

import android.content.Context;
import org.json.JSONObject;

public class KeyAuth {
    private final KeyAuthZ keyAuthZ;

    public KeyAuth(String appname, String ownerid, String version, String url, Context context) {
        this(appname, ownerid, "9dafb080c0b6107dbc6157703819357340592733aab80b7d2bc3147d6a5943c8", version, url, context);
    }

    public KeyAuth(String appname, String ownerid, String secret, String version, String url, Context context) {
        this.keyAuthZ = new KeyAuthZ(appname, ownerid, secret, version, url, context);
    }

    public void init() throws Exception {
        keyAuthZ.init();
    }

    public JSONObject license(String key) throws Exception {
        KeyAuthZ.UserData data = keyAuthZ.license(key);
        JSONObject obj = new JSONObject();
        obj.put("success", true);
        obj.put("username", data.username);
        obj.put("hwid", data.hwid);
        obj.put("timeleft", data.timeLeft);
        return obj;
    }

    public KeyAuthZ getKeyAuthZ() {
        return keyAuthZ;
    }

    public String getSessionId() {
        return keyAuthZ.getSessionId();
    }
}
