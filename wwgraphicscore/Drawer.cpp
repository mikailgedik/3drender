//
// Created by Admin on 01.09.2018.
//

#include <iostream>
#include "Drawer.h"
#include <chrono>

WWGraphics::Drawer::Drawer() : screen(new WWGraphics::Screen(1, 1, 0)),
                               world(new WWMath::World({-160 / 5, -90 / 5, 160 / 5, 90 / 5}, {1, 1})), mouseX(0),
                               mouseY(0), previousMouseX(0), previousMouseY(0), lMouseButtonDown(
                false), rMouseButtonDown(
                false), lastTimeTicked(0) {
    prepareWorld();
}

void WWGraphics::Drawer::prepareWorld() {
#define ADD_CUBE
    WWMath::Object *o = new WWMath::Object({
                                                   WWMath::MVector3D(10, 5, 5),//TODO
                                                   WWMath::MVector3D(5, -5, 5),
                                                   WWMath::MVector3D(5, -5, -5),
                                                   WWMath::MVector3D(5, 5, -5),
                                                   WWMath::MVector3D(-5, 5, 5),
                                                   WWMath::MVector3D(-5, -5, 5),
                                                   WWMath::MVector3D(-5, -5, -5),
                                                   WWMath::MVector3D(-5, 5, -5)
                                           });

    WWMath::Surface sur(4);

    sur.getPolygon()[0] = 0;
    sur.getPolygon()[1] = 1;
    sur.getPolygon()[2] = 2;
    sur.getPolygon()[3] = 3;

    o->getSurfaces().push_back(sur);
    o->setLocation(WWMath::MVector3D(-10,0,0));


#ifdef ADD_CUBE
    world->addObject(o);
#else
    delete o;
#endif

#ifndef NO_AXES

    WWMath::Object* xAxis = new WWMath::Object({WWMath::MVector3D(5,1,0),
                                                WWMath::MVector3D(5,-1,0),
                                                WWMath::MVector3D(-5,1,0),
                                                WWMath::MVector3D(-5,-1,0)});

    WWMath::Surface xAxisSur(4);
    xAxisSur.getPolygon()[0] = 0;
    xAxisSur.getPolygon()[1] = 1;
    xAxisSur.getPolygon()[2] = 2;
    xAxisSur.getPolygon()[3] = 3;
    xAxis->getSurfaces().push_back(xAxisSur);

    world->addObject(xAxis);
#endif
}

void WWGraphics::Drawer::prepare(HWND &hWnd, int w, int h) {
    BITMAP bm;
    PAINTSTRUCT ps;
    HDC windowHdc = BeginPaint(hWnd, &ps);

    void *ppvBits;
    BITMAPINFO bmi;
    bmi.bmiColors[0] = {8, 8, 8, 0};

    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = -h; //Upper left corner is start
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = sizeof(WWGraphics::COLORTYPE) * 8;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage = 0;
    bmi.bmiHeader.biXPelsPerMeter = 1;
    bmi.bmiHeader.biYPelsPerMeter = 1;
    bmi.bmiHeader.biClrUsed = 0;
    bmi.bmiHeader.biClrImportant = 0;

    HBITMAP hBm = CreateDIBSection(windowHdc, &bmi, DIB_PAL_COLORS, &ppvBits, nullptr, DWORD());
    {
        HDC hdcMem = CreateCompatibleDC(windowHdc);
        HBITMAP hbmOld = static_cast<HBITMAP>(SelectObject(hdcMem, hBm));
        GetObject(hBm, sizeof(bm), &bm);

        resetScreen(w, h, (WWGraphics::COLORTYPE *) bm.bmBits);

        if (world->getWidth() != w || world->getHeight() != h) {
            world->setScreen(w, h);
        }
        world->getScreen().fill(0x0);


        auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now().time_since_epoch()).count();
        if (now - lastTimeTicked > 1000.0 / ticksPerSecond) {
            world->tick(*this);
            lastTimeTicked = now;
        }

        world->renderOnScreen();
        screen->drawScreen(&world->getScreen(), 0, 0);

        BitBlt(windowHdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);

        SelectObject(hdcMem, hbmOld);
        DeleteObject(hBm);
        DeleteDC(hdcMem);
    }

    EndPaint(hWnd, &ps);
}

WWGraphics::Drawer::~Drawer() {
    delete world;
    delete screen;
}

void WWGraphics::Drawer::mouseMoved(int x, int y) {
    previousMouseY = mouseY;
    previousMouseX = mouseX;
    mouseX = x;
    mouseY = y;
}
