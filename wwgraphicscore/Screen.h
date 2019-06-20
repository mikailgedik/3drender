//
// Created by Admin on 08.09.2018.
//

#ifndef INC_3DGRAPHICSCALCULATOR_SCREEN_H
#define INC_3DGRAPHICSCALCULATOR_SCREEN_H


#include <exception>
#include <string>
#include <cmath>

namespace WWGraphics {
    typedef int COLORTYPE;

    class Screen {
    public:
        Screen(int w, int h, COLORTYPE color);

        Screen(int w, int h);

        Screen(WWGraphics::COLORTYPE* const ref, int w, int h);

        virtual ~Screen();

        Screen& fill(WWGraphics::COLORTYPE color);

        Screen& drawScreen(const Screen * const other, int xStartOnThis, int yStartOnThis, int xStartOnOther, int yStartOnOther, int width, int height);

        Screen& drawScreen(const Screen * const other, int xStartOnThis, int yStartOnThis, int xStartOnOther, int yStartOnOther);

        Screen& drawScreen(const Screen * const other, int xStartOnThis, int yStartOnThis);

        Screen& drawOval(int yStart, int xStart, int width, int height, COLORTYPE color);

        Screen& fillOval(int yStart, int xStart, int width, int height, COLORTYPE color);

        Screen& drawCircle(int xStart, int yStart, int r, COLORTYPE color);

        Screen& fillCircle(int xStart, int yStart, int r, COLORTYPE color);

        Screen& drawLine(int xstart, int ystart, int xend, int yend, COLORTYPE color);

        inline bool setPixel(int x, int y, WWGraphics::COLORTYPE color) {
            if(!isValid(x, y)) {
                return false;
            }
            pixels[x + y* width] = color;
            return true;
        }

        inline bool isValid(int x, int y) const {
            return x >= 0 & x < width & y >= 0 & y < height;
        }

        inline WWGraphics::COLORTYPE* const getPixels() const {
            return pixels;
        }

        const int getWidth() const;

        const int getHeight() const;

        const int getSize() const;

    private:
        const int width, height, size;
        WWGraphics::COLORTYPE* const pixels;
        bool isRef = false;

        inline int getXForOval(int x, int a, int b) {
            return int(std::sqrt(b * b - (b * b * x * x) / (a * a)));
        }
        inline int getYForOval(int y, int a, int b) {
            return int(std::sqrt((a * a * (b * b - y * y)) / (b * b)));
        }
    };

}


#endif //INC_3DGRAPHICSCALCULATOR_SCREEN_H
