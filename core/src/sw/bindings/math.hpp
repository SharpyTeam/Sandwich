//
// Created by Ilya on 29.08.2019.
//

#ifndef SANDWICH_BINDINGS_MATH_HPP
#define SANDWICH_BINDINGS_MATH_HPP

#include <v8bind/v8bind.hpp>
#include <sw/math/vector.hpp>
#include <sw/math/matrix.hpp>

#include <iostream>

namespace v8b {

template<>
struct DefaultBindings<sw::math::Vector2> {
    static void Initialize(v8::Isolate *isolate) {
        v8b::Class<sw::math::Vector2> v2(isolate);

        // Vars
        v2
            .Var("x", &sw::math::Vector2::x)
            .Var("y", &sw::math::Vector2::y)
        ;

        // Constructors
        v2
            .Constructor<
                std::tuple<>,
                std::tuple<double>,
                std::tuple<double, double>,
                std::tuple<const sw::math::Vector2 &>
            >()
        ;

        // Functions
        v2
            .Function<
                double (sw::math::Vector2::*)(double, double) const,
                double (sw::math::Vector2::*)(const sw::math::Vector2 &) const>
                ("angle", &sw::math::Vector2::Angle, &sw::math::Vector2::Angle)
            .Function<
                double (sw::math::Vector2::*)(double, double) const,
                double (sw::math::Vector2::*)(const sw::math::Vector2 &) const>
                ("determinant", &sw::math::Vector2::Determinant, &sw::math::Vector2::Determinant)
            .Function<
                double (sw::math::Vector2::*)(double, double) const,
                double (sw::math::Vector2::*)(const sw::math::Vector2 &) const>
                ("distance", &sw::math::Vector2::Distance, &sw::math::Vector2::Distance)
            .Function<
                double (sw::math::Vector2::*)(double, double) const,
                double (sw::math::Vector2::*)(const sw::math::Vector2 &) const>
                ("distanceSquared", &sw::math::Vector2::DistanceSquared, &sw::math::Vector2::DistanceSquared)
            .Function<
                double (sw::math::Vector2::*)(double, double) const,
                double (sw::math::Vector2::*)(const sw::math::Vector2 &) const>
                ("dot", &sw::math::Vector2::Dot, &sw::math::Vector2::Dot)
            .Function("length", &sw::math::Vector2::Length)
            .Function("lengthSquared", &sw::math::Vector2::LengthSquared)

            .Function<
                sw::math::Vector2 (sw::math::Vector2::*)(double, double, double) const,
                sw::math::Vector2 (sw::math::Vector2::*)(const sw::math::Vector2 &, double) const>
                ("lerp", &sw::math::Vector2::Lerp, &sw::math::Vector2::Lerp)
            .Function<
                sw::math::Vector2 (sw::math::Vector2::*)(double, double) const,
                sw::math::Vector2 (sw::math::Vector2::*)(const sw::math::Vector2 &) const>
                ("max", &sw::math::Vector2::Max, &sw::math::Vector2::Max)
            .Function<
                sw::math::Vector2 (sw::math::Vector2::*)(double, double) const,
                sw::math::Vector2 (sw::math::Vector2::*)(const sw::math::Vector2 &) const>
                ("min", &sw::math::Vector2::Min, &sw::math::Vector2::Min)
            .Function("normalized", &sw::math::Vector2::Normalized)
            .Function("perpendicular", &sw::math::Vector2::Perpendicular)

            .Function<
                sw::math::Vector2 (sw::math::Vector2::*)() const>
                ("negated", &sw::math::Vector2::operator-)

            .Function("ceil", &sw::math::Vector2::Ceil)
            .Function("floor", &sw::math::Vector2::Floor)
            .Function("normalize", &sw::math::Vector2::Normalize)
            .Function("round", &sw::math::Vector2::Round)
            .Function<
                sw::math::Vector2 &(sw::math::Vector2::*)(double),
                sw::math::Vector2 &(sw::math::Vector2::*)(double, double),
                sw::math::Vector2 &(sw::math::Vector2::*)(const sw::math::Vector2 &)>
                ("set", &sw::math::Vector2::Set, &sw::math::Vector2::Set, &sw::math::Vector2::Set)
            .Function("zero", &sw::math::Vector2::Zero)

            .Function<
                sw::math::Vector2 &(sw::math::Vector2::*)(double),
                sw::math::Vector2 &(sw::math::Vector2::*)(const sw::math::Vector2 &)>
                ("add", &sw::math::Vector2::operator+=, &sw::math::Vector2::operator+=)
            .Function<
                sw::math::Vector2 &(sw::math::Vector2::*)(double),
                sw::math::Vector2 &(sw::math::Vector2::*)(const sw::math::Vector2 &)>
                ("sub", &sw::math::Vector2::operator-=, &sw::math::Vector2::operator-=)
            .Function<
                sw::math::Vector2 &(sw::math::Vector2::*)(double),
                sw::math::Vector2 &(sw::math::Vector2::*)(const sw::math::Vector2 &)>
                ("mul", &sw::math::Vector2::operator*=, &sw::math::Vector2::operator*=)
            .Function<
                sw::math::Vector2 &(sw::math::Vector2::*)(double),
                sw::math::Vector2 &(sw::math::Vector2::*)(const sw::math::Vector2 &)>
                ("div", &sw::math::Vector2::operator/=, &sw::math::Vector2::operator/=)

            .Function("toString", [](sw::math::Vector2 &v) -> std::string {
                return "(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ")";
            })
        ;

        // Static functions
        v2
            .StaticFunction("add", [](const sw::math::Vector2 &v1, const sw::math::Vector2 &v2) {
                return v1 + v2;
             })
            .StaticFunction("sub", [](const sw::math::Vector2 &v1, const sw::math::Vector2 &v2) {
                return v1 - v2;
             })
            .StaticFunction("mul", [](const sw::math::Vector2 &v1, const sw::math::Vector2 &v2) {
                return v1 * v2;
             })
            .StaticFunction("div", [](const sw::math::Vector2 &v1, const sw::math::Vector2 &v2) {
                return v1 / v2;
             })
        ;

        // Wrappers
        v2
            .AutoWrap()
            .PointerAutoWrap()
        ;
    }
};

template<>
struct DefaultBindings<sw::math::Vector3> {
    static void Initialize(v8::Isolate *isolate) {
        v8b::Class<sw::math::Vector3> v3(isolate);

        // Vars
        v3
            .Var("x", &sw::math::Vector3::x)
            .Var("y", &sw::math::Vector3::y)
            .Var("z", &sw::math::Vector3::z)
        ;

        // Constructors
        v3
            .Constructor<
                std::tuple<>,
                std::tuple<double>,
                std::tuple<double, double, double>,
                std::tuple<const sw::math::Vector3 &>,
                std::tuple<const sw::math::Vector2 &, double>
            >()
        ;

        // Functions
        v3
            .Function<
                double (sw::math::Vector3::*)(double, double, double) const,
                double (sw::math::Vector3::*)(const sw::math::Vector3 &) const>
                ("angle", &sw::math::Vector3::Angle, &sw::math::Vector3::Angle)
            .Function<
                double (sw::math::Vector3::*)(double, double, double) const,
                double (sw::math::Vector3::*)(const sw::math::Vector3 &) const>
                ("angleCos", &sw::math::Vector3::AngleCos, &sw::math::Vector3::AngleCos)
            .Function<
                double (sw::math::Vector3::*)(double, double, double) const,
                double (sw::math::Vector3::*)(const sw::math::Vector3 &) const>
                ("distance", &sw::math::Vector3::Distance, &sw::math::Vector3::Distance)
            .Function<
                double (sw::math::Vector3::*)(double, double, double) const,
                double (sw::math::Vector3::*)(const sw::math::Vector3 &) const>
                ("distanceSquared", &sw::math::Vector3::DistanceSquared, &sw::math::Vector3::DistanceSquared)
            .Function<
                double (sw::math::Vector3::*)(double, double, double) const,
                double (sw::math::Vector3::*)(const sw::math::Vector3 &) const>
                ("dot", &sw::math::Vector3::Dot, &sw::math::Vector3::Dot)
            .Function("length", &sw::math::Vector3::Length)
            .Function("lengthSquared", &sw::math::Vector3::LengthSquared)

            .Function<
                sw::math::Vector3 (sw::math::Vector3::*)(double, double, double) const,
                sw::math::Vector3 (sw::math::Vector3::*)(const sw::math::Vector3 &) const>
                ("cross", &sw::math::Vector3::Cross, &sw::math::Vector3::Cross)
            .Function<
                sw::math::Vector3 (sw::math::Vector3::*)(double, double, double, double) const,
                sw::math::Vector3 (sw::math::Vector3::*)(const sw::math::Vector3 &, double) const>
                ("lerp", &sw::math::Vector3::Lerp, &sw::math::Vector3::Lerp)
            .Function<
                sw::math::Vector3 (sw::math::Vector3::*)(double, double, double) const,
                sw::math::Vector3 (sw::math::Vector3::*)(const sw::math::Vector3 &) const>
                ("max", &sw::math::Vector3::Max, &sw::math::Vector3::Max)
            .Function<
                sw::math::Vector3 (sw::math::Vector3::*)(double, double, double) const,
                sw::math::Vector3 (sw::math::Vector3::*)(const sw::math::Vector3 &) const>
                ("min", &sw::math::Vector3::Min, &sw::math::Vector3::Min)
            .Function("normalized", &sw::math::Vector3::Normalized)

            .Function<
                sw::math::Vector3 (sw::math::Vector3::*)() const>
                ("negated", &sw::math::Vector3::operator-)

            .Function("ceil", &sw::math::Vector3::Ceil)
            .Function("floor", &sw::math::Vector3::Floor)
            .Function("normalize", &sw::math::Vector3::Normalize)
            .Function("round", &sw::math::Vector3::Round)
            .Function<
                sw::math::Vector3 &(sw::math::Vector3::*)(double),
                sw::math::Vector3 &(sw::math::Vector3::*)(double, double, double),
                sw::math::Vector3 &(sw::math::Vector3::*)(const sw::math::Vector3 &),
                sw::math::Vector3 &(sw::math::Vector3::*)(const sw::math::Vector2 &, double)>
                ("set", &sw::math::Vector3::Set, &sw::math::Vector3::Set, &sw::math::Vector3::Set, &sw::math::Vector3::Set)
            .Function("zero", &sw::math::Vector3::Zero)

            .Function<
                sw::math::Vector3 &(sw::math::Vector3::*)(double),
                sw::math::Vector3 &(sw::math::Vector3::*)(const sw::math::Vector3 &)>
                ("add", &sw::math::Vector3::operator+=, &sw::math::Vector3::operator+=)
            .Function<
                sw::math::Vector3 &(sw::math::Vector3::*)(double),
                sw::math::Vector3 &(sw::math::Vector3::*)(const sw::math::Vector3 &)>
                ("sub", &sw::math::Vector3::operator-=, &sw::math::Vector3::operator-=)
            .Function<
                sw::math::Vector3 &(sw::math::Vector3::*)(double),
                sw::math::Vector3 &(sw::math::Vector3::*)(const sw::math::Vector3 &)>
                ("mul", &sw::math::Vector3::operator*=, &sw::math::Vector3::operator*=)
            .Function<
                sw::math::Vector3 &(sw::math::Vector3::*)(double),
                sw::math::Vector3 &(sw::math::Vector3::*)(const sw::math::Vector3 &)>
                ("div", &sw::math::Vector3::operator/=, &sw::math::Vector3::operator/=)

            .Function("toString", [](sw::math::Vector3 &v) -> std::string {
                return "(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ")";
            })
        ;

        // Static functions
        v3
            .StaticFunction("add", [](const sw::math::Vector3 &v1, const sw::math::Vector3 &v2) {
                return v1 + v2;
            })
            .StaticFunction("sub", [](const sw::math::Vector3 &v1, const sw::math::Vector3 &v2) {
                return v1 - v2;
            })
            .StaticFunction("mul", [](const sw::math::Vector3 &v1, const sw::math::Vector3 &v2) {
                return v1 * v2;
            })
            .StaticFunction("div", [](const sw::math::Vector3 &v1, const sw::math::Vector3 &v2) {
                return v1 / v2;
            })
        ;

        // Wrappers
        v3
            .AutoWrap()
            .PointerAutoWrap()
        ;
    }
};

template<>
struct DefaultBindings<sw::math::Vector4> {
    static void Initialize(v8::Isolate *isolate) {
        v8b::Class<sw::math::Vector4> v4(isolate);

        // Vars
        v4
            .Var("x", &sw::math::Vector4::x)
            .Var("y", &sw::math::Vector4::y)
            .Var("z", &sw::math::Vector4::z)
            .Var("z", &sw::math::Vector4::w)
        ;

        // Constructors
        v4
            .Constructor<
                std::tuple<>,
                std::tuple<double>,
                std::tuple<double, double, double, double>,
                std::tuple<const sw::math::Vector4 &>,
                std::tuple<const sw::math::Vector3 &, double>,
                std::tuple<const sw::math::Vector2 &, double, double>
            >()
        ;

        // Functions
        v4
            .Function<
                double (sw::math::Vector4::*)(double, double, double, double) const,
                double (sw::math::Vector4::*)(const sw::math::Vector4 &) const>
                ("angle", &sw::math::Vector4::Angle, &sw::math::Vector4::Angle)
            .Function<
                double (sw::math::Vector4::*)(double, double, double, double) const,
                double (sw::math::Vector4::*)(const sw::math::Vector4 &) const>
                ("angleCos", &sw::math::Vector4::AngleCos, &sw::math::Vector4::AngleCos)
            .Function<
                double (sw::math::Vector4::*)(double, double, double, double) const,
                double (sw::math::Vector4::*)(const sw::math::Vector4 &) const>
                ("distance", &sw::math::Vector4::Distance, &sw::math::Vector4::Distance)
            .Function<
                double (sw::math::Vector4::*)(double, double, double, double) const,
                double (sw::math::Vector4::*)(const sw::math::Vector4 &) const>
                ("distanceSquared", &sw::math::Vector4::DistanceSquared, &sw::math::Vector4::DistanceSquared)
            .Function<
                double (sw::math::Vector4::*)(double, double, double, double) const,
                double (sw::math::Vector4::*)(const sw::math::Vector4 &) const>
                ("dot", &sw::math::Vector4::Dot, &sw::math::Vector4::Dot)
            .Function("length", &sw::math::Vector4::Length)
            .Function("lengthSquared", &sw::math::Vector4::LengthSquared)

            .Function<
                sw::math::Vector4 (sw::math::Vector4::*)(double, double, double, double, double) const,
                sw::math::Vector4 (sw::math::Vector4::*)(const sw::math::Vector4 &, double) const>
                ("lerp", &sw::math::Vector4::Lerp, &sw::math::Vector4::Lerp)
            .Function<
                sw::math::Vector4 (sw::math::Vector4::*)(double, double, double, double) const,
                sw::math::Vector4 (sw::math::Vector4::*)(const sw::math::Vector4 &) const>
                ("max", &sw::math::Vector4::Max, &sw::math::Vector4::Max)
            .Function<
                sw::math::Vector4 (sw::math::Vector4::*)(double, double, double, double) const,
                sw::math::Vector4 (sw::math::Vector4::*)(const sw::math::Vector4 &) const>
                ("min", &sw::math::Vector4::Min, &sw::math::Vector4::Min)
            .Function("normalized", &sw::math::Vector4::Normalized)

            .Function<
                sw::math::Vector4 (sw::math::Vector4::*)() const>
                ("negated", &sw::math::Vector4::operator-)

            .Function("ceil", &sw::math::Vector4::Ceil)
            .Function("floor", &sw::math::Vector4::Floor)
            .Function("normalize", &sw::math::Vector4::Normalize)
            .Function("round", &sw::math::Vector4::Round)
            .Function<
                sw::math::Vector4 &(sw::math::Vector4::*)(double),
                sw::math::Vector4 &(sw::math::Vector4::*)(double, double, double, double),
                sw::math::Vector4 &(sw::math::Vector4::*)(const sw::math::Vector4 &),
                sw::math::Vector4 &(sw::math::Vector4::*)(const sw::math::Vector3 &, double),
                sw::math::Vector4 &(sw::math::Vector4::*)(const sw::math::Vector2 &, double, double)>
                ("set", &sw::math::Vector4::Set, &sw::math::Vector4::Set,
                    &sw::math::Vector4::Set, &sw::math::Vector4::Set, &sw::math::Vector4::Set)
            .Function("zero", &sw::math::Vector4::Zero)

            .Function<
                sw::math::Vector4 &(sw::math::Vector4::*)(double),
                sw::math::Vector4 &(sw::math::Vector4::*)(const sw::math::Vector4 &)>
                ("add", &sw::math::Vector4::operator+=, &sw::math::Vector4::operator+=)
            .Function<
                sw::math::Vector4 &(sw::math::Vector4::*)(double),
                sw::math::Vector4 &(sw::math::Vector4::*)(const sw::math::Vector4 &)>
                ("sub", &sw::math::Vector4::operator-=, &sw::math::Vector4::operator-=)
            .Function<
                sw::math::Vector4 &(sw::math::Vector4::*)(double),
                sw::math::Vector4 &(sw::math::Vector4::*)(const sw::math::Vector4 &)>
                ("mul", &sw::math::Vector4::operator*=, &sw::math::Vector4::operator*=)
            .Function<
                sw::math::Vector4 &(sw::math::Vector4::*)(double),
                sw::math::Vector4 &(sw::math::Vector4::*)(const sw::math::Vector4 &)>
                ("div", &sw::math::Vector4::operator/=, &sw::math::Vector4::operator/=)

            .Function("toString", [](sw::math::Vector4 &v) -> std::string {
                return "(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", "
                    + std::to_string(v.z) + ", " + std::to_string(v.w) + ")";
            })
        ;

        // Static functions
        v4
            .StaticFunction("add", [](const sw::math::Vector4 &v1, const sw::math::Vector4 &v2) {
                return v1 + v2;
            })
            .StaticFunction("sub", [](const sw::math::Vector4 &v1, const sw::math::Vector4 &v2) {
                return v1 - v2;
            })
            .StaticFunction("mul", [](const sw::math::Vector4 &v1, const sw::math::Vector4 &v2) {
                return v1 * v2;
            })
            .StaticFunction("div", [](const sw::math::Vector4 &v1, const sw::math::Vector4 &v2) {
                return v1 / v2;
            })
        ;

        // Wrappers
        v4
            .AutoWrap()
            .PointerAutoWrap()
        ;
    }
};

template<>
struct DefaultBindings<sw::math::AxisAngle> {
    static void Initialize(v8::Isolate *isolate) {
        v8b::Class<sw::math::AxisAngle> aa(isolate);

        // Vars
        aa
            .Var("axis", &sw::math::AxisAngle::axis)
            .Var("angle", &sw::math::AxisAngle::angle)
        ;

        // Constructors
        aa
            .Constructor<
                std::tuple<>,
                std::tuple<double, double, double, double>,
                std::tuple<double, const sw::math::Vector3 &>,
                std::tuple<const sw::math::AxisAngle &>
            >()
        ;

        // Functions
        aa
            .Function("rotate", &sw::math::AxisAngle::Rotate)
            .Function<
                sw::math::AxisAngle &(sw::math::AxisAngle::*)(double, double, double, double),
                sw::math::AxisAngle &(sw::math::AxisAngle::*)(double, const sw::math::Vector3 &),
                sw::math::AxisAngle &(sw::math::AxisAngle::*)(const sw::math::AxisAngle &)>
                ("set", &sw::math::AxisAngle::Set, &sw::math::AxisAngle::Set, &sw::math::AxisAngle::Set)
        ;

        // Wrappers
        aa
            .AutoWrap()
            .PointerAutoWrap()
        ;
    }
};

template<>
struct DefaultBindings<sw::math::Matrix4> {
    static void Initialize(v8::Isolate *isolate) {
        v8b::Class<sw::math::Matrix4> m4(isolate);

        // Constructors
        m4
            .Constructor<
                std::tuple<>,
                std::tuple<
                    double, double, double, double,
                    double, double, double, double,
                    double, double, double, double,
                    double, double, double, double>,
                std::tuple<const sw::math::Matrix4 &>
            >()
        ;

        // Functions
        m4
            .Function("identity", &sw::math::Matrix4::Identity)
            .Function("invert", &sw::math::Matrix4::Invert)
            .Function<
                sw::math::Matrix4 &(sw::math::Matrix4::*)(double, double, double, double),
                sw::math::Matrix4 &(sw::math::Matrix4::*)(double, const sw::math::Vector3 &),
                sw::math::Matrix4 &(sw::math::Matrix4::*)(const sw::math::AxisAngle &)>
                ("rotate", &sw::math::Matrix4::Rotate, &sw::math::Matrix4::Rotate, &sw::math::Matrix4::Rotate)
            .Function<
                sw::math::Matrix4 &(sw::math::Matrix4::*)(double, double, double),
                sw::math::Matrix4 &(sw::math::Matrix4::*)(const sw::math::Vector3 &)>
                ("scale", &sw::math::Matrix4::Scale, &sw::math::Matrix4::Scale)
            .Function<
                sw::math::Matrix4 &(sw::math::Matrix4::*)(double, double, double),
                sw::math::Matrix4 &(sw::math::Matrix4::*)(const sw::math::Vector3 &)>
                ("translate", &sw::math::Matrix4::Translate, &sw::math::Matrix4::Translate)
            .Function("transpose", &sw::math::Matrix4::Transpose)

            .Function<
                sw::math::Matrix4 &(sw::math::Matrix4::*)(
                    double, double, double, double,
                    double, double, double, double,
                    double, double, double, double,
                    double, double, double, double),
                sw::math::Matrix4 &(sw::math::Matrix4::*)(const sw::math::Matrix4 &)>
                ("set", &sw::math::Matrix4::Set, &sw::math::Matrix4::Set)
            .Function("setOrtho", &sw::math::Matrix4::SetOrtho)
            .Function("setOrtho", [](sw::math::Matrix4 &m, double left, double right, double bottom, double top,
                                     double z_near, double z_far) {
                return m.SetOrtho(left, right, bottom, top, z_near, z_far);
            })
            .Function("setOrtho2D", &sw::math::Matrix4::SetOrtho2D)
            .Function("setPerspective", &sw::math::Matrix4::SetPerspective)
            .Function("setPerspective", [](sw::math::Matrix4 &m, double fov_y, double aspect, double z_near, double z_far) {
                return m.SetPerspective(fov_y, aspect, z_near, z_far);
            })

            .Function("getRotation", &sw::math::Matrix4::GetRotation)
            .Function("getScale", &sw::math::Matrix4::GetScale)
            .Function("getTranslation", &sw::math::Matrix4::GetTranslation)

            .Function("determinant", &sw::math::Matrix4::Determinant)

            .Function("mul", &sw::math::Matrix4::operator*=)
            .Function("transform", [](sw::math::Matrix4 &m, sw::math::Vector4 &v) {
                v = m * v;
                return v;
            })
        ;

        // Wrappers
        m4
            .AutoWrap()
            .PointerAutoWrap()
        ;
    }
};

}

#endif //SANDWICH_BINDINGS_MATH_HPP
