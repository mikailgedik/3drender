//
// Created by Admin on 15.02.2019.
//

#ifndef INC_3DGRAPHICSCALCULATOR_POLYGON2D_H
#define INC_3DGRAPHICSCALCULATOR_POLYGON2D_H

#include "MVector.h"

namespace WWMath {
    class Polygon2D {
    private:
        unsigned size;
        WWMath::MVector2D *corners;
    public:
        explicit Polygon2D(unsigned corners);
        ~Polygon2D();

        inline unsigned getSize() {
            return size;
        }

        inline MVector2D* getEdges() {
            return corners;
        }

        MVector2D&operator[](unsigned n) {
            return corners[n];
        }
    };
}

#endif //INC_3DGRAPHICSCALCULATOR_POLYGON2D_H
