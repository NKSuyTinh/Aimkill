package com.terminalx999;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Base64;
import android.widget.ImageView;

public class ImageBase64 extends ImageView {

    public ImageBase64(Context context) {
        super(context);
        this.setScaleType(ImageView.ScaleType.FIT_CENTER);
        this.setAdjustViewBounds(true);
    }

    public void setImageBase64(String image) {
        try {
            if (image == null || image.isEmpty()) {
                return;
            }
            byte[] decodeImageBase64 = Base64.decode(image, Base64.DEFAULT);
            Bitmap bitmap = BitmapFactory.decodeByteArray(decodeImageBase64, 0, decodeImageBase64.length);
            if (bitmap != null) {
                this.setImageBitmap(bitmap);
            }
        } catch (Exception e) {
            // Ignore invalid Base64 strings to prevent crash
        }
    }

}

