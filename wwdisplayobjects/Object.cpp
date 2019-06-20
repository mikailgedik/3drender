//
// Created by Admin on 10.09.2018.
//

#include <cassert>
#include "Object.h"
#include "../wwmathcore/MMatrix.h"

std::ostream& WWMath::operator<<(std::ostream &out, const Object &object) {
    out << "Object[Location[" << object.getLocation() << "], Rotation[" << object.getRotation() << "]]";
    return out;
}

WWMath::Object::Object(std::initializer_list<MVector3D> corners) : corners(std::vector<MVector3D>(corners)), transformedCorners(std::vector<MVector3D>(corners)),
                                                                   location(MVector3D(0, 0, 0)), rotation(MVector3D(0, 0, 0)), surfaces(std::vector<Surface>({})), transformedSurfaces(std::vector<Surface>({})) {
}

WWMath::Object::~Object() {
}

std::vector<WWMath::MVector3D>& WWMath::Object::getCorners() {
    return corners;
}

std::vector<WWMath::Surface>& WWMath::Object::getSurfaces() {
    return surfaces;
}

const WWMath::MVector3D &WWMath::Object::getLocation() const {
    return location;
}

WWMath::MVector3D& WWMath::Object::getLocation() {
    return location;
}

void WWMath::Object::setLocation(const WWMath::MVector3D &l) {
    assert(location.size() == 3);
    location[0] = l[0];
    location[1] = l[1];
    location[2] = l[2];
}

const WWMath::MVector3D &WWMath::Object::getRotation() const {
    return rotation;
}

WWMath::MVector3D& WWMath::Object::getRotation() {
    return rotation;
}

void WWMath::Object::setRotation(const WWMath::MVector3D &r) {
    assert(r.size() == 3);
    rotation[0] = r[0];
    rotation[1] = r[1];
    rotation[2] = r[2];
}

void WWMath::Object::transformObject() {
    transformedCorners.resize(corners.size(), MVector3D(0,0,0));
    transformedSurfaces.resize(surfaces.size(), Surface(1));

    WWMath::MMatrix rotationMatrix = WWMath::MMatrix::createTripleMatrixRotation(this->rotation[0], this->rotation[1], this->rotation[2]);

    for(int i = 0; i < transformedCorners.size(); i++) {
        transformedCorners[i] = corners[i];

        rotationMatrix.transform(transformedCorners[i]);

        transformedCorners[i] = transformedCorners[i] + location;
    }

    for(int i = 0; i < transformedSurfaces.size(); i++) {
        transformedSurfaces[i].reinit(surfaces.size());
        for(int j = 0; j < surfaces[i].getSize(); j++) {
            transformedSurfaces[i] = surfaces[i];
        }
    }
}

std::vector<WWMath::MVector3D> WWMath::Object::getTransformedCorners() {
    return transformedCorners;
}

std::vector<WWMath::Surface> WWMath::Object::getTransformedSurfaces() {
    return transformedSurfaces;
}