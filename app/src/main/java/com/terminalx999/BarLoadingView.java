package com.terminalx999;

import android.animation.ValueAnimator;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.RectF;
import android.util.AttributeSet;
import android.view.View;
import android.view.animation.LinearInterpolator;

/**
 * 3 vertical bars, bottom-aligned, heights animate in wave (equalizer style). UI color.
 */
public class BarLoadingView extends View {

    private static final int BAR_COUNT = 3;

    private final Paint paint = new Paint();
    private final float[] barHeights = new float[BAR_COUNT];
    private float barWidth;
    private float gap;
    private float maxHeight;
    private float cornerRadiusPx;
    private int barColor = 0xFFFFFFFF;  // Default white for loading animation
    private ValueAnimator animator;
    private float phase;

    public BarLoadingView(Context context) {
        super(context);
        init();
    }

    public BarLoadingView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    private void init() {
        cornerRadiusPx = 2.5f * getContext().getResources().getDisplayMetrics().density;
        paint.setAntiAlias(true);
        paint.setStyle(Paint.Style.FILL);
        paint.setColor(barColor);
    }

    public void setPrimaryColor(int color) {
        barColor = color;
        paint.setColor(barColor);
    }

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        super.onSizeChanged(w, h, oldw, oldh);
        float totalBarWidth = w * 0.6f;
        gap = w * 0.08f;
        barWidth = (totalBarWidth - gap * (BAR_COUNT - 1)) / BAR_COUNT;
        maxHeight = h * 0.85f;
    }

    @Override
    protected void onDraw(Canvas canvas) {
        float bottom = getHeight();
        float leftStart = (getWidth() - (barWidth * BAR_COUNT + gap * (BAR_COUNT - 1))) / 2f;

        for (int i = 0; i < BAR_COUNT; i++) {
            float x = leftStart + i * (barWidth + gap);
            float h = barHeights[i];
            if (h < 4f) h = 4f;
            RectF r = new RectF(x, bottom - h, x + barWidth, bottom);
            float r2 = Math.min(cornerRadiusPx, barWidth / 2f);
            canvas.drawRoundRect(r, r2, r2, paint);
        }
    }

    @Override
    protected void onAttachedToWindow() {
        super.onAttachedToWindow();
        startAnimation();
    }

    @Override
    protected void onDetachedFromWindow() {
        stopAnimation();
        super.onDetachedFromWindow();
    }

    @Override
    protected void onVisibilityChanged(View changedView, int visibility) {
        super.onVisibilityChanged(changedView, visibility);
        if (visibility == View.VISIBLE) {
            startAnimation();
        } else {
            stopAnimation();
        }
    }

    private void startAnimation() {
        if (animator != null) return;
        animator = ValueAnimator.ofFloat(0f, 1f);
        animator.setDuration(1200);
        animator.setRepeatCount(ValueAnimator.INFINITE);
        animator.setRepeatMode(ValueAnimator.RESTART);
        animator.setInterpolator(new LinearInterpolator());
        animator.addUpdateListener(animation -> {
            phase = (float) animation.getAnimatedValue();
            float minH = maxHeight * 0.2f;
            float range = maxHeight * 0.8f;
            for (int i = 0; i < BAR_COUNT; i++) {
                float t = phase + i * 0.35f;
                if (t > 1f) t -= 1f;
                float factor = (float) Math.sin(t * Math.PI);
                barHeights[i] = minH + range * factor;
            }
            invalidate();
        });
        animator.start();
    }

    private void stopAnimation() {
        if (animator != null) {
            animator.cancel();
            animator = null;
        }
    }
}

