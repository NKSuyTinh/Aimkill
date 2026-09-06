package com.terminalx999;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.LinearGradient;
import android.graphics.Paint;
import android.graphics.Shader;
import android.util.AttributeSet;
import android.view.View;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class ParticlesView extends View {

    private static final int PARTICLE_COUNT = 45;
    private final List<BoldParticle> particles = new ArrayList<>();
    private final Paint glowPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final Paint corePaint = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final Paint bgPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final Random random = new Random();

    public ParticlesView(Context context) {
        super(context);
        init();
    }

    public ParticlesView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    private void init() {
        glowPaint.setStyle(Paint.Style.FILL);
        corePaint.setStyle(Paint.Style.FILL);
        bgPaint.setStyle(Paint.Style.FILL);
    }

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        super.onSizeChanged(w, h, oldw, oldh);
        setupGradient(w, h);
        createParticles(w, h);
    }

    private void setupGradient(int w, int h) {
        int topColor = 0xFA0B0C10;
        int bottomColor = 0xFA050508;
        bgPaint.setShader(new LinearGradient(0, 0, 0, h, topColor, bottomColor, Shader.TileMode.CLAMP));
    }

    private void createParticles(int width, int height) {
        particles.clear();
        for (int i = 0; i < PARTICLE_COUNT; i++) {
            particles.add(new BoldParticle(width, height, true));
        }
    }

    @Override
    protected void onDraw(Canvas canvas) {
        if (bgPaint.getShader() != null) {
            canvas.drawRect(0, 0, getWidth(), getHeight(), bgPaint);
        }

        for (BoldParticle p : particles) {
            p.update(getWidth(), getHeight());

            glowPaint.setColor(p.color);
            glowPaint.setAlpha((int) (p.alpha * 0.35f));
            canvas.drawCircle(p.x, p.y, p.radius * 2.2f, glowPaint);

            corePaint.setColor(p.color);
            corePaint.setAlpha(p.alpha);
            canvas.drawCircle(p.x, p.y, p.radius, corePaint);
        }

        invalidate();
    }

    private class BoldParticle {
        float x, y;
        float speedY;
        float speedX;
        float radius;
        int alpha;
        int color;

        BoldParticle(int width, int height, boolean randomizeY) {
            reset(width, height, randomizeY);
        }

        void reset(int width, int height, boolean randomizeY) {
            x = random.nextFloat() * width;
            y = randomizeY ? random.nextFloat() * height : height + 10;
            radius = 2.5f + random.nextFloat() * 4.5f;
            speedY = -(0.6f + random.nextFloat() * 1.4f);
            speedX = (random.nextFloat() - 0.5f) * 0.5f;
            alpha = 100 + random.nextInt(155);

            float chance = random.nextFloat();
            if (chance > 0.6f) {
                color = 0xFFFF1A3C;
            } else if (chance > 0.3f) {
                color = 0xFFFF6600;
            } else {
                color = 0xFFFFFFFF;
            }
        }

        void update(int width, int height) {
            y += speedY;
            x += speedX;
            if (y < -20 || x < -20 || x > width + 20) {
                reset(width, height, false);
            }
        }
    }
}
