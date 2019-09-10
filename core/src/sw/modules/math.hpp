//
// Created by Ilya on 29.08.2019.
//

#ifndef SANDWICH_CORE_MODULE_MATH_HPP
#define SANDWICH_CORE_MODULE_MATH_HPP

#include <v8bind/v8bind.hpp>
#include <sw/math/vector.hpp>

namespace v8b {

template<>
struct DefaultBindings<sw::Vector2> {
    static void Initialize(v8::Isolate *isolate) {
        v8b::Class<sw::Vector2> v(isolate);

        // Constructor
        v
            .Constructor<std::tuple<>, std::tuple<double>, std::tuple<double, double>, std::tuple<const sw::Vector2 &>>()
        ;

        // Vars
        v
            .Var("x", &sw::Vector2::x)
            .Var("y", &sw::Vector2::y)
        ;

        // Usual functions
        v
            .Function("length", &sw::Vector2::Length)
            .Function<
                sw::Vector2 &(sw::Vector2::*)(double, double),
                sw::Vector2 &(sw::Vector2::*)(double),
                sw::Vector2 &(sw::Vector2::*)(const sw::Vector2 &)>
                ("set", &sw::Vector2::Set, &sw::Vector2::Set, &sw::Vector2::Set)
            .Function<
                double (sw::Vector2::*)(double, double) const,
                double (sw::Vector2::*)(const sw::Vector2 &) const>
                ("dot", &sw::Vector2::Dot, &sw::Vector2::Dot)
            .Function<
                double (sw::Vector2::*)(double, double) const,
                double (sw::Vector2::*)(const sw::Vector2 &) const>
                ("distance", &sw::Vector2::Distance, &sw::Vector2::Distance)
            .Function<
                double (sw::Vector2::*)(double, double) const,
                double (sw::Vector2::*)(const sw::Vector2 &) const>
                ("determinant", &sw::Vector2::Determinant, &sw::Vector2::Determinant)
            .Function<
                double (sw::Vector2::*)(double, double) const,
                double (sw::Vector2::*)(const sw::Vector2 &) const>
                ("angle", &sw::Vector2::Angle, &sw::Vector2::Angle)
            .Function("normalized", &sw::Vector2::Normalized)
            .Function("normalize", &sw::Vector2::Normalize)
            .Function("floor", &sw::Vector2::Floor)
            .Function("ceil", &sw::Vector2::Ceil)
            .Function("round", &sw::Vector2::Round)
            .Function("zero", &sw::Vector2::Zero)
            .Function("lengthSquared", &sw::Vector2::LengthSquared)
            .Function<
                double (sw::Vector2::*)(double, double) const,
                double (sw::Vector2::*)(const sw::Vector2 &) const>
                ("distanceSquared", &sw::Vector2::DistanceSquared, &sw::Vector2::DistanceSquared)
            .Function("perpendicular", &sw::Vector2::Perpendicular)
            .Function<
                sw::Vector2 (sw::Vector2::*)(double, double) const,
                sw::Vector2 (sw::Vector2::*)(const sw::Vector2 &) const>
                ("min", &sw::Vector2::Min, &sw::Vector2::Min)
            .Function<
                sw::Vector2 (sw::Vector2::*)(double, double, double) const,
                sw::Vector2 (sw::Vector2::*)(const sw::Vector2 &, double) const>
                ("lerp", &sw::Vector2::Lerp, &sw::Vector2::Lerp)
            .Function<
                sw::Vector2 (sw::Vector2::*)(double, double) const,
                sw::Vector2 (sw::Vector2::*)(const sw::Vector2 &) const>
                ("max", &sw::Vector2::Max, &sw::Vector2::Max)
            .Function("toString", [](sw::Vector2 &v) -> std::string {
                return "(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ")";
            })
        ;

        // Operators (replaced by functions in JS API)
        v
            .Function<
                sw::Vector2 &(sw::Vector2::*)(double),
                sw::Vector2 &(sw::Vector2::*)(const sw::Vector2 &)>
                ("add", &sw::Vector2::operator+=, &sw::Vector2::operator+=)
            .Function<
                sw::Vector2 &(sw::Vector2::*)(double),
                sw::Vector2 &(sw::Vector2::*)(const sw::Vector2 &)>
                ("sub", &sw::Vector2::operator-=, &sw::Vector2::operator-=)
            .Function<
                sw::Vector2 &(sw::Vector2::*)(double),
                sw::Vector2 &(sw::Vector2::*)(const sw::Vector2 &)>
                ("mul", &sw::Vector2::operator*=, &sw::Vector2::operator*=)
            .Function<
                sw::Vector2 &(sw::Vector2::*)(double),
                sw::Vector2 &(sw::Vector2::*)(const sw::Vector2 &)>
                ("div", &sw::Vector2::operator/=, &sw::Vector2::operator/=)
            .Function<
                bool (sw::Vector2::*)(double) const,
                bool (sw::Vector2::*)(const sw::Vector2 &) const>
                ("isEqual", &sw::Vector2::operator==, &sw::Vector2::operator==)
        ;

        // Static functions (currently only for +-*/ operators replacement)
        v
            .StaticFunction("add", [](const sw::Vector2 &v1, const sw::Vector2 &v2) -> sw::Vector2 {
                return v1 + v2;
             })
            .StaticFunction("sub", [](const sw::Vector2 &v1, const sw::Vector2 &v2) -> sw::Vector2 {
                return v1 - v2;
             })
            .StaticFunction("mul", [](const sw::Vector2 &v1, const sw::Vector2 &v2) -> sw::Vector2 {
                return v1 * v2;
             })
            .StaticFunction("div", [](const sw::Vector2 &v1, const sw::Vector2 &v2) -> sw::Vector2 {
                return v1 / v2;
             })
        ;

        // Wrappers
        v
            .AutoWrap()
            .PointerAutoWrap()
        ;
    }
};

};

#endif //SANDWICH_CORE_MODULE_MATH_HPP
