//
// Created by Admin on 12.09.2018.
//

#include <cassert>
#include <cmath>
#include "MMatrix.h"

WWMath::MMatrix::MMatrix(unsigned rows, unsigned columns) : rows(rows), columns(columns), content(std::vector<double>(rows*columns)){
}

WWMath::MMatrix::MMatrix(unsigned rows, unsigned columns, std::vector<double> content) : rows(rows), columns(columns), content(content) {
    assert(rows*columns == content.size());
}


WWMath::MMatrix& WWMath::MMatrix::transform(MVector &other) const {
    assert(other.size() == this->columns);

    MVector copy(other);

    for (int i = 0; i <other.size(); ++i) {
        other[i] = 0;
        for(int x = 0; x < columns; x++) {
            double res = copy[x] * (*this)[getIndex(x,i)];
            other[i] += res;
        }
    }

    return *const_cast<MMatrix*>(this);
}

unsigned WWMath::MMatrix::getIndex(unsigned row, unsigned column) const {
    return row * columns + column;
}

unsigned WWMath::MMatrix::getColumn(unsigned index) const {
    return index % columns;
}

unsigned WWMath::MMatrix::getRow(unsigned index) const {
    return index / columns;
}

double WWMath::MMatrix::getItem(unsigned row, unsigned column) const {
    return content[row * columns + column];
}

double& WWMath::MMatrix::getItem(unsigned row, unsigned column) {
    return content[row * columns + column];
}

WWMath::MMatrix& WWMath::MMatrix::setItem(unsigned row, unsigned column, double value) {
    content[row * columns + column] = value;
    return *this;
}

unsigned WWMath::MMatrix::getRows() const {
    return rows;
}

unsigned WWMath::MMatrix::getColumns() const {
    return columns;
}

double WWMath::MMatrix::operator[](unsigned index) const {
    return this->content[index];
}

double& WWMath::MMatrix::operator[](unsigned index) {
    return this->content[index];
}

WWMath::MMatrix WWMath::MMatrix::createRotationMatrix(char axis, double angle) {
    switch (axis) {
        case 'x':
            return MMatrix(3,3,std::vector<double>({
                                                           1,0,0,
                                                           0,std::cos(angle),-std::sin(angle),
                                                           0,std::sin(angle),std::cos(angle)
                                                   }));
        case 'y':
            return MMatrix(3,3,std::vector<double>({
                                                           std::cos(angle), 0, std::sin(angle),
                                                           0, 1, 0,
                                                           -std::sin(angle), 0, std::cos(angle)
                                                   }));
        case 'z':
            return MMatrix(3,3,std::vector<double>({
                                                           std::cos(angle),-std::sin(angle), 0,
                                                           std::sin(angle), std::cos(angle), 0,
                                                           0, 0, 1
                                                   }));
        default:
            throw "Invalid axis";
    }
}

WWMath::MMatrix WWMath::MMatrix::createTripleMatrixRotation(double xAngle, double yAngle, double zAngle) {
    return matrixMultiplication(MMatrix::matrixMultiplication(MMatrix::createRotationMatrix('x', xAngle),MMatrix::createRotationMatrix('y', yAngle)), MMatrix::createRotationMatrix('z', zAngle));
}

WWMath::MVector WWMath::MMatrix::transformedVector(const MMatrix &matrix, const MVector &vector) {
    assert(vector.size() == matrix.getColumns());

    MVector ret(vector);
    for (int i = 0; i < ret.size(); ++i) {
        ret[i] = 0;
        for(int x = 0; x < matrix.getColumns(); x++) {
            double res = vector[x] * matrix[matrix.getIndex(x,i)];
            ret[i] += res;
        }
    }
    return ret;
}

WWMath::MMatrix WWMath::MMatrix::matrixMultiplication(const MMatrix &a, const MMatrix &b) {
    assert(a.getColumns() == b.getRows());
    const unsigned n = a.getRows(), m = a.getColumns(), p = b.getColumns();
    MMatrix ret(n, p);
    for(unsigned i = 0; i < n; i++) {
        for(unsigned j = 0; j < p; j++) {
            for(unsigned k = 0; k < m; k++) {
                ret.getItem(i,j) += a.getItem(i, k) * b.getItem(k, j);
            }
        }
    }
    return ret;
}

std::ostream& WWMath::operator<<(std::ostream &out, const MMatrix &m) {
    out << "<M" << m.getRows() << "x" << m.getColumns() << "<" << std::endl;
    for(unsigned row = 0; row < m.getRows(); row++) {
        for(unsigned col = 0; col < m.getColumns() - 1; col++) {
            out << m.getItem(row, col) << ",";
        }
        out << m.getItem(row, m.getColumns()-1) << std::endl;
    }
    out << ">>";
    return out;
}