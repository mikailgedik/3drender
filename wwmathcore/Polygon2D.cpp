//
// Created by Admin on 15.02.2019.
//

#include "Polygon2D.h"

WWMath::Polygon2D::Polygon2D(unsigned nOfEdges) : size(nOfEdges), corners(new MVector2D[nOfEdges]){
}

WWMath::Polygon2D::~Polygon2D() {
    delete[] corners;
}