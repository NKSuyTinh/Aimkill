package com.terminalx999;

import android.graphics.Typeface;
import android.text.TextPaint;
import android.text.style.MetricAffectingSpan;

public class CustomTypefaceSpan extends MetricAffectingSpan {
    private final Typeface typeface;

    public CustomTypefaceSpan(Typeface tf) {
        this.typeface = tf;
    }

    @Override
    public void updateDrawState(TextPaint paint) {
        paint.setTypeface(typeface);
    }

    @Override
    public void updateMeasureState(TextPaint paint) {
        paint.setTypeface(typeface);
    }
}

