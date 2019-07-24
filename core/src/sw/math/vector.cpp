//
// Created by Ilya on 30.06.2019.
//

#include <cmath>
#include <string>
#include "vector.hpp"

namespace sw {
// ----------------------------------------------- Vector2 ------------------------------------------------

Vector2::Vector2() : x(0.0), y(0.0) {}

Vector2::Vector2(double x, double y) : x(x), y(y) {}

Vector2::Vector2(double scalar) : x(scalar), y(scalar) {}

Vector2::Vector2(const Vector2 &other) : x(other.x), y(other.y) {}


double Vector2::Length() const {
    return std::sqrt(x * x + y * y);
}


double Vector2::LengthSquared() const {
    return x * x + y * y;
}


double Vector2::Distance(double x, double y) const {
    double x_diff = this->x - x;
    double y_diff = this->y - y;
    return std::sqrt(x_diff * x_diff + y_diff * y_diff);
}


double Vector2::Distance(const Vector2 &other) const {
    double x_diff = x - other.x;
    double y_diff = y - other.y;
    return std::sqrt(x_diff * x_diff + y_diff * y_diff);
}


double Vector2::DistanceSquared(double x, double y) const {
    double x_diff = this->x - x;
    double y_diff = this->y - y;
    return x_diff * x_diff + y_diff * y_diff;
}


double Vector2::DistanceSquared(const Vector2 &other) const {
    double x_diff = x - other.x;
    double y_diff = y - other.y;
    return x_diff * x_diff + y_diff * y_diff;
}


double Vector2::Dot(double x, double y) const {
    return this->x * x + this->y * y;
}


double Vector2::Dot(const Vector2 &other) const {
    return x * other.x + y * other.y;
}


double Vector2::Determinant(double x, double y) const {
    return this->x * y - this->y * x;
}


double Vector2::Determinant(const Vector2 &other) const {
    return x * other.y - y * other.x;
}


double Vector2::Angle(double x, double y) const {
    double dot = this->x * x + this->y * y;
    double det = this->x * y - this->y * x;
    return std::atan2(det, dot);
}


double Vector2::Angle(const Vector2 &other) const {
    double dot = x * other.x + y * other.y;
    double det = x * other.y - y * other.x;
    return std::atan2(det, dot);
}


Vector2 Vector2::Normalized() const {
    double length = std::sqrt(x * x + y * y);
    return Vector2(x / length, y / length);
}


Vector2 Vector2::Perpendicular() const {
    return Vector2(y, -x);
}


Vector2 Vector2::Min(double x, double y) const {
    return Vector2(this->x > x ? x : this->x, this->y > y ? y : this->y);
}


Vector2 Vector2::Min(const Vector2 &other) const {
    return Vector2(x > other.x ? other.x : x, y > other.y ? other.y : y);
}


Vector2 Vector2::Max(double x, double y) const {
    return Vector2(this->x > x ? this->x : x, this->y > y ? this->y : y);
}


Vector2 Vector2::Max(const Vector2 &other) const {
    return Vector2(x > other.x ? x : other.x, y > other.y ? y : other.y);
}


Vector2 Vector2::Lerp(double x, double y, double t) const {
    return Vector2((double) (this->x + (x - this->x) * t), (double) (this->y + (y - this->y) * t));
}


Vector2 Vector2::Lerp(const Vector2 &other, double t) const {
    return Vector2((double) (x + (other.x - x) * t), (double) (y + (other.y - y) * t));
}


Vector2 Vector2::operator+(const Vector2 &other) const {
    return Vector2(x + other.x, y + other.y);
}


Vector2 Vector2::operator-(const Vector2 &other) const {
    return Vector2(x - other.x, y - other.y);
}


Vector2 Vector2::operator*(const Vector2 &other) const {
    return Vector2(x * other.x, y * other.y);
}


Vector2 Vector2::operator/(const Vector2 &other) const {
    return Vector2(x / other.x, y / other.y);
}


Vector2 Vector2::operator+(double scalar) const {
    return Vector2(x + scalar, y + scalar);
}


Vector2 Vector2::operator-(double scalar) const {
    return Vector2(x - scalar, y - scalar);
}


Vector2 Vector2::operator*(double scalar) const {
    return Vector2(x * scalar, y * scalar);
}


Vector2 Vector2::operator/(double scalar) const {
    return Vector2(x / scalar, y / scalar);
}


bool Vector2::operator==(const Vector2 &other) const {
    return (x == other.x && y == other.y);
}


bool Vector2::operator==(double scalar) const {
    return (x == scalar && y == scalar);
}


Vector2 &Vector2::Normalize() {
    double length = std::sqrt(x * x + y * y);
    x /= length;
    y /= length;
    return *this;
}


Vector2 &Vector2::Zero() {
    x = 0;
    y = 0;
    return *this;
}


Vector2 &Vector2::Floor() {
    x = std::floor(x);
    y = std::floor(y);
    return *this;
}


Vector2 &Vector2::Ceil() {
    x = std::ceil(x);
    y = std::ceil(y);
    return *this;
}

Vector2 &Vector2::Round() {
    x = std::round(x);
    y = std::round(y);
    return *this;
}

Vector2 &Vector2::Set(double x, double y) {
    this->x = x;
    this->y = y;
    return *this;
}

Vector2 &Vector2::Set(const Vector2 &other) {
    x = (double) other.x;
    y = (double) other.y;
    return *this;
}

Vector2 &Vector2::Set(double scalar) {
    x = scalar;
    y = scalar;
    return *this;
}

Vector2 &Vector2::operator-() {
    x = -x;
    y = -y;
    return *this;
}

Vector2 &Vector2::operator=(const Vector2 &other) {
    x = other.x;
    y = other.y;
    return *this;
}

Vector2 &Vector2::operator+=(const Vector2 &other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2 &Vector2::operator-=(const Vector2 &other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2 &Vector2::operator*=(const Vector2 &other) {
    x *= other.x;
    y *= other.y;
    return *this;
}

Vector2 &Vector2::operator/=(const Vector2 &other) {
    x /= other.x;
    y /= other.y;
    return *this;
}

Vector2 &Vector2::operator=(double scalar) {
    x = scalar;
    y = scalar;
    return *this;
}

Vector2 &Vector2::operator+=(double scalar) {
    x += scalar;
    y += scalar;
    return *this;
}

Vector2 &Vector2::operator-=(double scalar) {
    x -= scalar;
    y -= scalar;
    return *this;
}

Vector2 &Vector2::operator*=(double scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2 &Vector2::operator/=(double scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

template<>
v8::Local<v8::FunctionTemplate> ObjectWrap::GetObjectConstructorTemplate<Vector2>() {
    static v8::Local<v8::FunctionTemplate> function_template;
    if (!function_template.IsEmpty()) return function_template;

    // Constructor
    function_template = v8::FunctionTemplate::New(
            v8::Isolate::GetCurrent(),
            [](const v8::FunctionCallbackInfo<v8::Value> &info) {
                Vector2 *v = nullptr;
                switch (info.Length()) {
                    case 0:
                        v = new Vector2();
                        break;
                    case 1: {
                        if (info[0]->IsNumber())
                            v = new Vector2(info[0].As<v8::Number>()->Value());
                        else if (function_template->HasInstance(info[0]))
                            v = new Vector2(*ObjectWrap::Unwrap<Vector2>(info[0].As<v8::Object>()));
                        else
                            v8::Isolate::GetCurrent()->ThrowException(
                                    v8::Exception::TypeError(v8_str("Arguments mismatch")));
                        break;
                    }
                    default: {
                        if (info.Length() > 2) {
                            // TODO throw warning
                        }
                        if (info[0]->IsNumber() && info[1]->IsNumber()) {
                            v = new Vector2(info[0].As<v8::Number>()->Value(),
                                              info[1].As<v8::Number>()->Value());
                        } else {
                            v8::Isolate::GetCurrent()->ThrowException(
                                    v8::Exception::TypeError(v8_str("Arguments mismatch")));
                        }
                        break;
                    }
                }
                if (v) {
                    v->Wrap(info.This());
                }
            }
    );

    function_template->SetClassName(v8_str("Vector2"));
    function_template->InstanceTemplate()->SetInternalFieldCount(1);
    auto o_template = function_template->InstanceTemplate();
    auto o_prot_template = function_template->PrototypeTemplate();

    o_template->SetAccessor(
            v8_str("x"),
            [](v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector2>(info.Holder());
                info.GetReturnValue().Set(v->x);
            },
            [](v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info) {
                auto v = ObjectWrap::Unwrap<Vector2>(info.Holder());
                v->x = value.As<v8::Number>()->Value();
            }
    );

    o_template->SetAccessor(
            v8_str("y"),
            [](v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector2>(info.Holder());
                info.GetReturnValue().Set(v->y);
            },
            [](v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info) {
                auto v = ObjectWrap::Unwrap<Vector2>(info.Holder());
                v->y = value.As<v8::Number>()->Value();
            }
    );


    auto function_property_attributes = (v8::PropertyAttribute) (
            v8::PropertyAttribute::DontDelete |
            v8::PropertyAttribute::ReadOnly |
            v8::PropertyAttribute::DontEnum
    );

    o_prot_template->Set(
            v8_str("set"),
            v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), [](const v8::FunctionCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector2>(info.Holder());
                switch (info.Length()) {
                    case 0:
                        v8::Isolate::GetCurrent()->ThrowException(
                                v8::Exception::TypeError(v8_str("Arguments mismatch")));
                        break;
                    case 1: {
                        if (info[0]->IsNumber())
                            v->Set(info[0].As<v8::Number>()->Value());
                        else if (function_template->HasInstance(info[0]))
                            v->Set(*ObjectWrap::Unwrap<Vector2>(info[0].As<v8::Object>()));
                        else
                            v8::Isolate::GetCurrent()->ThrowException(
                                    v8::Exception::TypeError(v8_str("Arguments mismatch")));
                        break;
                    }
                    default: {
                        if (info[0]->IsNumber() && info[1]->IsNumber()) {
                            v->Set(info[0].As<v8::Number>()->Value(),
                                   info[1].As<v8::Number>()->Value());
                        } else {
                            v8::Isolate::GetCurrent()->ThrowException(
                                    v8::Exception::TypeError(v8_str("Arguments mismatch")));
                        }
                        break;
                    }
                }
                info.GetReturnValue().Set(info.Holder());
            }),
            function_property_attributes
    );

    o_prot_template->Set(
            v8_str("length"),
            v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), [](const v8::FunctionCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector2>(info.Holder());
                info.GetReturnValue().Set(v->Length());
            }),
            function_property_attributes
    );

    o_prot_template->Set(
            v8_str("lengthSquared"),
            v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), [](const v8::FunctionCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector2>(info.Holder());
                info.GetReturnValue().Set(v->LengthSquared());
            }),
            function_property_attributes
    );

    o_prot_template->Set(
            v8_str("normalized"),
            v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), [](const v8::FunctionCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector2>(info.Holder());
                auto n = new Vector2(v->Normalized());
                n->Wrap();
                info.GetReturnValue().Set(n->GetHandle());
            }),
            function_property_attributes
    );

    o_prot_template->Set(
            v8_str("normalize"),
            v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), [](const v8::FunctionCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector2>(info.Holder());
                v->Normalize();
                info.GetReturnValue().Set(info.Holder());
            }),
            function_property_attributes
    );

    o_prot_template->Set(
            v8_str("distance"),
            v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), [](const v8::FunctionCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector2>(info.Holder());
                switch (info.Length()) {
                    case 0:
                        v8::Isolate::GetCurrent()->ThrowException(
                                v8::Exception::TypeError(v8_str("Arguments mismatch")));
                        break;
                    case 1: {
                        if (function_template->HasInstance(info[0]))
                            info.GetReturnValue().Set(
                                    v->Distance(*ObjectWrap::Unwrap<Vector2>(info[0].As<v8::Object>())));
                        else
                            v8::Isolate::GetCurrent()->ThrowException(
                                    v8::Exception::TypeError(v8_str("Arguments mismatch")));
                        break;
                    }
                    default: {
                        if (info[0]->IsNumber() && info[1]->IsNumber()) {
                            info.GetReturnValue().Set(v->Distance(
                                    info[0].As<v8::Number>()->Value(),
                                    info[1].As<v8::Number>()->Value()
                            ));
                        } else {
                            v8::Isolate::GetCurrent()->ThrowException(
                                    v8::Exception::TypeError(v8_str("Arguments mismatch")));
                        }
                        break;
                    }
                }
            }),
            function_property_attributes
    );

    o_prot_template->Set(
            v8_str("distanceSquared"),
            v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), [](const v8::FunctionCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector2>(info.Holder());
                switch (info.Length()) {
                    case 0:
                        v8::Isolate::GetCurrent()->ThrowException(
                                v8::Exception::TypeError(v8_str("Arguments mismatch")));
                        break;
                    case 1: {
                        if (function_template->HasInstance(info[0]))
                            info.GetReturnValue().Set(
                                    v->DistanceSquared(*ObjectWrap::Unwrap<Vector2>(info[0].As<v8::Object>())));
                        else
                            v8::Isolate::GetCurrent()->ThrowException(
                                    v8::Exception::TypeError(v8_str("Arguments mismatch")));
                        break;
                    }
                    default: {
                        if (info[0]->IsNumber() && info[1]->IsNumber()) {
                            info.GetReturnValue().Set(v->DistanceSquared(
                                    info[0].As<v8::Number>()->Value(),
                                    info[1].As<v8::Number>()->Value()
                            ));
                        } else {
                            v8::Isolate::GetCurrent()->ThrowException(
                                    v8::Exception::TypeError(v8_str("Arguments mismatch")));
                        }
                        break;
                    }
                }
            }),
            function_property_attributes
    );

    o_prot_template->Set(
            v8_str("angle"),
            v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), [](const v8::FunctionCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector2>(info.Holder());
                switch (info.Length()) {
                    case 0:
                        v8::Isolate::GetCurrent()->ThrowException(
                                v8::Exception::TypeError(v8_str("Arguments mismatch")));
                        break;
                    case 1: {
                        if (function_template->HasInstance(info[0]))
                            info.GetReturnValue().Set(
                                    v->Angle(*ObjectWrap::Unwrap<Vector2>(info[0].As<v8::Object>())));
                        else
                            v8::Isolate::GetCurrent()->ThrowException(
                                    v8::Exception::TypeError(v8_str("Arguments mismatch")));
                        break;
                    }
                    default: {
                        if (info[0]->IsNumber() && info[1]->IsNumber()) {
                            info.GetReturnValue().Set(v->Angle(
                                    info[0].As<v8::Number>()->Value(),
                                    info[1].As<v8::Number>()->Value()
                            ));
                        } else {
                            v8::Isolate::GetCurrent()->ThrowException(
                                    v8::Exception::TypeError(v8_str("Arguments mismatch")));
                        }
                        break;
                    }
                }
            }),
            function_property_attributes
    );

    o_prot_template->Set(
            v8_str("dot"),
            v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), [](const v8::FunctionCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector2>(info.Holder());
                switch (info.Length()) {
                    case 0:
                        v8::Isolate::GetCurrent()->ThrowException(
                                v8::Exception::TypeError(v8_str("Arguments mismatch")));
                        break;
                    case 1: {
                        if (function_template->HasInstance(info[0]))
                            info.GetReturnValue().Set(
                                    v->Dot(*ObjectWrap::Unwrap<Vector2>(info[0].As<v8::Object>())));
                        else
                            v8::Isolate::GetCurrent()->ThrowException(
                                    v8::Exception::TypeError(v8_str("Arguments mismatch")));
                        break;
                    }
                    default: {
                        if (info[0]->IsNumber() && info[1]->IsNumber()) {
                            info.GetReturnValue().Set(v->Dot(
                                    info[0].As<v8::Number>()->Value(),
                                    info[1].As<v8::Number>()->Value()
                            ));
                        } else {
                            v8::Isolate::GetCurrent()->ThrowException(
                                    v8::Exception::TypeError(v8_str("Arguments mismatch")));
                        }
                        break;
                    }
                }
            }),
            function_property_attributes
    );

    o_prot_template->Set(
            v8_str("perpendicular"),
            v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), [](const v8::FunctionCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector2>(info.Holder());
                switch (info.Length()) {
                    case 0:
                        v8::Isolate::GetCurrent()->ThrowException(
                                v8::Exception::TypeError(v8_str("Arguments mismatch")));
                        break;
                    default: {
                        if (function_template->HasInstance(info[0])) {
                            auto p = new Vector2(v->Perpendicular());
                            p->Wrap();
                            info.GetReturnValue().Set(p->GetHandle());
                        } else {
                            v8::Isolate::GetCurrent()->ThrowException(
                                    v8::Exception::TypeError(v8_str("Arguments mismatch")));
                        }
                        break;
                    }
                }
            }),
            function_property_attributes
    );

    o_prot_template->Set(
            v8_str("lerp"),
            v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), [](const v8::FunctionCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector2>(info.Holder());
                switch (info.Length()) {
                    case 0:
                        v8::Isolate::GetCurrent()->ThrowException(
                                v8::Exception::TypeError(v8_str("Arguments mismatch")));
                        break;
                    case 2: {
                        if (function_template->HasInstance(info[0]) && info[1]->IsNumber()) {
                            auto p = new Vector2(v->Lerp(*ObjectWrap::Unwrap<Vector2>(info[0].As<v8::Object>()),
                                    info[1].As<v8::Number>()->Value()));
                            p->Wrap();
                            info.GetReturnValue().Set(p->GetHandle());
                        } else {
                            v8::Isolate::GetCurrent()->ThrowException(
                                    v8::Exception::TypeError(v8_str("Arguments mismatch")));
                        }
                        break;
                    }
                    default: {
                        if (info[0]->IsNumber() && info[1]->IsNumber() && info[2]->IsNumber()) {
                            auto p = new Vector2(v->Lerp(info[0].As<v8::Number>()->Value(),
                                                           info[1].As<v8::Number>()->Value(),
                                                           info[2].As<v8::Number>()->Value()));
                            p->Wrap();
                            info.GetReturnValue().Set(p->GetHandle());
                        } else {
                            v8::Isolate::GetCurrent()->ThrowException(
                                    v8::Exception::TypeError(v8_str("Arguments mismatch")));
                        }
                        break;
                    }
                }
            }),
            function_property_attributes
    );

    o_prot_template->Set(
            v8_str("toString"),
            v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), [](const v8::FunctionCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector2>(info.Holder());
                auto s = "Vector2(" + std::to_string(v->x) + ", " + std::to_string(v->y) + ")";
                info.GetReturnValue().Set(v8_str(s.c_str()));
            }),
            function_property_attributes
    );

    return function_template;
}

DEFINE_WRAP(Vector2)



// ----------------------------------------------- Vector3 ------------------------------------------------





Vector3::Vector3() : x(0), y(0), z(0) {}


Vector3::Vector3(double scalar) : x(scalar), y(scalar), z(scalar) {}


Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z) {}


Vector3::Vector3(const Vector3 &other) : x((double) other.x), y((double) other.y), z((double) other.z) {}


Vector3::Vector3(const Vector2 &v2, double z) : x((double) v2.x), y((double) v2.y), z(z) {}


double Vector3::Length() const {
    return std::sqrt(x * x + y * y + z * z);
}


double Vector3::LengthSquared() const {
    return x * x + y * y + z * z;
}


double Vector3::Distance(const Vector3 &other) const {
    double x_diff = x - other.x;
    double y_diff = y - other.y;
    double z_diff = z - other.z;
    return std::sqrt(x_diff * x_diff + y_diff * y_diff + z_diff * z_diff);
}


double Vector3::Distance(double x, double y, double z) const {
    double x_diff = this->x - x;
    double y_diff = this->y - y;
    double z_diff = this->z - z;
    return std::sqrt(x_diff * x_diff + y_diff * y_diff + z_diff * z_diff);
}


double Vector3::DistanceSquared(const Vector3 &other) const {
    double x_diff = x - other.x;
    double y_diff = y - other.y;
    double z_diff = z - other.z;
    return x_diff * x_diff + y_diff * y_diff + z_diff * z_diff;
}


double Vector3::Dot(const Vector3 &other) const {
    return x * other.x + y * other.y + z * other.z;
}


double Vector3::AngleCos(const Vector3 &other) const {
    return (double) ((x * other.x + y * other.y + z * other.z) /
                     std::sqrt((x * x + y * y + z * z) * (other.x * other.x + other.y * other.y + other.z * other.z)));
}


double Vector3::Angle(const Vector3 &other) const {
    double cos = (x * other.x + y * other.y + z * other.z) /
                 std::sqrt((x * x + y * y + z * z) * (other.x * other.x + other.y * other.y + other.z * other.z));
    // doublehis is because sometimes cos goes above 1 or below -1 because of lost precision
    cos = cos < 1 ? cos : 1;
    cos = cos > -1 ? cos : -1;
    return std::acos(cos);
}


Vector3 Vector3::Normalized() const {
    double length = std::sqrt(x * x + y * y + z * z);
    return Vector3(x / length, y / length, z / length);
}


Vector3 Vector3::Cross(const Vector3 &other) const {
    return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}


Vector3 Vector3::Min(const Vector3 &other) const {
    return Vector3(x > other.x ? other.x : x, y > other.y ? other.y : y, z > other.z ? other.z : z);
}


Vector3 Vector3::Max(const Vector3 &other) const {
    return Vector3(x > other.x ? x : other.x, y > other.y ? y : other.y, z > other.z ? z : other.z);
}


Vector3 Vector3::Lerp(const Vector3 &other, double t) const {
    return Vector3((double) (x + (other.x - x) * t), (double) (y + (other.y - y) * t),
                     (double) (z + (other.z - z) * t));
}


Vector3 Vector3::operator+(const Vector3 &other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
}


Vector3 Vector3::operator-(const Vector3 &other) const {
    return Vector3(x - other.x, y - other.y, z - other.z);
}


Vector3 Vector3::operator*(const Vector3 &other) const {
    return Vector3(x * other.x, y * other.y, z * other.z);
}


Vector3 Vector3::operator/(const Vector3 &other) const {
    return Vector3(x / other.x, y / other.y, z / other.z);
}


Vector3 Vector3::operator+(double scalar) const {
    return Vector3(x + scalar, y + scalar, z + scalar);
}


Vector3 Vector3::operator-(double scalar) const {
    return Vector3(x - scalar, y - scalar, z - scalar);
}


Vector3 Vector3::operator*(double scalar) const {
    return Vector3(x * scalar, y * scalar, z * scalar);
}


Vector3 Vector3::operator/(double scalar) const {
    return Vector3(x / scalar, y / scalar, z / scalar);
}


bool Vector3::operator==(const Vector3 &other) const {
    return (x == other.x && y == other.y && z == other.z);
}


bool Vector3::operator==(double scalar) const {
    return (x == scalar && y == scalar && z == scalar);
}


Vector3 &Vector3::Normalize() {
    double length = std::sqrt(x * x + y * y + z * z);
    x /= length;
    y /= length;
    z /= length;
    return *this;
}


Vector3 &Vector3::Zero() {
    x = 0;
    y = 0;
    z = 0;
    return *this;
}


Vector3 &Vector3::Floor() {
    x = std::floor(x);
    y = std::floor(y);
    z = std::floor(z);
    return *this;
}


Vector3 &Vector3::Ceil() {
    x = std::ceil(x);
    y = std::ceil(y);
    z = std::ceil(z);
    return *this;
}


Vector3 &Vector3::Round() {
    x = std::round(x);
    y = std::round(y);
    z = std::round(z);
    return *this;
}


Vector3 &Vector3::Set(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
    return *this;
}


Vector3 &Vector3::Set(const Vector3 &other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    return *this;
}


Vector3 &Vector3::Set(const Vector2 &other, double z) {
    this->x = other.x;
    this->y = other.y;
    this->z = z;
    return *this;
}


Vector3 &Vector3::Set(double scalar) {
    x = scalar;
    y = scalar;
    z = scalar;
    return *this;
}


Vector3 &Vector3::operator-() {
    x = -x;
    y = -y;
    z = -z;
    return *this;
}


Vector3 &Vector3::operator=(const Vector3 &other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}


Vector3 &Vector3::operator+=(const Vector3 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}


Vector3 &Vector3::operator-=(const Vector3 &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}


Vector3 &Vector3::operator*=(const Vector3 &other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}


Vector3 &Vector3::operator/=(const Vector3 &other) {
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
}


Vector3 &Vector3::operator=(double scalar) {
    x = scalar;
    y = scalar;
    z = scalar;
    return *this;
}


Vector3 &Vector3::operator+=(double scalar) {
    x += scalar;
    y += scalar;
    z += scalar;
    return *this;
}


Vector3 &Vector3::operator-=(double scalar) {
    x -= scalar;
    y -= scalar;
    z -= scalar;
    return *this;
}


Vector3 &Vector3::operator*=(double scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}


Vector3 &Vector3::operator/=(double scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}


template<>
v8::Local<v8::FunctionTemplate> ObjectWrap::GetObjectConstructorTemplate<Vector3>() {
    static v8::Local<v8::FunctionTemplate> function_template;
    if (!function_template.IsEmpty()) return function_template;

    // Constructor
    function_template = v8::FunctionTemplate::New(
            v8::Isolate::GetCurrent(),
            [](const v8::FunctionCallbackInfo<v8::Value> &info) {
                Vector3 *v = nullptr;
                if (info.Length() == 1 && info[0]->IsObject()) {
                    v = new Vector3(*ObjectWrap::Unwrap<Vector3>(info[0].As<v8::Object>()));
                } else {
                    switch (info.Length()) {
                        case 0:
                            v = new Vector3();
                            break;
                        case 1:
                            v = new Vector3(info[0].As<v8::Number>()->Value());
                            break;
                        case 2:
                            v = new Vector3(info[0].As<v8::Number>()->Value(),
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
                auto v = ObjectWrap::Unwrap<Vector3>(info.Holder());
                info.GetReturnValue().Set(v->x);
            },
            [](v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info) {
                auto v = ObjectWrap::Unwrap<Vector3>(info.Holder());
                v->x = value.As<v8::Number>()->Value();
            }
    );

    o_template->SetAccessor(
            v8_str("y"),
            [](v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector3>(info.Holder());
                info.GetReturnValue().Set(v->y);
            },
            [](v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info) {
                auto v = ObjectWrap::Unwrap<Vector3>(info.Holder());
                v->y = value.As<v8::Number>()->Value();
            }
    );

    o_template->SetAccessor(
            v8_str("z"),
            [](v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector3>(info.Holder());
                info.GetReturnValue().Set(v->z);
            },
            [](v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info) {
                auto v = ObjectWrap::Unwrap<Vector3>(info.Holder());
                v->z = value.As<v8::Number>()->Value();
            }
    );

    o_template->Set(
            v8_str("set"),
            v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), [](const v8::FunctionCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector3>(info.Holder());
                v->Set(info[0].As<v8::Number>()->Value());
                info.GetReturnValue().Set(info.Holder());
            })
    );

    return function_template;
}

DEFINE_WRAP(Vector3)


// ----------------------------------------------- Vector4 ------------------------------------------------





Vector4::Vector4() : x(0.0), y(0.0), z(0.0), w(0.0) {}


Vector4::Vector4(double scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {}


Vector4::Vector4(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}


Vector4::Vector4(const Vector4 &other) : x((double) other.x), y((double) other.y), z((double) other.z),
                                            w((double) other.w) {}


Vector4::Vector4(const Vector3 &v3, double w) : x((double) v3.x), y((double) v3.y), z((double) v3.z), w(w) {}


Vector4::Vector4(const Vector2 &v2, double z, double w) : x((double) v2.x), y((double) v2.y), z(z), w(w) {}


double Vector4::Length() const {
    return std::sqrt(x * x + y * y + z * z + w * w);
}


double Vector4::LengthSquared() const {
    return x * x + y * y + z * z + w * w;
}


double Vector4::Distance(const Vector4 &other) const {
    double x_diff = x - other.x;
    double y_diff = y - other.y;
    double z_diff = z - other.z;
    double w_diff = w - other.w;
    return std::sqrt(x_diff * x_diff + y_diff * y_diff + z_diff * z_diff + w_diff * w_diff);
}


double Vector4::DistanceSquared(const Vector4 &other) const {
    double x_diff = x - other.x;
    double y_diff = y - other.y;
    double z_diff = z - other.z;
    double w_diff = w - other.w;
    return x_diff * x_diff + y_diff * y_diff + z_diff * z_diff + w_diff * w_diff;
}


double Vector4::Dot(const Vector4 &other) const {
    return x * other.x + y * other.y + z * other.z + w * other.w;
}


double Vector4::AngleCos(const Vector4 &other) const {
    return (double) ((x * other.x + y * other.y + z * other.z + w * other.w) /
                     std::sqrt((x * x + y * y + z * z + w * w) *
                               (other.x * other.x + other.y * other.y + other.z * other.z + other.w * other.w)));
}


double Vector4::Angle(const Vector4 &other) const {
    double cos = (x * other.x + y * other.y + z * other.z + w * other.w) /
                 std::sqrt((x * x + y * y + z * z + w * w) *
                           (other.x * other.x + other.y * other.y + other.z * other.z + other.w * other.w));
    // doublehis is because sometimes cos goes above 1 or below -1 because of lost precision
    cos = cos < 1 ? cos : 1;
    cos = cos > -1 ? cos : -1;
    return std::acos(cos);
}


Vector4 Vector4::Normalized() const {
    double length = std::sqrt(x * x + y * y + z * z + w * w);
    return Vector4(x / length, y / length, z / length, w / length);
}


Vector4 Vector4::Min(const Vector4 &other) const {
    return Vector4(x > other.x ? other.x : x, y > other.y ? other.y : y, z > other.z ? other.z : z,
                     w > other.w ? other.w : w);
}


Vector4 Vector4::Max(const Vector4 &other) const {
    return Vector4(x > other.x ? x : other.x, y > other.y ? y : other.y, z > other.z ? z : other.z,
                     w > other.w ? w : other.w);
}


Vector4 Vector4::Lerp(const Vector4 &other, double t) const {
    return Vector4((double) (x + (other.x - x) * t), (double) (y + (other.y - y) * t),
                     (double) (z + (other.z - z) * t),
                     (double) (w + (other.w - w) * t));
}


Vector4 Vector4::operator+(const Vector4 &other) const {
    return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}


Vector4 Vector4::operator-(const Vector4 &other) const {
    return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}


Vector4 Vector4::operator*(const Vector4 &other) const {
    return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
}


Vector4 Vector4::operator/(const Vector4 &other) const {
    return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
}


Vector4 Vector4::operator+(double scalar) const {
    return Vector4(x + scalar, y + scalar, z + scalar, w + scalar);
}


Vector4 Vector4::operator-(double scalar) const {
    return Vector4(x - scalar, y - scalar, z - scalar, w - scalar);
}


Vector4 Vector4::operator*(double scalar) const {
    return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
}


Vector4 Vector4::operator/(double scalar) const {
    return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
}


bool Vector4::operator==(const Vector4 &other) const {
    return (x == other.x && y == other.y && z == other.z && w == other.w);
}


bool Vector4::operator==(double scalar) const {
    return (x == scalar && y == scalar && z == scalar && w == scalar);
}


Vector4 &Vector4::Normalize() {
    double length = std::sqrt(x * x + y * y + z * z + w * w);
    x /= length;
    y /= length;
    z /= length;
    w /= length;
    return *this;
}


Vector4 &Vector4::Zero() {
    x = 0;
    y = 0;
    z = 0;
    w = 0;
    return *this;
}


Vector4 &Vector4::Floor() {
    x = std::floor(x);
    y = std::floor(y);
    z = std::floor(z);
    w = std::floor(w);
    return *this;
}


Vector4 &Vector4::Ceil() {
    x = std::ceil(x);
    y = std::ceil(y);
    z = std::ceil(z);
    w = std::ceil(w);
    return *this;
}


Vector4 &Vector4::Round() {
    x = std::round(x);
    y = std::round(y);
    z = std::round(z);
    w = std::round(w);
    return *this;
}


Vector4 &Vector4::Set(double x, double y, double z, double w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
    return *this;
}


Vector4 &Vector4::Set(const Vector4 &other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->w = other.w;
    return *this;
}


Vector4 &Vector4::Set(const Vector3 &other, double w) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->w = w;
    return *this;
}


Vector4 &Vector4::Set(const Vector2 &other, double z, double w) {
    this->x = other.x;
    this->y = other.y;
    this->z = z;
    this->w = w;
    return *this;
}


Vector4 &Vector4::Set(double scalar) {
    x = scalar;
    y = scalar;
    z = scalar;
    w = scalar;
    return *this;
}


Vector4 &Vector4::operator-() {
    x = -x;
    y = -y;
    z = -z;
    w = -w;
    return *this;
}


Vector4 &Vector4::operator=(const Vector4 &other) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}


Vector4 &Vector4::operator+=(const Vector4 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}


Vector4 &Vector4::operator-=(const Vector4 &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}


Vector4 &Vector4::operator*=(const Vector4 &other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    w *= other.w;
    return *this;
}


Vector4 &Vector4::operator/=(const Vector4 &other) {
    x /= other.x;
    y /= other.y;
    z /= other.z;
    w /= other.w;
    return *this;
}


Vector4 &Vector4::operator=(double scalar) {
    x = scalar;
    y = scalar;
    z = scalar;
    w = scalar;
    return *this;
}


Vector4 &Vector4::operator+=(double scalar) {
    x += scalar;
    y += scalar;
    z += scalar;
    w += scalar;
    return *this;
}


Vector4 &Vector4::operator-=(double scalar) {
    x -= scalar;
    y -= scalar;
    z -= scalar;
    w -= scalar;
    return *this;
}


Vector4 &Vector4::operator*=(double scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
}


Vector4 &Vector4::operator/=(double scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
    return *this;
}

template<>
v8::Local<v8::FunctionTemplate> ObjectWrap::GetObjectConstructorTemplate<Vector4>() {
    static v8::Local<v8::FunctionTemplate> function_template;
    if (!function_template.IsEmpty()) return function_template;

    // Constructor
    function_template = v8::FunctionTemplate::New(
            v8::Isolate::GetCurrent(),
            [](const v8::FunctionCallbackInfo<v8::Value> &info) {
                Vector4 *v = nullptr;
                if (info.Length() == 1 && info[0]->IsObject()) {
                    v = new Vector4(*ObjectWrap::Unwrap<Vector4>(info[0].As<v8::Object>()));
                } else {
                    switch (info.Length()) {
                        case 0:
                            v = new Vector4();
                            break;
                        case 1:
                            v = new Vector4(info[0].As<v8::Number>()->Value());
                            break;
                        case 2:
                            v = new Vector4(info[0].As<v8::Number>()->Value(),
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
                auto v = ObjectWrap::Unwrap<Vector4>(info.Holder());
                info.GetReturnValue().Set(v->x);
            },
            [](v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info) {
                auto v = ObjectWrap::Unwrap<Vector4>(info.Holder());
                v->x = value.As<v8::Number>()->Value();
            }
    );

    o_template->SetAccessor(
            v8_str("y"),
            [](v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector4>(info.Holder());
                info.GetReturnValue().Set(v->y);
            },
            [](v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info) {
                auto v = ObjectWrap::Unwrap<Vector4>(info.Holder());
                v->y = value.As<v8::Number>()->Value();
            }
    );

    o_template->SetAccessor(
            v8_str("z"),
            [](v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector4>(info.Holder());
                info.GetReturnValue().Set(v->z);
            },
            [](v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info) {
                auto v = ObjectWrap::Unwrap<Vector4>(info.Holder());
                v->z = value.As<v8::Number>()->Value();
            }
    );

    o_template->SetAccessor(
            v8_str("w"),
            [](v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector4>(info.Holder());
                info.GetReturnValue().Set(v->w);
            },
            [](v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info) {
                auto v = ObjectWrap::Unwrap<Vector4>(info.Holder());
                v->w = value.As<v8::Number>()->Value();
            }
    );

    o_template->Set(
            v8_str("set"),
            v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), [](const v8::FunctionCallbackInfo<v8::Value> &info) {
                auto v = ObjectWrap::Unwrap<Vector4>(info.Holder());
                v->Set(info[0].As<v8::Number>()->Value());
                info.GetReturnValue().Set(info.Holder());
            })
    );

    return function_template;
}

DEFINE_WRAP(Vector4)


}
