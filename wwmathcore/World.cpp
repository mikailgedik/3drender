//
// Created by Admin on 10.09.2018.
//

#include <iostream>
#include <cassert>
#include "World.h"
#include "MMatrix.h"
#include "../wwgraphicscore/Drawer.h"
#include "Polygon2D.h"

WWMath::World::World(const MVector2D &leftUpper, const MVector2D &rightLower, int screenWidth, int screenHeight)
        : leftUpper(leftUpper),
          rightLower(
                  rightLower),
          objects(std::vector<Object *>()),
          eyeRayLength(
                  EYERAY_LENGTH),
          eyeLocation(
                  MVector3D(0, 0,
                            0)),
          eyeRotation(
                  MVector3D(0, 0,
                            0)),
          eyeRay(MVector3D(eyeRayLength, 0, 0)),
          parallelHelpLineY(MVector3D(0, 0, 0)),
          parallelHelpLineX(MVector3D(0, 0, 0)),
          planeCenter(MVector3D(0, 0, 0)),
          plane(MVector(4)),
          screen(new WWGraphics::Screen(
                  screenWidth,
                  screenHeight)) {
    assert(*(leftUpper.x) < *(rightLower.x) && *(leftUpper.y) < *(rightLower.y));
    assert(leftUpper.size() == 2 && rightLower.size() == 2);

    //TODO
    std::cout << "TOOO: World crashes when object is on" << std::endl;
}


WWMath::World::World(std::initializer_list<double> corners, std::initializer_list<int> screenInfo) : leftUpper(
        MVector2D(corners.begin()[0], corners.begin()[1])), rightLower(
        MVector2D(corners.begin()[2], corners.begin()[3])), objects(std::vector<Object *>()),
                                                                                                     eyeRayLength(
                                                                                                             EYERAY_LENGTH),
                                                                                                     eyeLocation(
                                                                                                             MVector3D(
                                                                                                                     0,
                                                                                                                     0,
                                                                                                                     0)),
                                                                                                     eyeRotation(
                                                                                                             MVector3D(
                                                                                                                     0,
                                                                                                                     0,
                                                                                                                     0)),
                                                                                                     eyeRay(MVector3D(
                                                                                                             eyeRayLength,
                                                                                                             0, 0)),
                                                                                                     parallelHelpLineY(
                                                                                                             MVector3D(
                                                                                                                     0,
                                                                                                                     0,
                                                                                                                     0)),
                                                                                                     parallelHelpLineX(
                                                                                                             MVector3D(
                                                                                                                     0,
                                                                                                                     0,
                                                                                                                     0)),
                                                                                                     planeCenter(
                                                                                                             MVector3D(
                                                                                                                     0,
                                                                                                                     0,
                                                                                                                     0)),
                                                                                                     plane(MVector(4)),
                                                                                                     screen(new WWGraphics::Screen(
                                                                                                             screenInfo.begin()[0],
                                                                                                             screenInfo.begin()[1])) {

    assert(corners.size() == 4 && screenInfo.size() == 2);
}

void WWMath::World::addObject(Object *o) {
    objects.push_back(o);
}

void WWMath::World::doPreMath() {
    MMatrix oneRotation = MMatrix::matrixMultiplication(
            MMatrix::matrixMultiplication(MMatrix::createRotationMatrix('x', *eyeRotation.x),
                                          MMatrix::createRotationMatrix('y', *eyeRotation.y)),
            MMatrix::createRotationMatrix('z', *eyeRotation.z));

    eyeRay[0] = eyeRayLength;
    eyeRay[1] = 0;
    eyeRay[2] = 0;
    parallelHelpLineY[0] = 0;
    parallelHelpLineY[1] = 0;
    parallelHelpLineY[2] = eyeRayLength;
    parallelHelpLineX[0] = 0;
    parallelHelpLineX[1] = -eyeRayLength;
    parallelHelpLineX[2] = 0;

    oneRotation.transform(eyeRay);
    oneRotation.transform(parallelHelpLineX);
    oneRotation.transform(parallelHelpLineY);

    planeCenter = eyeLocation + eyeRay;

    plane[0] = eyeRay[0];
    plane[1] = eyeRay[1];
    plane[2] = eyeRay[2];
    plane[3] = planeCenter[0] * eyeRay[0] + planeCenter[1] * eyeRay[1] + planeCenter[2] * eyeRay[2];
}


#define RENDER_WAY 2

#if RENDER_WAY == 0
WWMath::MVector3D WWMath::World::calculatePointInPlane(const MVector3D &pointToDisplay) {
    /** Division trough zero if the point is vector is parallel to the plane */
    /** TODO somehow a division trough 0*/

    MVector3D vectorFromEyeToP = pointToDisplay - eyeLocation;
    double divisor = plane[3] - WWMath::MVector3D::dotProduct(eyeLocation,MVector3D(plane[0],plane[1],plane[2]));
    double dividend = WWMath::MVector3D::dotProduct(vectorFromEyeToP,MVector3D(plane[0],plane[1],plane[2]));

    double vectorScale;

    if(dividend == 0) {
        /** Todo*/
        vectorScale = 1;
    } else {
        vectorScale=divisor/dividend;
    }
    //vectorScale=divisor/dividend;

    return MVector3D(eyeLocation[0] + vectorFromEyeToP[0] * vectorScale,
                     eyeLocation[1] + vectorFromEyeToP[1] * vectorScale,
                     eyeLocation[2] + vectorFromEyeToP[2] * vectorScale);
}
#elif RENDER_WAY==1
WWMath::MVector3D WWMath::World::calculatePointInPlane(const MVector3D &pointToDisplay) {
    double lambda = - (plane[3] - pointToDisplay[0]*plane[0]- pointToDisplay[1]*plane[1]- pointToDisplay[2]*plane[2])/
            (plane[0]*plane[0]+plane[1]*plane[1]+plane[2]*plane[2]);
    return pointToDisplay - MVector3D(plane[0] * lambda, plane[1] * lambda, plane[2] * lambda);
}
#elif RENDER_WAY == 2
WWMath::MVector3D WWMath::World::calculatePointInPlane(const MVector3D &pointToDisplay) {
    /** Division trough zero if the point is vector is parallel to the plane */
    /** TODO somehow a division trough 0*/
    MVector3D eyeLocation = this->eyeLocation + testFactor * eyeRay;
    MVector3D vectorFromEyeToP = pointToDisplay - eyeLocation;
    double divisor = plane[3] - WWMath::MVector3D::dotProduct(eyeLocation,MVector3D(plane[0],plane[1],plane[2]));
    double dividend = WWMath::MVector3D::dotProduct(vectorFromEyeToP,MVector3D(plane[0],plane[1],plane[2]));

    double vectorScale;

    if(dividend == 0) {
        /** Todo*/
        vectorScale = 1;
    } else {
        vectorScale=divisor/dividend;
    }
    //vectorScale=divisor/dividend;

    return MVector3D(eyeLocation[0] + vectorFromEyeToP[0] * vectorScale,
                     eyeLocation[1] + vectorFromEyeToP[1] * vectorScale,
                     eyeLocation[2] + vectorFromEyeToP[2] * vectorScale);
}
#endif


WWMath::MVector2D WWMath::World::calculatePointOn2DPlane(const MVector3D& pointInPlane) {
    double helpLineScaleY =
            (parallelHelpLineY[0] * pointInPlane[0] + parallelHelpLineY[1] * pointInPlane[1] +
             parallelHelpLineY[2] * pointInPlane[2] - parallelHelpLineY[0] * planeCenter[0] -
             parallelHelpLineY[1] * planeCenter[1] - parallelHelpLineY[2] * planeCenter[2]) /
            (parallelHelpLineY[0] * parallelHelpLineY[0] + parallelHelpLineY[1] * parallelHelpLineY[1] +
             parallelHelpLineY[2] * parallelHelpLineY[2]);

    double helpLineScaleX =
            (parallelHelpLineX[0] * pointInPlane[0] + parallelHelpLineX[1] * pointInPlane[1] +
             parallelHelpLineX[2] * pointInPlane[2] - parallelHelpLineX[0] * planeCenter[0] -
             parallelHelpLineX[1] * planeCenter[1] - parallelHelpLineX[2] * planeCenter[2]) /
            (parallelHelpLineX[0] * parallelHelpLineX[0] + parallelHelpLineX[1] * parallelHelpLineX[1] +
             parallelHelpLineX[2] * parallelHelpLineX[2]);
    //(x > 0) - (x < 0) = sign(x)

    return MVector2D(((helpLineScaleX > 0) - (helpLineScaleX < 0)) * (helpLineScaleX * parallelHelpLineX).length(),
                     ((helpLineScaleY > 0) - (helpLineScaleY < 0)) * (helpLineScaleY * parallelHelpLineY).length());
}

void WWMath::World::renderOnScreen() {
    doPreMath();

    using namespace std;

    for (Object *j: objects) {
        j->transformObject();
#define ONLY_CORNERS
#ifdef ONLY_CORNERS
        for (const MVector3D &pf: j->getTransformedCorners()) {
            //Check if it has to draw by looking if the angle is greater than Pi/2
            //between the vector
            // pf - eyelocation
            // eyeRay
            {
                MVector3D temp = pf - eyeLocation;
                double arcCos = MVector3D::dotProduct(pf, eyeRay) / (pf.length() * eyeRay.length());
                if (arcCos < 0) {
                    //continue; TODO
                }
            }

            MVector3D pointInPlane = calculatePointInPlane(pf);
            MVector2D coordinatesOn2DPlane = calculatePointOn2DPlane(pointInPlane);
            MVector2D coordinatesOnScreen = getLocationOnScreen(coordinatesOn2DPlane);

            screen->fillCircle((int)coordinatesOnScreen[0], (int)coordinatesOnScreen[1], 3, 0xffffff);
        }
#else
        for (const Surface &surface: j->getTransformedSurfaces()) {
            WWMath::Polygon2D poly(surface.getSize());
            for(int i = 0; i < poly.getSize(); i++) {
                MVector3D pointInPlane = calculatePointInPlane(j->getTransformedCorners()[i]);

                MVector2D coordinatesOn2DPlane = calculatePointOn2DPlane(pointInPlane);

                MVector2D coordinatesOnScreen = getLocationOnScreen(coordinatesOn2DPlane);
                poly[i] = coordinatesOnScreen;
            }

            if(poly.getSize() >= 2) {
                for(unsigned i = 0; i < poly.getSize() -1; i++) {
                    int xStart = *poly[i].x, yStart = *poly[i].y, xEnd = *poly[i+1].x, yEnd = *poly[i+1].y;
                    screen->drawLine(xStart, yStart, xEnd, yEnd, 0xffffff);
                }
                screen->drawLine(*poly[poly.getSize()-1].x, *poly[poly.getSize()-1].y, *poly[0].x, *poly[0].y, 0xffffff);
            }

        }
#endif
    }

}

WWMath::MVector2D WWMath::World::getLocationOnScreen(const MVector2D &other) {
    assert(other.size() == 2);
    auto w = *rightLower.x - *leftUpper.x, h = (*rightLower.y - *leftUpper.y);
    double nX = *other.x, nY = *other.y;

    double xFrac, yFrac;
    xFrac = 1.0 / w * screen->getWidth();
    yFrac = 1.0 / h * screen->getHeight();

    nX -= *leftUpper.x;
    nY -= *leftUpper.y;

    nX *= xFrac;
    nY *= yFrac;

    return MVector2D(nX, nY);
}

WWGraphics::Screen &WWMath::World::getScreen() const {
    return *screen;
}

void WWMath::World::setScreen(int w, int h) {
    delete screen;
    screen = new WWGraphics::Screen(w, h);
}

WWMath::World::~World() {
    for (int i = 0; i < objects.size(); i++) {
        delete objects[i];
    }

    objects.clear();
    delete World::screen;
}

void WWMath::World::tick(WWGraphics::Drawer& drawer) {
    WWMath::MVector3D &rotation = getEyeRotation();
    WWMath::MVector3D &location = getEyeLocation();

    if(drawer.isKeyDown('K')) {
       objects[0]->getRotation()[2] += .1;
    }
    if(drawer.isKeyDown('H')) {
        objects[0]->getRotation()[2] -= .1;
    }
    if(drawer.isKeyDown('U')) {
        objects[0]->getRotation()[1] += .1;
    }
    if(drawer.isKeyDown('J')) {
        objects[0]->getRotation()[1] -= .1;
    }

    if (drawer.isKeyDown('A')) {
        location[0] += 0.5;
    }
    if (drawer.isKeyDown('D')) {
        location[0] -= 0.5;
    }
    if (drawer.isKeyDown('W')) {
        location[1] += 0.5;
    }
    if (drawer.isKeyDown('S')) {
        location[1] -= 0.5;
    }

    if(drawer.isKeyDown('Y')) {
        testFactor += .075;
    }
    if(drawer.isKeyDown('X')) {
        testFactor -= .075;
    }

    if(testFactor > 3) {
        testFactor = 3;
    }
    if(testFactor < -3) {
        testFactor = -3;
    }

    if (drawer.getMouseX() != drawer.getPreviousMouseX() && drawer.isMouseButtonDown('l')) {
        int diff = drawer.getMouseX() - drawer.getPreviousMouseX();
        rotation[2] += diff / 100.0;
    }
}

