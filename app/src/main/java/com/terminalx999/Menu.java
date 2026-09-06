package com.terminalx999;

import android.animation.ValueAnimator;
import android.graphics.LinearGradient;
import android.graphics.Matrix;
import android.graphics.Shader;
import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.PixelFormat;
import android.graphics.PorterDuff;
import android.graphics.Typeface;
import android.graphics.drawable.GradientDrawable;
import android.graphics.drawable.Drawable;
import android.graphics.Paint;
import android.graphics.Path;
import android.graphics.Rect;
import android.graphics.ColorFilter;
import android.os.Build;
import android.text.Html;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.HorizontalScrollView;
import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.ScrollView;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.CheckBox;
import android.content.res.ColorStateList;

import com.topjohnwu.superuser.Shell;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Menu {

    private static Typeface menuFont;

    private static void setShimmer(final TextView tv, boolean enable) {
        if (!enable) {
            Object animObj = tv.getTag();
            if (animObj instanceof ValueAnimator) {
                ((ValueAnimator) animObj).cancel();
            }
            tv.setTag(null);
            tv.getPaint().setShader(null);
            tv.invalidate();
            return;
        }

        try {
            tv.post(new Runnable() {
                private int retryCount = 0;
                @Override
                public void run() {
                    try {
                        final int width = tv.getWidth();
                        if (width <= 0) {
                            if (retryCount++ < 20) { tv.postDelayed(this, 100); }
                            return;
                        }

                        LinearGradient grad = new LinearGradient(
                                0, 0, width * 2f, 0,
                                new int[]{PrimaryColor, Color.WHITE, PrimaryColor},
                                new float[]{0.0f, 0.5f, 1.0f}, Shader.TileMode.REPEAT);
                        tv.getPaint().setShader(grad);

                        ValueAnimator anim = ValueAnimator.ofFloat(0f, 1f);
                        anim.setDuration(2500);
                        anim.setRepeatCount(ValueAnimator.INFINITE);
                        anim.setInterpolator(new android.view.animation.LinearInterpolator());
                        final Matrix m = new Matrix();
                        anim.addUpdateListener(a -> {
                            try {
                                float v = (float) a.getAnimatedValue();
                                m.setTranslate(-(width * 2f * v), 0);
                                grad.setLocalMatrix(m);
                                tv.invalidate();
                            } catch (Exception ignored) {}
                        });
                        tv.setTag(anim);
                        anim.start();
                    } catch (Exception ignored) {}
                }
            });
        } catch (Exception ignored) {}
    }

    private static void applySweepingGradient(final TextView tv) {
        setShimmer(tv, true);
    }

    private static void updateKeybindTvColor(TextView tv, String text) {
        if (text == null || text.equalsIgnoreCase("NONE") || text.equalsIgnoreCase("Press")) {
            tv.setTextColor(0xFF888888);
        } else {
            tv.setTextColor(0xFF00FF88);
        }
    }

    private static void startBreathingAnimation(final GradientDrawable drawable, final View view, final int strokeWidth, final int color1, final int color2) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            try {
                ValueAnimator anim = ValueAnimator.ofArgb(color1, color2);
                anim.setDuration(1500);
                anim.setRepeatMode(ValueAnimator.REVERSE);
                anim.setRepeatCount(ValueAnimator.INFINITE);
                anim.addUpdateListener(new ValueAnimator.AnimatorUpdateListener() {
                    @Override
                    public void onAnimationUpdate(ValueAnimator a) {
                        drawable.setStroke(strokeWidth, (int) a.getAnimatedValue());
                        view.invalidate();
                    }
                });
                anim.start();
            } catch (Exception ignored) {}
        }
    }

    private static GradientDrawable getTabDrawable(boolean active) {
        GradientDrawable bg = new GradientDrawable();
        bg.setCornerRadius(utils.FixDP(16));
        if (active) {
            bg.setColor(0xFFFF0000);
        } else {
            bg.setColor(0xFF222222);
        }
        return bg;
    }

    // Native Functions - Init requires context; call nativeVerifyCredentials before
    // Init.
    public static native void Functions();

    public static native void ChangesID(int ID, int Value);

    /**
     * Must call nativeVerifyCredentials(context, user, pass) first. If false, do
     * not call Init (app corrupted).
     */
    public static native void Init(Context context);

    /**
     * Returns int[2]: { matchAlive, remainingTimeSeconds }. Used for keybind
     * overlay timer.
     */
    public static native int[] getMatchTimerStatus();
    public static native void LockPlayer(long ptr);
    public static native String[] getEnemyList();
    
    private static Menu instance;
    public static String target = "com.dts.freefireth";
    private int injectType;

    // Minimal Clean theme
    private int buttonClick = 0;
    public static int PrimaryColor = 0xFFE53935; // Red accent
    public static int TabSelectedColor = 0xFFE53935;
    private static final int AccentBorderColor = 0xFFE53935;
    private static final int AccentGradientEnd = 0xFFB71C1C;
    private static final int MenuBgColor = 0xFF0D0D0D; // Near-black
    private static final int MenuBorderColor = 0xFF1A1A1A; // Subtle divider
    private static final int CardBgColor = 0xFF0D0D0D;
    private static final int CardBorderColor = 0xFF1A1A1A;
    private static final int InactiveTabBgColor = 0x00000000; // Fully transparent
    private static final int InactiveTabBorderColor = 0x00000000; // No border
    private static final int InactiveTabTextColor = 0xFF666666; // Dimmed text
    private static final int KeybindBtnBgColor = 0x1AFFFFFF;
    private static final int KeybindBtnBorderColor = 0xFF333333;
    private static final int TextPrimaryColor = 0xFFF5F5F5; // Clean white
    private static final int TextSecondaryColor = 0xFF999999; // Soft grey
    private static Context context;
    private static Utils utils;

    public static native String imageBase64();

    // Parte Do Sistema De Janela
    private WindowManager windowManager;
    private WindowManager.LayoutParams windowManagerParams;
    private FrameLayout frameLayout;

    // DrawView Global
    DrawView drawView;

    // Target List UI
    private LinearLayout targetListLayout;
    private WindowManager.LayoutParams targetListParams;
    private LinearLayout targetItemsContainer;
    private android.os.Handler targetRefreshHandler = new android.os.Handler();
    private boolean isTargetListVisible = false;
    private long currentlyLockedPtr = 0;

    // Tab Management
    private static Map<String, LinearLayout> tabContentContainers = new HashMap<>();
    private static List<TextView> tabButtons = new ArrayList<>();
    private static String currentTab = "";
    private static String populateTab = "";

    // Keybind (ToggleBind) - verox style
    private static Map<Integer, Integer> idToKeyCode = new HashMap<>();
    private static Map<Integer, TextView> idToKeybindTv = new HashMap<>();
    private static final String KEYBIND_PREFS = "keybinds";
    private static final String PREF_KEYBIND_ENABLED = "keybind_enabled";
    private static final String PREF_KEYBIND_STATUS = "keybind_status";
    private static volatile boolean keybindDialogShowing = false;
    private static volatile Integer pendingKeybindId = null;
    private static Menu menuInstance;

    private static SharedPreferences getKeybindPrefs() {
        return context.getSharedPreferences(KEYBIND_PREFS, Context.MODE_PRIVATE);
    }

    private static int getKeybindForId(int id) {
        return getKeybindPrefs().getInt("keybind_" + id, -1);
    }

    private static String keyCodeToLabel(int keyCode) {
        String s = KeyEvent.keyCodeToString(keyCode);
        if (s != null && s.startsWith("KEYCODE_"))
            s = s.substring(7);
        else if (s == null)
            s = String.valueOf(keyCode);
        if (s != null)
            while (s.startsWith("_"))
                s = s.substring(1);
        return s != null ? s : String.valueOf(keyCode);
    }

    private static void setKeybindForId(int id, int keyCode) {
        getKeybindPrefs().edit().putInt("keybind_" + id, keyCode).apply();
        idToKeyCode.put(id, keyCode);
        for (Map.Entry<Integer, Integer> e : new HashMap<>(idToKeyCode).entrySet()) {
            if (e.getValue() == keyCode && e.getKey() != id) {
                idToKeyCode.remove(e.getKey());
                TextView other = idToKeybindTv.get(e.getKey());
                if (other != null) {
                    other.setText("NONE");
                    updateKeybindTvColor(other, "NONE");
                }
                break;
            }
        }
        TextView tv = idToKeybindTv.get(id);
        if (tv != null) {
            tv.setText(keyCodeToLabel(keyCode));
            updateKeybindTvColor(tv, tv.getText().toString());
        }
        if (menuInstance != null)
            menuInstance.updateKeybindOverlay();
    }

    private static Map<Integer, SwitchStyle> idToBindSwitch = new HashMap<>();
    private static Map<Integer, String> idToName = new HashMap<>();
    private static List<TextView> allKeybindButtons = new ArrayList<>();
    private static final int ID_TURN_ON_KEYBIND = 6000;
    private static final int ID_CLEAR_KEYBINDS = 6001;
    private static final int ID_SHOW_KEYBIND_STATUS = 6002;
    private static final int ID_SHOW_MATCH_TIMER = 6003;
    private static volatile boolean keybindEnabled = false;
    private static volatile boolean showKeybindStatus = false;
    private static volatile boolean showMatchTimer = false;

    // Auto-toggle tracking
    private static boolean speedTimerAutoOffed = false;
    private static boolean isLinkingHacks = false;
    private static boolean isTeleportingSequence = false;

    private LinearLayout keybindOverlay;
    private LinearLayout keybindList;
    private WindowManager.LayoutParams keybindOverlayParams;
    private final android.os.Handler keybindOverlayHandler = new android.os.Handler(android.os.Looper.getMainLooper());
    private Runnable keybindOverlayRefreshRunnable;

    // Parte do Draw
    WindowManager.LayoutParams windowManagerDrawViewParams;

    public static native void OnDrawLoad(DrawView drawView, Canvas canvas);

    public void DrawCanvas() {
        int LAYOUT_FLAG;
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            LAYOUT_FLAG = WindowManager.LayoutParams.TYPE_APPLICATION_OVERLAY;
        } else {
            LAYOUT_FLAG = WindowManager.LayoutParams.TYPE_PHONE;
        }

        drawView = new DrawView(context);
        windowManagerDrawViewParams = new WindowManager.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.MATCH_PARENT,
                LAYOUT_FLAG,
                WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL |
                        WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE |
                        WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE |
                        WindowManager.LayoutParams.FLAG_FULLSCREEN |
                        WindowManager.LayoutParams.FLAG_HARDWARE_ACCELERATED,
                PixelFormat.TRANSPARENT);
        windowManagerDrawViewParams.gravity = Gravity.CENTER;
        windowManager.addView(drawView, windowManagerDrawViewParams);
    }

    // Parte Do Template Do Menu
    private static ScrollView scrollView_center;
    private static LinearLayout tabsContainer;
    private static LinearLayout featuresScrollContainer;
    private static LinearLayout container_menu;
    private static ImageBase64 icon_cheat;

    public Menu(Context globContext, int glob_injectType, String glob_target) {
        context = globContext;
        utils = new Utils(context);
        injectType = glob_injectType;
        target = glob_target;
        menuInstance = this;
        System.loadLibrary("TERMINALX_MENU");
        onCreate();
    }

    public void onCreate() {
        onCreateSystemWindow();
        onCreateTemplate();
    }

    // Criar Template
    public void onCreateTemplate() {
        int menuWidth = utils.FixDP(275);
        int menuHeight = utils.FixDP(340);

        GradientDrawable gradientDrawable_container = new GradientDrawable(
                GradientDrawable.Orientation.TL_BR, new int[]{0xFA0D0D12, 0xFA050508});
        gradientDrawable_container.setCornerRadius(utils.FixDP(18));
        gradientDrawable_container.setStroke(utils.FixDP(2), 0xFFFF1A3C);

        LinearLayout container = new LinearLayout(context);
        container.setOrientation(LinearLayout.VERTICAL);
        container.setLayoutParams(new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.WRAP_CONTENT,
                ViewGroup.LayoutParams.WRAP_CONTENT));

        container_menu = new LinearLayout(context);
        container_menu.setLayoutParams(new LinearLayout.LayoutParams(menuWidth, menuHeight));
        container_menu.setOrientation(LinearLayout.VERTICAL);
        container_menu.setVisibility(View.GONE);
        container_menu.setBackground(gradientDrawable_container);
        startBreathingAnimation(gradientDrawable_container, container_menu, utils.FixDP(2), 0xFFFF1A3C, 0xFFFF6600);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            container_menu.setElevation(utils.FixDP(20));
            container_menu.setClipToOutline(true);
        }

        // Floating icon - Circular shape with neon glowing stroke ring
        icon_cheat = new ImageBase64(context);
        icon_cheat.setLayoutParams(new LinearLayout.LayoutParams(
                utils.FixDP(46), utils.FixDP(46)));
        android.graphics.Bitmap logoBm = Utils.getBannerBitmap(context);
        if (logoBm != null) {
            icon_cheat.setImageBitmap(logoBm);
        } else {
            icon_cheat.setImageBase64(imageBase64());
        }
        icon_cheat.setPadding(utils.FixDP(4), utils.FixDP(4), utils.FixDP(4), utils.FixDP(4));
        GradientDrawable iconBg = new GradientDrawable();
        iconBg.setShape(GradientDrawable.OVAL);
        iconBg.setColor(0xFF0F0F14);
        iconBg.setStroke(utils.FixDP(2), PrimaryColor);
        icon_cheat.setBackground(iconBg);
        startBreathingAnimation(iconBg, icon_cheat, utils.FixDP(2), 0xFFFF1A3C, 0xFFFF7700);

        icon_cheat.setOnTouchListener(onTouchListener());
        icon_cheat.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                icon_cheat.setVisibility(View.GONE);
                container_menu.setVisibility(View.VISIBLE);
                if (menuInstance != null) {
                    if (keybindEnabled) {
                        menuInstance.enableHotkeys();
                    }
                    menuInstance.requestKeybindFocus();
                }
            }
        });

        // Header - Circular logo + BanAimKill title
        LinearLayout container_top = new LinearLayout(context);
        container_top.setLayoutParams(new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, utils.FixDP(42)));
        container_top.setPadding(utils.FixDP(8), utils.FixDP(6), utils.FixDP(8), 0);
        container_top.setGravity(Gravity.CENTER);
        container_top.setOrientation(LinearLayout.HORIZONTAL);

        Typeface kcFont = null;
        try { kcFont = Typeface.createFromAsset(context.getAssets(), "kcfonts/ethnocentric.ttf"); } catch (Exception e) {}
        
        android.widget.ImageView headerLogo = new android.widget.ImageView(context);
        LinearLayout.LayoutParams logoLp = new LinearLayout.LayoutParams(utils.FixDP(26), utils.FixDP(26));
        logoLp.rightMargin = utils.FixDP(6);
        headerLogo.setLayoutParams(logoLp);
        android.graphics.Bitmap headerBm = Utils.getBannerBitmap(context);
        if (headerBm != null) {
            headerLogo.setImageBitmap(headerBm);
        } else {
            try { headerLogo.setImageDrawable(context.getPackageManager().getApplicationIcon(context.getPackageName())); } catch (Exception ignored) {}
        }
        GradientDrawable headerLogoBg = new GradientDrawable();
        headerLogoBg.setShape(GradientDrawable.OVAL);
        headerLogoBg.setColor(0xFF151520);
        headerLogoBg.setStroke(utils.FixDP(2), PrimaryColor);
        headerLogo.setBackground(headerLogoBg);
        headerLogo.setPadding(utils.FixDP(2), utils.FixDP(2), utils.FixDP(2), utils.FixDP(2));

        TextView titleRed = new TextView(context);
        titleRed.setText("BanAimKill ");
        titleRed.setTextColor(PrimaryColor);
        titleRed.setTextSize(10);
        titleRed.setSingleLine(true);
        titleRed.setGravity(Gravity.CENTER_VERTICAL);
        titleRed.setTypeface(kcFont != null ? kcFont : Typeface.create("sans-serif-black", Typeface.BOLD), Typeface.BOLD);
        applySweepingGradient(titleRed);

        TextView titleWhite = new TextView(context);
        titleWhite.setText("AIMKILL MAX");
        titleWhite.setTextColor(0xFFFFFFFF);
        titleWhite.setTextSize(10);
        titleWhite.setSingleLine(true);
        titleWhite.setGravity(Gravity.CENTER_VERTICAL);
        titleWhite.setTypeface(kcFont != null ? kcFont : Typeface.create("sans-serif-black", Typeface.BOLD), Typeface.BOLD);

        LinearLayout brandHolder = new LinearLayout(context);
        brandHolder.setOrientation(LinearLayout.HORIZONTAL);
        brandHolder.setLayoutParams(new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        brandHolder.setGravity(Gravity.CENTER);
        brandHolder.addView(headerLogo);
        brandHolder.addView(titleRed);
        brandHolder.addView(titleWhite);

        container_top.addView(brandHolder);

        View headerSeparator = new View(context);
        headerSeparator.setLayoutParams(new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, utils.FixDP(1)));
        headerSeparator.setBackgroundColor(0x33FF1A3C);

        // Body - Simple vertical layout
        LinearLayout body_wrapper = new LinearLayout(context);
        body_wrapper.setLayoutParams(new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                0, 1.0f));
        body_wrapper.setOrientation(LinearLayout.VERTICAL);

        // Tab bar - Premium glass-effect tab bar
        tabsContainer = new LinearLayout(context);
        LinearLayout.LayoutParams tabContainerLp = new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, utils.FixDP(40));
        tabContainerLp.setMargins(utils.FixDP(8), utils.FixDP(4), utils.FixDP(8), 0);
        tabsContainer.setLayoutParams(tabContainerLp);
        tabsContainer.setOrientation(LinearLayout.HORIZONTAL);
        tabsContainer.setGravity(Gravity.CENTER);
        tabsContainer.setPadding(utils.FixDP(3), utils.FixDP(3), utils.FixDP(3), utils.FixDP(3));
        GradientDrawable tabContainerBg = new GradientDrawable();
        tabContainerBg.setColor(0xFF0A0A0A);
        tabContainerBg.setCornerRadius(utils.FixDP(12));
        tabContainerBg.setStroke(utils.FixDP(1), 0xFF1A1A1A);
        tabsContainer.setBackground(tabContainerBg);

        // Glowing bottom accent line under tabs
        View tabDivider = new View(context);
        LinearLayout.LayoutParams dividerLp = new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, utils.FixDP(1));
        dividerLp.setMargins(utils.FixDP(16), 0, utils.FixDP(16), 0);
        tabDivider.setLayoutParams(dividerLp);
        GradientDrawable dividerGrad = new GradientDrawable(
                GradientDrawable.Orientation.LEFT_RIGHT,
                new int[]{0x00000000, 0x44FF1A3C, 0x00000000});
        tabDivider.setBackground(dividerGrad);

        // Center section where features will be displayed
        final LinearLayout container_center = new LinearLayout(context);
        LinearLayout.LayoutParams centerParams = new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                0,
                1.0f
        );
        container_center.setLayoutParams(centerParams);
        container_center.setGravity(Gravity.CENTER);
        container_center.setOrientation(LinearLayout.VERTICAL);

        // Scroll view for features
        scrollView_center = new ScrollView(context);
        scrollView_center.setLayoutParams(new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.MATCH_PARENT));
        scrollView_center.setPadding(0, utils.FixDP(2), 0, utils.FixDP(2));
        scrollView_center.setVerticalScrollBarEnabled(false);

        // Container for all feature tabs
        featuresScrollContainer = new LinearLayout(context);
        featuresScrollContainer.setLayoutParams(new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.MATCH_PARENT));
        featuresScrollContainer.setOrientation(LinearLayout.VERTICAL);

        scrollView_center.addView(featuresScrollContainer);

        // Loading spinner - red
        final ProgressBar progressBar = new ProgressBar(context);
        progressBar.setLayoutParams(new LinearLayout.LayoutParams(
                utils.FixDP(32), utils.FixDP(32)));
        progressBar.getIndeterminateDrawable().setColorFilter(PrimaryColor, PorterDuff.Mode.SRC_IN);

        // Bottom divider
        View botDivider = new View(context);
        botDivider.setLayoutParams(new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, 1));
        botDivider.setBackgroundColor(0x22FF1A3C);

        // Bottom bar - Modern action container
        LinearLayout container_bottom = new LinearLayout(context);
        container_bottom.setLayoutParams(new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, utils.FixDP(44)));
        container_bottom.setGravity(Gravity.CENTER);
        container_bottom.setOrientation(LinearLayout.HORIZONTAL);

        GradientDrawable gradientDrawable_inject_close = new GradientDrawable(
                GradientDrawable.Orientation.LEFT_RIGHT, new int[]{0xFFFF1A3C, 0xFFFF5500});
        gradientDrawable_inject_close.setCornerRadius(utils.FixDP(16));

        final Button inject_close = new Button(context);
        LinearLayout.LayoutParams injectBtnParams = new LinearLayout.LayoutParams(
                utils.FixDP(125), utils.FixDP(32));
        injectBtnParams.setMargins(0, utils.FixDP(4), 0, utils.FixDP(4));
        inject_close.setLayoutParams(injectBtnParams);
        inject_close.setPadding(0, 0, 0, 0);
        inject_close.setText("INJECT");
        inject_close.setTextSize(11);
        inject_close.setAllCaps(false);
        inject_close.setTypeface(null, Typeface.BOLD);
        inject_close.setTextColor(0xFFFFFFFF);
        inject_close.setGravity(Gravity.CENTER);
        inject_close.setBackground(gradientDrawable_inject_close);
        inject_close.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (buttonClick == 0) {
                    // Loading start
                    progressBar.setVisibility(View.VISIBLE);

                    // Injection Process
                    boolean success = false;
                    if (injectType == 0) {
                        success = InjectX32("libTERMINALX999.so");
                    } else {
                        success = InjectX86("libTERMINALX999.so");
                    }

                    if (success) {
                        Init(context);
                        Functions();

                        new android.os.Handler(android.os.Looper.getMainLooper()).postDelayed(() -> {
                            progressBar.setVisibility(View.GONE);
                            inject_close.setText("CLOSE");

                            container_center.removeAllViews();
                            container_center.addView(scrollView_center);

                            buttonClick = 1;
                            if (menuInstance != null && keybindEnabled)
                                menuInstance.enableHotkeys();

                            Toast.makeText(context, "Menu Loaded Successfully!", Toast.LENGTH_SHORT).show();
                        }, 100);

                    } else {
                        progressBar.setVisibility(View.GONE);
                        Toast.makeText(context, "Injection Failed!", Toast.LENGTH_LONG).show();
                    }
                } else {
                    container_menu.setVisibility(View.GONE);
                    icon_cheat.setVisibility(View.VISIBLE);
                    if (menuInstance != null && !keybindEnabled) {
                        menuInstance.disableHotkeys();
                    }
                }
            }
        });

        frameLayout.addView(container); 
        container.addView(icon_cheat);
        container.addView(container_menu);

        container_menu.addView(container_top);
        container_menu.addView(headerSeparator);

        body_wrapper.addView(tabsContainer);
        body_wrapper.addView(tabDivider);
        body_wrapper.addView(container_center);
        container_menu.addView(body_wrapper);

        container_center.addView(progressBar);

        container_menu.addView(botDivider);
        container_menu.addView(container_bottom);
        container_bottom.addView(inject_close);
    }


    // Create System Window
    public void onCreateSystemWindow() {
        int LAYOUT_FLAG;
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            LAYOUT_FLAG = WindowManager.LayoutParams.TYPE_APPLICATION_OVERLAY;
        } else {
            LAYOUT_FLAG = WindowManager.LayoutParams.TYPE_PHONE;
        }

        frameLayout = new FrameLayout(context);
        frameLayout.setLayoutParams(new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.WRAP_CONTENT,
                ViewGroup.LayoutParams.WRAP_CONTENT));
        frameLayout.setOnTouchListener(onTouchListener());
        frameLayout.setAlpha(1.0f);

        windowManagerParams = new WindowManager.LayoutParams(
                WindowManager.LayoutParams.WRAP_CONTENT,
                WindowManager.LayoutParams.WRAP_CONTENT,
                LAYOUT_FLAG,
                WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE | WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL
                        | WindowManager.LayoutParams.FLAG_LAYOUT_IN_OVERSCAN
                        | WindowManager.LayoutParams.FLAG_LAYOUT_IN_SCREEN
                        | WindowManager.LayoutParams.FLAG_ALT_FOCUSABLE_IM
                        | WindowManager.LayoutParams.FLAG_SPLIT_TOUCH | WindowManager.LayoutParams.FLAG_HARDWARE_ACCELERATED,
                PixelFormat.TRANSPARENT);
        windowManagerParams.gravity = Gravity.TOP | Gravity.LEFT;
        windowManagerParams.x = 50;// 50
        windowManagerParams.y = 100;// 100

        windowManager = (WindowManager) context.getSystemService(Context.WINDOW_SERVICE);
        DrawCanvas();
        windowManager.addView(frameLayout, windowManagerParams);
    }

    private void enableHotkeys() {
        if (windowManagerParams == null || frameLayout == null)
            return;
        createKeybindOverlay();
        windowManagerParams.flags &= ~WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
        windowManagerParams.flags &= ~WindowManager.LayoutParams.FLAG_ALT_FOCUSABLE_IM;
        windowManager.updateViewLayout(frameLayout, windowManagerParams);
        frameLayout.setFocusable(true);
        frameLayout.setFocusableInTouchMode(true);
        frameLayout.requestFocus();
        frameLayout.post(new Runnable() {
            @Override
            public void run() {
                if (frameLayout != null)
                    frameLayout.requestFocus();
            }
        });
        frameLayout.setOnKeyListener(new View.OnKeyListener() {
            @Override
            public boolean onKey(View v, int keyCode, KeyEvent event) {
                if (event.getAction() != KeyEvent.ACTION_DOWN)
                    return false;

                if (keyCode == KeyEvent.KEYCODE_BACK) {
                    if (keybindDialogShowing && pendingKeybindId != null) {
                        int cancelledId = pendingKeybindId;
                        pendingKeybindId = null;
                        keybindDialogShowing = false;
                        TextView tv = idToKeybindTv.get(cancelledId);
                        if (tv != null) {
                            int k = getKeybindForId(cancelledId);
                            tv.setText(k != -1 ? keyCodeToLabel(k) : "NONE");
                        }
                        Toast.makeText(context, "Key selection cancelled", Toast.LENGTH_SHORT).show();
                        if (!keybindEnabled) {
                            disableHotkeys();
                        }
                        return true;
                    }
                    // Handle BACK button to minimize menu
                    if (container_menu != null && icon_cheat != null && container_menu.getVisibility() == View.VISIBLE) {
                        container_menu.setVisibility(View.GONE);
                        icon_cheat.setVisibility(View.VISIBLE);
                        if (!keybindEnabled) {
                            disableHotkeys();
                        }
                        return true;
                    }
                }

                if (keybindDialogShowing && pendingKeybindId != null) {
                    int targetId = pendingKeybindId;
                    pendingKeybindId = null;
                    keybindDialogShowing = false;
                    setKeybindForId(targetId, keyCode);
                    TextView tv = idToKeybindTv.get(targetId);
                    if (tv != null) {
                        tv.setText(keyCodeToLabel(keyCode));
                    }
                    Toast.makeText(context, "Key set: " + keyCodeToLabel(keyCode), Toast.LENGTH_SHORT).show();
                    if (!keybindEnabled) {
                        disableHotkeys();
                    } else {
                        enableHotkeys();
                    }
                    return true;
                }
                if (keybindDialogShowing)
                    return false;
                if (!keybindEnabled)
                    return false;

                boolean handled = false;
                for (Map.Entry<Integer, Integer> entry : new HashMap<>(idToKeyCode).entrySet()) {
                    if (entry.getValue() != null && entry.getValue() == keyCode) {
                        int id = entry.getKey();
                        SwitchStyle sw = idToBindSwitch.get(id);
                        if (sw != null) {
                            sw.toggle();
                            handled = true;
                        }
                    }
                }
                return handled;
            }
        });
        updateKeybindOverlay();
    }

    private void createKeybindOverlay() {
        if (keybindOverlay != null)
            return;
        int LAYOUT_FLAG = Build.VERSION.SDK_INT >= Build.VERSION_CODES.O
                ? WindowManager.LayoutParams.TYPE_APPLICATION_OVERLAY
                : WindowManager.LayoutParams.TYPE_PHONE;
        keybindOverlay = new LinearLayout(context);
        keybindOverlay.setOrientation(LinearLayout.VERTICAL);
        keybindOverlay.setPadding(utils.FixDP(8), utils.FixDP(6), utils.FixDP(8), utils.FixDP(6));
        keybindOverlay.setMinimumWidth(utils.FixDP(60));
        GradientDrawable keybindBg = new GradientDrawable();
        keybindBg.setCornerRadius(utils.FixDP(6));
        keybindBg.setColor(0xFF181818);
        keybindBg.setStroke(utils.FixDP(1), 0xFF4A1515);
        keybindOverlay.setBackground(keybindBg);

        // Removed KEYBINDS header title view

        keybindList = new LinearLayout(context);
        keybindList.setOrientation(LinearLayout.VERTICAL);
        keybindOverlay.addView(keybindList);

        keybindOverlayParams = new WindowManager.LayoutParams(
                WindowManager.LayoutParams.WRAP_CONTENT, WindowManager.LayoutParams.WRAP_CONTENT,
                LAYOUT_FLAG,
                WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE | WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL,
                PixelFormat.TRANSPARENT);
        keybindOverlayParams.gravity = Gravity.TOP | Gravity.LEFT;
        keybindOverlayParams.x = utils.FixDP(8);
        keybindOverlayParams.y = utils.FixDP(12);

        keybindOverlay.setOnTouchListener(new View.OnTouchListener() {
            private int startX, startY;
            private int startParamsX, startParamsY;

            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        startX = (int) event.getRawX();
                        startY = (int) event.getRawY();
                        startParamsX = keybindOverlayParams.x;
                        startParamsY = keybindOverlayParams.y;
                        return true;
                    case MotionEvent.ACTION_MOVE:
                        keybindOverlayParams.x = startParamsX + (int) event.getRawX() - startX;
                        keybindOverlayParams.y = startParamsY + (int) event.getRawY() - startY;
                        windowManager.updateViewLayout(keybindOverlay, keybindOverlayParams);
                        return true;
                    default:
                        return false;
                }
            }
        });
        windowManager.addView(keybindOverlay, keybindOverlayParams);
        updateKeybindOverlay();
    }

    public void updateKeybindOverlay() {
        if (keybindOverlay == null) {
            if ((showKeybindStatus || showMatchTimer) && menuInstance != null) {
                createKeybindOverlay();
            } else {
                return;
            }
        }
        if (keybindList == null)
            return;
        keybindList.removeAllViews();
        if (!showKeybindStatus && !showMatchTimer) {
            keybindOverlay.setVisibility(View.GONE);
            stopKeybindOverlayRefresh();
            return;
        }

        if (showMatchTimer) {
            int[] timerStatus = null;
            try {
                timerStatus = getMatchTimerStatus();
            } catch (Throwable ignored) {
            }
            int ma = (timerStatus != null && timerStatus.length >= 2) ? timerStatus[0] : 0;
            int rem = (timerStatus != null && timerStatus.length >= 2) ? timerStatus[1] : -1;
            String timerText;
            int timerColor = Color.WHITE;
            if (ma != 1) {
                timerText = "ESP Timer: Invalid Timer (Time )";
                timerColor = 0xFFFF4444;
            } else if (rem <= 0) {
                timerText = "ESP Timer: Invalid Timer (Time )";
                timerColor = 0xFFFF4444;
            } else {
                int mm = rem / 60, ss = rem % 60;
                timerText = "ESP Timer: " + String.format("%02d:%02d", mm, ss);
                if (rem > 120)
                    timerColor = 0xFF00FF88;
                else if (rem > 60)
                    timerColor = 0xFFFFFF33;
                else
                    timerColor = 0xFFFF9900;
            }

            TextView creditHeader = new TextView(context);
            creditHeader.setText("\u2605 BanAimKill \u2605");
            creditHeader.setTextSize(9);
            creditHeader.setTypeface(Typeface.DEFAULT_BOLD);
            creditHeader.setTextColor(0xFF00E5FF);
            creditHeader.setPadding(0, utils.FixDP(2), 0, utils.FixDP(2));
            keybindList.addView(creditHeader);

            TextView timerRow = new TextView(context);
            timerRow.setTextSize(8);
            timerRow.setPadding(utils.FixDP(4), 0, 0, utils.FixDP(6));
            timerRow.setTextColor(timerColor);
            timerRow.setTypeface(Typeface.MONOSPACE);
            timerRow.setText(timerText);
            keybindList.addView(timerRow);

            View lineBreak = new View(context);
            LinearLayout.LayoutParams lbParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, utils.FixDP(1));
            lbParams.setMargins(0, 0, 0, utils.FixDP(4));
            lineBreak.setLayoutParams(lbParams);
            lineBreak.setBackgroundColor(0x22FFFFFF);
            keybindList.addView(lineBreak);
        }

        if (showKeybindStatus) {
            for (Map.Entry<Integer, SwitchStyle> e : new HashMap<>(idToBindSwitch).entrySet()) {
                int id = e.getKey();
                SwitchStyle sw = e.getValue();
                if (sw == null)
                    continue;
                Integer keyCode = idToKeyCode.get(id);
                if (keyCode == null || keyCode == -1)
                    continue;
                String name = idToName.get(id);
                if (name == null)
                    name = "ID " + id;
                String keyLabel = keyCodeToLabel(keyCode);
                boolean isOn = sw.isChecked();

                TextView row = new TextView(context);
                row.setTextSize(7);
                row.setPadding(0, utils.FixDP(1), 0, utils.FixDP(1));
                row.setTextColor(isOn ? 0xFFFFFFFF : 0xFF666666);
                row.setText(name + "  [" + keyLabel + "]");
                keybindList.addView(row);
            }
        }
        keybindOverlay.setVisibility(View.VISIBLE);
        if (keybindOverlayRefreshRunnable == null)
            startKeybindOverlayRefresh();
    }

    private void startKeybindOverlayRefresh() {
        if (keybindOverlayRefreshRunnable != null)
            return;
        keybindOverlayRefreshRunnable = new Runnable() {
            @Override
            public void run() {
                if ((!showKeybindStatus && !showMatchTimer) || keybindOverlay == null
                        || keybindOverlay.getVisibility() != View.VISIBLE) {
                    keybindOverlayRefreshRunnable = null;
                    return;
                }
                updateKeybindOverlay();
                keybindOverlayHandler.postDelayed(this, 1000);
            }
        };
        keybindOverlayHandler.postDelayed(keybindOverlayRefreshRunnable, 1000);
    }

    private void stopKeybindOverlayRefresh() {
        if (keybindOverlayRefreshRunnable != null) {
            keybindOverlayHandler.removeCallbacks(keybindOverlayRefreshRunnable);
            keybindOverlayRefreshRunnable = null;
        }
    }

    private void disableHotkeys() {
        if (windowManagerParams == null || frameLayout == null)
            return;
        frameLayout.setOnKeyListener(null);
        frameLayout.setFocusable(false);
        frameLayout.setFocusableInTouchMode(false);
        windowManagerParams.flags |= WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
        windowManager.updateViewLayout(frameLayout, windowManagerParams);
    }

    /**
     * F1/F2 etc keys ke liye focus ensure karo - keybind set karte waqt call karo
     */
    public void requestKeybindFocus() {
        if (frameLayout == null)
            return;
        frameLayout.requestFocus();
        frameLayout.post(new Runnable() {
            @Override
            public void run() {
                if (frameLayout != null) {
                    frameLayout.requestFocus();
                    frameLayout.postDelayed(new Runnable() {
                        @Override
                        public void run() {
                            if (frameLayout != null)
                                frameLayout.requestFocus();
                        }
                    }, 150);
                }
            }
        });
    }

    // OnTouchListener for menu
    private View.OnTouchListener onTouchListener() {
        return new View.OnTouchListener() {
            private static final int TOUCH_MOVE_THRESHOLD = 8;
            private int x;
            private int y;
            private int initialX;
            private int initialY;
            private boolean isMoving = false;

            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        x = (int) event.getRawX();
                        y = (int) event.getRawY();
                        initialX = x;
                        initialY = y;
                        isMoving = false;
                        frameLayout.setAlpha(1.0f);
                        return true;

                    case MotionEvent.ACTION_MOVE:
                        int nowX = (int) event.getRawX();
                        int nowY = (int) event.getRawY();

                        int totalMoveX = Math.abs(nowX - initialX);
                        int totalMoveY = Math.abs(nowY - initialY);

                        if (!isMoving && (totalMoveX > TOUCH_MOVE_THRESHOLD || totalMoveY > TOUCH_MOVE_THRESHOLD)) {
                            isMoving = true;
                        }

                        if (isMoving) {
                            int movedX = nowX - x;
                            int movedY = nowY - y;
                            x = nowX;
                            y = nowY;
                            windowManagerParams.x = windowManagerParams.x + movedX;
                            windowManagerParams.y = windowManagerParams.y + movedY;
                            windowManager.updateViewLayout(frameLayout, windowManagerParams);
                        }
                        return true;

                    case MotionEvent.ACTION_UP:
                        if (!isMoving) {
                            v.performClick();
                        }
                        frameLayout.setAlpha(1.0f);
                        return true;

                    default:
                        break;
                }
                return false;
            }
        };
    }

    // -------------------- NEW TAB METHODS --------------------

    /**
     * Create a new tab and its content container
     *
     * @param tabName name of the tab
     */
    private static GradientDrawable getGlowingTabDrawable(boolean isSelected) {
        GradientDrawable tabBg;
        if (isSelected) {
            // Active tab: solid fill with gradient + subtle glow border
            tabBg = new GradientDrawable(
                    GradientDrawable.Orientation.LEFT_RIGHT,
                    new int[]{0xFFE53935, 0xFFFF5252});
            tabBg.setCornerRadius(utils.FixDP(9));
            tabBg.setStroke(utils.FixDP(1), 0x55FF8A80);
        } else {
            // Inactive tab: transparent with very subtle border
            tabBg = new GradientDrawable();
            tabBg.setCornerRadius(utils.FixDP(9));
            tabBg.setColor(0x00000000);
            tabBg.setStroke(0, 0x00000000);
        }
        return tabBg;
    }

    public static void addTab(final String tabName) {
        final boolean isFirstTab = tabButtons.isEmpty();

        if (menuFont == null) {
            try {
                menuFont = Typeface.createFromAsset(context.getAssets(), "kcfonts/ethnocentric.ttf");
            } catch (Exception e) {
                menuFont = Typeface.create("sans-serif-black", Typeface.BOLD);
            }
        }

        final TextView tabButton = new TextView(context);
        LinearLayout.LayoutParams tabParams = new LinearLayout.LayoutParams(
                0, utils.FixDP(32), 1.0f);
        tabParams.setMargins(utils.FixDP(2), 0, utils.FixDP(2), 0);
        tabButton.setLayoutParams(tabParams);
        tabButton.setText(tabName.toUpperCase());
        tabButton.setTextSize(9);
        tabButton.setLetterSpacing(0.08f);
        tabButton.setTypeface(menuFont != null ? menuFont : Typeface.DEFAULT_BOLD);
        tabButton.setGravity(Gravity.CENTER);
        tabButton.setPadding(utils.FixDP(6), 0, utils.FixDP(6), 0);
        tabButton.setSingleLine(true);
        tabButton.setEllipsize(android.text.TextUtils.TruncateAt.END);

        tabButton.setBackground(getGlowingTabDrawable(isFirstTab));
        tabButton.setTextColor(isFirstTab ? 0xFFFFFFFF : 0xFF555566);

        tabButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                selectTab(tabName);
            }
        });

        tabButtons.add(tabButton);
        tabsContainer.addView(tabButton);

        LinearLayout tabContent = new LinearLayout(context);
        tabContent.setLayoutParams(new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.WRAP_CONTENT));
        tabContent.setOrientation(LinearLayout.VERTICAL);
        tabContent.setPadding(0, utils.FixDP(4), 0, 0);
        tabContent.setVisibility(isFirstTab ? View.VISIBLE : View.GONE);

        tabContentContainers.put(tabName, tabContent);
        featuresScrollContainer.addView(tabContent);

        if (isFirstTab) {
            currentTab = tabName;
        }
        populateTab = tabName;
    }

    /**
     * Select a tab and show its content
     *
     * @param tabName name of the tab to select
     */
    private static void selectTab(String tabName) {
        if (tabName.equals(currentTab)) return;

        for (TextView tabButton : tabButtons) {
            boolean isSelected = tabButton.getText().toString().equalsIgnoreCase(tabName);
            tabButton.setBackground(getGlowingTabDrawable(isSelected));
            tabButton.setTextColor(isSelected ? 0xFFFFFFFF : 0xFF555566);
            // Subtle scale animation for selected tab
            if (isSelected) {
                tabButton.animate().scaleX(1.0f).scaleY(1.0f).setDuration(200).start();
            } else {
                tabButton.animate().scaleX(0.95f).scaleY(0.95f).setDuration(200).start();
            }
        }

        for (Map.Entry<String, LinearLayout> entry : tabContentContainers.entrySet()) {
            boolean visible = entry.getKey().equals(tabName);
            LinearLayout content = entry.getValue();
            if (visible) {
                content.setVisibility(View.VISIBLE);
                content.setAlpha(0f);
                content.animate().alpha(1f).setDuration(250).start();
            } else {
                content.setVisibility(View.GONE);
            }
        }

        currentTab = tabName;
    }

    /**
     * Add a category heading within the current tab (Aim Hacks, Mark Pos style -
     * image jaisa)
     */
    public static void addCategory(String name) {
        if (populateTab.isEmpty() || !tabContentContainers.containsKey(populateTab)) return;

        LinearLayout catWrapper = new LinearLayout(context);
        LinearLayout.LayoutParams catLp = new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, utils.FixDP(22));
        catLp.setMargins(utils.FixDP(10), utils.FixDP(6), utils.FixDP(10), utils.FixDP(2));
        catWrapper.setLayoutParams(catLp);
        catWrapper.setOrientation(LinearLayout.HORIZONTAL);
        catWrapper.setGravity(Gravity.CENTER_VERTICAL);

        View accentBar = new View(context);
        accentBar.setLayoutParams(new LinearLayout.LayoutParams(utils.FixDP(2), utils.FixDP(12)));
        accentBar.setBackgroundColor(PrimaryColor);
        accentBar.setPadding(0, 0, utils.FixDP(4), 0);

        TextView textView = new TextView(context);
        textView.setText(name);
        textView.setTextSize(8);
        textView.setTextColor(0xFF999999);
        textView.setTypeface(null, Typeface.BOLD);
        textView.setPadding(utils.FixDP(6), 0, 0, 0);

        catWrapper.addView(accentBar);
        catWrapper.addView(textView);
        tabContentContainers.get(populateTab).addView(catWrapper);
    }

    /**
     * Add a switch to the current tab
     */
    public static void addSwitchWithCheckbox(String name, final int mainID, final int subID) {
        if (populateTab.isEmpty() || !tabContentContainers.containsKey(populateTab)) return;

        LinearLayout cardWrapper = new LinearLayout(context);
        LinearLayout.LayoutParams wrapperLp = new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        wrapperLp.setMargins(utils.FixDP(10), utils.FixDP(4), utils.FixDP(10), utils.FixDP(4));
        cardWrapper.setLayoutParams(wrapperLp);

        GradientDrawable cardBg = new GradientDrawable();
        cardBg.setColor(0xFF0F0F0F);
        cardBg.setCornerRadius(utils.FixDP(14));
        cardBg.setStroke(utils.FixDP(1), 0xFF1E1E1E);
        cardWrapper.setBackground(cardBg);

        LinearLayout card = new LinearLayout(context);
        card.setLayoutParams(new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, utils.FixDP(50)));
        card.setPadding(utils.FixDP(16), 0, utils.FixDP(14), 0);
        card.setOrientation(LinearLayout.HORIZONTAL);
        card.setGravity(Gravity.CENTER_VERTICAL);

        LinearLayout linearLayout = new LinearLayout(context);
        linearLayout.setLayoutParams(new LinearLayout.LayoutParams(
                0, ViewGroup.LayoutParams.WRAP_CONTENT, 1));
        linearLayout.setOrientation(LinearLayout.VERTICAL);
        linearLayout.setGravity(Gravity.CENTER_VERTICAL);

        final TextView textView = new TextView(context);
        textView.setLayoutParams(new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        textView.setText(name.toUpperCase());
        textView.setTextColor(PrimaryColor);
        textView.setTextSize(11);
        textView.setTypeface(Typeface.create("sans-serif-bold", Typeface.BOLD));

        final TextView subDesc = new TextView(context);
        subDesc.setLayoutParams(new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        subDesc.setText("Toggle " + name);
        subDesc.setTextColor(0xFF888888);
        subDesc.setTextSize(8);

        linearLayout.addView(textView);
        linearLayout.addView(subDesc);

        final CheckBox subBox = new CheckBox(context);
        LinearLayout.LayoutParams subLp = new LinearLayout.LayoutParams(utils.FixDP(24), utils.FixDP(24));
        subLp.setMargins(0, 0, utils.FixDP(4), 0);
        subBox.setLayoutParams(subLp);
        subBox.setPadding(0, 0, 0, 0);
        subBox.setScaleX(0.75f);
        subBox.setScaleY(0.75f);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            subBox.setButtonTintList(ColorStateList.valueOf(PrimaryColor));
        }
        subBox.setChecked(false);
        subBox.setOnCheckedChangeListener(new android.widget.CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(android.widget.CompoundButton buttonView, boolean isChecked) {
                ChangesID(subID, isChecked ? 1 : 0);
            }
        });

        final TextView keybindTv = new TextView(context);
        LinearLayout.LayoutParams keybindLp = new LinearLayout.LayoutParams(utils.FixDP(44), utils.FixDP(20));
        keybindLp.setMargins(0, 0, utils.FixDP(6), 0);
        keybindTv.setLayoutParams(keybindLp);
        keybindTv.setGravity(Gravity.CENTER);
        keybindTv.setTextSize(10);
        keybindTv.setTypeface(Typeface.create("sans-serif-bold", Typeface.BOLD));

        int savedKey = getKeybindForId(mainID);
        if (savedKey != -1) {
            idToKeyCode.put(mainID, savedKey);
            keybindTv.setText(keyCodeToLabel(savedKey));
        } else {
            keybindTv.setText("NONE");
        }
        updateKeybindTvColor(keybindTv, keybindTv.getText().toString());
        idToKeybindTv.put(mainID, keybindTv);
        keybindTv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                keybindTv.setText("Press");
                updateKeybindTvColor(keybindTv, "Press");
                pendingKeybindId = mainID;
                keybindDialogShowing = true;
                if (menuInstance != null) {
                    menuInstance.enableHotkeys();
                    menuInstance.requestKeybindFocus();
                }
            }
        });
        keybindTv.setVisibility(keybindEnabled ? View.VISIBLE : View.GONE);
        allKeybindButtons.add(keybindTv);

        final CheckBox customCheckbox = new CheckBox(context);
        LinearLayout.LayoutParams chkLp = new LinearLayout.LayoutParams(utils.FixDP(22), utils.FixDP(22));
        customCheckbox.setLayoutParams(chkLp);
        customCheckbox.setButtonDrawable(new android.graphics.drawable.ColorDrawable(Color.TRANSPARENT));
        final CustomCheckboxDrawable chkDrawable = new CustomCheckboxDrawable(PrimaryColor);
        customCheckbox.setBackground(chkDrawable);
        customCheckbox.setClickable(false);
        customCheckbox.setOnCheckedChangeListener(new android.widget.CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(android.widget.CompoundButton buttonView, boolean isChecked) {
                chkDrawable.setChecked(isChecked);
                setShimmer(textView, isChecked);
            }
        });

        final SwitchStyle switchStyle = new SwitchStyle(context);
        switchStyle.setLayoutParams(new LinearLayout.LayoutParams(utils.FixDP(40), utils.FixDP(20)));
        idToBindSwitch.put(mainID, switchStyle);
        idToName.put(mainID, name);
        switchStyle.setVisibility(View.GONE);
        switchStyle.setOnCheckedChangeListener(new SwitchStyle.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(final SwitchStyle view, boolean isChecked) {
                customCheckbox.setChecked(isChecked);
                ChangesID(mainID, isChecked ? 1 : 0);
            }
        });

        View.OnClickListener toggleOnClick = new View.OnClickListener() {
            @Override
            public void onClick(View view) { switchStyle.toggle(); }
        };
        card.setOnClickListener(toggleOnClick);
        linearLayout.setOnClickListener(toggleOnClick);

        card.addView(linearLayout);
        card.addView(subBox);
        card.addView(keybindTv);
        card.addView(customCheckbox);
        card.addView(switchStyle);
        cardWrapper.addView(card);
        tabContentContainers.get(populateTab).addView(cardWrapper, wrapperLp);
    }

    public static void addSwitch(String name, final int ID) {
        if (populateTab.isEmpty() || !tabContentContainers.containsKey(populateTab)) return;

        LinearLayout cardWrapper = new LinearLayout(context);
        LinearLayout.LayoutParams wrapperLp = new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        wrapperLp.setMargins(utils.FixDP(10), utils.FixDP(4), utils.FixDP(10), utils.FixDP(4));
        cardWrapper.setLayoutParams(wrapperLp);

        GradientDrawable cardBg = new GradientDrawable();
        cardBg.setColor(0xFF0F0F0F);
        cardBg.setCornerRadius(utils.FixDP(14));
        cardBg.setStroke(utils.FixDP(1), 0xFF1E1E1E);
        cardWrapper.setBackground(cardBg);

        LinearLayout card = new LinearLayout(context);
        card.setLayoutParams(new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, utils.FixDP(50)));
        card.setPadding(utils.FixDP(16), 0, utils.FixDP(14), 0);
        card.setOrientation(LinearLayout.HORIZONTAL);
        card.setGravity(Gravity.CENTER_VERTICAL);

        LinearLayout linearLayout = new LinearLayout(context);
        linearLayout.setLayoutParams(new LinearLayout.LayoutParams(
                0, ViewGroup.LayoutParams.WRAP_CONTENT, 1));
        linearLayout.setOrientation(LinearLayout.VERTICAL);
        linearLayout.setGravity(Gravity.CENTER_VERTICAL);

        final TextView textView = new TextView(context);
        textView.setLayoutParams(new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        textView.setText(name.toUpperCase());
        textView.setTextColor(PrimaryColor);
        textView.setTextSize(11);
        textView.setTypeface(Typeface.create("sans-serif-bold", Typeface.BOLD));

        final TextView subDesc = new TextView(context);
        subDesc.setLayoutParams(new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        String descStr = name;
        if (name.equalsIgnoreCase("ENABLE FUNCTIONS")) descStr = "Main Hack Enable";
        else if (name.equalsIgnoreCase("NOVA NEW")) descStr = "Auto Kill";
        else if (name.equalsIgnoreCase("GAME SPEED")) descStr = "Increase Game Speed";
        else if (name.equalsIgnoreCase("CHRONO DEFENDER")) descStr = "Pull enemy out of Chrono shield";
        else if (name.equalsIgnoreCase("AUTO SWITCH")) descStr = "Auto Weapon Switch";
        subDesc.setText(descStr);
        subDesc.setTextColor(0xFF888888);
        subDesc.setTextSize(8);

        final TextView keybindTv = new TextView(context);
        LinearLayout.LayoutParams keybindLp = new LinearLayout.LayoutParams(utils.FixDP(44), utils.FixDP(20));
        keybindLp.setMargins(0, 0, utils.FixDP(6), 0);
        keybindTv.setLayoutParams(keybindLp);
        keybindTv.setGravity(Gravity.CENTER);
        keybindTv.setTextSize(10);
        keybindTv.setTypeface(Typeface.create("sans-serif-bold", Typeface.BOLD));

        int savedKey = getKeybindForId(ID);
        if (savedKey != -1) {
            idToKeyCode.put(ID, savedKey);
            keybindTv.setText(keyCodeToLabel(savedKey));
        } else {
            keybindTv.setText("NONE");
        }
        updateKeybindTvColor(keybindTv, keybindTv.getText().toString());
        idToKeybindTv.put(ID, keybindTv);

        keybindTv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                keybindTv.setText("Press");
                updateKeybindTvColor(keybindTv, "Press");
                pendingKeybindId = ID;
                keybindDialogShowing = true;
                if (menuInstance != null) {
                    menuInstance.enableHotkeys();
                    menuInstance.requestKeybindFocus();
                }
                new android.os.Handler(android.os.Looper.getMainLooper()).postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        if (pendingKeybindId != null && pendingKeybindId == ID) {
                            pendingKeybindId = null;
                            keybindDialogShowing = false;
                            TextView tv = idToKeybindTv.get(ID);
                            if (tv != null) {
                                int k = getKeybindForId(ID);
                                tv.setText(k != -1 ? keyCodeToLabel(k) : "NONE");
                                updateKeybindTvColor(tv, tv.getText().toString());
                            }
                            Toast.makeText(context, "Key selection cancelled", Toast.LENGTH_SHORT).show();
                            if (menuInstance != null && !keybindEnabled) {
                                menuInstance.disableHotkeys();
                            }
                        }
                    }
                }, 10000);
            }
        });

        keybindTv.setVisibility(
                keybindEnabled && ID != ID_TURN_ON_KEYBIND && ID != ID_SHOW_KEYBIND_STATUS && ID != ID_SHOW_MATCH_TIMER
                        ? View.VISIBLE
                        : View.GONE);
        if (ID != ID_TURN_ON_KEYBIND && ID != ID_SHOW_KEYBIND_STATUS && ID != ID_SHOW_MATCH_TIMER) {
            allKeybindButtons.add(keybindTv);
        }

        final CheckBox customCheckbox = new CheckBox(context);
        LinearLayout.LayoutParams chkLp = new LinearLayout.LayoutParams(utils.FixDP(22), utils.FixDP(22));
        customCheckbox.setLayoutParams(chkLp);
        customCheckbox.setButtonDrawable(new android.graphics.drawable.ColorDrawable(Color.TRANSPARENT));
        final CustomCheckboxDrawable chkDrawable = new CustomCheckboxDrawable(PrimaryColor);
        customCheckbox.setBackground(chkDrawable);
        customCheckbox.setClickable(false);
        customCheckbox.setOnCheckedChangeListener(new android.widget.CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(android.widget.CompoundButton buttonView, boolean isChecked) {
                chkDrawable.setChecked(isChecked);
                // Subtle border glow when enabled
                cardBg.setStroke(utils.FixDP(1), isChecked ? 0x33E53935 : 0xFF1E1E1E);
                setShimmer(textView, isChecked);
            }
        });

        idToName.put(ID, name);

        final SwitchStyle switchStyle = new SwitchStyle(context);
        switchStyle.setLayoutParams(new LinearLayout.LayoutParams(
                utils.FixDP(42),
                utils.FixDP(21)));
        idToBindSwitch.put(ID, switchStyle);
        switchStyle.setVisibility(View.GONE);
        // Add active line state logic
        switchStyle.setOnCheckedChangeListener(new SwitchStyle.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(final SwitchStyle view, boolean isChecked) {
                customCheckbox.setChecked(isChecked);

                // --- ENABLE ALL ESP MACRO (ID 102) ---
                if (ID == 102 && isChecked && !isLinkingHacks) {
                    isLinkingHacks = true;
                    int[] espIds = {1, 2, 3, 9, 4, 16};
                    for (int espId : espIds) {
                        SwitchStyle espSwitch = idToBindSwitch.get(espId);
                        if (espSwitch != null && !espSwitch.isChecked()) {
                            espSwitch.setChecked(true);
                            ChangesID(espId, 1); // Ensure native activation
                        }
                    }
                    isLinkingHacks = false;
                }

                if (ID == ID_CLEAR_KEYBINDS && isChecked) {
                    clearAllKeybinds();
                    Toast.makeText(context, "Keybinds cleared", Toast.LENGTH_SHORT).show();
                    new android.os.Handler(android.os.Looper.getMainLooper()).postDelayed(new Runnable() {
                        @Override
                        public void run() { view.setChecked(false); }
                    }, 300);
                    return;
                }
                if (ID == ID_TURN_ON_KEYBIND) {
                    keybindEnabled = isChecked;
                    for (TextView kbv : allKeybindButtons) {
                        kbv.setVisibility(isChecked ? View.VISIBLE : View.GONE);
                    }
                    try {
                        getKeybindPrefs().edit().putBoolean(PREF_KEYBIND_ENABLED, isChecked).apply();
                    } catch (Throwable ignored) {
                    }
                    if (menuInstance != null) {
                        if (isChecked)
                            menuInstance.enableHotkeys();
                        else
                            menuInstance.disableHotkeys();
                    }
                }
                if (ID == ID_SHOW_KEYBIND_STATUS) {
                    showKeybindStatus = isChecked;
                    try {
                        getKeybindPrefs().edit().putBoolean(PREF_KEYBIND_STATUS, isChecked).apply();
                    } catch (Throwable ignored) {
                    }
                    if (menuInstance != null)
                        menuInstance.updateKeybindOverlay();
                }
                if (ID == ID_SHOW_MATCH_TIMER) {
                    showMatchTimer = isChecked;
                    if (menuInstance != null)
                        menuInstance.updateKeybindOverlay();
                }

                // --- Fly and Speed Auto-Toggle Logic ---
                if ((ID == 111 || ID == 5001) && !isLinkingHacks) {
                    isLinkingHacks = true;

                    if (ID == 5001) {
                        if (isChecked) {
                            // --- SPECIAL SEQUENCE: Snap Fly ON (500ms) ---
                            // 1. Turn OFF Speeds immediately
                            SwitchStyle sTimer = idToBindSwitch.get(517);
                            if (sTimer != null && sTimer.isChecked()) { speedTimerAutoOffed = true; sTimer.setChecked(false); }

                            // 2. Turn ON Flyhack immediately
                            SwitchStyle fh = idToBindSwitch.get(111);
                            if (fh != null && !fh.isChecked()) fh.setChecked(true);

                            // 3. Delay Snap Fly Native Activation
                            new android.os.Handler(android.os.Looper.getMainLooper()).postDelayed(new Runnable() {
                                @Override
                                public void run() {
                                    isLinkingHacks = true;
                                    ChangesID(5001, 1);
                                    if (menuInstance != null) menuInstance.updateKeybindOverlay();
                                    isLinkingHacks = false;
                                }
                            }, 300);

                            isLinkingHacks = false;
                            return;
                        } else {
                            // --- SPECIAL SEQUENCE: Snap Fly OFF (300ms) ---
                            // 1. Immediately turn OFF Snap Fly Native
                            ChangesID(5001, 0);
                            if (menuInstance != null) menuInstance.updateKeybindOverlay();

                            // 2. Delay before Flyhack OFF and Speed Restoration (Now Instant)
                            new android.os.Handler(android.os.Looper.getMainLooper()).postDelayed(new Runnable() {
                                @Override
                                public void run() {
                                    isLinkingHacks = true;
                                    SwitchStyle fh = idToBindSwitch.get(111);
                                    if (fh != null && fh.isChecked()) {
                                        fh.setChecked(false); // This will trigger restoration of speeds in the Flyhack logic leg
                                    }
                                    isLinkingHacks = false;
                                }
                            }, 1000);

                            isLinkingHacks = false;
                            return;
                        }
                    }

                    // --- NORMAL LOGIC: For Flyhack (ID 111) ---
                    // Determine if ANY fly hack is active (using fresh 'isChecked' for 111)
                    boolean f1Status = (ID == 111) ? isChecked : (idToBindSwitch.get(111) != null && idToBindSwitch.get(111).isChecked());
                    boolean f2Status = (ID == 5001) ? isChecked : (idToBindSwitch.get(5001) != null && idToBindSwitch.get(5001).isChecked());
                    boolean anyFlyActive = f1Status || f2Status;

                    if (anyFlyActive) {
                        SwitchStyle sTimer = idToBindSwitch.get(517);
                        if (sTimer != null && sTimer.isChecked()) {
                            speedTimerAutoOffed = true;
                            sTimer.setChecked(false);
                        }
                    } else {
                        if (speedTimerAutoOffed) {
                            SwitchStyle sTimer = idToBindSwitch.get(517);
                            if (sTimer != null && !sTimer.isChecked()) sTimer.setChecked(true);
                            speedTimerAutoOffed = false;
                        }
                    }
                    isLinkingHacks = false;
                }
                // ----------------------------------------
                // --- MARK TELEPORT SEQUENCE ---
                if (ID == 56578 && isChecked && !isTeleportingSequence) {
                    isTeleportingSequence = true;
                    // 1. Snap Fly ON immediately
                    SwitchStyle snapFly = idToBindSwitch.get(5001);
                    if (snapFly != null && !snapFly.isChecked()) {
                        snapFly.setChecked(true);
                    }

                    // 2. Wait 600ms (Adjusted from 1s for better response)
                    new android.os.Handler(android.os.Looper.getMainLooper()).postDelayed(new Runnable() {
                        @Override
                        public void run() {
                            // 3. Mark Teleport ON (Native)
                            ChangesID(56578, 1);

                            // 4. Wait 100ms (Old project timing for teleport hold)
                            new android.os.Handler(android.os.Looper.getMainLooper()).postDelayed(new Runnable() {
                                @Override
                                public void run() {
                                    // 5. Reset flag first
                                    isTeleportingSequence = false;

                                    // 6. Reset UI Switch (Teleport OFF)
                                    SwitchStyle markTele = idToBindSwitch.get(56578);
                                    if (markTele != null && markTele.isChecked()) {
                                        markTele.setChecked(false);
                                    }

                                    // 7. Wait 100ms before dropping (Cleanup delay)
                                    new android.os.Handler(android.os.Looper.getMainLooper()).postDelayed(new Runnable() {
                                        @Override
                                        public void run() {
                                            // 8. Snap Fly OFF
                                            SwitchStyle sf = idToBindSwitch.get(5001);
                                            if (sf != null && sf.isChecked()) {
                                                sf.setChecked(false);
                                            }
                                        }
                                    }, 100);
                                }
                            }, 100);
                        }
                    }, 600);
                    return; // Skip normal ChangesID below
                }

                if (ID == 56578 && !isChecked && isTeleportingSequence) return;

                // --- TELEPORT ENEMY SEQUENCE ---
                if (ID == 5657899 && isChecked && !isTeleportingSequence) {
                    isTeleportingSequence = true;
                    // 1. Snap Fly ON immediately
                    SwitchStyle snapFly = idToBindSwitch.get(5001);
                    if (snapFly != null && !snapFly.isChecked()) {
                        snapFly.setChecked(true);
                    }

                    // 2. Wait 600ms
                    new android.os.Handler(android.os.Looper.getMainLooper()).postDelayed(new Runnable() {
                        @Override
                        public void run() {
                            // 3. Teleport Enemy ON (Native)
                            ChangesID(5657899, 1);

                            // 4. Wait 100ms for stable positioning
                            new android.os.Handler(android.os.Looper.getMainLooper()).postDelayed(new Runnable() {
                                @Override
                                public void run() {
                                    // 5. Reset flag first
                                    isTeleportingSequence = false;

                                    // 6. Reset UI Switch (Teleport Enemy OFF)
                                    SwitchStyle enemyTele = idToBindSwitch.get(5657899);
                                    if (enemyTele != null && enemyTele.isChecked()) {
                                        enemyTele.setChecked(false);
                                    }

                                    // 7. Wait 100ms before dropping
                                    new android.os.Handler(android.os.Looper.getMainLooper()).postDelayed(new Runnable() {
                                        @Override
                                        public void run() {
                                            // 8. Snap Fly OFF
                                            SwitchStyle sf = idToBindSwitch.get(5001);
                                            if (sf != null && sf.isChecked()) {
                                                sf.setChecked(false);
                                            }
                                        }
                                    }, 100);
                                }
                            }, 100);
                        }
                    }, 600);
                    return; // Skip normal ChangesID below
                }

                if (ID == 5657899 && !isChecked && isTeleportingSequence) return;
                // ----------------------------------

                ChangesID(ID, isChecked ? 1 : 0);
                if (menuInstance != null) {
                    menuInstance.updateKeybindOverlay();
                }
            }
        });

        if (ID == ID_TURN_ON_KEYBIND) {
            try {
                switchStyle.setChecked(false);
                keybindEnabled = false;
                getKeybindPrefs().edit().putBoolean(PREF_KEYBIND_ENABLED, false).apply();
            } catch (Throwable ignored) {
                keybindEnabled = false;
            }
        }
        if (ID == ID_SHOW_KEYBIND_STATUS) {
            try {
                boolean savedStatus = getKeybindPrefs().getBoolean(PREF_KEYBIND_STATUS, false);
                if (savedStatus != switchStyle.isChecked()) {
                    switchStyle.setChecked(savedStatus);
                }
                showKeybindStatus = savedStatus;
            } catch (Throwable ignored) {
                showKeybindStatus = switchStyle.isChecked();
            }
        }

        if (ID == 102) {
            switchStyle.setChecked(false);
        }

        View.OnClickListener toggleOnClick = new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                switchStyle.toggle();
            }
        };
        card.setOnClickListener(toggleOnClick);
        linearLayout.setOnClickListener(toggleOnClick);

        linearLayout.addView(textView);
        linearLayout.addView(subDesc);

        card.addView(linearLayout);

        if (ID != ID_TURN_ON_KEYBIND && ID != ID_SHOW_KEYBIND_STATUS && ID != ID_SHOW_MATCH_TIMER) {
            card.addView(keybindTv);
        }

        card.addView(customCheckbox);
        card.addView(switchStyle);

        cardWrapper.addView(card);
        tabContentContainers.get(populateTab).addView(cardWrapper, wrapperLp);
    }

    /**
     * AdiButton - card with label (left) + button (right). Same card style as
     * switch.
     */
    public static void addButton(String label, String buttonText, final int ID) {
        if (populateTab.isEmpty() || !tabContentContainers.containsKey(populateTab)) {
            return;
        }

        // Flat row style for buttons - matching old UI
        LinearLayout card = new LinearLayout(context);
        card.setLayoutParams(new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, utils.FixDP(32)));
        card.setBackgroundColor(MenuBgColor);
        card.setPadding(utils.FixDP(8), 0, utils.FixDP(8), 0);
        card.setOrientation(LinearLayout.HORIZONTAL);
        card.setGravity(Gravity.CENTER_VERTICAL);

        View rowDivider = new View(context);
        rowDivider.setLayoutParams(new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, 1));
        rowDivider.setBackgroundColor(MenuBorderColor);

        LinearLayout row = new LinearLayout(context);
        row.setLayoutParams(new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.WRAP_CONTENT));
        row.setOrientation(LinearLayout.HORIZONTAL);
        row.setGravity(Gravity.CENTER_VERTICAL);

        TextView labelTv = new TextView(context);
        labelTv.setLayoutParams(new LinearLayout.LayoutParams(
                0, ViewGroup.LayoutParams.WRAP_CONTENT, 1));
        labelTv.setGravity(Gravity.CENTER_VERTICAL);
        labelTv.setText(label);
        labelTv.setTextColor(TextSecondaryColor);
        labelTv.setTextSize(9);
        labelTv.setTypeface(null, Typeface.NORMAL);

        // Outlined button
        GradientDrawable btnBg = new GradientDrawable();
        btnBg.setColor(0x33FFFFFF);
        btnBg.setCornerRadius(utils.FixDP(4));
        btnBg.setStroke(utils.FixDP(1), PrimaryColor);

        Button adiBtn = new Button(context);
        LinearLayout.LayoutParams btnLp = new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.WRAP_CONTENT, utils.FixDP(22));
        btnLp.setMargins(utils.FixDP(4), 0, 0, 0);
        adiBtn.setLayoutParams(btnLp);
        adiBtn.setMinWidth(utils.FixDP(60));
        adiBtn.setPadding(utils.FixDP(8), 0, utils.FixDP(8), 0);
        adiBtn.setText(buttonText);
        adiBtn.setTextColor(PrimaryColor);
        adiBtn.setTextSize(9);
        adiBtn.setTypeface(null, Typeface.BOLD);
        adiBtn.setBackground(btnBg);
        adiBtn.setAllCaps(false);
        adiBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (ID == ID_CLEAR_KEYBINDS) {
                    clearAllKeybinds();
                    Toast.makeText(context, "Keybinds cleared", Toast.LENGTH_SHORT).show();
                } else if (ID == 7000) {
                    saveConfig(v.getContext());
                } else if (ID == 7001) {
                    loadConfig(v.getContext());
                } else {
                    ChangesID(ID, 0);
                }
            }
        });

        row.addView(labelTv);
        row.addView(adiBtn);
        card.addView(row);
        tabContentContainers.get(populateTab).addView(card);
        rowDivider = new View(context);
        rowDivider.setLayoutParams(new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, 1));
        rowDivider.setBackgroundColor(MenuBorderColor);
        tabContentContainers.get(populateTab).addView(rowDivider);
    }

    private static void clearAllKeybinds() {
        android.content.SharedPreferences.Editor editor = getKeybindPrefs().edit();
        for (String key : getKeybindPrefs().getAll().keySet()) {
            editor.remove(key);
        }
        editor.apply();
        idToKeyCode.clear();
        for (Map.Entry<Integer, TextView> e : idToKeybindTv.entrySet()) {
            TextView tv = e.getValue();
            if (tv != null)
                tv.setText("None");
        }
    }

    private static void saveConfig(Context context) {
        android.content.SharedPreferences prefs = context.getSharedPreferences("NX999_Config", Context.MODE_PRIVATE);
        android.content.SharedPreferences.Editor editor = prefs.edit();
        for (Map.Entry<Integer, SwitchStyle> entry : idToBindSwitch.entrySet()) {
            editor.putBoolean(String.valueOf(entry.getKey()), entry.getValue().isChecked());
        }
        editor.apply();
        Toast.makeText(context, "Config Saved Successfully", Toast.LENGTH_SHORT).show();
    }

    private static void loadConfig(Context context) {
        android.content.SharedPreferences prefs = context.getSharedPreferences("NX999_Config", Context.MODE_PRIVATE);
        for (Map.Entry<Integer, SwitchStyle> entry : idToBindSwitch.entrySet()) {
            int ID = entry.getKey();
            // Skip SETTING tab or keybind related IDs if needed, but usually it's fine
            if (ID >= 6000 && ID <= 7001) continue;

            boolean isChecked = prefs.getBoolean(String.valueOf(ID), false);
            SwitchStyle s = entry.getValue();
            if (s != null && s.isChecked() != isChecked) {
                s.setChecked(isChecked);
            }
        }
        Toast.makeText(context, "Config Restored", Toast.LENGTH_SHORT).show();
    }

    /**
     * Add a ToggleBind row: Label + Keybind button (click to set key) + Toggle
     * switch.
     * Same card style as switch. Use for Active All etc. - keybind se toggle
     * on/off.
     */
    public static void addToggleBind(String name, final int ID) {
        if (populateTab.isEmpty() || !tabContentContainers.containsKey(populateTab)) {
            return;
        }

        GradientDrawable cardBg = new GradientDrawable();
        cardBg.setColor(0xFF0F0F0F);
        cardBg.setCornerRadius(utils.FixDP(14));
        cardBg.setStroke(utils.FixDP(1), 0xFF1E1E1E);

        LinearLayout card = new LinearLayout(context);
        LinearLayout.LayoutParams cardParams = new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.WRAP_CONTENT);
        cardParams.setMargins(utils.FixDP(10), utils.FixDP(4), utils.FixDP(10), utils.FixDP(4));
        card.setLayoutParams(cardParams);
        card.setBackground(cardBg);
        card.setPadding(utils.FixDP(14), utils.FixDP(8), utils.FixDP(14), utils.FixDP(8));
        card.setOrientation(LinearLayout.HORIZONTAL);
        card.setGravity(Gravity.CENTER_VERTICAL);

        LinearLayout row = new LinearLayout(context);
        row.setLayoutParams(new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.WRAP_CONTENT));
        row.setPadding(0, 0, 0, 0);
        row.setOrientation(LinearLayout.HORIZONTAL);
        row.setGravity(Gravity.CENTER_VERTICAL);

        TextView labelTv = new TextView(context);
        labelTv.setLayoutParams(new LinearLayout.LayoutParams(
                0,
                ViewGroup.LayoutParams.WRAP_CONTENT,
                1));
        labelTv.setGravity(Gravity.CENTER_VERTICAL);
        labelTv.setText(name);
        labelTv.setTextColor(TextPrimaryColor);
        labelTv.setTextSize(8);
        labelTv.setTypeface(Typeface.create("sans-serif", Typeface.NORMAL));
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            labelTv.setLetterSpacing(0.01f);
        }

        // Keybind button - compact, shows [(None)] when no key
        GradientDrawable keybindBtnBg = new GradientDrawable();
        keybindBtnBg.setCornerRadius(utils.FixDP(3));
        keybindBtnBg.setColor(KeybindBtnBgColor);
        keybindBtnBg.setStroke(utils.FixDP(1), KeybindBtnBorderColor);

        final TextView keybindTv = new TextView(context);
        LinearLayout.LayoutParams keybindLp = new LinearLayout.LayoutParams(
                utils.FixDP(50),
                utils.FixDP(20));
        keybindLp.setMargins(utils.FixDP(3), 0, utils.FixDP(3), 0);
        keybindTv.setLayoutParams(keybindLp);
        keybindTv.setGravity(Gravity.CENTER);
        keybindTv.setTextSize(8);
        keybindTv.setTypeface(Typeface.DEFAULT_BOLD);
        keybindTv.setTextColor(0xFFDDDDDD);
        keybindTv.setBackground(keybindBtnBg);
        int savedKey = getKeybindForId(ID);
        if (savedKey != -1) {
            idToKeyCode.put(ID, savedKey);
            keybindTv.setText(keyCodeToLabel(savedKey));
        } else {
            keybindTv.setText("NONE");
        }
        idToKeybindTv.put(ID, keybindTv);
        keybindTv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                keybindTv.setText("Press");
                pendingKeybindId = ID;
                keybindDialogShowing = true;
                if (menuInstance != null) {
                    menuInstance.enableHotkeys();
                    menuInstance.requestKeybindFocus();
                }
                new android.os.Handler(android.os.Looper.getMainLooper()).postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        if (pendingKeybindId != null && pendingKeybindId == ID) {
                            pendingKeybindId = null;
                            keybindDialogShowing = false;
                            TextView tv = idToKeybindTv.get(ID);
                            if (tv != null) {
                                int k = getKeybindForId(ID);
                                tv.setText(k != -1 ? keyCodeToLabel(k) : "NONE");
                            }
                            Toast.makeText(context, "Key selection cancelled", Toast.LENGTH_SHORT).show();
                            if (menuInstance != null && !keybindEnabled) {
                                menuInstance.disableHotkeys();
                            }
                        }
                    }
                }, 10000);
            }
        });

        final SwitchStyle switchStyle = new SwitchStyle(context);
        switchStyle.setLayoutParams(new LinearLayout.LayoutParams(
                utils.FixDP(42),
                utils.FixDP(21)));
        switchStyle.setOnCheckedChangeListener(new SwitchStyle.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(SwitchStyle view, boolean isChecked) {
                ChangesID(ID, isChecked ? 1 : 0);
                if (menuInstance != null)
                    menuInstance.updateKeybindOverlay();
            }
        });
        idToBindSwitch.put(ID, switchStyle);
        idToName.put(ID, name);

        View.OnClickListener toggleOnClick = new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                switchStyle.toggle();
            }
        };
        card.setOnClickListener(toggleOnClick);
        row.setOnClickListener(toggleOnClick);
        labelTv.setOnClickListener(toggleOnClick);

        row.addView(labelTv);
        row.addView(keybindTv);
        row.addView(switchStyle);
        card.addView(row);
        tabContentContainers.get(populateTab).addView(card);
    }

    /**
     * Add a seekbar to the current tab
     */
    public static void addSeekBar(final String name, int value, int max, final String type, final int ID) {
        if (populateTab.isEmpty() || !tabContentContainers.containsKey(populateTab)) {
            return;
        }

        GradientDrawable cardBg = new GradientDrawable();
        cardBg.setColor(0xFF0F0F0F);
        cardBg.setCornerRadius(utils.FixDP(14));
        cardBg.setStroke(utils.FixDP(1), 0xFF1E1E1E);

        LinearLayout card = new LinearLayout(context);
        LinearLayout.LayoutParams cardParams = new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.WRAP_CONTENT);
        cardParams.setMargins(utils.FixDP(10), utils.FixDP(4), utils.FixDP(10), utils.FixDP(4));
        card.setLayoutParams(cardParams);
        card.setBackground(cardBg);
        card.setPadding(utils.FixDP(14), utils.FixDP(8), utils.FixDP(14), utils.FixDP(8));
        card.setOrientation(LinearLayout.VERTICAL);

        LinearLayout linearLayout = new LinearLayout(context);
        linearLayout.setLayoutParams(new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.WRAP_CONTENT));
        linearLayout.setPadding(0, 0, 0, 0);
        linearLayout.setOrientation(LinearLayout.VERTICAL);

        final TextView textView = new TextView(context);
        textView.setText(name.concat(": ") + value + type);
        textView.setTextSize(8);
        textView.setTypeface(Typeface.create("sans-serif", Typeface.NORMAL));
        textView.setTextColor(TextPrimaryColor);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            textView.setLetterSpacing(0.01f);
        }
        if (type.equals("Color")) {
            if (value == 0) {
                textView.setText(Html.fromHtml(name + ": <font color='#ffffff'>" + "White" + "</font>"));
            } else if (value == 1) {
                textView.setText(Html.fromHtml(name + ": <font color='#00FF00'>" + "Green" + "</font>"));
            } else if (value == 2) {
                textView.setText(Html.fromHtml(name + ": <font color='#FF5722'>" + "Orange" + "</font>"));
            } else if (value == 3) {
                textView.setText(Html.fromHtml(name + ": <font color='#FF0000'>" + "Red" + "</font>"));
            } else if (value == 4) {
                textView.setText(Html.fromHtml(name + ": <font color='#000000'>" + "Black" + "</font>"));
            } else if (value == 5) {
                textView.setText(Html.fromHtml(name + ": <font color='#FFFF00'>" + "Yellow" + "</font>"));
            } else if (value == 6) {
                textView.setText(Html.fromHtml(name + ": <font color='#00FFFF'>" + "Cyan" + "</font>"));
            } else if (value == 7) {
                textView.setText(Html.fromHtml(name + ": <font color='#FF00FF'>" + "Magenta" + "</font>"));
            } else if (value == 8) {
                textView.setText(Html.fromHtml(name + ": <font color='#808080'>" + "Gray" + "</font>"));
            } else if (value == 9) {
                textView.setText(Html.fromHtml(name + ": <font color='#A020F0'>" + "Purple" + "</font>"));
            }
        } else if (type.equals("BoxType")) {
            if (value == 0) {
                textView.setText(name.concat(": Normal"));
            } else if (value == 1) {
                textView.setText(name.concat(": 3D"));
            } else if (value == 2) {
                textView.setText(name.concat(": Corner"));
            }
        } else if (type.equals("LineType")) {
            if (value == 0) {
                textView.setText(name.concat(": Top"));
            } else if (value == 1) {
                textView.setText(name.concat(": Center"));
            } else if (value == 2) {
                textView.setText(name.concat(": Bottom"));
            }
        }

        SeekBar seekBar = new SeekBar(context);
        LinearLayout.LayoutParams seekBarParams = new LinearLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                utils.FixDP(16));
        seekBarParams.setMargins(0, utils.FixDP(2), 0, 0);
        seekBar.setLayoutParams(seekBarParams);

        seekBar.getThumb().setColorFilter(PrimaryColor, PorterDuff.Mode.SRC_IN);
        seekBar.getProgressDrawable().setColorFilter(PrimaryColor, PorterDuff.Mode.SRC_IN);

        seekBar.setMax(max);
        if (type.equals("Color")) {
            seekBar.setMax(9);
        } else if (type.equals("BoxType")) {
            seekBar.setMax(2);
        } else if (type.equals("LineType")) {
            seekBar.setMax(2);
        }
        seekBar.setProgress(value);

        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                if (type.equals("Color")) {
                    if (i == 0) {
                        textView.setText(Html.fromHtml(name + ": <font color='#ffffff'>" + "White" + "</font>"));
                    } else if (i == 1) {
                        textView.setText(Html.fromHtml(name + ": <font color='#00FF00'>" + "Green" + "</font>"));
                    } else if (i == 2) {
                        textView.setText(Html.fromHtml(name + ": <font color='#FF5722'>" + "Orange" + "</font>"));
                    } else if (i == 3) {
                        textView.setText(Html.fromHtml(name + ": <font color='#FF0000'>" + "Red" + "</font>"));
                    } else if (i == 4) {
                        textView.setText(Html.fromHtml(name + ": <font color='#000000'>" + "Black" + "</font>"));
                    } else if (i == 5) {
                        textView.setText(Html.fromHtml(name + ": <font color='#FFFF00'>" + "Yellow" + "</font>"));
                    } else if (i == 6) {
                        textView.setText(Html.fromHtml(name + ": <font color='#00FFFF'>" + "Cyan" + "</font>"));
                    } else if (i == 7) {
                        textView.setText(Html.fromHtml(name + ": <font color='#FF00FF'>" + "Magenta" + "</font>"));
                    } else if (i == 8) {
                        textView.setText(Html.fromHtml(name + ": <font color='#808080'>" + "Gray" + "</font>"));
                    } else if (i == 9) {
                        textView.setText(Html.fromHtml(name + ": <font color='#A020F0'>" + "Purple" + "</font>"));
                    }
                } else if (type.equals("BoxType")) {
                    if (i == 0) {
                        textView.setText(name.concat(": Normal"));
                    } else if (i == 1) {
                        textView.setText(name.concat(": 3D"));
                    } else if (i == 2) {
                        textView.setText(name.concat(": Corner"));
                    }
                } else if (type.equals("LineType")) {
                    if (i == 0) {
                        textView.setText(name.concat(": Top"));
                    } else if (i == 1) {
                        textView.setText(name.concat(": Center"));
                    } else if (i == 2) {
                        textView.setText(name.concat(": Bottom"));
                    }
                } else {
                    textView.setText(name.concat(": ") + i + type);
                }

                ChangesID(ID, i);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                seekBar.setAlpha(0.8f);
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                seekBar.setAlpha(1.0f);
            }
        });

        linearLayout.addView(textView);
        linearLayout.addView(seekBar);
        card.addView(linearLayout);
        tabContentContainers.get(populateTab).addView(card);
    }

    // Injection methods - Based on noonroot project approach
    public static boolean InjectX86(String Lib) {
        try {
            String injector = context.getApplicationInfo().nativeLibraryDir + File.separator + "libinjectEmulator.so";
            String payload_source = context.getApplicationInfo().nativeLibraryDir + File.separator + Lib;

            String injector_dest = "/data/local/tmp/libinject";
            String payload_dest = "/data/local/tmp/" + Lib;
            String payload_alias = "/data/local/tmp/libmeuovo.so";

            Shell.su("rm -f " + injector_dest).exec();
            Shell.su("rm -f " + payload_dest).exec();
            Shell.su("rm -f " + payload_alias).exec();

            Shell.Result result = Shell.su("cat " + injector + " > " + injector_dest).exec();

            Shell.su("cat " + payload_source + " > " + payload_dest).exec();
            Shell.su("cat " + payload_source + " > " + payload_alias).exec();

            Shell.su("chmod 777 " + injector_dest).exec();
            Shell.su("chmod 777 " + payload_dest).exec();
            Shell.su("chmod 777 " + payload_alias).exec();

            String injectCmd = "su -c \"/data/local/tmp/libinject -pkg " + target + " -lib " + payload_dest
                    + " -open -dl_memfd\"";

            result = Shell.su(injectCmd).exec();

            Shell.su("rm -f " + injector_dest).exec();
            Shell.su("rm -f " + payload_dest).exec();
            Shell.su("rm -f " + payload_alias).exec();

            // Removed duplicated Functions() here
            Toast.makeText(context, "Injection Successful", Toast.LENGTH_SHORT).show();
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    public static boolean InjectX32(String Lib) {
        try {
            String injector = context.getApplicationInfo().nativeLibraryDir + File.separator + "libinjectEmulator.so";
            String payload_source = context.getApplicationInfo().nativeLibraryDir + File.separator + Lib;

            String injector_dest = "/data/local/tmp/libinject";
            String payload_dest = "/data/local/tmp/" + Lib;
            String payload_alias = "/data/local/tmp/libmeuovo.so";
            String suPath = "/boot/android/android/system/xbin/bstk/su";

            execWithCustomSu(suPath, "rm -f " + injector_dest);
            execWithCustomSu(suPath, "rm -f " + payload_dest);
            execWithCustomSu(suPath, "rm -f " + payload_alias);

            execWithCustomSu(suPath, "cat " + injector + " > " + injector_dest);

            execWithCustomSu(suPath, "cat " + payload_source + " > " + payload_dest);
            execWithCustomSu(suPath, "cat " + payload_source + " > " + payload_alias);

            execWithCustomSu(suPath, "chmod 777 " + injector_dest);
            execWithCustomSu(suPath, "chmod 777 " + payload_dest);
            execWithCustomSu(suPath, "chmod 777 " + payload_alias);

            String injectCmd = suPath + " -c \"/data/local/tmp/libinject -pkg " + target + " -lib " + payload_dest
                    + " -open -dl_memfd\"";
            execWithCustomSu(suPath, injectCmd);

            execWithCustomSu(suPath, "rm -f " + injector_dest);
            execWithCustomSu(suPath, "rm -f " + payload_dest);
            execWithCustomSu(suPath, "rm -f " + payload_alias);

            // Removed duplicated Functions() here

            return true;
        } catch (Exception e) {
            e.printStackTrace();
            Toast.makeText(context, "Error: " + e.getMessage(), Toast.LENGTH_LONG).show();
            return false;
        }
    }

    public static void execWithCustomSu(String str, String str2) {
        try {
            java.io.BufferedReader bufferedReader = new java.io.BufferedReader(
                    new java.io.InputStreamReader(new ProcessBuilder(new String[] { str, "-c", str2 })
                            .redirectErrorStream(true).start().getInputStream()));
            while (true) {
                try {
                    str = bufferedReader.readLine();
                    if (str != null) {
                        java.io.PrintStream printStream = System.out;
                        StringBuilder stringBuilder = new StringBuilder();
                        stringBuilder.append("[SU OUTPUT] ");
                        stringBuilder.append(str);
                        printStream.println(stringBuilder.toString());
                    } else {
                        bufferedReader.close();
                        return;
                    }
                } catch (Throwable th) {
                    th.addSuppressed(th);
                }
            }
        } catch (java.io.IOException e) {
            e.printStackTrace();
        }
    }

    private void toggleSu(boolean enable) {
        String from = enable ? "/system/xbin/su" : "/system/xbin/su1";
        String to = enable ? "/system/xbin/su1" : "/system/xbin/su";

        try {
            Process process = Runtime.getRuntime().exec(enable ? "su" : "su1");
            process.getOutputStream().write(("mount -o remount,rw /system\n").getBytes());
            process.getOutputStream().write(("mv " + from + " " + to + "\n").getBytes());
            process.getOutputStream().write("exit\n".getBytes());
            process.getOutputStream().flush();
            process.waitFor();
            Toast.makeText(context, "ROOT BYPASS " + (enable ? "ENABLED" : "DISABLED"), Toast.LENGTH_SHORT).show();
        } catch (Exception e) {
            // Toast.makeText(context, "Root rename failed: " + e.getMessage(),
            // Toast.LENGTH_LONG).show();
        }
    }
    public static void toggleTargetListStatic() {
        if (menuInstance != null) {
            menuInstance.toggleTargetList();
        }
    }

    public void toggleTargetList() {
        if (!isTargetListVisible) {
            initTargetList();
            isTargetListVisible = true;
            startTargetRefresh();
            Toast.makeText(context, "Target List ON", Toast.LENGTH_SHORT).show();
        } else {
            if (targetListLayout != null) {
                windowManager.removeView(targetListLayout);
                targetListLayout = null;
            }
            isTargetListVisible = false;
            stopTargetRefresh();
            Toast.makeText(context, "Target List OFF", Toast.LENGTH_SHORT).show();
        }
    }

    private void initTargetList() {
        targetListLayout = new LinearLayout(context);
        targetListLayout.setOrientation(LinearLayout.VERTICAL);
        
        // Stealth Glass Styling
        GradientDrawable windowBg = new GradientDrawable();
        windowBg.setColor(0xEE0D0D0D); // Deep dark charcoal
        windowBg.setCornerRadius(utils.FixDP(5));
        windowBg.setStroke((int)utils.FixDP(1.2f), 0xFFDA2A2A); // Deep red border
        targetListLayout.setBackground(windowBg);
        
        // Title / Header
        TextView header = new TextView(context);
        header.setText("TARGET RADAR");
        header.setTextColor(0xFFDA2A2A); // Red theme
        header.setPadding(utils.FixDP(10), utils.FixDP(7), utils.FixDP(10), utils.FixDP(7));
        header.setGravity(Gravity.CENTER);
        header.setTextSize(10);
        header.setTypeface(Typeface.create("sans-serif-medium", Typeface.BOLD));
        header.setLetterSpacing(0.05f);
        targetListLayout.addView(header);

        // Thin separator
        View separator = new View(context);
        separator.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, utils.FixDP(1)));
        separator.setBackgroundColor(0x33DA2A2A);
        targetListLayout.addView(separator);

        // Content ScrollView
        ScrollView scroll = new ScrollView(context);
        scroll.setLayoutParams(new LinearLayout.LayoutParams(utils.FixDP(140), utils.FixDP(170)));
        scroll.setVerticalScrollBarEnabled(false);
        
        targetItemsContainer = new LinearLayout(context);
        targetItemsContainer.setOrientation(LinearLayout.VERTICAL);
        targetItemsContainer.setPadding(utils.FixDP(4), utils.FixDP(4), utils.FixDP(4), utils.FixDP(4));
        
        scroll.addView(targetItemsContainer);
        targetListLayout.addView(scroll);

        targetListParams = new WindowManager.LayoutParams();
        targetListParams.width = WindowManager.LayoutParams.WRAP_CONTENT;
        targetListParams.height = WindowManager.LayoutParams.WRAP_CONTENT;
        targetListParams.x = 100;
        targetListParams.y = 300;
        targetListParams.gravity = Gravity.TOP | Gravity.LEFT;
        targetListParams.type = (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) 
            ? WindowManager.LayoutParams.TYPE_APPLICATION_OVERLAY 
            : WindowManager.LayoutParams.TYPE_PHONE;
        targetListParams.flags = WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
        targetListParams.format = PixelFormat.TRANSLUCENT;

        // Custom touch to drag
        targetListLayout.setOnTouchListener(new View.OnTouchListener() {
            private int initialX, initialY;
            private float initialTouchX, initialTouchY;

            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        initialX = targetListParams.x;
                        initialY = targetListParams.y;
                        initialTouchX = event.getRawX();
                        initialTouchY = event.getRawY();
                        return true;
                    case MotionEvent.ACTION_MOVE:
                        targetListParams.x = initialX + (int) (event.getRawX() - initialTouchX);
                        targetListParams.y = initialY + (int) (event.getRawY() - initialTouchY);
                        windowManager.updateViewLayout(targetListLayout, targetListParams);
                        return true;
                }
                return false;
            }
        });

        windowManager.addView(targetListLayout, targetListParams);
    }

    private void startTargetRefresh() {
        targetRefreshHandler.postDelayed(new Runnable() {
            @Override
            public void run() {
                if (isTargetListVisible) {
                    refreshTargets();
                    targetRefreshHandler.postDelayed(this, 1000);
                }
            }
        }, 1000);
    }

    private void stopTargetRefresh() {
        targetRefreshHandler.removeCallbacksAndMessages(null);
    }

    private void refreshTargets() {
        if (targetItemsContainer == null) return;
        targetItemsContainer.removeAllViews();
        
        String[] enemies = getEnemyList();
        if (enemies == null || enemies.length == 0) {
            TextView none = new TextView(context);
            none.setText("No Enemies Found");
            none.setTextColor(0xFF888888);
            none.setTextSize(9);
            none.setPadding(utils.FixDP(8), utils.FixDP(8), utils.FixDP(8), utils.FixDP(8));
            targetItemsContainer.addView(none);
            return;
        }

        for (int i = 0; i < enemies.length; i += 2) {
            final String name = enemies[i];
            final long ptr = Long.parseLong(enemies[i+1]);
            

            LinearLayout item = new LinearLayout(context);
            item.setOrientation(LinearLayout.HORIZONTAL);
            LinearLayout.LayoutParams itemLp = new LinearLayout.LayoutParams(
                    ViewGroup.LayoutParams.MATCH_PARENT, utils.FixDP(26));
            itemLp.setMargins(0, 0, 0, utils.FixDP(3));
            item.setLayoutParams(itemLp);
            item.setGravity(Gravity.CENTER_VERTICAL);
            item.setPadding(utils.FixDP(8), 0, utils.FixDP(8), 0);

            GradientDrawable itemBg = new GradientDrawable();
            itemBg.setCornerRadius(utils.FixDP(3));
            
            TextView tv = new TextView(context);
            tv.setText(name);
            tv.setTextSize(10);
            
            if (currentlyLockedPtr == ptr) {
                itemBg.setColor(0x44DA2A2A); // Active selection background
                item.setAlpha(1.0f);
                tv.setTextColor(0xFFFFFFFF);
                tv.setTypeface(null, Typeface.BOLD);
            } else {
                itemBg.setColor(0x11FFFFFF); // Subtle dark row
                item.setAlpha(0.85f);
                tv.setTextColor(0xFFDDDDDD);
            }
            
            item.setBackground(itemBg);
            item.addView(tv);

            item.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    LockPlayer(ptr);
                    currentlyLockedPtr = ptr;
                    
                    // Sync with Main Switch (ID 523) visually
                    SwitchStyle mainLockSwitch = idToBindSwitch.get(523);
                    if (mainLockSwitch != null && !mainLockSwitch.isChecked()) {
                        mainLockSwitch.setChecked(true);
                    }
                    
                    refreshTargets();
                }
            });

            targetItemsContainer.addView(item);
        }
    }

    private static class HexagonDrawable extends Drawable {
        private Paint paint;
        private Paint strokePaint;
        private Path path;

        public HexagonDrawable(int color, boolean outline, int strokeColor) {
            paint = new Paint(Paint.ANTI_ALIAS_FLAG);
            paint.setColor(color);
            paint.setStyle(Paint.Style.FILL);

            if (outline) {
                strokePaint = new Paint(Paint.ANTI_ALIAS_FLAG);
                strokePaint.setColor(strokeColor);
                strokePaint.setStyle(Paint.Style.STROKE);
                strokePaint.setStrokeWidth(3.0f);
            }

            path = new Path();
        }

        @Override
        protected void onBoundsChange(Rect bounds) {
            super.onBoundsChange(bounds);
            float width = bounds.width();
            float height = bounds.height();
            float cut = height / 3.0f;

            path.reset();
            path.moveTo(cut, 0);
            path.lineTo(width - cut, 0);
            path.lineTo(width, cut);
            path.lineTo(width, height - cut);
            path.lineTo(width - cut, height);
            path.lineTo(cut, height);
            path.lineTo(0, height - cut);
            path.lineTo(0, cut);
            path.close();
        }

        @Override
        public void draw(Canvas canvas) {
            canvas.drawPath(path, paint);
            if (strokePaint != null) {
                canvas.drawPath(path, strokePaint);
            }
        }

        @Override
        public void setAlpha(int alpha) { paint.setAlpha(alpha); }
        @Override
        public void setColorFilter(ColorFilter colorFilter) { paint.setColorFilter(colorFilter); }
        @Override
        public int getOpacity() { return PixelFormat.TRANSLUCENT; }
    }

    private static class CustomCheckboxDrawable extends Drawable {
        private Paint borderPaint;
        private Paint fillPaint;
        private Paint checkPaint;
        private Paint glowPaint;
        private Path checkPath;
        private boolean isChecked;
        private int accentColor;

        public CustomCheckboxDrawable(int color) {
            accentColor = color;

            borderPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
            borderPaint.setColor(0xFF333333);
            borderPaint.setStyle(Paint.Style.STROKE);
            borderPaint.setStrokeWidth(utils.FixDP(1.5f));

            fillPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
            fillPaint.setColor(color);
            fillPaint.setStyle(Paint.Style.FILL);

            checkPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
            checkPaint.setColor(0xFFFFFFFF);
            checkPaint.setStyle(Paint.Style.STROKE);
            checkPaint.setStrokeWidth(utils.FixDP(2f));
            checkPaint.setStrokeCap(Paint.Cap.ROUND);
            checkPaint.setStrokeJoin(Paint.Join.ROUND);

            glowPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
            glowPaint.setColor(color);
            glowPaint.setStyle(Paint.Style.FILL);
            glowPaint.setAlpha(40);

            checkPath = new Path();
            isChecked = false;
        }

        public void setChecked(boolean checked) {
            if (this.isChecked != checked) {
                this.isChecked = checked;
                borderPaint.setColor(checked ? accentColor : 0xFF333333);
                invalidateSelf();
            }
        }

        @Override
        protected void onBoundsChange(Rect bounds) {
            super.onBoundsChange(bounds);
            float w = bounds.width();
            float h = bounds.height();

            checkPath.reset();
            checkPath.moveTo(w * 0.25f, h * 0.5f);
            checkPath.lineTo(w * 0.42f, h * 0.68f);
            checkPath.lineTo(w * 0.75f, h * 0.3f);
        }

        @Override
        public void draw(Canvas canvas) {
            Rect bounds = getBounds();
            float pad = utils.FixDP(1.5f);
            float radius = utils.FixDP(6);

            if (isChecked) {
                // Draw outer glow
                float glowPad = utils.FixDP(1);
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
                    canvas.drawRoundRect(
                        bounds.left + pad - glowPad, bounds.top + pad - glowPad,
                        bounds.right - pad + glowPad, bounds.bottom - pad + glowPad,
                        radius + glowPad, radius + glowPad, glowPaint);
                }

                // Draw filled background
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
                    canvas.drawRoundRect(
                        bounds.left + pad, bounds.top + pad,
                        bounds.right - pad, bounds.bottom - pad,
                        radius, radius, fillPaint);
                } else {
                    canvas.drawRect(
                        bounds.left + pad, bounds.top + pad,
                        bounds.right - pad, bounds.bottom - pad, fillPaint);
                }

                // Draw white checkmark
                canvas.drawPath(checkPath, checkPaint);
            } else {
                // Draw border only
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
                    canvas.drawRoundRect(
                        bounds.left + pad, bounds.top + pad,
                        bounds.right - pad, bounds.bottom - pad,
                        radius, radius, borderPaint);
                } else {
                    canvas.drawRect(
                        bounds.left + pad, bounds.top + pad,
                        bounds.right - pad, bounds.bottom - pad, borderPaint);
                }
            }
        }

        @Override
        public void setAlpha(int alpha) {
            borderPaint.setAlpha(alpha);
            fillPaint.setAlpha(alpha);
            checkPaint.setAlpha(alpha);
        }

        @Override
        public void setColorFilter(ColorFilter colorFilter) {
            borderPaint.setColorFilter(colorFilter);
            fillPaint.setColorFilter(colorFilter);
            checkPaint.setColorFilter(colorFilter);
        }

        @Override
        public int getOpacity() {
            return PixelFormat.TRANSLUCENT;
        }
    }
}

