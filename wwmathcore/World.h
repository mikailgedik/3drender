//
// Created by Admin on 10.09.2018.
//

#ifndef INC_3DGRAPHICSCALCULATOR_WORLD_H
#define INC_3DGRAPHICSCALCULATOR_WORLD_H

#include <vector>
#include "../wwdisplayobjects/Object.h"
#include "../wwgraphicscore/Screen.h"

/** Used for WWMath::World::tick(Drawer& d)*/
namespace WWGraphics {
    class Drawer;
}

namespace WWMath {
    constexpr double EYERAY_LENGTH = 10;
    class World {
    private:
        WWGraphics::Screen *screen;

        MVector2D leftUpper, rightLower;
        std::vector<Object *> objects;

        //Render math
        double eyeRayLength;
        double testFactor = 0;
        MVector3D eyeLocation, eyeRotation, eyeRay, parallelHelpLineY, parallelHelpLineX,planeCenter;

        /** Value
         * 0: x
         * 1: y
         * 2: z
         * 3: c
         */
        MVector plane;

        void doPreMath();
        MVector3D calculatePointInPlane(const MVector3D&);
        MVector2D calculatePointOn2DPlane(const MVector3D& pointInPlane);

        MVector2D getLocationOnScreen(const MVector2D&);
    public:

        /** Parameter rightlower is ignored */
        World(const MVector2D &leftUpper, const MVector2D &rightLower, int screenWidth, int screenHeight);

        World(std::initializer_list<double> corners, std::initializer_list<int> screenInfo);

        void addObject(Object* o);

        virtual ~World();

        void renderOnScreen();

        WWGraphics::Screen& getScreen() const;

        void setScreen(int w, int h);

        int getWidth() {
            return screen->getWidth();
        }

        int getHeight() {
            return screen->getHeight();
        }

        MVector3D& getEyeRotation() {
            return eyeRotation;
        }

        MVector3D &getEyeLocation() {
            return eyeLocation;
        }

        void setEyeLocation(const MVector3D& n) {
            this->eyeLocation = n;
        }

        void setEyeRotation(const MVector3D& n) {
            this->eyeRotation = n;
        }

        void tick(WWGraphics::Drawer& drawer);
    };
}

#endif //INC_3DGRAPHICSCALCULATOR_WORLD_H
