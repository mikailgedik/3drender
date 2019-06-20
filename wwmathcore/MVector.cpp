//
// Created by Admin on 11.09.2018.
//

#include <cassert>
#include <iostream>
#include "MVector.h"

WWMath::MVector & WWMath::MVector::add(const MVector&v) {
    assert(this->size() == v.size());
    for(int i = 0; i < v.content.size(); i++) {
        content[i] += v.content[i];
    }
    return *this;
}

WWMath::MVector3D& WWMath::MVector3D::crossProduct(const MVector3D &v) {
    double a = (*this)[1] * (v)[2] - (*this)[2] * (v)[1];
    double b = (*this)[2] * (v)[0] - (*this)[0] * (v)[2];
    double c = (*this)[0] * (v)[1] - (*this)[1] * (v)[0];

    *x = a;
    *y = b;
    *z = c;

    return *this;
}

unsigned WWMath::MVector::size() const {
    return content.size();
}

const double WWMath::MVector::operator[](int index) const {
    return content[index];
}

double& WWMath::MVector::operator[](int index) {
    return content[index];
}

std::ostream& WWMath::operator<<(std::ostream &out, const MVector &vector) {
    out << "<";
    for(int i = 0; i < vector.size() -1; i++) {
        out << vector[ i] << ", ";
    }
    if(vector.size() != 0) {
        out << vector[vector.size() -1];
    }
    out << ">";

    return out;
}

WWMath::MVector WWMath::MVector::dotProduct(const MVector &other) const {
    assert(size() == other.size());
    MVector ret(size());
    for(int i = 0; i < size(); i++) {
        ret[i] = other[i] * (*this)[i];
    }
    return ret;
}

WWMath::MVector2D WWMath::MVector2D::dotProduct(const MVector2D &other) const {
    return MVector2D(*x* *other.x, *y * *other.y);
}

WWMath::MVector WWMath::operator+(const MVector &v1, const MVector &v2) {
    assert(v1.size() == v2.size());
    MVector ret(v1.size());
    for(int i = 0; i < v1.size(); i++) {
        ret[i] = v1[i] + v2[i];
    }
    return ret;
}

WWMath::MVector WWMath::MVector::operator-(const MVector &v) const {
    assert(size() == v.size());
    MVector ret(v.size());
    for(int i = 0; i < size(); i++) {
        ret[i] = (*this)[i] - v[i];
    }
    return ret;
}

WWMath::MVector2D WWMath::operator+(const MVector2D &v1, const MVector2D &v2) {
    return MVector2D(*v1.x + *v2.x, *v1.y + *v2.y);
}

WWMath::MVector2D WWMath::MVector2D::operator-(const MVector2D &v) const {
    return MVector2D(*x - *v.x, *y - *v.y);
}

WWMath::MVector3D WWMath::operator+(const MVector3D &v1, const MVector3D &v2) {
    return MVector3D(*v1.x + *v2.x, *v1.y + *v2.y, *v1.z + *v2.z);
}

WWMath::MVector3D WWMath::MVector3D::operator-(const MVector3D &v) const {
    return MVector3D(*x - *v.x, *y - *v.y, *z - *v.z);
}

WWMath::MVector3D WWMath::operator*(double factor, const MVector3D &v) {
    return MVector3D(*v.x * factor, *v.y * factor, *v.z * factor);
}

double WWMath::MVector3D::dotProduct(const MVector3D &v, const MVector3D &u) {
    return v[0] * u[0] + v[1] * u[1] + v[2] * u[2];
}