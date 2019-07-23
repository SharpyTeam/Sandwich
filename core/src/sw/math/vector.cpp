//
// Created by Ilya on 30.06.2019.
//

#include <cmath>
#include "vector.hpp"

namespace sw {
// ----------------------------------------------- Vector<2> ------------------------------------------------

Vector<2>::Vector() : x(0.0), y(0.0) {}

Vector<2>::Vector(double x, double y) : x(x), y(y) {}

Vector<2>::Vector(double scalar) : x(scalar), y(scalar) {}

Vector<2>::Vector(const Vector<2> &other) : x(other.x), y(other.y) {}


double Vector<2>::Length() const {
    return std::sqrt(x * x + y * y);
}


double Vector<2>::LengthSquared() const {
    return x * x + y * y;
}


double Vector<2>::Distance(double x, double y) const {
    double x_diff = this->x - x;
    double y_diff = this->y - y;
    return std::sqrt(x_diff * x_diff + y_diff * y_diff);
}


double Vector<2>::Distance(const Vector<2> &other) const {
    double x_diff = x - other.x;
    double y_diff = y - other.y;
    return std::sqrt(x_diff * x_diff + y_diff * y_diff);
}


double Vector<2>::DistanceSquared(double x, double y) const {
    double x_diff = this->x - x;
    double y_diff = this->y - y;
    return x_diff * x_diff + y_diff * y_diff;
}


double Vector<2>::DistanceSquared(const Vector<2> &other) const {
    double x_diff = x - other.x;
    double y_diff = y - other.y;
    return x_diff * x_diff + y_diff * y_diff;
}


double Vector<2>::Dot(double x, double y) const {
    return this->x * x + this->y * y;
}


double Vector<2>::Dot(const Vector<2> &other) const {
    return x * other.x + y * other.y;
}


double Vector<2>::Determinant(double x, double y) const {
    return this->x * y - this->y * x;
}


double Vector<2>::Determinant(const Vector<2> &other) const {
    return x * other.y - y * other.x;
}


double Vector<2>::Angle(double x, double y) const {
    double dot = this->x * x + this->y * y;
    double det = this->x * y - this->y * x;
    return std::atan2(det, dot);
}


double Vector<2>::Angle(const Vector<2> &other) const {
    double dot = x * other.x + y * other.y;
    double det = x * other.y - y * other.x;
    return std::atan2(det, dot);
}


Vector<2> Vector<2>::Normalized() const {
    double length = std::sqrt(x * x + y * y);
    return Vector<2>(x / length, y / length);
}


Vector<2> Vector<2>::Perpendicular() const {
    return Vector<2>(y, -x);
}


Vector<2> Vector<2>::Min(double x, double y) const {
    return Vector<2>(this->x > x ? x : this->x, this->y > y ? y : this->y);
}


Vector<2> Vector<2>::Min(const Vector<2> &other) const {
    return Vector<2>(x > other.x ? other.x : x, y > other.y ? other.y : y);
}


Vector<2> Vector<2>::Max(double x, double y) const {
    return Vector<2>(this->x > x ? this->x : x, this->y > y ? this->y : y);
}


Vector<2> Vector<2>::Max(const Vector<2> &other) const {
    return Vector<2>(x > other.x ? x : other.x, y > other.y ? y : other.y);
}


Vector<2> Vector<2>::Lerp(double x, double y, double t) const {
    return Vector<2>((double) (this->x + (x - this->x) * t), (double) (this->y + (y - this->y) * t));
}


Vector<2> Vector<2>::Lerp(const Vector<2> &other, double t) const {
    return Vector<2>((double) (x + (other.x - x) * t), (double) (y + (other.y - y) * t));
}


Vector<2> Vector<2>::operator+(const Vector<2> &other) const {
    return Vector<2>(x + other.x, y + other.y);
}


Vector<2> Vector<2>::operator-(const Vector<2> &other) const {
    return Vector<2>(x - other.x, y - other.y);
}


Vector<2> Vector<2>::operator*(const Vector<2> &other) const {
    return Vector<2>(x * other.x, y * other.y);
}


Vector<2> Vector<2>::operator/(const Vector<2> &other) const {
    return Vector<2>(x / other.x, y / other.y);
}


Vector<2> Vector<2>::operator+(double scalar) const {
    return Vector<2>(x + scalar, y + scalar);
}


Vector<2> Vector<2>::operator-(double scalar) const {
    return Vector<2>(x - scalar, y - scalar);
}


Vector<2> Vector<2>::operator*(double scalar) const {
    return Vector<2>(x * scalar, y * scalar);
}


Vector<2> Vector<2>::operator/(double scalar) const {
    return Vector<2>(x / scalar, y / scalar);
}


bool Vector<2>::operator==(const Vector<2> &other) const {
    return (x == other.x && y == other.y);
}


bool Vector<2>::operator==(double scalar) const {
    return (x == scalar && y == scalar);
}


Vector<2> &Vector<2>::Normalize() {
    double length = std::sqrt(x * x + y * y);
    x /= length;
    y /= length;
    return *this;
}


Vector<2> &Vector<2>::Zero() {
    x = 0;
    y = 0;
    return *this;
}


Vector<2> &Vector<2>::Floor() {
    x = std::floor(x);
    y = std::floor(y);
    return *this;
}


Vector<2> &Vector<2>::Ceil() {
    x = std::ceil(x);
    y = std::ceil(y);
    return *this;
}

Vector<2> &Vector<2>::Round() {
    x = std::round(x);
    y = std::round(y);
    return *this;
}

Vector<2> &Vector<2>::Set(double x, double y) {
    this->x = x;
    this->y = y;
    return *this;
}

Vector<2> &Vector<2>::Set(const Vector<2> &other) {
    x = (double) other.x;
    y = (double) other.y;
    return *this;
}

Vector<2> &Vector<2>::Set(double scalar) {
    x = scalar;
    y = scalar;
    return *this;
}

Vector<2> &Vector<2>::operator-() {
    x = -x;
    y = -y;
    return *this;
}

Vector<2> &Vector<2>::operator=(const Vector<2> &other) {
    x = other.x;
    y = other.y;
    return *this;
}

Vector<2> &Vector<2>::operator+=(const Vector<2> &other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector<2> &Vector<2>::operator-=(const Vector<2> &other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector<2> &Vector<2>::operator*=(const Vector<2> &other) {
    x *= other.x;
    y *= other.y;
    return *this;
}

Vector<2> &Vector<2>::operator/=(const Vector<2> &other) {
    x /= other.x;
    y /= other.y;
    return *this;
}

Vector<2> &Vector<2>::operator=(double scalar) {
    x = scalar;
    y = scalar;
    return *this;
}

Vector<2> &Vector<2>::operator+=(double scalar) {
    x += scalar;
    y += scalar;
    return *this;
}

Vector<2> &Vector<2>::operator-=(double scalar) {
    x -= scalar;
    y -= scalar;
    return *this;
}

Vector<2> &Vector<2>::operator*=(double scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector<2> &Vector<2>::operator/=(double scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

template<>
v8::Local<v8::FunctionTemplate> ObjectWrap::GetObjectConstructorTemplate<Vector<2>>() {
    static v8::Local<v8::FunctionTemplate> function_template;
    if (!function_template.IsEmpty()) return function_template;

    // Constructor
    function_template = v8::FunctionTemplate::New(
            v8::Isolate::GetCurrent(),
            [](const v8::FunctionCallbackInfo<v8::Value> &info) {
                Vector<2> *v = nullptr;
                if (info.Length() == 1 && info[0]->IsObject()) {
                    v = new Vector<2>(*ObjectWrap::Unwrap<Vector<2>>(info[0].As<v8::Object>()));
                } else {
                    switch (info.Length()) {
                        case 0:
                            v = new Vector<2>();
                            break;
                        case 1:
                            v = new Vector<2>(info[0].As<v8::Number>()->Value());
                            break;
                        case 2:
                            v = new Vector<2>(info[0].As<v8::Number>()->Value(),
                                              info[1].As<v8::Number>()->Value());
                            break;
                    }
                }

                info.This()->SetAlignedPointerInInternalField(0, v);
            }
    );

    function_template->SetClassName(v8_str("Vector2"));

    function_template->InstanceTemplate()->SetInternalFieldCount(1);

    auto o_template = function_template->InstanceTemplate();

    o_template->SetAccessor(
            v8_str("x"),
            [](v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector<2>>(info.Holder());
                info.GetReturnValue().Set(v->x);
            },
            [](v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info) {
                auto v = ObjectWrap::Unwrap<Vector<2>>(info.Holder());
                v->x = value.As<v8::Number>()->Value();
            }
    );

    o_template->SetAccessor(
            v8_str("y"),
            [](v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector<2>>(info.Holder());
                info.GetReturnValue().Set(v->y);
            },
            [](v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info) {
                auto v = ObjectWrap::Unwrap<Vector<2>>(info.Holder());
                v->y = value.As<v8::Number>()->Value();
            }
    );

    o_template->Set(
            v8_str("set"),
            v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), [](const v8::FunctionCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector<2>>(info.Holder());
                v->Set(info[0].As<v8::Number>()->Value());
                info.GetReturnValue().Set(info.Holder());
            })
    );

    return function_template;
}

DEFINE_WRAP(Vector<2>)



// ----------------------------------------------- Vector<3> ------------------------------------------------





Vector<3>::Vector() : x(0), y(0), z(0) {}


Vector<3>::Vector(double scalar) : x(scalar), y(scalar), z(scalar) {}


Vector<3>::Vector(double x, double y, double z) : x(x), y(y), z(z) {}


Vector<3>::Vector(const Vector<3> &other) : x((double) other.x), y((double) other.y), z((double) other.z) {}


Vector<3>::Vector(const Vector<2> &v2, double z) : x((double) v2.x), y((double) v2.y), z(z) {}


double Vector<3>::Length() const {
    return std::sqrt(x * x + y * y + z * z);
}


double Vector<3>::LengthSquared() const {
    return x * x + y * y + z * z;
}


double Vector<3>::Distance(const Vector<3> &other) const {
    double x_diff = x - other.x;
    double y_diff = y - other.y;
    double z_diff = z - other.z;
    return std::sqrt(x_diff * x_diff + y_diff * y_diff + z_diff * z_diff);
}


double Vector<3>::Distance(double x, double y, double z) const {
    double x_diff = this->x - x;
    double y_diff = this->y - y;
    double z_diff = this->z - z;
    return std::sqrt(x_diff * x_diff + y_diff * y_diff + z_diff * z_diff);
}


double Vector<3>::DistanceSquared(const Vector<3> &other) const {
    double x_diff = x - other.x;
    double y_diff = y - other.y;
    double z_diff = z - other.z;
    return x_diff * x_diff + y_diff * y_diff + z_diff * z_diff;
}


double Vector<3>::Dot(const Vector<3> &other) const {
    return x * other.x + y * other.y + z * other.z;
}


double Vector<3>::AngleCos(const Vector<3> &other) const {
    return (double) ((x * other.x + y * other.y + z * other.z) /
                     std::sqrt((x * x + y * y + z * z) * (other.x * other.x + other.y * other.y + other.z * other.z)));
}


double Vector<3>::Angle(const Vector<3> &other) const {
    double cos = (x * other.x + y * other.y + z * other.z) /
                 std::sqrt((x * x + y * y + z * z) * (other.x * other.x + other.y * other.y + other.z * other.z));
    // doublehis is because sometimes cos goes above 1 or below -1 because of lost precision
    cos = cos < 1 ? cos : 1;
    cos = cos > -1 ? cos : -1;
    return std::acos(cos);
}


Vector<3> Vector<3>::Normalized() const {
    double length = std::sqrt(x * x + y * y + z * z);
    return Vector<3>(x / length, y / length, z / length);
}


Vector<3> Vector<3>::Cross(const Vector<3> &other) const {
    return Vector<3>(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}


Vector<3> Vector<3>::Min(const Vector<3> &other) const {
    return Vector<3>(x > other.x ? other.x : x, y > other.y ? other.y : y, z > other.z ? other.z : z);
}


Vector<3> Vector<3>::Max(const Vector<3> &other) const {
    return Vector<3>(x > other.x ? x : other.x, y > other.y ? y : other.y, z > other.z ? z : other.z);
}


Vector<3> Vector<3>::Lerp(const Vector<3> &other, double t) const {
    return Vector<3>((double) (x + (other.x - x) * t), (double) (y + (other.y - y) * t),
                     (double) (z + (other.z - z) * t));
}


Vector<3> Vector<3>::operator+(const Vector<3> &other) const {
    return Vector<3>(x + other.x, y + other.y, z + other.z);
}


Vector<3> Vector<3>::operator-(const Vector<3> &other) const {
    return Vector<3>(x - other.x, y - other.y, z - other.z);
}


Vector<3> Vector<3>::operator*(const Vector<3> &other) const {
    return Vector<3>(x * other.x, y * other.y, z * other.z);
}


Vector<3> Vector<3>::operator/(const Vector<3> &other) const {
    return Vector<3>(x / other.x, y / other.y, z / other.z);
}


Vector<3> Vector<3>::operator+(double scalar) const {
    return Vector<3>(x + scalar, y + scalar, z + scalar);
}


Vector<3> Vector<3>::operator-(double scalar) const {
    return Vector<3>(x - scalar, y - scalar, z - scalar);
}


Vector<3> Vector<3>::operator*(double scalar) const {
    return Vector<3>(x * scalar, y * scalar, z * scalar);
}


Vector<3> Vector<3>::operator/(double scalar) const {
    return Vector<3>(x / scalar, y / scalar, z / scalar);
}


bool Vector<3>::operator==(const Vector<3> &other) const {
    return (x == other.x && y == other.y && z == other.z);
}


bool Vector<3>::operator==(double scalar) const {
    return (x == scalar && y == scalar && z == scalar);
}


Vector<3> &Vector<3>::Normalize() {
    double length = std::sqrt(x * x + y * y + z * z);
    x /= length;
    y /= length;
    z /= length;
    return *this;
}


Vector<3> &Vector<3>::Zero() {
    x = 0;
    y = 0;
    z = 0;
    return *this;
}


Vector<3> &Vector<3>::Floor() {
    x = std::floor(x);
    y = std::floor(y);
    z = std::floor(z);
    return *this;
}


Vector<3> &Vector<3>::Ceil() {
    x = std::ceil(x);
    y = std::ceil(y);
    z = std::ceil(z);
    return *this;
}


Vector<3> &Vector<3>::Round() {
    x = std::round(x);
    y = std::round(y);
    z = std::round(z);
    return *this;
}


Vector<3> &Vector<3>::Set(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
    return *this;
}


Vector<3> &Vector<3>::Set(const Vector<3> &other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    return *this;
}


Vector<3> &Vector<3>::Set(const Vector<2> &other, double z) {
    this->x = other.x;
    this->y = other.y;
    this->z = z;
    return *this;
}


Vector<3> &Vector<3>::Set(double scalar) {
    x = scalar;
    y = scalar;
    z = scalar;
    return *this;
}


Vector<3> &Vector<3>::operator-() {
    x = -x;
    y = -y;
    z = -z;
    return *this;
}


Vector<3> &Vector<3>::operator=(const Vector<3> &other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}


Vector<3> &Vector<3>::operator+=(const Vector<3> &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}


Vector<3> &Vector<3>::operator-=(const Vector<3> &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}


Vector<3> &Vector<3>::operator*=(const Vector<3> &other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}


Vector<3> &Vector<3>::operator/=(const Vector<3> &other) {
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
}


Vector<3> &Vector<3>::operator=(double scalar) {
    x = scalar;
    y = scalar;
    z = scalar;
    return *this;
}


Vector<3> &Vector<3>::operator+=(double scalar) {
    x += scalar;
    y += scalar;
    z += scalar;
    return *this;
}


Vector<3> &Vector<3>::operator-=(double scalar) {
    x -= scalar;
    y -= scalar;
    z -= scalar;
    return *this;
}


Vector<3> &Vector<3>::operator*=(double scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}


Vector<3> &Vector<3>::operator/=(double scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}


template<>
v8::Local<v8::FunctionTemplate> ObjectWrap::GetObjectConstructorTemplate<Vector<3>>() {
    static v8::Local<v8::FunctionTemplate> function_template;
    if (!function_template.IsEmpty()) return function_template;

    // Constructor
    function_template = v8::FunctionTemplate::New(
            v8::Isolate::GetCurrent(),
            [](const v8::FunctionCallbackInfo<v8::Value> &info) {
                Vector<3> *v = nullptr;
                if (info.Length() == 1 && info[0]->IsObject()) {
                    v = new Vector<3>(*ObjectWrap::Unwrap<Vector<3>>(info[0].As<v8::Object>()));
                } else {
                    switch (info.Length()) {
                        case 0:
                            v = new Vector<3>();
                            break;
                        case 1:
                            v = new Vector<3>(info[0].As<v8::Number>()->Value());
                            break;
                        case 2:
                            v = new Vector<3>(info[0].As<v8::Number>()->Value(),
                                              info[1].As<v8::Number>()->Value(),
                                              info[2].As<v8::Number>()->Value());
                            break;
                    }
                }

                info.This()->SetAlignedPointerInInternalField(0, v);
            }
    );

    function_template->SetClassName(v8_str("Vector3"));

    function_template->InstanceTemplate()->SetInternalFieldCount(1);

    auto o_template = function_template->InstanceTemplate();

    o_template->SetAccessor(
            v8_str("x"),
            [](v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector<3>>(info.Holder());
                info.GetReturnValue().Set(v->x);
            },
            [](v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info) {
                auto v = ObjectWrap::Unwrap<Vector<3>>(info.Holder());
                v->x = value.As<v8::Number>()->Value();
            }
    );

    o_template->SetAccessor(
            v8_str("y"),
            [](v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector<3>>(info.Holder());
                info.GetReturnValue().Set(v->y);
            },
            [](v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info) {
                auto v = ObjectWrap::Unwrap<Vector<3>>(info.Holder());
                v->y = value.As<v8::Number>()->Value();
            }
    );

    o_template->SetAccessor(
            v8_str("z"),
            [](v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector<3>>(info.Holder());
                info.GetReturnValue().Set(v->z);
            },
            [](v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info) {
                auto v = ObjectWrap::Unwrap<Vector<3>>(info.Holder());
                v->z = value.As<v8::Number>()->Value();
            }
    );

    o_template->Set(
            v8_str("set"),
            v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), [](const v8::FunctionCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector<3>>(info.Holder());
                v->Set(info[0].As<v8::Number>()->Value());
                info.GetReturnValue().Set(info.Holder());
            })
    );

    return function_template;
}

DEFINE_WRAP(Vector<3>)


// ----------------------------------------------- Vector<4> ------------------------------------------------





Vector<4>::Vector() : x(0.0), y(0.0), z(0.0), w(0.0) {}


Vector<4>::Vector(double scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {}


Vector<4>::Vector(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}


Vector<4>::Vector(const Vector<4> &other) : x((double) other.x), y((double) other.y), z((double) other.z),
                                            w((double) other.w) {}


Vector<4>::Vector(const Vector<3> &v3, double w) : x((double) v3.x), y((double) v3.y), z((double) v3.z), w(w) {}


Vector<4>::Vector(const Vector<2> &v2, double z, double w) : x((double) v2.x), y((double) v2.y), z(z), w(w) {}


double Vector<4>::Length() const {
    return std::sqrt(x * x + y * y + z * z + w * w);
}


double Vector<4>::LengthSquared() const {
    return x * x + y * y + z * z + w * w;
}


double Vector<4>::Distance(const Vector<4> &other) const {
    double x_diff = x - other.x;
    double y_diff = y - other.y;
    double z_diff = z - other.z;
    double w_diff = w - other.w;
    return std::sqrt(x_diff * x_diff + y_diff * y_diff + z_diff * z_diff + w_diff * w_diff);
}


double Vector<4>::DistanceSquared(const Vector<4> &other) const {
    double x_diff = x - other.x;
    double y_diff = y - other.y;
    double z_diff = z - other.z;
    double w_diff = w - other.w;
    return x_diff * x_diff + y_diff * y_diff + z_diff * z_diff + w_diff * w_diff;
}


double Vector<4>::Dot(const Vector<4> &other) const {
    return x * other.x + y * other.y + z * other.z + w * other.w;
}


double Vector<4>::AngleCos(const Vector<4> &other) const {
    return (double) ((x * other.x + y * other.y + z * other.z + w * other.w) /
                     std::sqrt((x * x + y * y + z * z + w * w) *
                               (other.x * other.x + other.y * other.y + other.z * other.z + other.w * other.w)));
}


double Vector<4>::Angle(const Vector<4> &other) const {
    double cos = (x * other.x + y * other.y + z * other.z + w * other.w) /
                 std::sqrt((x * x + y * y + z * z + w * w) *
                           (other.x * other.x + other.y * other.y + other.z * other.z + other.w * other.w));
    // doublehis is because sometimes cos goes above 1 or below -1 because of lost precision
    cos = cos < 1 ? cos : 1;
    cos = cos > -1 ? cos : -1;
    return std::acos(cos);
}


Vector<4> Vector<4>::Normalized() const {
    double length = std::sqrt(x * x + y * y + z * z + w * w);
    return Vector<4>(x / length, y / length, z / length, w / length);
}


Vector<4> Vector<4>::Min(const Vector<4> &other) const {
    return Vector<4>(x > other.x ? other.x : x, y > other.y ? other.y : y, z > other.z ? other.z : z,
                     w > other.w ? other.w : w);
}


Vector<4> Vector<4>::Max(const Vector<4> &other) const {
    return Vector<4>(x > other.x ? x : other.x, y > other.y ? y : other.y, z > other.z ? z : other.z,
                     w > other.w ? w : other.w);
}


Vector<4> Vector<4>::Lerp(const Vector<4> &other, double t) const {
    return Vector<4>((double) (x + (other.x - x) * t), (double) (y + (other.y - y) * t),
                     (double) (z + (other.z - z) * t),
                     (double) (w + (other.w - w) * t));
}


Vector<4> Vector<4>::operator+(const Vector<4> &other) const {
    return Vector<4>(x + other.x, y + other.y, z + other.z, w + other.w);
}


Vector<4> Vector<4>::operator-(const Vector<4> &other) const {
    return Vector<4>(x - other.x, y - other.y, z - other.z, w - other.w);
}


Vector<4> Vector<4>::operator*(const Vector<4> &other) const {
    return Vector<4>(x * other.x, y * other.y, z * other.z, w * other.w);
}


Vector<4> Vector<4>::operator/(const Vector<4> &other) const {
    return Vector<4>(x / other.x, y / other.y, z / other.z, w / other.w);
}


Vector<4> Vector<4>::operator+(double scalar) const {
    return Vector<4>(x + scalar, y + scalar, z + scalar, w + scalar);
}


Vector<4> Vector<4>::operator-(double scalar) const {
    return Vector<4>(x - scalar, y - scalar, z - scalar, w - scalar);
}


Vector<4> Vector<4>::operator*(double scalar) const {
    return Vector<4>(x * scalar, y * scalar, z * scalar, w * scalar);
}


Vector<4> Vector<4>::operator/(double scalar) const {
    return Vector<4>(x / scalar, y / scalar, z / scalar, w / scalar);
}


bool Vector<4>::operator==(const Vector<4> &other) const {
    return (x == other.x && y == other.y && z == other.z && w == other.w);
}


bool Vector<4>::operator==(double scalar) const {
    return (x == scalar && y == scalar && z == scalar && w == scalar);
}


Vector<4> &Vector<4>::Normalize() {
    double length = std::sqrt(x * x + y * y + z * z + w * w);
    x /= length;
    y /= length;
    z /= length;
    w /= length;
    return *this;
}


Vector<4> &Vector<4>::Zero() {
    x = 0;
    y = 0;
    z = 0;
    w = 0;
    return *this;
}


Vector<4> &Vector<4>::Floor() {
    x = std::floor(x);
    y = std::floor(y);
    z = std::floor(z);
    w = std::floor(w);
    return *this;
}


Vector<4> &Vector<4>::Ceil() {
    x = std::ceil(x);
    y = std::ceil(y);
    z = std::ceil(z);
    w = std::ceil(w);
    return *this;
}


Vector<4> &Vector<4>::Round() {
    x = std::round(x);
    y = std::round(y);
    z = std::round(z);
    w = std::round(w);
    return *this;
}


Vector<4> &Vector<4>::Set(double x, double y, double z, double w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
    return *this;
}


Vector<4> &Vector<4>::Set(const Vector<4> &other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->w = other.w;
    return *this;
}


Vector<4> &Vector<4>::Set(const Vector<3> &other, double w) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->w = w;
    return *this;
}


Vector<4> &Vector<4>::Set(const Vector<2> &other, double z, double w) {
    this->x = other.x;
    this->y = other.y;
    this->z = z;
    this->w = w;
    return *this;
}


Vector<4> &Vector<4>::Set(double scalar) {
    x = scalar;
    y = scalar;
    z = scalar;
    w = scalar;
    return *this;
}


Vector<4> &Vector<4>::operator-() {
    x = -x;
    y = -y;
    z = -z;
    w = -w;
    return *this;
}


Vector<4> &Vector<4>::operator=(const Vector<4> &other) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}


Vector<4> &Vector<4>::operator+=(const Vector<4> &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}


Vector<4> &Vector<4>::operator-=(const Vector<4> &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}


Vector<4> &Vector<4>::operator*=(const Vector<4> &other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    w *= other.w;
    return *this;
}


Vector<4> &Vector<4>::operator/=(const Vector<4> &other) {
    x /= other.x;
    y /= other.y;
    z /= other.z;
    w /= other.w;
    return *this;
}


Vector<4> &Vector<4>::operator=(double scalar) {
    x = scalar;
    y = scalar;
    z = scalar;
    w = scalar;
    return *this;
}


Vector<4> &Vector<4>::operator+=(double scalar) {
    x += scalar;
    y += scalar;
    z += scalar;
    w += scalar;
    return *this;
}


Vector<4> &Vector<4>::operator-=(double scalar) {
    x -= scalar;
    y -= scalar;
    z -= scalar;
    w -= scalar;
    return *this;
}


Vector<4> &Vector<4>::operator*=(double scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
}


Vector<4> &Vector<4>::operator/=(double scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
    return *this;
}

template<>
v8::Local<v8::FunctionTemplate> ObjectWrap::GetObjectConstructorTemplate<Vector<4>>() {
    static v8::Local<v8::FunctionTemplate> function_template;
    if (!function_template.IsEmpty()) return function_template;

    // Constructor
    function_template = v8::FunctionTemplate::New(
            v8::Isolate::GetCurrent(),
            [](const v8::FunctionCallbackInfo<v8::Value> &info) {
                Vector<4> *v = nullptr;
                if (info.Length() == 1 && info[0]->IsObject()) {
                    v = new Vector<4>(*ObjectWrap::Unwrap<Vector<4>>(info[0].As<v8::Object>()));
                } else {
                    switch (info.Length()) {
                        case 0:
                            v = new Vector<4>();
                            break;
                        case 1:
                            v = new Vector<4>(info[0].As<v8::Number>()->Value());
                            break;
                        case 2:
                            v = new Vector<4>(info[0].As<v8::Number>()->Value(),
                                              info[1].As<v8::Number>()->Value(),
                                              info[2].As<v8::Number>()->Value(),
                                              info[3].As<v8::Number>()->Value());
                            break;
                    }
                }

                info.This()->SetAlignedPointerInInternalField(0, v);
            }
    );

    function_template->SetClassName(v8_str("Vector4"));

    function_template->InstanceTemplate()->SetInternalFieldCount(1);

    auto o_template = function_template->InstanceTemplate();

    o_template->SetAccessor(
            v8_str("x"),
            [](v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector<4>>(info.Holder());
                info.GetReturnValue().Set(v->x);
            },
            [](v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info) {
                auto v = ObjectWrap::Unwrap<Vector<4>>(info.Holder());
                v->x = value.As<v8::Number>()->Value();
            }
    );

    o_template->SetAccessor(
            v8_str("y"),
            [](v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector<4>>(info.Holder());
                info.GetReturnValue().Set(v->y);
            },
            [](v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info) {
                auto v = ObjectWrap::Unwrap<Vector<4>>(info.Holder());
                v->y = value.As<v8::Number>()->Value();
            }
    );

    o_template->SetAccessor(
            v8_str("z"),
            [](v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector<4>>(info.Holder());
                info.GetReturnValue().Set(v->z);
            },
            [](v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info) {
                auto v = ObjectWrap::Unwrap<Vector<4>>(info.Holder());
                v->z = value.As<v8::Number>()->Value();
            }
    );

    o_template->SetAccessor(
            v8_str("w"),
            [](v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector<4>>(info.Holder());
                info.GetReturnValue().Set(v->w);
            },
            [](v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info) {
                auto v = ObjectWrap::Unwrap<Vector<4>>(info.Holder());
                v->w = value.As<v8::Number>()->Value();
            }
    );

    o_template->Set(
            v8_str("set"),
            v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), [](const v8::FunctionCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector<4>>(info.Holder());
                v->Set(info[0].As<v8::Number>()->Value());
                info.GetReturnValue().Set(info.Holder());
            })
    );

    return function_template;
}

DEFINE_WRAP(Vector<4>)


}
