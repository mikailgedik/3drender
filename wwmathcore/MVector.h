//
// Created by Admin on 11.09.2018.
//

#ifndef INC_3DGRAPHICSCALCULATOR_MVECTOR_H
#define INC_3DGRAPHICSCALCULATOR_MVECTOR_H

#include <vector>
#include <ostream>
#include <iostream>
#include <cassert>
#include <cmath>

namespace WWMath {
    struct MVector;
    std::ostream& operator<<(std::ostream& out, const WWMath::MVector& vector);

    struct MVector {
        std::vector<double> content;

        explicit MVector(unsigned size) : content(std::vector<double>(size)){
        };

        MVector(std::initializer_list<double> value) : content(std::vector<double>(value)) {
        };

        MVector(const MVector& other) = default;

        MVector& add(const MVector& v);

        MVector dotProduct(const MVector& other) const ;

        unsigned size() const;

        MVector operator-(const MVector& v) const ;

        double& operator[](int index);

        const double operator[](int index) const;
    };

    struct MVector2D : public MVector {
        double * const x, * const y;

        MVector2D() : MVector2D(0, 0){
        };

        MVector2D(double x, double y) : MVector(2), x(&content[0]), y(&content[1]) {
            *MVector2D::x = x;
            *MVector2D::y = y;
        }

        MVector2D(const MVector2D& o) : MVector(o), x(&content[0]), y(&content[1]) {
        }

        MVector2D(double x, double y, char s) : MVector(3), x(&content[0]), y(&content[1]) {
            *MVector2D::x = x;
            *MVector2D::y = y;
        }

        inline MVector2D& add(const MVector2D& other) {
            *x += *other.x;
            *y += *other.y;
            return *this;
        }

        MVector2D dotProduct(const MVector2D& other) const ;

        unsigned size() const {
            return 2;
        }
        MVector2D operator-(const MVector2D& v) const ;

        MVector2D& operator=(const MVector2D& o) {
            *x = *o.x;
            *y = *o.y;
            return *this;
        }
    };

    struct MVector3D : public MVector2D {
        double * const z;

        MVector3D() : MVector3D(0,0,0) {
        };

        MVector3D(double x, double y, double z) : MVector2D(x, y, '0'), z(&content[2]) {
            *MVector3D::z = z;
        }

        MVector3D(const MVector3D& o) : MVector2D(o), z(&content[2]) {
        }

        inline MVector3D& add(const MVector3D& other) {
            MVector2D::add(other);
            *z += *other.z;
            return *this;
        }

        MVector3D& crossProduct(const MVector3D& v);

        MVector3D& dotProduct(const MVector3D& other) const ;

        unsigned size() const {
            return 3;
        }

        double length() const {
            return std::sqrt(*x * *x + *y * *y + *z * *z);
        }

        double lengthSquared() {
            return *x * *x + *y * *y + *z * *z;
        }

        MVector3D operator-(const MVector3D& v) const ;

        MVector3D& operator=(const MVector3D& v) {
            *x = *v.x;
            *y = *v.y;
            *z = *v.z;
            return *this;
        }

        static double dotProduct(const MVector3D& v, const MVector3D& u);
    };

    MVector operator+(const MVector& v1, const MVector& v2);
    MVector2D operator+(const MVector2D& v1, const MVector2D& v2);
    MVector3D operator+(const MVector3D& v1, const MVector3D& v2);

    MVector3D operator*(double factor, const MVector3D& v);
}

#endif //INC_3DGRAPHICSCALCULATOR_MVECTOR_H
