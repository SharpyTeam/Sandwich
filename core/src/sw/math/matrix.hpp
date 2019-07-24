//
// Created by selya on 24.07.2019.
//

#ifndef SANDWICH_CORE_MATRIX_HPP
#define SANDWICH_CORE_MATRIX_HPP

#include <sw/math/vector.hpp>

namespace sw {

template<int N, int M>
class Matrix;

typedef Matrix<3, 3> Matrix3;
typedef Matrix<4, 4> Matrix4;

// Matrix is column-major
// 0 4 8  12
// 1 5 9  13
// 2 6 10 14
// 3 7 11 15

template<>
class Matrix<4, 4> {
private:
    double data[16];

public:
    Matrix();
    Matrix(const Matrix<4, 4> &other);
    Matrix(const double data[16]);

    //
    // Non const methods
    //

    Matrix<4, 4> &Identity();
    Matrix<4, 4> &Inverse();
    Matrix<4, 4> &Transpose();
    Matrix<4, 4> &Set(const Matrix<4, 4> &other);
    Matrix<4, 4> &Set(const double data[16]);
    Matrix<4, 4> &Scale(double x, double y, double z);
    Matrix<4, 4> &Scale(const Vector<3> &scale);
    Matrix<4, 4> &Rotate(double ang, double x, double y, double z);
    Matrix<4, 4> &Rotate(double ang, const Vector<3> &axis);
    Matrix<4, 4> &Translate(double x, double y, double z);
    Matrix<4, 4> &Translate(const Vector<3> &translate);
    Matrix<4, 4> &SetOrtho2D(double left, double right, double bottom, double top);
    Matrix<4, 4> &operator=(const Matrix<4, 4> &other);

    double *operator[](int index);

    //
    // Const methods
    //

    Matrix<4, 4> operator*(const Matrix<4, 4> &other) const;
    Vector<4> operator*(const Vector<4> &v) const;
    const double *operator[](int index) const;

    /*Vector<4> Unproject(double x, double y, double z) const;
    Vector<4> Unproject(const Vector<3> &v) const;*/
    Vector<3> GetTranslation() const;
    float GetRotationZ() const;
};

} //namespace a2d

#endif //SANDWICH_CORE_MATRIX_HPP
