//
// Created by Admin on 12.09.2018.
//

#ifndef INC_3DGRAPHICSCALCULATOR_MMATRIX_H
#define INC_3DGRAPHICSCALCULATOR_MMATRIX_H

#include <vector>
#include "MVector.h"

namespace WWMath {
    class MMatrix {
    private:
        std::vector<double> content;
        const unsigned columns, rows;
    public:
        MMatrix(unsigned rows, unsigned columns);

        MMatrix(unsigned rows, unsigned columns, std::vector<double> content);

        MMatrix &transform(MVector &other) const;

        unsigned getIndex(unsigned row, unsigned column) const;

        unsigned getColumn(unsigned index) const;

        unsigned getRow(unsigned index) const;

        double getItem(unsigned row, unsigned column) const;

        double &getItem(unsigned row, unsigned column);

        WWMath::MMatrix &setItem(unsigned row, unsigned column, double value);

        unsigned getRows() const;

        unsigned getColumns() const;

        double &operator[](unsigned index);

        double operator[](unsigned index) const;

        static MVector transformedVector(const MMatrix& matrix, const MVector& vector);

        static MMatrix createRotationMatrix(char axis, double angle);

        static MMatrix createTripleMatrixRotation(double xAngle, double yAngle, double zAngle);

        static MMatrix matrixMultiplication(const MMatrix& a, const MMatrix& b);
    };

    std::ostream& operator<<(std::ostream& out, const MMatrix& m);
}

#endif //INC_3DGRAPHICSCALCULATOR_MMATRIX_H
