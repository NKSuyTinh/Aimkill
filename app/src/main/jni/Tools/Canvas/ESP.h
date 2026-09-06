#ifndef ESP_H
#define ESP_H

#include <jni.h>
#include "Color.hpp"
#include "Rect.hpp"

class ESP {
private:
    JNIEnv *_env;
    jobject _cvsView;
    jobject _cvs;

public:
    ESP() {
        _env = nullptr;
        _cvsView = nullptr;
        _cvs = nullptr;
    }

    ESP(JNIEnv *env, jobject cvsView, jobject cvs) {
        this->_env = env;
        this->_cvsView = cvsView;
        this->_cvs = cvs;
    }

    bool isValid() const {
        return (_env != nullptr && _cvsView != nullptr && _cvs != nullptr);
    }

    int getWidth() const {
        if (isValid()) {
            jclass canvas = _env->GetObjectClass(_cvs);
            jmethodID width = _env->GetMethodID(canvas, "getWidth", "()I");
            return _env->CallIntMethod(_cvs, width);
        }
        return 0;
    }

    int getHeight() const {
        if (isValid()) {
            jclass canvas = _env->GetObjectClass(_cvs);
            jmethodID width = _env->GetMethodID(canvas, "getHeight", "()I");
            return _env->CallIntMethod(_cvs, width);
        }
        return 0;
    }

    void DrawLine(Color color, float thickness, Vector3 start, Vector3 end) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawline = _env->GetMethodID(canvasView, "DrawLine",
                                                   "(Landroid/graphics/Canvas;IIIIFFFFF)V");
            _env->CallVoidMethod(_cvsView, drawline, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 thickness,
                                 start.X, start.Y, end.X, end.Y);
        }
    }

    void DrawText(Color color, const char *txt, Vector2 pos, float size) {
        if (!isValid() || txt == nullptr)
            return;

        JNIEnv* env = _env;  // assuming _env is your JNI environment pointer
        jobject cvsView = _cvsView; // your Java canvas view object
        jobject cvs = _cvs;          // your Canvas object

        jclass canvasViewClass = env->GetObjectClass(cvsView);
        if (canvasViewClass == nullptr) return;

        jmethodID drawTextMethod = env->GetMethodID(
                canvasViewClass,
                "DrawText",
                "(Landroid/graphics/Canvas;IIIILjava/lang/String;FFF)V"
        );
        if (drawTextMethod == nullptr) {
            env->DeleteLocalRef(canvasViewClass);
            return;
        }

        // Convert UTF-8 C string to Java String using NewStringUTF is risky
        // Instead, use NewString with UTF-16 if you have it,
        // but if not, convert manually:

        // Convert UTF-8 (char*) to UTF-16 (jchar array)
        // We'll use a helper here:

        // Step 1: convert UTF-8 string to UTF-16 in C++
        std::u16string utf16str;
        {
            const char* src = txt;
            while (*src) {
                unsigned char c = *src;
                if (c < 0x80) {
                    utf16str.push_back(c);
                    src++;
                } else if ((c & 0xE0) == 0xC0) { // 2 bytes
                    char c1 = *(src + 1);
                    char16_t w = ((c & 0x1F) << 6) | (c1 & 0x3F);
                    utf16str.push_back(w);
                    src += 2;
                } else if ((c & 0xF0) == 0xE0) { // 3 bytes
                    char c1 = *(src + 1);
                    char c2 = *(src + 2);
                    char16_t w = ((c & 0x0F) << 12) | ((c1 & 0x3F) << 6) | (c2 & 0x3F);
                    utf16str.push_back(w);
                    src += 3;
                } else {
                    // skip or replace invalid
                    src++;
                }
            }
        }

        // Step 2: create Java String from UTF-16 array
        jstring javaStr = env->NewString((const jchar*)utf16str.data(), utf16str.size());
        if (javaStr == nullptr) {
            env->DeleteLocalRef(canvasViewClass);
            return;
        }

        // Call the Java DrawText method
        env->CallVoidMethod(
                cvsView,
                drawTextMethod,
                cvs,
                (int)color.a, (int)color.r, (int)color.g, (int)color.b,
                javaStr, pos.X, pos.Y, size
        );

        // Clean up local refs
        env->DeleteLocalRef(javaStr);
        env->DeleteLocalRef(canvasViewClass);
    }


    void DrawText2(Color color, float stroke, const char *txt, Vector2 pos, float size) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtext = _env->GetMethodID(canvasView, "DrawText",
                                                   "(Landroid/graphics/Canvas;IIIILjava/lang/String;FFF)V");
            _env->CallVoidMethod(_cvsView, drawtext, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 _env->NewStringUTF(txt), pos.X, pos.Y, size);
        }
    }

    void DrawName(Color color, const char *txt, Vector3 pos, float size) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtext = _env->GetMethodID(canvasView, "DrawName",
                                                   "(Landroid/graphics/Canvas;IIIILjava/lang/String;IFFF)V");
            jstring s=_env->NewStringUTF(txt);
            _env->CallVoidMethod(_cvsView, drawtext, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 s, pos.X, pos.Y, size);
            _env->DeleteLocalRef(s);
        }
    }

    void DrawFilledCircle(Color color, Vector2 pos, float radius) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawfilledcircle = _env->GetMethodID(canvasView, "DrawFilledCircle",
                                                           "(Landroid/graphics/Canvas;IIIIFFF)V");
            _env->CallVoidMethod(_cvsView, drawfilledcircle, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b, pos.X, pos.Y, radius);
        }
    }

    void DrawCircle(Color color,float stroke, Vector2 pos, float radius) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawcircle = _env->GetMethodID(canvasView, "DrawCircle",
                                                     "(Landroid/graphics/Canvas;IIIIFFFF)V");
            _env->CallVoidMethod(_cvsView, drawcircle, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,stroke, pos.X, pos.Y, radius);
        }
    }

    void DrawCircleSket(Color color, float stroke, Vector3 pos, float radius) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawcircle = _env->GetMethodID(canvasView, "DrawCircle", "(Landroid/graphics/Canvas;IIIIFFFF)V");
            _env->CallVoidMethod(_cvsView, drawcircle, _cvs, (int) color.a, (int) color.r, (int) color.g, (int) color.b,stroke, pos.X, pos.Y, radius);
        }
    }

    void DrawCircleSkeleton(Color color, float stroke, Vector3 pos, float radius) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawcircle = _env->GetMethodID(canvasView, "DrawCircle", "(Landroid/graphics/Canvas;IIIIFFFF)V");
            _env->CallVoidMethod(_cvsView, drawcircle, _cvs, (int) color.a, (int) color.r, (int) color.g, (int) color.b,stroke, pos.X, pos.Y, radius);
        }
    }

    void DrawFilledRect(Color color, Vector3 pos, float width, float height) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawfilledrect = _env->GetMethodID(canvasView, "DrawFilledRect",
                                                         "(Landroid/graphics/Canvas;IIIIFFFF)V");
            _env->CallVoidMethod(_cvsView, drawfilledrect, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b, pos.X, pos.Y, width, height);
        }
    }

    void DrawBox(Color color, float stroke, Rect rect) {
        Vector3 v1 = Vector3(rect.x, rect.y);
        Vector3 v2 = Vector3(rect.x + rect.width, rect.y);
        Vector3 v3 = Vector3(rect.x + rect.width, rect.y + rect.height);
        Vector3 v4 = Vector3(rect.x, rect.y + rect.height);

        DrawLine(color, stroke, v1, v2); // LINE UP
        DrawLine(color, stroke, v2, v3); // LINE RIGHT
        DrawLine(color, stroke, v3, v4); // LINE DOWN
        DrawLine(color, stroke, v4, v1); // LINE LEFT
    }

    void DrawBox4Line(int x, int y, int w, int h, Color color, float thickness) {
        int iw = w / 4;
        int ih = h / 4;

        DrawLine(color,thickness,Vector3(x, y),Vector3(x + iw, y));
        DrawLine(color,thickness,Vector3(x + w - iw, y),Vector3(x + w, y));
        DrawLine(color,thickness,Vector3(x, y),Vector3(x, y + ih));
        DrawLine(color,thickness,Vector3(x + w - 1, y),Vector3(x + w - 1, y + ih));

        DrawLine(color,thickness,Vector3(x, y + h),Vector3(x + iw, y + h));
        DrawLine(color,thickness,Vector3(x + w - iw, y + h),Vector3(x + w, y + h));
        DrawLine(color,thickness,Vector3(x, y + h - ih), Vector3(x, y + h));
        DrawLine(color,thickness,Vector3(x + w - 1, y + h - ih), Vector3(x + w - 1, y + h));
    }

    void DrawLineVida(Color color, float thickness, Vector2 start, Vector2 end) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawlinevida = _env->GetMethodID(canvasView, "DrawLineVida",
                                                       "(Landroid/graphics/Canvas;IIIIFFFFF)V");
            _env->CallVoidMethod(_cvsView, drawlinevida, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 thickness,
                                 start.X, start.Y, end.X, end.Y);
        }
    }

    void DrawVerticalHealthBar(Vector2 screenPos, float height, float maxHealth, float currentHealth) {
        screenPos += Vector2(8.0f, 0.0f);
        DrawBox(Color(0, 0, 0, 255), 3, Rect(screenPos.X, screenPos.Y, 5.0f, height + 2));
        screenPos += Vector2(1.0f, 1.0f);
        Color clr = Color(255, 0, 255, 0);
        float barHeight = (currentHealth * height) / maxHealth;
        if (currentHealth <= (maxHealth * 0.6)) {
            clr = Color(0, 255, 0, 255);
        }
        if (currentHealth < (maxHealth * 0.3)) {
            clr = Color(255, 255, 0, 255);
        }
        DrawBox(clr, 3, Rect(screenPos.X, screenPos.Y, 2.0f, barHeight));
    }

    void DrawHorizontalHealthBar(Vector2 screenPos, float width, float maxHealth, float currentHealth) {
        screenPos -= Vector2(0.0f, 5.0f);
        DrawBox(Color(0, 0, 0, 255), 1, Rect(screenPos.X, screenPos.Y, width + 2, 5.0f));
        screenPos += Vector2(1.0f, 1.0f);
        Color clr = Color(0, 255, 0, 255);
        float hpWidth = (currentHealth * width) / maxHealth;
        if (currentHealth <= (maxHealth * 0.6)) {
            clr = Color(255, 255, 0, 255);
        }
        if (currentHealth < (maxHealth * 0.4)) {
            clr = Color(255, 0, 0, 255);
        }
        DrawBox(clr, 1, Rect(screenPos.X, screenPos.Y, hpWidth, 3.0f));
    }
};

#endif


