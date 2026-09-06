#include "Color.hpp"
#include "Unity/Vector2.hpp"
#include "../Canvas/Rect.hpp"

#ifndef ANDROID_MENU_DRAW_H
#define ANDROID_MENU_DRAW_H

class DrawView {
private:

    JNIEnv *_env;
    jobject _cvsView;
    jobject _cvs;

public:
    DrawView() {
        _env = nullptr;
        _cvsView = nullptr;
        _cvs = nullptr;
    }

    DrawView(JNIEnv *env, jobject cvsView, jobject cvs) {
        this->_env = env;
        this->_cvsView = cvsView;
        this->_cvs = cvs;
    }

    bool isValid() const {
        return (this->_env != nullptr && this->_cvsView != nullptr && this->_cvs != nullptr);
    }

    int getWidth() const {
        if (isValid()) {
            return _env->CallIntMethod(_cvs,
                                       _env->GetMethodID(_env->GetObjectClass(_cvs), "getWidth",
                                                         "()I"));
        }
        return 0;
    }

    int getHeight() const {
        if (isValid()) {
            return _env->CallIntMethod(_cvs,
                                       _env->GetMethodID(_env->GetObjectClass(_cvs), "getHeight",
                                                         "()I"));
        }
        return 0;
    }

    void DrawLine(Color color, float thickness, Vector2 start, Vector2 end) {
        if (isValid()) {
            _env->CallVoidMethod(_cvsView,
                                 _env->GetMethodID(_env->GetObjectClass(_cvsView), "DrawLine",
                                                   "(Landroid/graphics/Canvas;IIIIFFFFF)V"), _cvs,
                                 (int) color.a, (int) color.r, (int) color.g, (int) color.b,
                                 thickness, start.X, start.Y, end.X, end.Y);
        }
        return;
    }

    void DrawTextWithShadow(Color textColor, const char *str, Vector2 pos, float size, Vector2 shadowOffset, float shadowOpacity) {
        if (isValid()) {
            // Desenhar a sombra em preto
            _env->CallVoidMethod(_cvsView,_env->GetMethodID(_env->GetObjectClass(_cvsView), "DrawText","(Landroid/graphics/Canvas;IIIIFLjava/lang/String;FFF)V"),_cvs,(int)(shadowOpacity * 255),0,0,0,0.6f,_env->NewStringUTF(str),pos.X + shadowOffset.X,pos.Y + shadowOffset.Y,size);

            // Desenhar o texto principal
            _env->CallVoidMethod(_cvsView,_env->GetMethodID(_env->GetObjectClass(_cvsView), "DrawText","(Landroid/graphics/Canvas;IIIIFLjava/lang/String;FFF)V"),_cvs,(int)textColor.a, (int)textColor.r, (int)textColor.g, (int)textColor.b,0.6f,_env->NewStringUTF(str),pos.X,pos.Y,size);
        }
        return;
    }

    void DrawFilledBoxGradient(Color startColor, Color endColor, Rect rect) {
        if (isValid()) {
            // Desenhar um retângulo com gradiente
            _env->CallVoidMethod(_cvsView,_env->GetMethodID(_env->GetObjectClass(_cvsView), "DrawGradientRect","(Landroid/graphics/Canvas;IIIIIIIIFFFF)V"),_cvs,(int)startColor.a, (int)startColor.r, (int)startColor.g, (int)startColor.b,(int)endColor.a, (int)endColor.r, (int)endColor.g, (int)endColor.b,rect.x, rect.y, rect.w, rect.h
            );
        }
        return;
    }


    void DrawText(Color color, const char *str, Vector2 pos, float size) {
        if (isValid()) {
            _env->CallVoidMethod(_cvsView,_env->GetMethodID(_env->GetObjectClass(_cvsView), "DrawText","(Landroid/graphics/Canvas;IIIIFLjava/lang/String;FFF)V"),_cvs, (int) color.a, (int) color.r, (int) color.g, (int) color.b,0.6f, _env->NewStringUTF(str), pos.X, pos.Y, size);
        }
        return;
    }

    void DrawCircle(Color color, float stroke, Vector2 pos, float radius) {
        if (isValid()) {
            _env->CallVoidMethod(_cvsView,
                                 _env->GetMethodID(_env->GetObjectClass(_cvsView), "DrawCircle",
                                                   "(Landroid/graphics/Canvas;IIIIFFFF)V"), _cvs,
                                 (int) color.a, (int) color.r, (int) color.g, (int) color.b, stroke,
                                 pos.X, pos.Y, radius);
        }
        return;
    }

    void DrawRoundRect(Color color, float stroke, int cx, int cy, Rect rect) {
        if (isValid()) {
            _env->CallVoidMethod(_cvsView,
                                 _env->GetMethodID(_env->GetObjectClass(_cvsView), "DrawRoundRect",
                                                   "(Landroid/graphics/Canvas;IIIIFIIFFFF)V"), _cvs,
                                 (int) color.a, (int) color.r, (int) color.g, (int) color.b, stroke,
                                 cx, cy, rect.x, rect.y, rect.w, rect.h);
        }
        return;
    }

    void DrawTextRect(Color color, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8,
                      Vector2 pos) {
        if (isValid()) {
            _env->CallVoidMethod(_cvsView,
                                 _env->GetMethodID(_env->GetObjectClass(_cvsView), "DrawTextRect",
                                                   "(Landroid/graphics/Canvas;IIIIIIIIIIIIFF)V"),
                                 _cvs, (int) color.a, (int) color.r, (int) color.g, (int) color.b,
                                 a1, a2, a3, a4, a5, a6, a7, a8, pos.X, pos.Y);
        }
        return;
    }

    void DrawFilledBox(Color color, Rect rect) {
        if (isValid()) {
            _env->CallVoidMethod(_cvsView,
                                 _env->GetMethodID(_env->GetObjectClass(_cvsView), "DrawFilledRect",
                                                   "(Landroid/graphics/Canvas;IIIIFFFF)V"), _cvs,
                                 (int) atoi("157"), (int) color.r, (int) color.g, (int) color.b,
                                 rect.x, rect.y, rect.w, rect.h);
        }
        return;
    }

    void DrawFilledRect(Color color, Rect rect) {
        if (isValid()) {
            _env->CallVoidMethod(_cvsView,
                                 _env->GetMethodID(_env->GetObjectClass(_cvsView), "DrawFilledRect",
                                                   "(Landroid/graphics/Canvas;IIIIFFFF)V"), _cvs,
                                 (int) color.a, (int) color.r, (int) color.g, (int) color.b, rect.x,
                                 rect.y, rect.w, rect.h);
        }
        return;
    }

    void DrawFilledRectinfo(Color color, Rect rect) {
        if (isValid()) {
            _env->CallVoidMethod(_cvsView,
                                 _env->GetMethodID(_env->GetObjectClass(_cvsView),
                                                   "DrawFilledRectInfo",
                                                   "(Landroid/graphics/Canvas;IIIIFFFF)V"), _cvs,
                                 (int) color.a, (int) color.r, (int) color.g, (int) color.b, rect.x,
                                 rect.y, rect.w, rect.h);
        }
        return;
    }

    void DrawFilledCircle(Color color, Vector2 pos, float radius) {
        if (isValid()) {
            _env->CallVoidMethod(_cvsView, _env->GetMethodID(_env->GetObjectClass(_cvsView),
                                                             "DrawFilledCircle",
                                                             "(Landroid/graphics/Canvas;IIIIFFF)V"),
                                 _cvs, (int) color.a, (int) color.r, (int) color.g, (int) color.b,
                                 pos.X, pos.Y, radius);
        }
        return;
    }

    void DrawBox(Color color, float stroke, Rect rect) {
        Vector2 v1 = Vector2(rect.x, rect.y);
        Vector2 v2 = Vector2(rect.x + rect.w, rect.y);
        Vector2 v3 = Vector2(rect.x + rect.w, rect.y + rect.h);
        Vector2 v4 = Vector2(rect.x, rect.y + rect.h);

        DrawLine(color, stroke, v1, v2); // LINE UP
        DrawLine(color, stroke, v2, v3); // LINE RIGHT
        DrawLine(color, stroke, v3, v4); // LINE DOWN
        DrawLine(color, stroke, v4, v1); // LINE LEFT
    }

    void DrawBox3D(Color color, float stroke, Rect rect, float depth) {
        // Vértices da frente
        Vector2 v1 = Vector2(rect.x, rect.y);                     // Canto superior esquerdo
        Vector2 v2 = Vector2(rect.x + rect.w, rect.y);            // Canto superior direito
        Vector2 v3 = Vector2(rect.x + rect.w, rect.y + rect.h);   // Canto inferior direito
        Vector2 v4 = Vector2(rect.x, rect.y + rect.h);            // Canto inferior esquerdo

        // Vértices da parte de trás com perspectiva
        float offsetX = depth * 0.8f; // Ajuste do deslocamento em X para perspectiva
        float offsetY = depth * 0.8f; // Ajuste do deslocamento em Y para perspectiva

        Vector2 v5 = Vector2(rect.x - offsetX, rect.y - offsetY);      // Canto superior esquerdo
        Vector2 v6 = Vector2(rect.x + rect.w - offsetX, rect.y - offsetY); // Canto superior direito
        Vector2 v7 = Vector2(rect.x + rect.w - offsetX,
                             rect.y + rect.h - offsetY); // Canto inferior direito
        Vector2 v8 = Vector2(rect.x - offsetX,
                             rect.y + rect.h - offsetY); // Canto inferior esquerdo

        // Desenhar a frente da caixa
        DrawLine(color, stroke, v1, v2); // Linha superior
        DrawLine(color, stroke, v2, v3); // Linha direita
        DrawLine(color, stroke, v3, v4); // Linha inferior
        DrawLine(color, stroke, v4, v1); // Linha esquerda

        // Desenhar a parte de trás
        DrawLine(color, stroke, v5, v6); // Linha superior
        DrawLine(color, stroke, v6, v7); // Linha direita
        DrawLine(color, stroke, v7, v8); // Linha inferior
        DrawLine(color, stroke, v8, v5); // Linha esquerda

        // Conectar a frente à parte de trás
        DrawLine(color, stroke, v1, v5); // Conexão esquerda
        DrawLine(color, stroke, v2, v6); // Conexão direita
        DrawLine(color, stroke, v3, v7); // Conexão inferior direita
        DrawLine(color, stroke, v4, v8); // Conexão inferior esquerda
    }


    void DrawCornerBox(Color color, float stroke, Rect rect, int cx, int cy) {
        DrawLine(color, stroke, Vector2(rect.x, rect.y), Vector2(rect.x + (rect.w / cx), rect.y));
        DrawLine(color, stroke, Vector2(rect.x, rect.y), Vector2(rect.x, rect.y + (rect.h / cy)));

        DrawLine(color, stroke, Vector2(rect.x + rect.w, rect.y),
                 Vector2(rect.x + rect.w - (rect.w / cx), rect.y));
        DrawLine(color, stroke, Vector2(rect.x + rect.w, rect.y),
                 Vector2(rect.x + rect.w, rect.y + (rect.h / cy)));

        DrawLine(color, stroke, Vector2(rect.x, rect.y + rect.h),
                 Vector2(rect.x + (rect.w / cx), rect.y + rect.h));
        DrawLine(color, stroke, Vector2(rect.x, rect.y + rect.h),
                 Vector2(rect.x, rect.y + rect.h - (rect.h / cy)));

        DrawLine(color, stroke, Vector2(rect.x + rect.w, rect.y + rect.h),
                 Vector2(rect.x + rect.w - (rect.w / cx), rect.y + rect.h));
        DrawLine(color, stroke, Vector2(rect.x + rect.w, rect.y + rect.h),
                 Vector2(rect.x + rect.w, rect.y + rect.h - (rect.h / cy)));
    }

    void DrawInfo(Color color, Rect screenPos, const char *Distance, float size) {
        // Define a altura acima da cabeça do jogador
        float offsetY = 100.0f; // Ajuste este valor para posicionar o texto corretamente

        // Desenha o texto da distância na cabeça do jogador
        DrawText(color, Distance, Vector2(screenPos.x + screenPos.w / 2, screenPos.y + offsetY), size);
    }


    void DrawText2(Color color, const char *nick, Vector2 pos, float size) {
        if (isValid()) {
            _env->CallVoidMethod(_cvsView,_env->GetMethodID(_env->GetObjectClass(_cvsView), "DrawText2","(Landroid/graphics/Canvas;IIIIFLjava/lang/String;FFF)V"),_cvs, (int) color.a, (int) color.r, (int) color.g, (int) color.b,0.6f, _env->NewStringUTF(nick), pos.X, pos.Y, size);
        }
        return;
    }




    void DrawSimpleHealthBar(Vector2 screenPos, float boxHeight, float maxHealth, float currentHealth) {
        float barWidth = 4.0f;
        currentHealth = std::max(0.0f, std::min(currentHealth, maxHealth));
        float healthPercentage = currentHealth / maxHealth;
        float filledHeight = boxHeight * healthPercentage;

        // Simple dark background
        DrawFilledRectHP(Color(20, 20, 20, 180), Rect(screenPos.X, screenPos.Y, barWidth, boxHeight));

        // Simple health fill
        Color fillColor = (healthPercentage > 0.6f) ? Color(0, 255, 0, 255) :
                          (healthPercentage > 0.3f) ? Color(255, 255, 0, 255) :
                          Color(255, 0, 0, 255);

        DrawFilledRectHP(fillColor, Rect(
                screenPos.X,
                screenPos.Y + boxHeight - filledHeight,
                barWidth,
                filledHeight
        ));
    }

    void DrawVerticalHealthBar(Vector2 screenPos, float boxHeight, float maxHealth, float currentHealth) {
        DrawSimpleHealthBar(screenPos, boxHeight, maxHealth, currentHealth);
    }


    void DrawFilledRectHP(Color color, Rect rect) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawrect = _env->GetMethodID(canvasView, ("DrawFilledRect"),
                                                   ("(Landroid/graphics/Canvas;IIIIFFFF)V"));
            _env->CallVoidMethod(_cvsView, drawrect, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 rect.x, rect.y, rect.w, rect.h);
        }
    }




    void DrawRoundRect(Color color, int stroke, int cx,int cy, Rect rect) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawrect = _env->GetMethodID(canvasView, "DrawRoundRect",
                                                   "(Landroid/graphics/Canvas;IIIIIIIFFFF)V");
            _env->CallVoidMethod(_cvsView, drawrect, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 stroke, cx,cy, rect.x, rect.y, rect.w, rect.h);
        }
    }

    void HealthBar(float hp, Vector2 pos, int height )
    {
        float flBoxes = ceil(hp / 10.f);
        float flX = pos.X + 2 - height / 4.f;
        float flY = pos.Y - 1;
        float flHeight = height / 10.f;
        float flMultiplier = 12 / 250.f; flMultiplier *= flBoxes - 1;
        Color ColHealth = FromHSB( flMultiplier, 1, 1 );

        DrawBox(Color( 80, 80, 80, 125 ),2, Rect(flX, flY, 4, height + 2));
        DrawFilledRectHP( Color::Black1(),Rect(flX, flY, 2, height + 2));
        DrawFilledRectHP(ColHealth, Rect(flX - 1, flY, 2, flHeight * flBoxes + 1) );

        for ( int i = 0; i < 10; i++ )
            DrawLine(Color::Black(), 1,Vector2( flX, flY + i * flHeight), Vector2(flX + 4, flY + i * flHeight));
    }





    void DrawNameWithCard(Color color, const char *name, const char *distance, Vector2 pos, float size) {
        if (isValid()) {
            _env->CallVoidMethod(_cvsView,
                                 _env->GetMethodID(_env->GetObjectClass(_cvsView), "DrawNameWithCard",
                                                   "(Landroid/graphics/Canvas;IIIILjava/lang/String;Ljava/lang/String;FFF)V"), _cvs,
                                 (int) color.a, (int) color.r, (int) color.g, (int) color.b,
                                 _env->NewStringUTF(name), _env->NewStringUTF(distance), pos.X, pos.Y, size);
        }
        return;
    }

};

#endif
