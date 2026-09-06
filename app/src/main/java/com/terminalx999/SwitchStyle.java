package com.terminalx999;

import android.animation.Animator;
import android.animation.ValueAnimator;
import android.annotation.TargetApi;
import android.content.Context;
import android.content.res.Resources;
import android.content.res.TypedArray;
import android.graphics.Canvas;
import android.graphics.LinearGradient;
import android.graphics.Paint;
import android.graphics.RadialGradient;
import android.graphics.RectF;
import android.graphics.Shader;
import android.os.Build;
import android.util.AttributeSet;
import android.util.TypedValue;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Checkable;

public class SwitchStyle extends View implements Checkable {
    private static final int DEFAULT_WIDTH = dp2pxInt(46);
    private static final int DEFAULT_HEIGHT = dp2pxInt(24);

    private final int ANIMATE_STATE_NONE = 0;
    private final int ANIMATE_STATE_PENDING_DRAG = 1;
    private final int ANIMATE_STATE_DRAGING = 2;
    private final int ANIMATE_STATE_PENDING_RESET = 3;
    private final int ANIMATE_STATE_PENDING_SETTLE = 4;
    private final int ANIMATE_STATE_SWITCH = 5;

    public SwitchStyle(Context context) {
        super(context);
        init(context, null);
    }

    public SwitchStyle(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context, attrs);
    }

    public SwitchStyle(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(context, attrs);
    }

    @TargetApi(Build.VERSION_CODES.LOLLIPOP)
    public SwitchStyle(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
        super(context, attrs, defStyleAttr, defStyleRes);
        init(context, attrs);
    }

    @Override
    public final void setOnClickListener(OnClickListener l) {}

    @Override
    public final void setOnLongClickListener(OnLongClickListener l) {}

    public void setOnCheckedChangeListener(OnCheckedChangeListener l){
        onCheckedChangeListener = l;
    }

    public interface OnCheckedChangeListener{
        void onCheckedChanged(SwitchStyle view, boolean isChecked);
    }

    @Override
    public final void setPadding(int left, int top, int right, int bottom) {
        super.setPadding(0, 0, 0, 0);
    }

    @Override
    public void setChecked(boolean checked) {
        if(checked == isChecked()){
            postInvalidate();
            return;
        }
        toggle(enableEffect, false);
    }

    @Override
    public boolean isChecked() {
        return isChecked;
    }

    @Override
    public void toggle() {
        toggle(true);
    }

    public void toggle(boolean animate) {
        toggle(animate, true);
    }

    private void init(Context context, AttributeSet attrs) {
        // Premium dark track colors
        uncheckColor = 0xFF1A1A1A;
        checkedColor = Menu.PrimaryColor;

        // Thumb colors
        uncheckButtonColor = 0xFF555555;
        checkedButtonColor = 0xFFFFFFFF;

        borderWidth = dp2pxInt(1f);

        int effectDuration = 300;
        enableEffect = true;

        shadowEffect = true;

        paint = new Paint(Paint.ANTI_ALIAS_FLAG);
        buttonPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
        buttonPaint.setColor(uncheckButtonColor);

        glowPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
        trackBorderPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
        trackBorderPaint.setStyle(Paint.Style.STROKE);

        shadowPaint = new Paint(Paint.ANTI_ALIAS_FLAG);

        viewState = new ViewState();
        beforeState = new ViewState();
        afterState = new ViewState();

        valueAnimator = ValueAnimator.ofFloat(0f, 1f);
        valueAnimator.setDuration(effectDuration);
        valueAnimator.setRepeatCount(0);
        valueAnimator.setInterpolator(new android.view.animation.OvershootInterpolator(0.6f));

        valueAnimator.addUpdateListener(animatorUpdateListener);
        valueAnimator.addListener(animatorListener);

        super.setClickable(true);
        this.setPadding(0, 0, 0, 0);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
            setLayerType(LAYER_TYPE_SOFTWARE, null);
        }
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        final int widthMode = MeasureSpec.getMode(widthMeasureSpec);
        final int heightMode = MeasureSpec.getMode(heightMeasureSpec);

        if(widthMode == MeasureSpec.UNSPECIFIED || widthMode == MeasureSpec.AT_MOST){
            widthMeasureSpec = MeasureSpec.makeMeasureSpec(DEFAULT_WIDTH, MeasureSpec.EXACTLY);
        }
        if(heightMode == MeasureSpec.UNSPECIFIED || heightMode == MeasureSpec.AT_MOST){
            heightMeasureSpec = MeasureSpec.makeMeasureSpec(DEFAULT_HEIGHT, MeasureSpec.EXACTLY);
        }
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);
    }

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        super.onSizeChanged(w, h, oldw, oldh);

        float viewPadding = dp2px(3);

        height = h - viewPadding - viewPadding;
        width = w - viewPadding - viewPadding;

        viewRadius = height * .5f;
        buttonRadius = viewRadius - dp2px(2.5f);

        left = viewPadding;
        top = viewPadding;
        right = w - viewPadding;
        bottom = h - viewPadding;

        centerX = (left + right) * .5f;
        centerY = (top + bottom) * .5f;

        buttonMinX = left + viewRadius;
        buttonMaxX = right - viewRadius;

        if(isChecked()){
            setCheckedViewState(viewState);
        }else{
            setUncheckViewState(viewState);
        }

        isUiInited = true;
        postInvalidate();
    }

    private void setUncheckViewState(ViewState viewState){
        viewState.radius = 0;
        viewState.checkStateColor = uncheckColor;
        viewState.buttonX = buttonMinX;
        buttonPaint.setColor(uncheckButtonColor);
    }

    private void setCheckedViewState(ViewState viewState){
        viewState.radius = viewRadius;
        viewState.checkStateColor = checkedColor;
        viewState.buttonX = buttonMaxX;
        buttonPaint.setColor(checkedButtonColor);
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);

        float fillProgress = 0f;
        if (buttonMaxX > buttonMinX) {
            fillProgress = (viewState.buttonX - buttonMinX) / (buttonMaxX - buttonMinX);
        }
        fillProgress = Math.max(0f, Math.min(1f, fillProgress));

        // 1. Draw outer glow when active
        if (fillProgress > 0.01f) {
            int glowAlpha = (int)(35 * fillProgress);
            glowPaint.setColor((glowAlpha << 24) | (checkedColor & 0x00FFFFFF));
            glowPaint.setStyle(Paint.Style.FILL);
            float glowExpand = dp2px(3) * fillProgress;
            drawRoundRect(canvas, left - glowExpand, top - glowExpand,
                    right + glowExpand, bottom + glowExpand,
                    viewRadius + glowExpand, glowPaint);
        }

        // 2. Draw track background (dark base)
        paint.setStyle(Paint.Style.FILL);
        paint.setColor(0xFF111111);
        drawRoundRect(canvas, left, top, right, bottom, viewRadius, paint);

        // 3. Draw active fill with gradient
        if (fillProgress > 0.01f) {
            int activeAlpha = (int)(255 * fillProgress);

            // Gradient fill from left to right
            int startColor = (activeAlpha << 24) | (checkedColor & 0x00FFFFFF);
            int endColor = (activeAlpha << 24) | (darkenColor(checkedColor, 0.7f) & 0x00FFFFFF);

            paint.setStyle(Paint.Style.FILL);
            paint.setShader(new LinearGradient(left, top, right, bottom,
                    startColor, endColor, Shader.TileMode.CLAMP));
            drawRoundRect(canvas, left, top, right, bottom, viewRadius, paint);
            paint.setShader(null);
        }

        // 4. Draw track border
        trackBorderPaint.setStrokeWidth(dp2px(1f));
        if (fillProgress > 0.5f) {
            int borderAlpha = (int)(100 * fillProgress);
            trackBorderPaint.setColor((borderAlpha << 24) | (checkedColor & 0x00FFFFFF));
        } else {
            trackBorderPaint.setColor(0xFF2A2A2A);
        }
        drawRoundRect(canvas, left, top, right, bottom, viewRadius, trackBorderPaint);

        // 5. Draw inner track highlight (subtle top reflection)
        paint.setStyle(Paint.Style.FILL);
        int highlightAlpha = fillProgress > 0.5f ? (int)(15 * fillProgress) : 8;
        paint.setColor((highlightAlpha << 24) | 0x00FFFFFF);
        float inset = dp2px(1.5f);
        drawRoundRect(canvas, left + inset, top + inset,
                right - inset, top + height * 0.45f,
                viewRadius - inset, paint);

        // 6. Draw button shadow
        float bx = viewState.buttonX;
        float by = centerY;
        shadowPaint.setColor(0x00000000);
        shadowPaint.setShadowLayer(dp2px(4), 0, dp2px(1.5f), 0x55000000);
        canvas.drawCircle(bx, by, buttonRadius, shadowPaint);

        // 7. Draw button (thumb) with gradient
        int thumbColor1, thumbColor2;
        if (fillProgress > 0.5f) {
            thumbColor1 = 0xFFFFFFFF;
            thumbColor2 = 0xFFE8E8E8;
        } else {
            thumbColor1 = blendColor(0xFF666666, 0xFFFFFFFF, fillProgress * 2f);
            thumbColor2 = blendColor(0xFF444444, 0xFFE8E8E8, fillProgress * 2f);
        }

        buttonPaint.setShader(new LinearGradient(
                bx - buttonRadius, by - buttonRadius,
                bx + buttonRadius, by + buttonRadius,
                thumbColor1, thumbColor2,
                Shader.TileMode.CLAMP));
        canvas.drawCircle(bx, by, buttonRadius, buttonPaint);
        buttonPaint.setShader(null);

        // 8. Draw thumb inner highlight (small bright dot)
        paint.setStyle(Paint.Style.FILL);
        int dotAlpha = fillProgress > 0.5f ? 60 : 30;
        paint.setColor((dotAlpha << 24) | 0x00FFFFFF);
        canvas.drawCircle(bx, by - buttonRadius * 0.3f, buttonRadius * 0.35f, paint);
    }

    private int darkenColor(int color, float factor) {
        int r = (int)(((color >> 16) & 0xFF) * factor);
        int g = (int)(((color >> 8) & 0xFF) * factor);
        int b = (int)((color & 0xFF) * factor);
        return 0xFF000000 | (r << 16) | (g << 8) | b;
    }

    private int blendColor(int color1, int color2, float ratio) {
        ratio = Math.max(0f, Math.min(1f, ratio));
        int r = (int)(((color1 >> 16) & 0xFF) * (1 - ratio) + ((color2 >> 16) & 0xFF) * ratio);
        int g = (int)(((color1 >> 8) & 0xFF) * (1 - ratio) + ((color2 >> 8) & 0xFF) * ratio);
        int b = (int)((color1 & 0xFF) * (1 - ratio) + (color2 & 0xFF) * ratio);
        return 0xFF000000 | (r << 16) | (g << 8) | b;
    }

    private void drawRoundRect(Canvas canvas, float left, float top, float right, float bottom, float backgroundRadius, Paint paint){
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            canvas.drawRoundRect(left, top, right, bottom, backgroundRadius, backgroundRadius, paint);
        }else{
            rect.set(left, top, right, bottom);
            canvas.drawRoundRect(rect, backgroundRadius, backgroundRadius, paint);
        }
    }

    private void toggle(boolean animate, boolean broadcast) {
        if(!isEnabled()){return;}

        if(isEventBroadcast){
            throw new RuntimeException("should NOT switch the state in method: [onCheckedChanged]!");
        }
        if(!isUiInited){
            isChecked = !isChecked;
            if(broadcast){
                broadcastEvent();
            }
            return;
        }

        if(valueAnimator.isRunning()){
            valueAnimator.cancel();
        }

        if(!enableEffect || !animate){
            isChecked = !isChecked;
            if(isChecked()){
                setCheckedViewState(viewState);
            }else{
                setUncheckViewState(viewState);
            }
            postInvalidate();
            if(broadcast){
                broadcastEvent();
            }
            return;
        }

        animateState = ANIMATE_STATE_SWITCH;
        beforeState.copy(viewState);

        if(isChecked()){
            setUncheckViewState(afterState);
        }else{
            setCheckedViewState(afterState);
        }
        valueAnimator.start();
    }

    private void broadcastEvent() {
        if(onCheckedChangeListener != null){
            isEventBroadcast = true;
            onCheckedChangeListener.onCheckedChanged(this, isChecked());
        }
        isEventBroadcast = false;
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if(!isEnabled()){return false;}
        int actionMasked = event.getActionMasked();

        switch (actionMasked){
            case MotionEvent.ACTION_DOWN:{
                isTouchingDown = true;
                touchDownTime = System.currentTimeMillis();
                removeCallbacks(postPendingDrag);
                break;
            }
            case MotionEvent.ACTION_MOVE:{
                break;
            }
            case MotionEvent.ACTION_UP:{
                isTouchingDown = false;
                removeCallbacks(postPendingDrag);
                toggle();
                break;
            }
            case MotionEvent.ACTION_CANCEL:{
                isTouchingDown = false;
                removeCallbacks(postPendingDrag);
                break;
            }
        }
        return true;
    }

    private boolean isInAnimating(){
        return animateState != ANIMATE_STATE_NONE;
    }

    private boolean isPendingDragState(){
        return animateState == ANIMATE_STATE_PENDING_DRAG || animateState == ANIMATE_STATE_PENDING_RESET;
    }

    private boolean isDragState(){
        return animateState == ANIMATE_STATE_DRAGING;
    }

    private void pendingDragState() {
        if(isInAnimating()){return;}
        if(!isTouchingDown){return;}
        if(valueAnimator.isRunning()){ valueAnimator.cancel(); }
        animateState = ANIMATE_STATE_PENDING_DRAG;
        beforeState.copy(viewState);
        afterState.copy(viewState);
        if(isChecked()){
            afterState.checkStateColor = checkedColor;
            afterState.buttonX = buttonMaxX;
        }else{
            afterState.checkStateColor = uncheckColor;
            afterState.buttonX = buttonMinX;
            afterState.radius = viewRadius;
        }
        valueAnimator.start();
    }

    private void pendingCancelDragState() {
        if(isDragState() || isPendingDragState()){
            if(valueAnimator.isRunning()){ valueAnimator.cancel(); }
            animateState = ANIMATE_STATE_PENDING_RESET;
            beforeState.copy(viewState);
            if(isChecked()){
                setCheckedViewState(afterState);
            }else{
                setUncheckViewState(afterState);
            }
            valueAnimator.start();
        }
    }

    private void pendingSettleState() {
        if(valueAnimator.isRunning()){ valueAnimator.cancel(); }
        animateState = ANIMATE_STATE_PENDING_SETTLE;
        beforeState.copy(viewState);
        if(isChecked()){
            setCheckedViewState(afterState);
        }else{
            setUncheckViewState(afterState);
        }
        valueAnimator.start();
    }

    private static float dp2px(float dp){
        Resources r = Resources.getSystem();
        return TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, dp, r.getDisplayMetrics());
    }

    private static int dp2pxInt(float dp){
        return (int) dp2px(dp);
    }

    private static int optInt(TypedArray typedArray, int index, int def) {
        if(typedArray == null){return def;}
        return typedArray.getInt(index, def);
    }

    private static float optPixelSize(TypedArray typedArray, int index, float def) {
        if(typedArray == null){return def;}
        return typedArray.getDimension(index, def);
    }

    private static int optPixelSize(TypedArray typedArray, int index, int def) {
        if(typedArray == null){return def;}
        return typedArray.getDimensionPixelOffset(index, def);
    }

    private static int optColor(TypedArray typedArray, int index, int def) {
        if(typedArray == null){return def;}
        return typedArray.getColor(index, def);
    }

    private static boolean optBoolean(TypedArray typedArray, int index, boolean def) {
        if(typedArray == null){return def;}
        return typedArray.getBoolean(index, def);
    }

    private int shadowRadius;
    private int shadowOffset;
    private int shadowColor;
    private float viewRadius;
    private float buttonRadius;
    private float height;
    private float width;
    private float left;
    private float top;
    private float right;
    private float bottom;
    private float centerX;
    private float centerY;
    private int uncheckColor;
    private int checkedColor;
    private int borderWidth;
    private int uncheckButtonColor;
    private int checkedButtonColor;
    private float buttonMinX;
    private float buttonMaxX;
    private Paint buttonPaint;
    private Paint paint;
    private Paint glowPaint;
    private Paint trackBorderPaint;
    private Paint shadowPaint;
    private ViewState viewState;
    private ViewState beforeState;
    private ViewState afterState;
    private RectF rect = new RectF();
    private int animateState = ANIMATE_STATE_NONE;
    private ValueAnimator valueAnimator;
    private final android.animation.ArgbEvaluator argbEvaluator = new android.animation.ArgbEvaluator();
    private boolean isChecked;
    private boolean enableEffect;
    private boolean shadowEffect;
    private boolean isTouchingDown = false;
    private boolean isUiInited = false;
    private boolean isEventBroadcast = false;
    private OnCheckedChangeListener onCheckedChangeListener;
    private long touchDownTime;

    private Runnable postPendingDrag = new Runnable() {
        @Override
        public void run() {
            if(!isInAnimating()){
                pendingDragState();
            }
        }
    };

    private ValueAnimator.AnimatorUpdateListener animatorUpdateListener = new ValueAnimator.AnimatorUpdateListener() {
        @Override
        public void onAnimationUpdate(ValueAnimator animation) {
            float value = (Float) animation.getAnimatedValue();
            switch (animateState) {
                case ANIMATE_STATE_PENDING_SETTLE:
                case ANIMATE_STATE_PENDING_RESET:
                case ANIMATE_STATE_PENDING_DRAG:
                    viewState.radius = beforeState.radius + (afterState.radius - beforeState.radius) * value;
                    if(animateState != ANIMATE_STATE_PENDING_DRAG){
                        viewState.buttonX = beforeState.buttonX + (afterState.buttonX - beforeState.buttonX) * value;
                    }
                    viewState.checkStateColor = (int) argbEvaluator.evaluate(value, beforeState.checkStateColor, afterState.checkStateColor);
                    break;
                case ANIMATE_STATE_SWITCH:
                    viewState.buttonX = beforeState.buttonX + (afterState.buttonX - beforeState.buttonX) * value;
                    float fraction = (viewState.buttonX - buttonMinX) / (buttonMaxX - buttonMinX);
                    viewState.checkStateColor = (int) argbEvaluator.evaluate(fraction, uncheckColor, checkedColor);
                    viewState.radius = fraction * viewRadius;
                    break;
                default:
                    break;
            }
            postInvalidate();
        }
    };

    private Animator.AnimatorListener animatorListener = new Animator.AnimatorListener() {
        @Override
        public void onAnimationStart(Animator animation) {}
        @Override
        public void onAnimationEnd(Animator animation) {
            switch (animateState) {
                case ANIMATE_STATE_PENDING_DRAG:
                    animateState = ANIMATE_STATE_DRAGING;
                    viewState.radius = viewRadius;
                    postInvalidate();
                    break;
                case ANIMATE_STATE_PENDING_RESET:
                case ANIMATE_STATE_PENDING_SETTLE:
                    animateState = ANIMATE_STATE_NONE;
                    postInvalidate();
                    broadcastEvent();
                    break;
                case ANIMATE_STATE_SWITCH:
                    isChecked = !isChecked;
                    animateState = ANIMATE_STATE_NONE;
                    postInvalidate();
                    broadcastEvent();
                    break;
                default:
                    break;
            }
        }
        @Override
        public void onAnimationCancel(Animator animation) {}
        @Override
        public void onAnimationRepeat(Animator animation) {}
    };

    private static class ViewState {
        float buttonX;
        int checkStateColor;
        float radius;
        ViewState(){}
        private void copy(ViewState source){
            this.buttonX = source.buttonX;
            this.checkStateColor = source.checkStateColor;
            this.radius = source.radius;
        }
    }
}
