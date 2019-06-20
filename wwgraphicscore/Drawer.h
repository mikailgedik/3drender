//
// Created by Admin on 01.09.2018.
//

#ifndef INC_3DGRAPHICSCALCULATOR_DRAWER_H
#define INC_3DGRAPHICSCALCULATOR_DRAWER_H

#include <windows.h>
#include <istream>
#include "Screen.h"
#include "../wwmathcore/World.h"

namespace WWGraphics {
    class Drawer {
    private:
        WWGraphics::Screen *screen;

        WWMath::World *world;
        /** Only uppercase characters are saved*/
        bool downKeys[65536];

        int mouseX, mouseY, previousMouseX, previousMouseY;
        bool lMouseButtonDown, rMouseButtonDown;

        const double ticksPerSecond = 100;
        long long int lastTimeTicked;

        void prepareWorld();
    public:
        Drawer();

        virtual ~Drawer();

        void prepare(HWND &hwnd, int w, int h);

        inline Drawer &resetScreen(int nw, int nh, WWGraphics::COLORTYPE *newRef) {
            delete screen;
            screen = new WWGraphics::Screen(newRef, nw, nh);
            return *this;
        }

        /** Use major cased letters*/
        bool *getDownKeys() {
            return downKeys;
        }

        /** Use major cased letters*/
        bool isKeyDown(char c) {
            return downKeys[c];
        }

        void mouseMoved(int x, int y);

        int &getMouseX() {
            return mouseX;
        }

        int &getMouseY() {
            return mouseY;
        }

        bool isMouseButtonDown(unsigned char button) {
            switch (button) {
                case 'l':
                    return lMouseButtonDown;
                case 'r':
                    return rMouseButtonDown;
                default:
                    throw "Error";
            }
        }

        void mouseButtonDown(unsigned char b, bool state) {
            switch (b) {
                case 'l':
                    lMouseButtonDown = state;
                    break;
                case 'r':
                    rMouseButtonDown = state;
                    break;
                default:
                    throw "Error";
            }
        }

        int &getPreviousMouseX() {
            return previousMouseX;
        }

        int &getPreviousMouseY() {
            return previousMouseY;
        }
    };
}

#endif //INC_3DGRAPHICSCALCULATOR_DRAWER_H
