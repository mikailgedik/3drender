//
// Created by Admin on 08.09.2018.
//

#include <cassert>
#include <cmath>
#include <iostream>
#include "Screen.h"

WWGraphics::Screen::Screen(int w, int h, WWGraphics::COLORTYPE color) : width(w), height(h), size(w * h),
                                                                        pixels(new WWGraphics::COLORTYPE[size]) {
    if (w < 0 || h < 0) {
        throw "width/height negative";
    }
    fill(color);
}

WWGraphics::Screen::Screen(WWGraphics::COLORTYPE *const ref, int w, int h) : width(w), height(h), size(w * h),
                                                                             pixels(ref), isRef(true) {
}

WWGraphics::Screen::Screen(int w, int h) : Screen(w, h, -1) {}

WWGraphics::Screen &WWGraphics::Screen::fill(WWGraphics::COLORTYPE color) {
    for (int i = 0; i < size; ++i) {
        pixels[i] = color;
    }
    return *this;
}

WWGraphics::Screen &
WWGraphics::Screen::drawScreen(const WWGraphics::Screen *other, int xStartOnThis, int yStartOnThis, int xStartOnOther,
                               int yStartOnOther,
                               int width, int height) {
    int cT[2];
    int cO[2];

    int value = 0;
    for (int x = 0; x < width; x++) {
        cT[0] = x + xStartOnThis;
        cO[0] = x + xStartOnOther;

        if(cT[0] < 0 || cO[0] < 0) {
            continue;
        }
        if (cT[0] >= this->width || cO[0] >= other->width) {
            break;
        }

        for (int y = 0; y < height; y++) {
            cT[1] = y + yStartOnThis;
            cO[1] = y + yStartOnOther;

            if (cT[1] >= this->height || cO[1] >= other->height || cT[1] < 0 || cO[1] < 0) {
                continue;
            }

            value = other->pixels[cO[0] + cO[1] * other->width];
            if (value != -1) {
                pixels[cT[0] + cT[1] * this->width] = value;
            }
        }
    }
    return *this;
}

WWGraphics::Screen& WWGraphics::Screen::drawOval(int xStart, int yStart, int width, int height, int color) {
    if (width == height) {
        return drawCircle(xStart, yStart, color, width / 2);
    }
    width /= 2;
    height /= 2;
    xStart += width;
    yStart += height;

    int yDest;
    for (int x = 0; x < width; x++) {
        yDest = getYForOval(x, width, height);
        setPixel(xStart + x, yStart + yDest, color);
        setPixel(xStart + x, yStart - yDest, color);

        setPixel(xStart - x, yStart + yDest, color);
        setPixel(xStart - x, yStart - yDest, color);
    }
    int xDest;
    for (int y = 0; y < height; y++) {
        xDest = getXForOval(y, width, height);
        setPixel(xStart + xDest, yStart + y, color);
        setPixel(xStart + xDest, yStart - y, color);

        setPixel(xStart - xDest, yStart + y, color);
        setPixel(xStart - xDest, yStart - y, color);
    }

    return *this;
}

WWGraphics::Screen& WWGraphics::Screen::fillOval(int xStart, int yStart, int width, int height, COLORTYPE color) {
    if (width == height) {
        return fillCircle(xStart, yStart, color, width / 2);
    }

    width /= 2;
    height /= 2;
    xStart += width;
    yStart += height;

    int yDest;
    for (int x = 0; x < width; x++) {
        yDest = getYForOval(x, width, height);
        drawLine(xStart + x, yStart + yDest, xStart + x, yStart - yDest, color);
        drawLine(xStart - x, yStart + yDest, xStart - x, yStart - yDest, color);
    }

    return *this;
}

WWGraphics::Screen& WWGraphics::Screen::drawCircle(int xStart, int yStart, int r, COLORTYPE color) {
    int d = -r;
    int x = r;
    int y = 0;

    xStart += r;
    yStart += r;

    while (y <= x) {
        setPixel(x + xStart, y + yStart, color);
        setPixel(-x + xStart, y + yStart, color);
        setPixel(x + xStart, -y + yStart, color);
        setPixel(-x + xStart, -y + yStart, color);

        setPixel(y + xStart, x + yStart, color);
        setPixel(-y + xStart, x + yStart, color);
        setPixel(y + xStart, -x + yStart, color);
        setPixel(-y + xStart, -x + yStart, color);

        d = d + 2 * y + 1;
        y = y + 1;

        if (d > 0) {
            d = d - 2 * x + 2;
            x = x - 1;
        }
    }
    return *this;
}

WWGraphics::Screen& WWGraphics::Screen::fillCircle(int xStart, int yStart, int r, COLORTYPE color) {
    int d = -r;
    int x = r;
    int y = 0;

    xStart += r;
    yStart += r;

    while (y <= x) {
        drawLine(x + xStart, y + yStart, -x + xStart, y + yStart, color);
        drawLine(x + xStart, -y + yStart, -x + xStart, -y + yStart, color);
        drawLine(y + xStart, x + yStart, -y + xStart, x + yStart, color);
        drawLine(y + xStart, -x + yStart, -y + xStart, -x + yStart, color);

        d = d + 2 * y + 1;
        y = y + 1;

        if (d > 0) {
            d = d - 2 * x + 2;
            x = x - 1;
        }
    }
    return *this;
}

WWGraphics::Screen& WWGraphics::Screen::drawLine(int xstart, int ystart, int xend, int yend, COLORTYPE color) {
    /*
     * TODO
    if(xstart < 0 || ystart < 0 || xend > getWidth() || yend > getHeight()){
        if(xstart < 0) {
            ystart = -ystart * ((yend- ystart)/(xend - xstart)) - ystart;
            xstart = 0;
        }
        if(ystart < 0) {
            xstart = -xstart * ((xend- xstart)/(yend - ystart)) - ystart;
            ystart = 0;
        }

        if(xstart < 0) {
            ystart = -ystart * ((yend- ystart)/(xend - xstart)) - ystart;
            xstart = 0;
        }
        if(ystart < 0) {
            xstart = -xstart * ((xend- xstart)/(yend - ystart)) - ystart;
            ystart = 0;
        }
    }
     std::cout << "test" << std::endl;
    */

    int x, y, t, dx, dy, incx, incy, pdx, pdy, ddx, ddy, deltaslowdirection, deltafastdirection, err;

    /* Entfernung in beiden Dimensionen berechnen */
    dx = xend - xstart;
    dy = yend - ystart;

    /* Vorzeichen des Inkrements bestimmen */
    incx = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
    incy = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;
    if (dx < 0)
        dx = -dx;
    if (dy < 0)
        dy = -dy;

    /* feststellen, welche Entfernung grï¿½ï¿½er ist */
    if (dx > dy) {
        /* x ist schnelle Richtung */
        pdx = incx;
        pdy = 0; /* pd. ist Parallelschritt */
        ddx = incx;
        ddy = incy; /* dd. ist Diagonalschritt */
        deltaslowdirection = dy;
        deltafastdirection = dx;
    } else {
        /* y ist schnelle Richtung */
        pdx = 0;
        pdy = incy; /* pd. ist Parallelschritt */
        ddx = incx;
        ddy = incy; /* dd. ist Diagonalschritt */
        deltaslowdirection = dx;
        deltafastdirection = dy;
    }

    /* Initialisierungen vor Schleifenbeginn */
    x = xstart;
    y = ystart;
    err = deltafastdirection / 2;
    setPixel(x, y, color);

    /* Pixel berechnen */
    for (t = 0; t < deltafastdirection; ++t) {
        err -= deltaslowdirection;
        if (err < 0) {
            err += deltafastdirection;
            x += ddx;
            y += ddy;
        } else {
            x += pdx;
            y += pdy;
        }
        setPixel(x, y, color);
    }

    return *this;
}

const int WWGraphics::Screen::getWidth() const {
    return width;
}

const int WWGraphics::Screen::getHeight() const {
    return height;
}

const int WWGraphics::Screen::getSize() const {
    return size;
}

WWGraphics::Screen::~Screen() {
    if (!isRef) {
        delete[] pixels;
    }
}

WWGraphics::Screen &
WWGraphics::Screen::drawScreen(const WWGraphics::Screen *const other, int xStartOnThis, int yStartOnThis,
                               int xStartOnOther, int yStartOnOther) {
    return drawScreen(other, xStartOnThis, yStartOnThis, xStartOnOther, yStartOnOther, other->getWidth(),
                      other->getHeight());
}

WWGraphics::Screen& WWGraphics::Screen::drawScreen(const Screen *const other, int xStartOnThis, int yStartOnThis) {
    return drawScreen(other, xStartOnThis, yStartOnThis, 0, 0, other->getWidth(),
                      other->getHeight());
}