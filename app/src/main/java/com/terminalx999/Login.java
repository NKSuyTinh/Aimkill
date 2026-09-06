package com.terminalx999;

import android.animation.AnimatorSet;
import android.animation.ObjectAnimator;
import android.animation.ValueAnimator;
import android.annotation.TargetApi;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.BlurMaskFilter;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.LinearGradient;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.RectF;
import android.graphics.Shader;
import android.graphics.Typeface;
import android.graphics.SweepGradient;
import android.graphics.drawable.GradientDrawable;
import android.os.Build;
import android.os.Handler;
import android.os.Looper;
import android.text.method.PasswordTransformationMethod;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

public class Login {

    private static final int PrimaryColor = 0xFFE53935;
    private static final int AccentColor = 0xFFFF6B6B;
    private static final int CardBgColor = 0xF00D0D0D;
    private static final int InputBgColor = 0xFF1A1A1A;

    private static String sLoginUsername = "";
    private static String sLoginPassword = "";
    public static String getStoredUsername() { return sLoginUsername; }
    public static String getStoredPassword() { return sLoginPassword; }

    private TextView logo;
    private TextView copyright;
    public void setLogoText(String value) {
        if (logo != null) { logo.setText(value); logo.setVisibility(View.VISIBLE); logo.invalidate(); }
    }
    public void setCopyrightText(String value) {
        if (copyright != null) copyright.setText(value);
    }

    private Context context;
    private Utils utils;
    private ImageString imageString;
    private Handler mainHandler;
    private EditText input_username;
    private String selectedTargetPackage = "com.dts.freefireth";
    private LinearLayout cardContainer;
    private int selectedInjectType = 0;

    private FrameLayout masterRoot;
    private ImageView splashLogo;
    private LinearLayout rootContainer;

    private static AuthHelper.LoginResult senniVerifyLicense(Context ctx, String key) {
        SenniAuth.VerifyResult res = SenniAuth.verify(ctx, key);
        return new AuthHelper.LoginResult(
                res.valid,
                res.message,
                "AIMCOVER",
                res.expiryFormatted,
                res.valid ? "Active" : "Inactive",
                "",
                res.hwid
        );
    }

    public static final String PREF_NAME = "LoginPrefs";
    public static final String LICENSE_KEY = "key";
    private static final String PREFS_NAME = "mvp_prefs";
    private static final String USERNAME_KEY = "username_key";

    public Login(Context ctx) {
        context = ctx;
        utils = new Utils(context);
        imageString = new ImageString();
        mainHandler = new Handler(Looper.getMainLooper());
        initUI();
    }

    private void initUI() {
        SharedPreferences preferences = context.getSharedPreferences(PREF_NAME, Context.MODE_PRIVATE);
        String savedKey = preferences.getString(LICENSE_KEY, "");

        masterRoot = new FrameLayout(context);
        masterRoot.setBackgroundColor(0xFF0A0A0A);

        rootContainer = new LinearLayout(context);
        rootContainer.setOrientation(LinearLayout.VERTICAL);
        FrameLayout.LayoutParams rootParams = new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        rootParams.gravity = Gravity.CENTER;
        rootContainer.setLayoutParams(rootParams);

        cardContainer = new LinearLayout(context);
        cardContainer.setOrientation(LinearLayout.VERTICAL);
        cardContainer.setGravity(Gravity.CENTER);

        initPremiumLoginUI(cardContainer, savedKey);

        rootContainer.addView(cardContainer);
        rootContainer.setAlpha(0f);
        rootContainer.setTranslationY(250f);
        masterRoot.addView(rootContainer);

        splashLogo = new ImageView(context);
        android.graphics.Bitmap splashBm = Utils.getBannerBitmap(context);
        if (splashBm != null) {
            splashLogo.setImageBitmap(splashBm);
        } else {
            try { splashLogo.setImageDrawable(context.getPackageManager().getApplicationIcon(context.getPackageName())); }
            catch (Exception e) { splashLogo.setImageResource(android.R.drawable.sym_def_app_icon); }
        }
        GradientDrawable splashBg = new GradientDrawable();
        splashBg.setShape(GradientDrawable.OVAL);
        splashBg.setColor(0xFF12121A);
        splashBg.setStroke(dp(3), PrimaryColor);
        splashLogo.setBackground(splashBg);
        splashLogo.setPadding(dp(8), dp(8), dp(8), dp(8));
        FrameLayout.LayoutParams logoParams = new FrameLayout.LayoutParams(dp(180), dp(180));
        logoParams.gravity = Gravity.CENTER;
        splashLogo.setLayoutParams(logoParams);
        masterRoot.addView(splashLogo);

        ((Activity) context).setContentView(masterRoot);

        startCinematicSequence();
    }

    private int dp(int d) {
        return (int) (d * context.getResources().getDisplayMetrics().density);
    }

    private void startCinematicSequence() {
        splashLogo.setScaleX(0f);
        splashLogo.setScaleY(0f);
        ObjectAnimator logoScaleX = ObjectAnimator.ofFloat(splashLogo, "scaleX", 0f, 1.3f);
        ObjectAnimator logoScaleY = ObjectAnimator.ofFloat(splashLogo, "scaleY", 0f, 1.3f);
        AnimatorSet logoAnim = new AnimatorSet();
        logoAnim.playTogether(logoScaleX, logoScaleY);
        logoAnim.setDuration(2000);
        logoAnim.setInterpolator(new android.view.animation.LinearInterpolator());
        logoAnim.start();

        new Handler(Looper.getMainLooper()).postDelayed(() -> {
            ObjectAnimator.ofFloat(splashLogo, "alpha", 1f, 0f).setDuration(500).start();

            new Handler(Looper.getMainLooper()).postDelayed(() -> {
                splashLogo.setVisibility(View.GONE);
            }, 500);

            new Handler(Looper.getMainLooper()).postDelayed(() -> {
                ObjectAnimator cardSlide = ObjectAnimator.ofFloat(rootContainer, "translationY", 250f, 0f);
                ObjectAnimator cardFade = ObjectAnimator.ofFloat(rootContainer, "alpha", 0f, 1f);
                AnimatorSet cardAnim = new AnimatorSet();
                cardAnim.playTogether(cardSlide, cardFade);
                cardAnim.setDuration(1000);
                cardAnim.start();
            }, 1500);

        }, 2000);
    }

    @TargetApi(Build.VERSION_CODES.M)
    private void initPremiumLoginUI(LinearLayout container_login, String savedKey) {
        container_login.setOrientation(LinearLayout.VERTICAL);
        container_login.setGravity(Gravity.CENTER);
        container_login.setBackgroundColor(Color.TRANSPARENT);

        LinearLayout bgContainer = new LinearLayout(context);
        bgContainer.setOrientation(LinearLayout.VERTICAL);
        bgContainer.setGravity(Gravity.CENTER);
        bgContainer.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));

        GradientDrawable cardBg = new GradientDrawable();
        cardBg.setColor(0x20111111);
        cardBg.setCornerRadius(dp(20));
        cardBg.setStroke(dp(1), 0x30FFFFFF);

        LinearLayout loginCard = new LinearLayout(context);
        loginCard.setOrientation(LinearLayout.VERTICAL);
        loginCard.setGravity(Gravity.CENTER_HORIZONTAL);
        loginCard.setBackground(cardBg);
        loginCard.setPadding(dp(24), dp(24), dp(24), dp(24));

        LinearLayout headerContainer = new LinearLayout(context);
        headerContainer.setOrientation(LinearLayout.HORIZONTAL);
        headerContainer.setGravity(Gravity.CENTER);
        LinearLayout.LayoutParams headerParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        headerParams.bottomMargin = dp(25);
        headerContainer.setLayoutParams(headerParams);

        ImageView logoImage = new ImageView(context);
        LinearLayout.LayoutParams headerLogoParams = new LinearLayout.LayoutParams(dp(52), dp(52));
        headerLogoParams.rightMargin = dp(12);
        logoImage.setLayoutParams(headerLogoParams);
        android.graphics.Bitmap loginLogoBm = Utils.getBannerBitmap(context);
        if (loginLogoBm != null) {
            logoImage.setImageBitmap(loginLogoBm);
        } else {
            try { logoImage.setImageDrawable(context.getPackageManager().getApplicationIcon(context.getPackageName())); }
            catch (Exception e) { logoImage.setImageResource(android.R.drawable.sym_def_app_icon); }
        }
        GradientDrawable logoBg = new GradientDrawable();
        logoBg.setShape(GradientDrawable.OVAL);
        logoBg.setColor(0xFF151520);
        logoBg.setStroke(dp(2), PrimaryColor);
        logoImage.setBackground(logoBg);
        logoImage.setPadding(dp(3), dp(3), dp(3), dp(3));
        headerContainer.addView(logoImage);


        TextView appTitle = new TextView(context);
        appTitle.setText("Onyx Aimkill AIMKILL MAX");
        appTitle.setTextColor(Color.WHITE);
        appTitle.setTextSize(11);
        appTitle.setSingleLine(true);

        Typeface customFont = null;
        try { customFont = Typeface.createFromAsset(context.getAssets(), "kcfonts/ethnocentric.ttf"); }
        catch (Exception e) { try { customFont = Typeface.createFromAsset(context.getAssets(), "kcfonts/ethnocentric.ttf.ttf"); } catch (Exception ignore) {} }
        appTitle.setTypeface(customFont != null ? customFont : Typeface.create("sans-serif-black", Typeface.BOLD));
        appTitle.setGravity(Gravity.CENTER_VERTICAL);
        applySweepingGradient(appTitle);

        headerContainer.addView(appTitle);
        loginCard.addView(headerContainer);

        input_username = createFloatingEditText("LICENSE KEY", PrimaryColor);
        LinearLayout.LayoutParams inputParams = new LinearLayout.LayoutParams(dp(270), dp(54));
        inputParams.gravity = Gravity.CENTER_HORIZONTAL;
        input_username.setLayoutParams(inputParams);
        input_username.setTransformationMethod(PasswordTransformationMethod.getInstance());
        if (savedKey != null && !savedKey.isEmpty()) input_username.setText(savedKey);
        loginCard.addView(input_username);

        CheckBox saveCheckBox = new CheckBox(context);
        saveCheckBox.setText("Save credentials");
        saveCheckBox.setTextColor(0xFFCCCCCC);
        saveCheckBox.setTextSize(12);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            saveCheckBox.setButtonTintList(android.content.res.ColorStateList.valueOf(PrimaryColor));
        }
        if (savedKey != null && !savedKey.isEmpty()) saveCheckBox.setChecked(true);
        LinearLayout.LayoutParams cbParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        cbParams.topMargin = dp(8);
        cbParams.gravity = Gravity.LEFT;
        saveCheckBox.setLayoutParams(cbParams);
        loginCard.addView(saveCheckBox);

        LinearLayout toggleBox = new LinearLayout(context);
        LinearLayout.LayoutParams toggleBoxParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, dp(36));
        toggleBoxParams.topMargin = dp(10);
        toggleBoxParams.gravity = Gravity.CENTER;
        toggleBox.setLayoutParams(toggleBoxParams);
        toggleBox.setOrientation(LinearLayout.HORIZONTAL);
        toggleBox.setGravity(Gravity.CENTER);
        toggleBox.setBackground(Utils.createRoundedDrawable(18, InputBgColor));

        Button btnFF = new Button(context);
        Button btnFFMax = new Button(context);
        LinearLayout.LayoutParams btnParams = new LinearLayout.LayoutParams(0, ViewGroup.LayoutParams.MATCH_PARENT, 1f);

        btnFF.setLayoutParams(btnParams);
        btnFFMax.setLayoutParams(btnParams);
        btnFF.setText("FREE FIRE");
        btnFFMax.setText("FF MAX");
        btnFF.setTextSize(9);
        btnFFMax.setTextSize(9);
        btnFF.setTypeface(null, android.graphics.Typeface.BOLD);
        btnFFMax.setTypeface(null, android.graphics.Typeface.BOLD);

        Runnable refreshToggles = () -> {
            if ("com.dts.freefireth".equals(selectedTargetPackage)) {
                btnFF.setBackground(Utils.createRoundedDrawable(18, PrimaryColor));
                btnFF.setTextColor(0xFFFFFFFF);
                btnFFMax.setBackgroundColor(Color.TRANSPARENT);
                btnFFMax.setTextColor(0xFF666666);
            } else {
                btnFFMax.setBackground(Utils.createRoundedDrawable(18, PrimaryColor));
                btnFFMax.setTextColor(0xFFFFFFFF);
                btnFF.setBackgroundColor(Color.TRANSPARENT);
                btnFF.setTextColor(0xFF666666);
            }
        };

        btnFF.setOnClickListener(v -> { selectedTargetPackage = "com.dts.freefireth"; refreshToggles.run(); });
        btnFFMax.setOnClickListener(v -> { selectedTargetPackage = "com.dts.freefiremax"; refreshToggles.run(); });
        refreshToggles.run();

        toggleBox.addView(btnFF);
        toggleBox.addView(btnFFMax);
        loginCard.addView(toggleBox);

        FrameLayout slideArea = createSlideToLogin(loginCard, saveCheckBox);
        loginCard.addView(slideArea);

        TextView actionGetKey = new TextView(context);
        actionGetKey.setText("GET LICENSE");
        actionGetKey.setTextColor(0xFF666666);
        actionGetKey.setTextSize(9);
        actionGetKey.setPadding(dp(10), dp(14), dp(10), dp(4));
        actionGetKey.setGravity(Gravity.CENTER);
        actionGetKey.setOnClickListener(v -> context.startActivity(new Intent(Intent.ACTION_VIEW, android.net.Uri.parse(""))));
        loginCard.addView(actionGetKey);

        int glowOffset = dp(25);
        FrameLayout cardWrapper = new FrameLayout(context);
        cardWrapper.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));

        int originalCardWidth = dp(350);
        int properCardHeight = dp(400);

        GlowingBorderView borderView = new GlowingBorderView(context);
        borderView.setLayoutParams(new FrameLayout.LayoutParams(originalCardWidth + 2 * glowOffset, properCardHeight + 2 * glowOffset, Gravity.CENTER));

        FrameLayout.LayoutParams loginParams = new FrameLayout.LayoutParams(originalCardWidth, properCardHeight, Gravity.CENTER);
        loginParams.setMargins(0, dp(20), 0, dp(20));

        FrameLayout innerCard = new FrameLayout(context);
        innerCard.setLayoutParams(loginParams);
        innerCard.setBackground(loginCard.getBackground());
        loginCard.setBackground(null);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            innerCard.setClipToOutline(true);
        }

        ParticleView particles = new ParticleView(context);

        innerCard.addView(particles, new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
        innerCard.addView(loginCard, new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));

        cardWrapper.addView(borderView);
        cardWrapper.addView(innerCard);

        ValueAnimator rotateAnimator = ValueAnimator.ofFloat(0f, 360f);
        rotateAnimator.setDuration(5000);
        rotateAnimator.setRepeatCount(ValueAnimator.INFINITE);
        rotateAnimator.addUpdateListener(animation -> borderView.setRotation((float) animation.getAnimatedValue()));
        rotateAnimator.start();

        bgContainer.addView(cardWrapper);
        container_login.addView(bgContainer);
    }

    private EditText createFloatingEditText(String hint, int accentColor) {
        EditText et = new EditText(context);
        et.setLayoutParams(new LinearLayout.LayoutParams(dp(300), dp(48)));
        et.setHint(hint);
        et.setHintTextColor(0x99FFFFFF);
        et.setTextColor(Color.WHITE);
        et.setTextSize(14);
        et.setSingleLine(true);
        et.setPadding(dp(16), dp(14), dp(16), dp(14));

        GradientDrawable bg = new GradientDrawable();
        bg.setCornerRadius(dp(12));
        bg.setColor(0x152A2A3A);
        bg.setStroke(dp(2), 0x55555577);
        et.setBackground(bg);

        et.setOnFocusChangeListener((v, hasFocus) -> {
            int color = hasFocus ? accentColor : 0x55555577;
            bg.setStroke(dp(hasFocus ? 3 : 2), color);
            et.setHintTextColor(hasFocus ? accentColor : 0x99FFFFFF);
        });

        return et;
    }

    private FrameLayout createSlideToLogin(LinearLayout loginCard, CheckBox saveCheckBox) {
        FrameLayout slideArea = new FrameLayout(context);
        LinearLayout.LayoutParams sp = new LinearLayout.LayoutParams(dp(270), dp(44));
        sp.gravity = Gravity.CENTER_HORIZONTAL;
        sp.setMargins(0, dp(14), 0, dp(6));
        slideArea.setLayoutParams(sp);

        GradientDrawable slideBg = new GradientDrawable(GradientDrawable.Orientation.LEFT_RIGHT, new int[]{0xFF990000, PrimaryColor});
        slideBg.setCornerRadius(dp(22));
        slideArea.setBackground(slideBg);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            slideArea.setClipToOutline(true);
        }

        View progressFill = new View(context);
        progressFill.setLayoutParams(new FrameLayout.LayoutParams(0, -1));
        GradientDrawable fill = new GradientDrawable(GradientDrawable.Orientation.LEFT_RIGHT, new int[]{PrimaryColor, 0xFF990000});
        fill.setCornerRadius(dp(22));
        progressFill.setBackground(fill);
        slideArea.addView(progressFill);

        TextView slideText = new TextView(context);
        slideText.setText("SLIDE TO LOGIN \u2192");
        slideText.setTextColor(Color.WHITE);
        slideText.setTextSize(12);
        slideText.setTypeface(null, android.graphics.Typeface.BOLD);
        slideText.setGravity(Gravity.CENTER);
        slideText.setLayoutParams(new FrameLayout.LayoutParams(-1, -1));
        slideArea.addView(slideText);

        View sliderThumb = new View(context);
        FrameLayout.LayoutParams thp = new FrameLayout.LayoutParams(dp(36), dp(36));
        thp.leftMargin = dp(4);
        thp.gravity = Gravity.CENTER_VERTICAL;
        sliderThumb.setLayoutParams(thp);
        GradientDrawable thumbBg = new GradientDrawable();
        thumbBg.setShape(GradientDrawable.OVAL);
        thumbBg.setColor(Color.WHITE);
        sliderThumb.setBackground(thumbBg);
        slideArea.addView(sliderThumb);

        final SharedPreferences preferences = context.getSharedPreferences(PREF_NAME, Context.MODE_PRIVATE);

        sliderThumb.setOnTouchListener(new View.OnTouchListener() {
            float dX;
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                FrameLayout.LayoutParams thumbLp = (FrameLayout.LayoutParams) sliderThumb.getLayoutParams();
                int maxX = slideArea.getWidth() - sliderThumb.getWidth() - dp(4);


                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        dX = event.getRawX() - thumbLp.leftMargin;
                        return true;
                    case MotionEvent.ACTION_MOVE:
                        int newX = (int) (event.getRawX() - dX);
                        if (newX < dp(8)) newX = dp(8);
                        if (newX > maxX) newX = maxX;
                        thumbLp.leftMargin = newX;
                        sliderThumb.setLayoutParams(thumbLp);

                        FrameLayout.LayoutParams pLp = (FrameLayout.LayoutParams) progressFill.getLayoutParams();
                        pLp.width = newX + sliderThumb.getWidth();
                        progressFill.setLayoutParams(pLp);
                        return true;
                    case MotionEvent.ACTION_UP:
                        if (thumbLp.leftMargin >= maxX - dp(10)) {
                            slideArea.setEnabled(false);
                            slideText.setText("VERIFYING...");
                            slideText.setTextColor(Color.GREEN);

                            final String key = input_username.getText().toString().trim();
                            if (key.isEmpty()) {
                                resetSlide(slideArea, slideText, sliderThumb, progressFill, thumbLp);
                                Toast.makeText(context, "Please enter a license key!", Toast.LENGTH_SHORT).show();
                                return true;
                            }

                            if (saveCheckBox.isChecked()) {
                                preferences.edit().putString(LICENSE_KEY, key).apply();
                            } else {
                                preferences.edit().remove(LICENSE_KEY).apply();
                            }

                            sLoginUsername = key;
                            sLoginPassword = "Authenticated";

                            new Thread(() -> {
                                final AuthHelper.LoginResult result = senniVerifyLicense(context, key);
                                ((Activity) context).runOnUiThread(() -> {
                                    if (result.success) {
                                        showSellerInfoPopup(result, key);
                                    } else {
                                        resetSlide(slideArea, slideText, sliderThumb, progressFill, thumbLp);
                                        Toast.makeText(context, result.message != null ? result.message : "Authentication failed", Toast.LENGTH_LONG).show();
                                    }
                                });
                            }).start();

                        } else {
                            resetSlide(slideArea, slideText, sliderThumb, progressFill, thumbLp);
                        }
                        return true;
                }
                return false;
            }
        });

        return slideArea;
    }

    private void resetSlide(FrameLayout slideArea, TextView slideText, View sliderThumb, View progressFill, FrameLayout.LayoutParams thumbLp) {
        slideArea.setEnabled(true);
        slideText.setText("SLIDE TO LOGIN \u2192");
        slideText.setTextColor(Color.WHITE);
        thumbLp.leftMargin = dp(6);
        sliderThumb.setLayoutParams(thumbLp);
        FrameLayout.LayoutParams pLp2 = (FrameLayout.LayoutParams) progressFill.getLayoutParams();
        pLp2.width = 0;
        progressFill.setLayoutParams(pLp2);
    }

    private void showSellerInfoPopup(final AuthHelper.LoginResult result, final String userKey) {
        ((Activity) context).runOnUiThread(() -> {
            ViewGroup rootView = (ViewGroup) ((Activity) context).findViewById(android.R.id.content);

            FrameLayout overlay = new FrameLayout(context);
            overlay.setLayoutParams(new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
            overlay.setBackgroundColor(0xDD000000);
            overlay.setClickable(true);

            ParticlesView overlayParticles = new ParticlesView(context);
            overlay.addView(overlayParticles, new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));

            LinearLayout modal = new LinearLayout(context);
            FrameLayout.LayoutParams modalParams = new FrameLayout.LayoutParams(utils.FixDP(270), ViewGroup.LayoutParams.WRAP_CONTENT, Gravity.CENTER);
            modal.setLayoutParams(modalParams);
            modal.setOrientation(LinearLayout.VERTICAL);
            modal.setPadding(utils.FixDP(18), utils.FixDP(16), utils.FixDP(18), utils.FixDP(16));
            modal.setGravity(Gravity.CENTER);

            GradientDrawable modalBg = new GradientDrawable(
                    GradientDrawable.Orientation.TL_BR, new int[]{0xFA0E0E16, 0xFA05050A});
            modalBg.setCornerRadius(utils.FixDP(18));
            modalBg.setStroke(utils.FixDP(2), PrimaryColor);
            modal.setBackground(modalBg);

            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
                modal.setClipToOutline(true);
                modal.setElevation(utils.FixDP(20));
            }

            LinearLayout headerRow = new LinearLayout(context);
            headerRow.setOrientation(LinearLayout.HORIZONTAL);
            headerRow.setGravity(Gravity.CENTER);
            headerRow.setPadding(0, 0, 0, utils.FixDP(10));

            Typeface kcFont = null;
            try { kcFont = Typeface.createFromAsset(context.getAssets(), "kcfonts/ethnocentric.ttf"); } catch (Exception ignored) {}

            TextView hRed = new TextView(context);
            hRed.setText("Onyx Aimkill ");
            hRed.setTextColor(PrimaryColor);
            hRed.setTextSize(10);
            hRed.setSingleLine(true);
            hRed.setTypeface(kcFont != null ? kcFont : Typeface.DEFAULT_BOLD, Typeface.BOLD);
            applySweepingGradient(hRed);

            TextView hWhite = new TextView(context);
            hWhite.setText("AIMKILL MAX");
            hWhite.setTextColor(0xFFFFFFFF);
            hWhite.setTextSize(10);
            hWhite.setSingleLine(true);
            hWhite.setTypeface(kcFont != null ? kcFont : Typeface.DEFAULT_BOLD, Typeface.BOLD);

            headerRow.addView(hRed);
            headerRow.addView(hWhite);
            modal.addView(headerRow);

            View div = new View(context);
            div.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, utils.FixDP(1)));
            div.setBackgroundColor(0x33FF1A3C);
            modal.addView(div);

            LinearLayout infoCont = new LinearLayout(context);
            infoCont.setOrientation(LinearLayout.VERTICAL);
            infoCont.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
            infoCont.setPadding(0, utils.FixDP(8), 0, utils.FixDP(10));

            infoCont.addView(createInfoRow("PACKAGE", result.packageName.toUpperCase(), 0xFFFFD700));
            infoCont.addView(createInfoRow("STATUS", result.status.toUpperCase(), 0xFF00FF88));
            String displayHwid = (result.hwid != null && result.hwid.length() > 8) ? result.hwid : AuthHelper.getDeviceId(context);
            infoCont.addView(createInfoRow("DEVICE", displayHwid.substring(0, Math.min(displayHwid.length(), 16)) + "...", 0xFFCCCCCC));
            
            final LinearLayout validRow = createInfoRow("EXPIRES", "", 0xFF00E5FF);
            final TextView validVal = (TextView) validRow.getChildAt(1);
            infoCont.addView(validRow);

            final Handler timerHandler = new Handler(Looper.getMainLooper());
            final Runnable timerRunnable = new Runnable() {
                @Override public void run() {
                    validVal.setText(getRemainingValidity(result.expiryDate).toUpperCase());
                    timerHandler.postDelayed(this, 1000);
                }
            };
            timerHandler.post(timerRunnable);

            LinearLayout keyRow = createInfoRow("LICENSE", userKey, PrimaryColor);
            final TextView keyVal = (TextView) keyRow.getChildAt(1);
            keyVal.setTypeface(null, android.graphics.Typeface.BOLD);
            infoCont.addView(keyRow);

            modal.addView(infoCont);

            GradientDrawable btnGrad = new GradientDrawable(
                    GradientDrawable.Orientation.LEFT_RIGHT, new int[]{0xFFFF1A3C, 0xFFFF5500});
            btnGrad.setCornerRadius(utils.FixDP(18));

            Button btnContinue = new Button(context);
            btnContinue.setText("CONTINUE");
            btnContinue.setTextColor(0xFFFFFFFF);
            btnContinue.setAllCaps(true);
            btnContinue.setTextSize(10);
            btnContinue.setTypeface(null, android.graphics.Typeface.BOLD);
            btnContinue.setBackground(btnGrad);
            btnContinue.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, utils.FixDP(36)));
            btnContinue.setOnClickListener(v -> {
                timerHandler.removeCallbacks(timerRunnable);
                overlay.animate().alpha(0).setDuration(250).withEndAction(() -> {
                    rootView.removeView(overlay);
                    new Menu(context, selectedInjectType, selectedTargetPackage);
                    launchGame();
                }).start();
            });
            modal.addView(btnContinue);

            overlay.addView(modal);
            rootView.addView(overlay);

            overlay.setAlpha(0f);
            modal.setScaleX(0.75f);
            modal.setScaleY(0.75f);

            overlay.animate().alpha(1f).setDuration(250).start();
            modal.animate().scaleX(1.0f).scaleY(1.0f).setDuration(300).setInterpolator(new android.view.animation.OvershootInterpolator(1.2f)).start();
        });
    }

    private String getRemainingValidity(String expiryStr) {
        if (expiryStr == null || expiryStr.trim().isEmpty() || expiryStr.equalsIgnoreCase("Lifetime")) return "LIFETIME";
        try {
            SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss", Locale.US);
            Date date = sdf.parse(expiryStr);
            if (date == null) return expiryStr;
            long diff = date.getTime() - System.currentTimeMillis();
            if (diff <= 0) return "EXPIRED";
            long seconds = diff / 1000;
            long minutes = seconds / 60;
            long hours = minutes / 60;
            long days = hours / 24;
            return String.format(Locale.US, "%dd %dh %dm %ds", days, hours % 24, minutes % 60, seconds % 60);
        } catch (Exception e) { return expiryStr; }
    }

    private LinearLayout createInfoRow(String label, String value) {
        return createInfoRow(label, value, 0xFFF5F5F5);
    }

    private LinearLayout createInfoRow(String label, String value, int valColor) {
        LinearLayout row = new LinearLayout(context);
        row.setOrientation(LinearLayout.HORIZONTAL);
        row.setPadding(0, utils.FixDP(4), 0, utils.FixDP(4));
        TextView lbl = new TextView(context);
        lbl.setText(label + ": ");
        lbl.setTextColor(0xFF888899);
        lbl.setTextSize(9);
        lbl.setLayoutParams(new LinearLayout.LayoutParams(0, ViewGroup.LayoutParams.WRAP_CONTENT, 1f));
        TextView val = new TextView(context);
        val.setText(value);
        val.setTextColor(valColor);
        val.setTextSize(9);
        val.setGravity(Gravity.RIGHT);
        val.setLayoutParams(new LinearLayout.LayoutParams(0, ViewGroup.LayoutParams.WRAP_CONTENT, 2f));
        row.addView(lbl);
        row.addView(val);
        return row;
    }

    private void launchGame() {
        Intent i = context.getPackageManager().getLaunchIntentForPackage(selectedTargetPackage);
        if (i != null) context.startActivity(i);
    }

    private void applySweepingGradient(TextView tv) {
        tv.setLayerType(View.LAYER_TYPE_SOFTWARE, null);
        tv.post(new Runnable() {
            @Override
            public void run() {
                final int width = tv.getWidth();
                if (width <= 0) { tv.post(this); return; }

                LinearGradient grad = new LinearGradient(
                        0, 0, width * 2f, 0,
                        new int[]{Color.WHITE, 0xFFE53935, Color.WHITE},
                        new float[]{0.0f, 0.5f, 1.0f}, Shader.TileMode.REPEAT);
                tv.getPaint().setShader(grad);

                ValueAnimator anim = ValueAnimator.ofFloat(0f, 1f);
                anim.setDuration(2500);
                anim.setRepeatCount(ValueAnimator.INFINITE);
                anim.setInterpolator(new android.view.animation.LinearInterpolator());
                final Matrix m = new Matrix();
                anim.addUpdateListener(a -> {
                    float v = (float) a.getAnimatedValue();
                    m.setTranslate(-(width * 2f * v), 0);
                    grad.setLocalMatrix(m);
                    tv.invalidate();
                });
                anim.start();
            }
        });
    }

    private class GlowingBorderView extends View {
        private Paint paint;
        private RectF rect;
        private Matrix matrix;
        private int glowOffsetPx;
        private float baseStroke;

        public GlowingBorderView(Context ctx) {
            super(ctx);
            paint = new Paint(Paint.ANTI_ALIAS_FLAG);
            paint.setStyle(Paint.Style.STROKE);
            baseStroke = dp(14);
            paint.setStrokeWidth(baseStroke);
            setLayerType(LAYER_TYPE_SOFTWARE, paint);
            paint.setMaskFilter(new BlurMaskFilter(dp(12), BlurMaskFilter.Blur.OUTER));
            matrix = new Matrix();
            glowOffsetPx = dp(15);
        }

        @Override
        protected void onSizeChanged(int w, int h, int oldw, int oldh) {
            super.onSizeChanged(w, h, oldw, oldh);
            rect = new RectF(glowOffsetPx, glowOffsetPx, w - glowOffsetPx, h - glowOffsetPx);
            int red = 0xFFE53935;
            int darkRed = 0xFF990000;
            int transparent = Color.argb(0, 0xFF, 0xE5, 0x39);
            paint.setShader(new SweepGradient(w / 2f, h / 2f, new int[]{transparent, red, darkRed, red, transparent}, new float[]{0f, 0.25f, 0.5f, 0.75f, 1f}));
        }

        @Override
        protected void onDraw(Canvas canvas) {
            super.onDraw(canvas);
            paint.setStrokeWidth(baseStroke);
            matrix.reset();
            matrix.setRotate(getRotation(), getWidth() / 2f, getHeight() / 2f);
            if (paint.getShader() != null) paint.getShader().setLocalMatrix(matrix);
            float corner = dp(22);
            canvas.drawRoundRect(rect, corner, corner, paint);
        }
    }

    private class ParticleView extends View {
        private final Paint glowPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
        private final Paint corePaint = new Paint(Paint.ANTI_ALIAS_FLAG);
        private final int PARTICLE_COUNT = 30;
        private final float[] xPositions = new float[PARTICLE_COUNT];
        private final float[] yPositions = new float[PARTICLE_COUNT];
        private final float[] speedsY = new float[PARTICLE_COUNT];
        private final float[] speedsX = new float[PARTICLE_COUNT];
        private final float[] radii = new float[PARTICLE_COUNT];
        private final int[] colors = new int[PARTICLE_COUNT];
        private boolean initialized = false;

        public ParticleView(Context context) {
            super(context);
            glowPaint.setStyle(Paint.Style.FILL);
            corePaint.setStyle(Paint.Style.FILL);
        }

        @Override
        protected void onDraw(Canvas canvas) {
            super.onDraw(canvas);
            int width = getWidth();
            int height = getHeight();
            if (width == 0 || height == 0) return;

            if (!initialized) {
                for (int i = 0; i < PARTICLE_COUNT; i++) {
                    xPositions[i] = (float) (Math.random() * width);
                    yPositions[i] = (float) (Math.random() * height);
                    speedsY[i] = (float) (-(0.4 + Math.random() * 1.2));
                    speedsX[i] = (float) ((Math.random() - 0.5) * 0.4);
                    radii[i] = (float) (dp(3) + Math.random() * dp(4));
                    float chance = (float) Math.random();
                    colors[i] = chance > 0.6f ? 0xFFFF1A3C : (chance > 0.3f ? 0xFFFF6600 : 0xFFFFFFFF);
                }
                initialized = true;
            }

            for (int i = 0; i < PARTICLE_COUNT; i++) {
                yPositions[i] += speedsY[i];
                xPositions[i] += speedsX[i];

                if (yPositions[i] < -20 || xPositions[i] < -20 || xPositions[i] > width + 20) {
                    yPositions[i] = height + 10;
                    xPositions[i] = (float) (Math.random() * width);
                }

                glowPaint.setColor(colors[i]);
                glowPaint.setAlpha(60);
                canvas.drawCircle(xPositions[i], yPositions[i], radii[i] * 2.2f, glowPaint);

                corePaint.setColor(colors[i]);
                corePaint.setAlpha(190);
                canvas.drawCircle(xPositions[i], yPositions[i], radii[i], corePaint);
            }
            invalidate();
        }
    }
}
