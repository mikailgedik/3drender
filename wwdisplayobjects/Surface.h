//
// Created by Admin on 01.02.2019.
//

#ifndef INC_3DGRAPHICSCALCULATOR_SURFACE_H
#define INC_3DGRAPHICSCALCULATOR_SURFACE_H

#include "../wwmathcore/MVector.h"

namespace WWMath {
    class Surface {
    private:
        unsigned size;
        /** Instead of saving the corners or adresses of the corners, we store the index of the corners they have in the object **/
        int* polygon;

    public:
        explicit Surface(unsigned size);
        Surface(const Surface&);
        ~Surface();

        inline int* getPolygon() const {
            return polygon;
        }

        void reinit(unsigned newSize);

        inline unsigned getSize() const {
            return size;
        }

    };
}



#endif //INC_3DGRAPHICSCALCULATOR_SURFACE_H
