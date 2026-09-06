package com.terminalx999;

import android.app.ActionBar;
import android.app.Activity;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.Typeface;
import android.graphics.drawable.ColorDrawable;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.provider.Settings;
import android.view.Gravity;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.TextView;

public class MainActivity extends Activity {
    static {
        try {
            System.loadLibrary("TERMINALX_MENU");
        } catch (UnsatisfiedLinkError e) {
            android.util.Log.e("MainActivity", "Lib load failed: " + e.getMessage());
        }
    }

    private static final int REQUEST_OVERLAY_PERMISSION = 1234;
    private LinearLayout splashLayout;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        ActionBar actionBar = getActionBar();
        if (actionBar != null) actionBar.hide();
        getWindow().setBackgroundDrawable(new ColorDrawable(Color.parseColor("#0A0A0A")));

        showSplash();
        new Handler().postDelayed(this::checkOverlayAndStartLogin, 1200);
    }

    private void checkOverlayAndStartLogin() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (!Settings.canDrawOverlays(this)) {
                Intent intent = new Intent(Settings.ACTION_MANAGE_OVERLAY_PERMISSION,
                        Uri.parse("package:" + getPackageName()));
                startActivityForResult(intent, REQUEST_OVERLAY_PERMISSION);
            } else {
                startLoginUI();
            }
        } else {
            startLoginUI();
        }
    }

    private void startLoginUI() {
        runCloseAnimationThen(() -> {
            new Handler().postDelayed(() -> {
                try {
                    new Login(MainActivity.this);
                } catch (Exception e) {
                    android.util.Log.e("MainActivity", "Login Error: " + e.getMessage());
                }
            }, 100);
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == REQUEST_OVERLAY_PERMISSION) {
            startLoginUI();
        }
    }

    private void showSplash() {
        FrameLayout rootFrame = new FrameLayout(this);
        rootFrame.setBackgroundColor(Color.parseColor("#0A0A0E"));

        ParticlesView particles = new ParticlesView(this);
        rootFrame.addView(particles, new FrameLayout.LayoutParams(
                android.view.ViewGroup.LayoutParams.MATCH_PARENT,
                android.view.ViewGroup.LayoutParams.MATCH_PARENT));

        splashLayout = new LinearLayout(this);
        splashLayout.setOrientation(LinearLayout.VERTICAL);
        splashLayout.setGravity(Gravity.CENTER);
        splashLayout.setBackgroundColor(Color.TRANSPARENT);

        // Circular Logo with glowing ring
        android.widget.ImageView splashLogo = new android.widget.ImageView(this);
        LinearLayout.LayoutParams logoLp = new LinearLayout.LayoutParams(100, 100);
        logoLp.bottomMargin = 16;
        splashLogo.setLayoutParams(logoLp);
        android.graphics.Bitmap bm = Utils.getBannerBitmap(this);
        if (bm != null) {
            splashLogo.setImageBitmap(bm);
        } else {
            try { splashLogo.setImageDrawable(getPackageManager().getApplicationIcon(getPackageName())); }
            catch (Exception e) { splashLogo.setImageResource(android.R.drawable.sym_def_app_icon); }
        }
        android.graphics.drawable.GradientDrawable logoBg = new android.graphics.drawable.GradientDrawable();
        logoBg.setShape(android.graphics.drawable.GradientDrawable.OVAL);
        logoBg.setColor(Color.parseColor("#151520"));
        logoBg.setStroke(3, Color.parseColor("#FF1A3C"));
        splashLogo.setBackground(logoBg);
        splashLogo.setPadding(6, 6, 6, 6);

        LinearLayout titleRow = new LinearLayout(this);
        titleRow.setGravity(Gravity.CENTER);
        titleRow.setOrientation(LinearLayout.HORIZONTAL);

        Typeface kcFont = null;
        try { kcFont = Typeface.createFromAsset(getAssets(), "kcfonts/ethnocentric.ttf"); } catch (Exception ignored) {}

        TextView partRed = new TextView(this);
        partRed.setText("ONYX ");
        partRed.setTextColor(Color.parseColor("#FF1A3C"));
        partRed.setTextSize(20);
        partRed.setTypeface(kcFont != null ? kcFont : Typeface.DEFAULT_BOLD, Typeface.BOLD);

        TextView partWhite = new TextView(this);
        partWhite.setText("VIP");
        partWhite.setTextColor(Color.WHITE);
        partWhite.setTextSize(20);
        partWhite.setTypeface(kcFont != null ? kcFont : Typeface.DEFAULT_BOLD, Typeface.BOLD);

        titleRow.addView(partRed);
        titleRow.addView(partWhite);

        View accentLine = new View(this);
        LinearLayout.LayoutParams lineParams = new LinearLayout.LayoutParams(160, 4);
        lineParams.setMargins(0, 12, 0, 0);
        accentLine.setLayoutParams(lineParams);
        android.graphics.drawable.GradientDrawable lineGrad = new android.graphics.drawable.GradientDrawable(
                android.graphics.drawable.GradientDrawable.Orientation.LEFT_RIGHT,
                new int[]{Color.parseColor("#FF1A3C"), Color.parseColor("#FF6600")});
        lineGrad.setCornerRadius(2);
        accentLine.setBackground(lineGrad);

        splashLayout.addView(splashLogo);
        splashLayout.addView(titleRow);
        splashLayout.addView(accentLine);

        rootFrame.addView(splashLayout, new FrameLayout.LayoutParams(
                android.view.ViewGroup.LayoutParams.MATCH_PARENT,
                android.view.ViewGroup.LayoutParams.MATCH_PARENT));

        setContentView(rootFrame);

        splashLogo.setScaleX(0f);
        splashLogo.setScaleY(0f);
        splashLogo.animate().scaleX(1f).scaleY(1f).setDuration(450).start();

        titleRow.setAlpha(0f);
        titleRow.setTranslationY(20);
        titleRow.animate().alpha(1f).translationY(0).setDuration(500).setStartDelay(150).start();

        accentLine.setScaleX(0f);
        accentLine.animate().scaleX(1f).setDuration(400).setStartDelay(350).start();
    }

    private void runCloseAnimationThen(Runnable onEnd) {
        if (splashLayout == null) {
            if (onEnd != null) onEnd.run();
            return;
        }
        splashLayout.animate()
                .alpha(0f)
                .scaleX(0.95f)
                .scaleY(0.95f)
                .setDuration(250)
                .withEndAction(onEnd)
                .start();
    }
}
