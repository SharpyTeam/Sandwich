//
// Created by Ilya on 29.08.2019.
//

#ifndef SANDWICH_CORE_MODULE_MATH_HPP
#define SANDWICH_CORE_MODULE_MATH_HPP

#include <v8bind/v8bind.hpp>
#include <sw/math/vector.hpp>
#include <sw/math/matrix.hpp>

#include <iostream>

namespace v8b {

template<>
struct DefaultBindings<sw::math::Vector2> {
    static void Initialize(v8::Isolate *isolate) {
        v8b::Class<sw::math::Vector2> v(isolate);

        // Constructor
        v
            .Constructor<std::tuple<>, std::tuple<double>, std::tuple<double, double>, std::tuple<const sw::math::Vector2 &>>()
        ;

        // Vars
        v
            .Var("x", &sw::math::Vector2::x)
            .Var("y", &sw::math::Vector2::y)
        ;

        // Usual functions
        v
            .Function("length", &sw::math::Vector2::Length)
            .Function<
                sw::math::Vector2 &(sw::math::Vector2::*)(double, double),
                sw::math::Vector2 &(sw::math::Vector2::*)(double),
                sw::math::Vector2 &(sw::math::Vector2::*)(const sw::math::Vector2 &)>
                ("set", &sw::math::Vector2::Set, &sw::math::Vector2::Set, &sw::math::Vector2::Set)
            .Function<
                double (sw::math::Vector2::*)(double, double) const,
                double (sw::math::Vector2::*)(const sw::math::Vector2 &) const>
                ("dot", &sw::math::Vector2::Dot, &sw::math::Vector2::Dot)
            .Function<
                double (sw::math::Vector2::*)(double, double) const,
                double (sw::math::Vector2::*)(const sw::math::Vector2 &) const>
                ("distance", &sw::math::Vector2::Distance, &sw::math::Vector2::Distance)
            .Function<
                double (sw::math::Vector2::*)(double, double) const,
                double (sw::math::Vector2::*)(const sw::math::Vector2 &) const>
                ("determinant", &sw::math::Vector2::Determinant, &sw::math::Vector2::Determinant)
            .Function<
                double (sw::math::Vector2::*)(double, double) const,
                double (sw::math::Vector2::*)(const sw::math::Vector2 &) const>
                ("angle", &sw::math::Vector2::Angle, &sw::math::Vector2::Angle)
            .Function("normalized", &sw::math::Vector2::Normalized)
            .Function("normalize", &sw::math::Vector2::Normalize)
            .Function("floor", &sw::math::Vector2::Floor)
            .Function("ceil", &sw::math::Vector2::Ceil)
            .Function("round", &sw::math::Vector2::Round)
            .Function("zero", &sw::math::Vector2::Zero)
            .Function("lengthSquared", &sw::math::Vector2::LengthSquared)
            .Function<
                double (sw::math::Vector2::*)(double, double) const,
                double (sw::math::Vector2::*)(const sw::math::Vector2 &) const>
                ("distanceSquared", &sw::math::Vector2::DistanceSquared, &sw::math::Vector2::DistanceSquared)
            .Function("perpendicular", &sw::math::Vector2::Perpendicular)
            .Function<
                sw::math::Vector2 (sw::math::Vector2::*)(double, double) const,
                sw::math::Vector2 (sw::math::Vector2::*)(const sw::math::Vector2 &) const>
                ("min", &sw::math::Vector2::Min, &sw::math::Vector2::Min)
            .Function<
                sw::math::Vector2 (sw::math::Vector2::*)(double, double, double) const,
                sw::math::Vector2 (sw::math::Vector2::*)(const sw::math::Vector2 &, double) const>
                ("lerp", &sw::math::Vector2::Lerp, &sw::math::Vector2::Lerp)
            .Function<
                sw::math::Vector2 (sw::math::Vector2::*)(double, double) const,
                sw::math::Vector2 (sw::math::Vector2::*)(const sw::math::Vector2 &) const>
                ("max", &sw::math::Vector2::Max, &sw::math::Vector2::Max)
            .Function("toString", [](sw::math::Vector2 &v) -> std::string {
                return "(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ")";
            })
        ;

        // Operators (replaced by functions in JS API)
        v
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
            .Function<
                bool (sw::math::Vector2::*)(double) const,
                bool (sw::math::Vector2::*)(const sw::math::Vector2 &) const>
                ("isEqual", &sw::math::Vector2::operator==, &sw::math::Vector2::operator==)
        ;

        // Static functions (currently only for +-*/ operators replacement)
        v
            .StaticFunction("add", [](const sw::math::Vector2 &v1, const sw::math::Vector2 &v2) -> sw::math::Vector2 {
                std::cout << "Static method of Vector2 object called: add" << std::endl;
                return v1 + v2;
             })
            .StaticFunction("sub", [](const sw::math::Vector2 &v1, const sw::math::Vector2 &v2) -> sw::math::Vector2 {
                std::cout << "Static method of Vector2 object called: sub" << std::endl;
                return v1 - v2;
             })
            .StaticFunction("mul", [](const sw::math::Vector2 &v1, const sw::math::Vector2 &v2) -> sw::math::Vector2 {
                std::cout << "Static method of Vector2 object called: mul" << std::endl;
                return v1 * v2;
             })
            .StaticFunction("div", [](const sw::math::Vector2 &v1, const sw::math::Vector2 &v2) -> sw::math::Vector2 {
                std::cout << "Static method of Vector2 object called: div" << std::endl;
                return v1 / v2;
             })
        ;

        // Wrappers
        v
            .AutoWrap()
            .PointerAutoWrap()
        ;




        v8b::Class<sw::math::Matrix4> m(isolate);

        // Constructor
        m.Constructor<std::tuple<>>();

        m.Function("setOrtho2D", &sw::math::Matrix4::SetOrtho2D);

        // Wrappers
        m.AutoWrap().PointerAutoWrap();
    }
};

};

#endif //SANDWICH_CORE_MODULE_MATH_HPP
