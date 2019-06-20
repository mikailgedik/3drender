//
// Created by Admin on 01.02.2019.
//

#include "Surface.h"

WWMath::Surface::Surface(unsigned size) : size(size), polygon(new int [size]) {
}

WWMath::Surface::Surface(const Surface & o) : size(o.size), polygon(new int [size]){
    for(int i = 0; i < size; i++) {
        polygon[i] = o.polygon[i];
    }
}

WWMath::Surface::~Surface() {
    delete[] polygon;
};

void WWMath::Surface::reinit(unsigned newSize) {
    delete[] polygon;
    size = newSize;
    polygon = new int[size];
}