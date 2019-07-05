//
// Created by Ilya on 30.06.2019.
//

#ifndef SANDWICH_VECTOR_HPP
#define SANDWICH_VECTOR_HPP

#include "sw/object_wrap.hpp"
#include "sw/sw_macros.hpp"

using namespace v8;

namespace sw {
template<int L>
class Vector;

template<>
class Vector<2> : public sw::ObjectWrap {
public:
    double x;
    double y;

    Vector<2>();
    explicit Vector<2>(double scalar);
    Vector<2>(double x, double y);
    Vector<2>(const Vector<2> &other);
    double Length() const;
    double Dot(double x, double y) const;
    double Dot(const Vector<2> &other) const;
    double Distance(double x, double y) const;
    double Distance(const Vector<2> &other) const;
    double Determinant(double x, double y) const;
    double Determinant(const Vector<2> &other) const;
    double Angle(double x, double y) const;
    double Angle(const Vector<2> &other) const;
    Vector<2> Normalized() const;
    double LengthSquared() const;
    double DistanceSquared(double x, double y) const;
    double DistanceSquared(const Vector<2> &other) const;
    Vector<2> Perpendicular() const;
    Vector<2> Min(double x, double y) const;
    Vector<2> Min(const Vector<2> &other) const;
    Vector<2> Max(double x, double y) const;
    Vector<2> Max(const Vector<2> &other) const;
    Vector<2> Lerp(double x, double y, double t) const;
    Vector<2> Lerp(const Vector<2> &other, double t) const;
    Vector<2> operator+(const Vector<2> &other) const;
    Vector<2> operator-(const Vector<2> &other) const;
    Vector<2> operator*(const Vector<2> &other) const;
    Vector<2> operator/(const Vector<2> &other) const;
    Vector<2> operator+(double scalar) const;
    Vector<2> operator-(double scalar) const;
    Vector<2> operator*(double scalar) const;
    Vector<2> operator/(double scalar) const;
    bool operator==(const Vector<2> &other) const;
    bool operator==(double scalar) const;
    Vector<2> &Normalize();
    Vector<2> &Floor();
    Vector<2> &Ceil();
    Vector<2> &Round();
    Vector<2> &Zero();
    Vector<2> &Set(double x, double y);
    Vector<2> &Set(const Vector<2> &other);
    Vector<2> &Set(double scalar);
    Vector<2> &operator-();
    Vector<2> &operator=(const Vector<2> &other);
    Vector<2> &operator+=(const Vector<2> &other);
    Vector<2> &operator-=(const Vector<2> &other);
    Vector<2> &operator*=(const Vector<2> &other);
    Vector<2> &operator/=(const Vector<2> &other);
    Vector<2> &operator=(double scalar);
    Vector<2> &operator+=(double scalar);
    Vector<2> &operator-=(double scalar);
    Vector<2> &operator*=(double scalar);
    Vector<2> &operator/=(double scalar);

    Local<FunctionTemplate> GetObjectConstructorTemplate() override;
};

template<>
class Vector<3> : public sw::ObjectWrap {
public:
    double x, y, z;

    Vector();
    explicit Vector(double scalar);
    Vector(double x, double y, double z);
    Vector(const Vector<3> &other);
    Vector(const Vector<2> &v2, double z);
    //
    // Const member functions
    //
    // Unsafe for integer vectors
    double Length() const;
    double Distance(const Vector<3> &other) const;
    double Distance(double x, double y, double z) const;
    double Dot(const Vector<3> &other) const;
    double AngleCos(const Vector<3> &other) const;
    double Angle(const Vector<3> &other) const;
    Vector<3> Normalized() const;
    double LengthSquared() const;
    double DistanceSquared(const Vector<3> &other) const;
    Vector<3> Cross(const Vector<3> &other) const;
    Vector<3> Min(const Vector<3> &other) const;
    Vector<3> Max(const Vector<3> &other) const;
    Vector<3> Lerp(const Vector<3> &other, double t) const;
    Vector<3> operator+(const Vector<3> &other) const;
    Vector<3> operator-(const Vector<3> &other) const;
    Vector<3> operator*(const Vector<3> &other) const;
    Vector<3> operator/(const Vector<3> &other) const;
    Vector<3> operator+(double scalar) const;
    Vector<3> operator-(double scalar) const;
    Vector<3> operator*(double scalar) const;
    Vector<3> operator/(double scalar) const;
    bool operator==(const Vector<3> &other) const;
    bool operator==(double scalar) const;
//
// Non-const member functions
//

    // Unsafe for integer vectors
    Vector<3> &Normalize();
    Vector<3> &Floor();
    Vector<3> &Ceil();
    Vector<3> &Round();
    Vector<3> &Zero();
    Vector<3> &Set(double x, double y, double z);
    Vector<3> &Set(const Vector<3> &other);
    Vector<3> &Set(const Vector<2> &other, double z);
    Vector<3> &Set(double scalar);
    Vector<3> &operator-();
    Vector<3> &operator=(const Vector<3> &other);
    Vector<3> &operator+=(const Vector<3> &other);
    Vector<3> &operator-=(const Vector<3> &other);
    Vector<3> &operator*=(const Vector<3> &other);
    Vector<3> &operator/=(const Vector<3> &other);
    Vector<3> &operator=(double scalar);
    Vector<3> &operator+=(double scalar);
    Vector<3> &operator-=(double scalar);
    Vector<3> &operator*=(double scalar);
    Vector<3> &operator/=(double scalar);

    Local<FunctionTemplate> GetObjectConstructorTemplate() override;
};

template<>
class Vector<4> : public sw::ObjectWrap {
public:
    double x, y, z, w;
    Vector();
    explicit Vector(double scalar);
    Vector(double x, double y, double z, double w);
    Vector(const Vector<4> &other);
    Vector(const Vector<3> &v3, double w);
    Vector(const Vector<2> &v2, double z, double w);
//
// Const member functions
//

    // Unsafe for integer vectors
    double Length() const;
    double Distance(const Vector<4> &other) const;
    double AngleCos(const Vector<4> &other) const;
    double Angle(const Vector<4> &other) const;
    Vector<4> Normalized() const;
    double LengthSquared() const;
    double DistanceSquared(const Vector<4> &other) const;
    double Dot(const Vector<4> &other) const;
    Vector<4> Min(const Vector<4> &other) const;
    Vector<4> Max(const Vector<4> &other) const;
    Vector<4> Lerp(const Vector<4> &other, double t) const;
    Vector<4> operator+(const Vector<4> &other) const;
    Vector<4> operator-(const Vector<4> &other) const;
    Vector<4> operator*(const Vector<4> &other) const;
    Vector<4> operator/(const Vector<4> &other) const;
    Vector<4> operator+(double scalar) const;
    Vector<4> operator-(double scalar) const;
    Vector<4> operator*(double scalar) const;
    Vector<4> operator/(double scalar) const;
    bool operator==(const Vector<4> &other) const;
    bool operator==(double scalar) const;
//
// Non-const member functions
//

    // Unsafe for integer vectors
    Vector<4> &Normalize();
    Vector<4> &Floor();
    Vector<4> &Ceil();
    Vector<4> &Round();
    Vector<4> &Zero();
    Vector<4> &Set(double x, double y, double z, double w);
    Vector<4> &Set(const Vector<4> &other);
    Vector<4> &Set(const Vector<3> &other, double w);
    Vector<4> &Set(const Vector<2> &other, double z, double w);
    Vector<4> &Set(double scalar);
    Vector<4> &operator-();
    Vector<4> &operator=(const Vector<4> &other);
    Vector<4> &operator+=(const Vector<4> &other);
    Vector<4> &operator-=(const Vector<4> &other);
    Vector<4> &operator*=(const Vector<4> &other);
    Vector<4> &operator/=(const Vector<4> &other);
    Vector<4> &operator=(double scalar);
    Vector<4> &operator+=(double scalar);
    Vector<4> &operator-=(double scalar);
    Vector<4> &operator*=(double scalar);
    Vector<4> &operator/=(double scalar);

    Local<FunctionTemplate> GetObjectConstructorTemplate() override;
};

typedef Vector<2> Vector2;
typedef Vector<3> Vector3;
typedef Vector<4> Vector4;
}

#endif //SANDWICH_VECTOR_HPP
