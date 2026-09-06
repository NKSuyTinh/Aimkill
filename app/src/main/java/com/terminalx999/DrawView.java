package com.terminalx999;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.LinearGradient;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.RectF;
import android.graphics.Shader;
import android.graphics.Typeface;
import android.view.View;

import java.util.Date;

public class DrawView extends View implements Runnable {
    Paint mStrokePaint;
    Paint mFilledPaint;
    Paint mTextPaint;
    Paint mBitMapPaint;
    Paint mRectPaint1;
    Paint mRectPaint2;

    Thread mThread;
    int FPS = 60;
    long sleepTime;
    Date time;

    public DrawView(Context context)
    {
        super(context, null, 0);
        InitializePaints();
        setFocusableInTouchMode(false);
        setBackgroundColor(0);
        time = new Date();
        sleepTime = (long)(1000 / FPS);
        mThread = new Thread(this);
        mThread.start();
    }

    @Override
    protected void onDraw(Canvas canvas)
    {
        if (canvas != null && getVisibility() == VISIBLE)
        {
            ClearCanvas(canvas);
            time.setTime(System.currentTimeMillis());
            Menu.OnDrawLoad(this, canvas);
            DrawWatermarkOverlay(canvas);
        }
    }

    public void DrawWatermarkOverlay(Canvas canvas) {
        if (canvas == null) return;
        int width = getWidth();
        int height = getHeight();
        if (width <= 0 || height <= 0) return;
        // Top banner removed
        float topBarHeight = 0f;

        // 2. Middle Card 1: "BanAimKill | Free Fire 1.126.1 | v0.1"
        String titleRed = "BanAimKill";
        String titleRest = " | Free Fire 1.126.1 | v0.1";

        Paint cardBgPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
        cardBgPaint.setColor(Color.argb(210, 25, 30, 40));
        cardBgPaint.setStyle(Paint.Style.FILL);

        Paint cardBorderPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
        cardBorderPaint.setColor(Color.argb(120, 255, 255, 255));
        cardBorderPaint.setStyle(Paint.Style.STROKE);
        cardBorderPaint.setStrokeWidth(1.5f);

        Paint redTextPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
        redTextPaint.setColor(Color.rgb(235, 45, 55));
        redTextPaint.setTypeface(Typeface.create(Typeface.DEFAULT, Typeface.BOLD));

        Paint whiteTextPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
        whiteTextPaint.setColor(Color.WHITE);
        whiteTextPaint.setTypeface(Typeface.create(Typeface.DEFAULT, Typeface.NORMAL));

        float cardTextSize = (width > 1920 || height > 1920) ? 20f : 15f;
        redTextPaint.setTextSize(cardTextSize);
        whiteTextPaint.setTextSize(cardTextSize);

        float redW = redTextPaint.measureText(titleRed);
        float restW = whiteTextPaint.measureText(titleRest);
        float box1Width = redW + restW + 24f;

        Paint.FontMetrics cardFm = redTextPaint.getFontMetrics();
        float box1Height = (cardFm.descent - cardFm.ascent) + 12f;

        float box1Left = (width - box1Width) / 2f;
        float box1Top = topBarHeight + 80f;

        RectF box1Rect = new RectF(box1Left, box1Top, box1Left + box1Width, box1Top + box1Height);
        canvas.drawRoundRect(box1Rect, 5f, 5f, cardBgPaint);
        canvas.drawRoundRect(box1Rect, 5f, 5f, cardBorderPaint);

        float box1Baseline = box1Top + (box1Height / 2f) - ((cardFm.ascent + cardFm.descent) / 2f);
        canvas.drawText(titleRed, box1Left + 12f, box1Baseline, redTextPaint);
        canvas.drawText(titleRest, box1Left + 12f + redW, box1Baseline, whiteTextPaint);

        // 3. Middle Card 2: "⚠ Free AimKill đem bán là TUẤT OK"
        String iconWarn = "\u26A0 ";
        String fullWarningText = "Free AimKill \u0111em b\u00E1n l\u00E0 TU\u1EA4T OK";

        Paint orangeTextPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
        orangeTextPaint.setColor(Color.rgb(255, 170, 0));
        orangeTextPaint.setTypeface(Typeface.create(Typeface.DEFAULT, Typeface.BOLD));
        orangeTextPaint.setTextSize(cardTextSize);

        Paint warnIconPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
        warnIconPaint.setColor(Color.rgb(255, 200, 0));
        warnIconPaint.setTextSize(cardTextSize);

        float iconW = warnIconPaint.measureText(iconWarn);
        float warnW = orangeTextPaint.measureText(fullWarningText);
        float box2Width = iconW + warnW + 24f;
        float box2Height = box1Height;

        float box2Left = (width - box2Width) / 2f;
        float box2Top = box1Top + box1Height + 6f;

        RectF box2Rect = new RectF(box2Left, box2Top, box2Left + box2Width, box2Top + box2Height);
        canvas.drawRoundRect(box2Rect, 5f, 5f, cardBgPaint);
        canvas.drawRoundRect(box2Rect, 5f, 5f, cardBorderPaint);

        float box2Baseline = box2Top + (box2Height / 2f) - ((cardFm.ascent + cardFm.descent) / 2f);
        canvas.drawText(iconWarn, box2Left + 12f, box2Baseline, warnIconPaint);
        canvas.drawText(fullWarningText, box2Left + 12f + iconW, box2Baseline, orangeTextPaint);
    }

    @Override
    public void run() {
        android.os.Process.setThreadPriority(android.os.Process.THREAD_PRIORITY_BACKGROUND);
        while (mThread.isAlive() && !mThread.isInterrupted())
        {
            try
            {
                long t1 = System.currentTimeMillis();
                postInvalidate();
                long td = System.currentTimeMillis() - t1;
                long delay = sleepTime - td;
                if (delay > 0) {
                    Thread.sleep(delay);
                }
            }
            catch (InterruptedException it)
            {
                return;
            }
        }
    }

    public void InitializePaints()
    {
        mStrokePaint = new Paint();
        mStrokePaint.setStyle(Paint.Style.STROKE);
        mStrokePaint.setAntiAlias(true);

        mFilledPaint = new Paint();
        mFilledPaint.setStyle(Paint.Style.FILL);
        mFilledPaint.setAntiAlias(true);

        mTextPaint = new Paint();
        mTextPaint.setTypeface(Typeface.MONOSPACE);
        mTextPaint.setAntiAlias(true);
        mTextPaint.setTextAlign(Paint.Align.CENTER);

        mRectPaint1 = new Paint();
        mRectPaint1.setTypeface(Typeface.MONOSPACE);
        mRectPaint1.setAntiAlias(true);
        mRectPaint1.setTextAlign(Paint.Align.CENTER);

        mRectPaint2 = new Paint();
        mRectPaint2.setTypeface(Typeface.MONOSPACE);
        mRectPaint2.setAntiAlias(true);
        mRectPaint2.setTextAlign(Paint.Align.CENTER);

        mBitMapPaint = new Paint();
        mBitMapPaint.setAntiAlias(true);
    }

    public void ClearCanvas(Canvas cvs) {
        cvs.drawColor(Color.TRANSPARENT, PorterDuff.Mode.CLEAR);
    }

    public void DrawLine(Canvas cvs, int a, int r, int g, int b, float lineWidth, float fromX, float fromY, float toX, float toY) {
        mStrokePaint.setColor(Color.rgb(r, g, b));
        mStrokePaint.setAlpha(a);
        mStrokePaint.setStrokeWidth(lineWidth);
        cvs.drawLine(fromX, fromY, toX, toY, mStrokePaint);
    }

    public void DrawGradientRect(Canvas canvas, int startA, int startR, int startG, int startB,
                                 int endA, int endR, int endG, int endB,
                                 float x, float y, float width, float height) {
        Paint paint = new Paint();
        LinearGradient gradient = new LinearGradient(
                x, y, x + width, y + height,
                Color.argb(startA, startR, startG, startB),
                Color.argb(endA, endR, endG, endB),
                Shader.TileMode.CLAMP
        );
        paint.setShader(gradient);
        canvas.drawRect(x, y, x + width, y + height, paint);
    }


    public void DrawText(Canvas cvs, int a, int r, int g, int b, float stroke, String txt, float posX, float posY, float size)
    {
        mTextPaint.setColor(Color.rgb(r, g, b));
        mTextPaint.setAlpha(a);
        mTextPaint.setTextSize(size);

        if (getRight() > 1920 || getBottom() > 1920) {
            mTextPaint.setTextSize(4.0f + size);
        }
        else if (getRight() == 1920 || getBottom() == 1920) {
            mTextPaint.setTextSize(size + 2.0f);
        }
        else
            mTextPaint.setTextSize(size);

        cvs.drawText(txt, posX, posY, mTextPaint);
    }

    public void DrawTextBold(Canvas cvs, int a, int r, int g, int b, float stroke, String txt, float posX, float posY, float size) {
        Paint boldPaint = new Paint(mTextPaint);
        boldPaint.setTypeface(Typeface.create(Typeface.DEFAULT, Typeface.BOLD));
        boldPaint.setFakeBoldText(true);
        boldPaint.setStyle(Paint.Style.FILL); // cleaner than stroke for UI
        boldPaint.setColor(Color.rgb(r, g, b));
        boldPaint.setAlpha(a);
        boldPaint.setTextSize(size);

        if (getRight() > 1920 || getBottom() > 1920) {
            boldPaint.setTextSize(4.0f + size);
        }
        else if (getRight() == 1920 || getBottom() == 1920) {
            boldPaint.setTextSize(size + 2.0f);
        }
        else {
            boldPaint.setTextSize(size);
        }

        cvs.drawText(txt, posX, posY, boldPaint);
    }

    public void DrawTextLeft(Canvas cvs, int a, int r, int g, int b, float stroke, String txt, float posX, float posY, float size) {
        Paint leftPaint = new Paint(mTextPaint);
        leftPaint.setTextAlign(Paint.Align.LEFT);
        leftPaint.setColor(Color.rgb(r, g, b));
        leftPaint.setAlpha(a);
        leftPaint.setTextSize(size);

        if (getRight() > 1920 || getBottom() > 1920) {
            leftPaint.setTextSize(4.0f + size);
        }
        else if (getRight() == 1920 || getBottom() == 1920) {
            leftPaint.setTextSize(size + 2.0f);
        }
        else {
            leftPaint.setTextSize(size);
        }

        cvs.drawText(txt, posX, posY, leftPaint);
    }

    public void DrawTextBoldLeft(Canvas cvs, int a, int r, int g, int b, float stroke, String txt, float posX, float posY, float size) {
        Paint leftBold = new Paint(mTextPaint);
        leftBold.setTextAlign(Paint.Align.LEFT);
        leftBold.setTypeface(Typeface.create(Typeface.DEFAULT, Typeface.BOLD));
        leftBold.setFakeBoldText(true);
        leftBold.setStyle(Paint.Style.FILL);
        leftBold.setColor(Color.rgb(r, g, b));
        leftBold.setAlpha(a);
        leftBold.setTextSize(size);

        if (getRight() > 1920 || getBottom() > 1920) {
            leftBold.setTextSize(4.0f + size);
        }
        else if (getRight() == 1920 || getBottom() == 1920) {
            leftBold.setTextSize(size + 2.0f);
        }
        else {
            leftBold.setTextSize(size);
        }

        cvs.drawText(txt, posX, posY, leftBold);
    }



    public void DrawText2(Canvas cvs, int a, int r, int g, int b, String txt, float posX, float posY, float size) {
        mTextPaint.clearShadowLayer();
        mTextPaint.setColor(Color.rgb(r, g, b));
        mTextPaint.setAlpha(a);
        if (getRight() > 1920 || getBottom() > 1920) {
            mTextPaint.setShadowLayer(12.0f, 0.0f, 0.0f, Color.rgb(r, g, b));
            mTextPaint.setTextSize(4 + size);
        }
        else if (getRight() == 1920 || getBottom() == 1920) {
            mTextPaint.setTextSize(2 + size);
            mTextPaint.setShadowLayer(12.0f, 0.0f, 0.0f, Color.rgb(r, g, b));
        }
        else
            mTextPaint.setTextSize(size);
        mTextPaint.setShadowLayer(12.0f, 0.0f, 0.0f, Color.rgb(r, g, b));
        cvs.drawText(txt, posX, posY, mTextPaint);
    }

    public void DrawCircle(Canvas cvs, int a, int r, int g, int b, float stroke, float posX, float posY, float radius)
    {
        mStrokePaint.setColor(Color.rgb(r, g, b));
        mStrokePaint.setAlpha(a);
        mStrokePaint.setStrokeWidth(stroke);
        cvs.drawCircle(posX, posY, radius, mStrokePaint);
    }

    public void DrawFilledCircle(Canvas cvs, int a, int r, int g, int b, float posX, float posY, float radius)
    {
        mFilledPaint.setColor(Color.rgb(r, g, b));
        mFilledPaint.setAlpha(a);
        cvs.drawCircle(posX, posY, radius, mFilledPaint);
    }

    public void DrawRoundRect(Canvas cvs, int a, int r, int g, int b, float stroke, int rx, int ry, float x, float y, float width, float height) {
        mStrokePaint.setStrokeWidth(stroke);
        mStrokePaint.setColor(Color.rgb(r, g, b));
        mStrokePaint.setAlpha(a);
        cvs.drawRoundRect(x, y, x + width, y + height, rx,ry, mStrokePaint);
    }

    public void DrawRect(Canvas cvs, int a, int r, int g, int b, int stroke, float x, float y, float width, float height)
    {
        mStrokePaint.setStrokeWidth(stroke);
        mStrokePaint.setColor(Color.rgb(r, g, b));
        mStrokePaint.setAlpha(a);
        cvs.drawRect(x, y, x + width, y + height, mStrokePaint);
    }

    public void DrawTextRect(Canvas cvs, int a, int r, int g, int b, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, float x, float y)
    {
        mRectPaint1.setColor(Color.rgb(r, g, b));
        mRectPaint1.setStrokeWidth(1.1f);
        mRectPaint1.setAlpha(a);

        mRectPaint2.setColor(Color.rgb(0, 0, 255));
        mRectPaint2.setStrokeWidth(1.1f);
        mRectPaint2.setAlpha(150);

        cvs.drawRect(x - a1, y - a2, x + a3, y + a4, mRectPaint1);
        cvs.drawRect(x - a5, y - a6, x - a7, y + a8, mRectPaint2);
    }

    public void DrawFilledRect(Canvas cvs, int a, int r, int g, int b, float x, float y, float width, float height)
    {
        mFilledPaint.setColor(Color.rgb(r, g, b));
        mFilledPaint.setAlpha(a);
        cvs.drawRect(x, y, x + width, y + height, mFilledPaint);
    }

    public void DrawFilledRectInfo(Canvas cvs, int a, int r, int g, int b, float x, float y, float width, float height)
    {
        mFilledPaint.setColor(Color.rgb(r, g, b));

        mFilledPaint.setAlpha(a);
        cvs.drawRect(x, y, x + width, y + height, mFilledPaint);
    }

    public void DrawFilledRoundRect(Canvas cvs, int a, int r, int g, int b, int rx, int ry, float x, float y, float width, float height) {
        mFilledPaint.setColor(Color.rgb(r, g, b));
        mFilledPaint.setAlpha(a);
        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.LOLLIPOP) {
            cvs.drawRoundRect(x, y, x + width, y + height, rx, ry, mFilledPaint);
        } else {
            android.graphics.RectF rect = new android.graphics.RectF(x, y, x + width, y + height);
            cvs.drawRoundRect(rect, rx, ry, mFilledPaint);
        }
    }

    public void DrawTextCenter(Canvas cvs, int a, int r, int g, int b, float stroke, String txt,
                                 float centerX, float posY, float size) {
        mTextPaint.setColor(Color.rgb(r, g, b));
        mTextPaint.setAlpha(a);
        mTextPaint.setTextSize(size);
        mTextPaint.setTextAlign(Paint.Align.CENTER);
        cvs.drawText(txt, centerX, posY, mTextPaint);
    }

    public void DrawWeaponIcon(Canvas cvs, String iconName, float x, float y, float width, float height) {
        if (iconName == null || iconName.isEmpty()) return;
        try {
            java.io.InputStream is = getContext().getAssets().open("icons/" + iconName + ".png");
            android.graphics.Bitmap bmp = android.graphics.BitmapFactory.decodeStream(is);
            is.close();
            if (bmp != null) {
                android.graphics.RectF destRect = new android.graphics.RectF(x, y, x + width, y + height);
                cvs.drawBitmap(bmp, null, destRect, mBitMapPaint);
            }
        } catch (Exception ignored) {
        }
    }

    public float MeasureTextWidth(String txt, float size) {
        if (txt == null || txt.isEmpty()) {
            return 0f;
        }
        mTextPaint.setTextSize(size);
        return mTextPaint.measureText(txt);
    }

    public float MeasureEspTextWidth(String txt, float size) {
        if (txt == null || txt.isEmpty()) {
            return 0f;
        }
        mTextPaint.setTextSize(size);
        return mTextPaint.measureText(txt);
    }

    public float HudBaselineY(float barTop, float barHeight, float size) {
        mTextPaint.setTextSize(size);
        android.graphics.Paint.FontMetrics fm = mTextPaint.getFontMetrics();
        float centerY = barTop + barHeight * 0.5f;
        return centerY - (fm.ascent + fm.descent) * 0.5f;
    }

    public void DrawNameWithCard(Canvas cvs, int a, int r, int g, int b, String name, String distance, float posX, float posY, float size) {
        mTextPaint.setTextSize(size);
        mTextPaint.setTypeface(Typeface.create(Typeface.DEFAULT, Typeface.BOLD));
        mTextPaint.setAntiAlias(true);

        boolean hasName = name != null && !name.isEmpty();
        boolean hasDist = distance != null && !distance.isEmpty();

        float nameW = hasName ? mTextPaint.measureText(name) : 0;
        float distW = hasDist ? mTextPaint.measureText(distance) : 0;

        Paint.FontMetrics fm = mTextPaint.getFontMetrics();
        float textH = fm.descent - fm.ascent;

        float paddingH = 8;
        float paddingV = 6;
        float separation = (hasName && hasDist) ? 10 : 0;

        float distCardPadding = hasDist ? 8 : 0;
        float totalW = nameW + separation + distW + (paddingH * 2) + distCardPadding;
        float totalH = textH + paddingV;

        float rectX = posX - (totalW / 2);
        float rectY = posY - totalH;

        // Draw Outer Black Card
        mFilledPaint.setColor(Color.BLACK);
        mFilledPaint.setAlpha(160);
        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.LOLLIPOP) {
            cvs.drawRoundRect(rectX, rectY, rectX + totalW, rectY + totalH, 8, 8, mFilledPaint);
        } else {
            cvs.drawRect(rectX, rectY, rectX + totalW, rectY + totalH, mFilledPaint);
        }

        float currentX = rectX + paddingH;
        float textBaseline = rectY + totalH - fm.descent - (paddingV / 2.5f);

        // Draw Name
        if (hasName) {
            mTextPaint.setColor(Color.WHITE);
            mTextPaint.setTextAlign(Paint.Align.LEFT);
            cvs.drawText(name, currentX, textBaseline, mTextPaint);
            currentX += nameW + separation;
        }

        // Draw Nested Red Card for Distance
        if (hasDist) {
            float redCardW = distW + 8;
            float redCardH = textH + 2;
            float redCardY = rectY + (totalH - redCardH) / 2;

            mFilledPaint.setColor(Color.RED);
            mFilledPaint.setAlpha(230);
            if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.LOLLIPOP) {
                cvs.drawRoundRect(currentX, redCardY, currentX + redCardW, redCardY + redCardH, 5, 5, mFilledPaint);
            } else {
                cvs.drawRect(currentX, redCardY, currentX + redCardW, redCardY + redCardH, mFilledPaint);
            }

            mTextPaint.setColor(Color.WHITE);
            mTextPaint.setTextAlign(Paint.Align.CENTER);
            cvs.drawText(distance, currentX + (redCardW / 2), textBaseline, mTextPaint);
        }
    }
}

