//
// Created by Admin on 10.09.2018.
//

#ifndef INC_3DGRAPHICSCALCULATOR_OBJECT_H
#define INC_3DGRAPHICSCALCULATOR_OBJECT_H

#include <ostream>
#include "../wwmathcore/MVector.h"
#include "Surface.h"

namespace WWMath {
    class Object {
    private:
        MVector3D location;
        MVector3D rotation;

        std::vector<MVector3D> corners;
        std::vector<MVector3D> transformedCorners;

        std::vector<Surface> surfaces;

        /**Technically not used as surfaces just store the indices of the corners */
        std::vector<Surface> transformedSurfaces;
    public:
        Object(std::initializer_list<MVector3D> corners);

        ~Object();

        const MVector3D &getLocation() const;

        void setLocation(const MVector3D &location);

        MVector3D& getLocation();

        const MVector3D &getRotation() const;

        MVector3D& getRotation();

        void setRotation(const MVector3D &rotation);

        std::vector<MVector3D>& getCorners();

        std::vector<Surface>& getSurfaces();

        MVector3D& getCorner(int index) {
            return corners[index];
        }

        void transformObject();

        std::vector<MVector3D> getTransformedCorners();

        std::vector<WWMath::Surface> getTransformedSurfaces();
    };

    std::ostream&operator<<(std::ostream& out, const Object& object);
}


#endif //INC_3DGRAPHICSCALCULATOR_OBJECT_H
