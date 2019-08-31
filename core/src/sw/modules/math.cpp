//
// Created by Ilya on 29.08.2019.
//

#include <v8pp/class.hpp>
#include <sw/vector.hpp>
#include <sw/matrix.hpp>
#include <iostream>
#include "math.hpp"

namespace sw {


void MathModule::Init(v8::Isolate *isolate) {
    v8pp::class_<Vector2> vector2(isolate);
    v8pp::class_<Vector3> vector3(isolate);
    v8pp::class_<Vector4> vector4(isolate);

    v8pp::class_<Matrix4> matrix4(isolate);


    vector2
            .set("Length", &Vector2::Length)
            .set("Dot", [isolate](v8::FunctionCallbackInfo<v8::Value> const &args) {
                auto *self = v8pp::class_<Vector2>::unwrap_object(args.GetIsolate(), args.This());
                switch (args.Length()) {
                    case 1: {
                        auto *v = v8pp::from_v8<Vector2 *>(args.GetIsolate(), args[0]);
                        if (v) {
                            args.GetReturnValue().Set(self->Dot(*v));
                        } else {
                            args.GetReturnValue().Set(v8::Null(isolate));
                            std::cerr << "Argument 0 in 'Vector2.Dot' cannot be null" << std::endl;
                        }
                        break;
                    }
                    case 2: {
                        double x = v8pp::from_v8<double>(isolate, args[0]);
                        double y = v8pp::from_v8<double>(isolate, args[1]);
                        args.GetReturnValue().Set(self->Dot(x, y));
                        break;
                    }
                    default: {
                        args.GetReturnValue().Set(v8::Null(isolate));
                        std::cerr << "Arguments mismatch in 'Vector2.Dot'" << std::endl;
                        break;
                    }
                }
            })
//            .set("Distance", &Vector2::Distance)
//            .set("Determinant", &Vector2::Determinant)
//            .set("Angle", &Vector2::Angle)
            .set("Normalized", &Vector2::Normalized)
            .set("Normalize", &Vector2::Normalize)
            .set("LengthSquared", &Vector2::LengthSquared)
//            .set("DistanceSquared", &Vector2::LengthSquared)
            .set("Perpendicular", &Vector2::Perpendicular)
            .set("Floor", &Vector2::Floor)
            .set("Ceil", &Vector2::Ceil)
            .set("Zero", &Vector2::Zero);
//            .set("Min", &Vector2::Min)
//            .set("Max", &Vector2::Max)
//            .set("Lerp", &Vector2::Lerp)
//            .set("Add", &Vector2::operator+)
//            .set("Subtract", &Vector2::operator-)
//            .set("Dot", &Vector2::operator*)
//            .set("Add", &Vector2::operator+);


    vector2.auto_wrap_objects();
    vector3.auto_wrap_objects();
    vector4.auto_wrap_objects();

    matrix4.auto_wrap_objects();
}

}

