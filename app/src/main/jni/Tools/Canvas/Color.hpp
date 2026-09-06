
#ifndef COLOR_H
#define COLOR_H

using namespace std;

class Color {
public:
    float r;
    float g;
    float b;
    float a;

    Color() {
        this->r = 0;
        this->g = 0;
        this->b = 0;
        this->a = 0;
    }

    Color(float r, float g, float b, float a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    Color(float r, float g, float b) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = 255;
    }

    static Color Red() {
        return Color(255, 0, 0);
    }
    static Color Green() {
        return Color(0, 255, 0);
    }
    static Color Blue() {
        return Color(0, 0, 255);
    }
    static Color White() {
        return Color(255, 255, 255);
    }
    static Color Black() {
        return Color(0, 0, 0);
    }
    static Color Yellow() {
        return Color(255, 255, 0);
    }
    static Color Cyan() {
        return Color(0, 255, 255);
    }
    static Color Magenta() {
        return Color(255, 0, 255);
    }
    static Color Gray() {
        return Color(128, 128, 128);
    }
    static Color Purple() {
        return Color(128,0,128);
    }
    static Color Orange() {
        return Color(255,140,0);
    }
    static Color Teal() {
        return Color(0,128,128);
    }
    static Color SteelBlue() {
        return Color(70,130,180);
    }
    static Color DeepPink() {
        return Color(255,20,147);
    }

    static Color Black1() {
        return Color(0, 0, 0,100);
    }
};

static Color FromHSB(float hue, float saturation, float brightness)
{
    Color white = Color::White();

    float h = hue == 1.0f ? 0 : hue * 6.0f;
    float f = h - (int)h;
    float p = brightness * (1.0f - saturation);
    float q = brightness * (1.0f - saturation * f);
    float t = brightness * (1.0f - (saturation * (1.0f - f)));

    if (h < 1)
    {
        white.r = (brightness * 255.0f);
        white.g = (t * 255.0f);
        white.b = (p * 255.0f);
    }
    else if (h < 2)
    {
        white.r = (q * 255.0f);
        white.g = (brightness * 255.0f);
        white.b = (p * 255.0f);
    }
    else if (h < 3)
    {
        white.r = (p * 255.0f);
        white.g = (brightness * 255.0f);
        white.b = (t * 255.0f);
    }
    else if (h < 4)
    {
        white.r = (p * 255.0f);
        white.g = (q * 255.0f);
        white.b = (brightness * 255.0f);
    }
    else if (h < 5)
    {

        white.r = (t * 255.0f);
        white.g = (p * 255.0f);
        white.b = (brightness * 255.0f);
    }
    else
    {

        white.r = (brightness * 255.0f);
        white.g = (p * 255.0f);
        white.b = (q * 255.0f);
    }
    return white;
}

#endif
