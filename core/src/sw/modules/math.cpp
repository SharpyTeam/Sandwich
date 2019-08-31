//
// Created by Ilya on 29.08.2019.
//

#include <v8pp/class.hpp>
#include <sw/math/vector.hpp>
#include <sw/math/matrix.hpp>
#include <iostream>
#include <sw/modules/math.hpp>

namespace sw {


void MathModule::Init(v8::Isolate *isolate) {
    v8pp::class_<Vector2> vector2(isolate);
    v8pp::class_<Vector3> vector3(isolate);
    v8pp::class_<Vector4> vector4(isolate);

    v8pp::class_<Matrix4> matrix4(isolate);


    vector2
            .function("Length", &Vector2::Length)
            .function("Dot", [isolate](v8::FunctionCallbackInfo<v8::Value> const &args) {
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
//            .function("Distance", &Vector2::Distance)
//            .function("Determinant", &Vector2::Determinant)
//            .function("Angle", &Vector2::Angle)
            .function("Normalized", &Vector2::Normalized)
            .function("Normalize", &Vector2::Normalize)
            .function("LengthSquared", &Vector2::LengthSquared)
//            .function("DistanceSquared", &Vector2::LengthSquared)
            .function("Perpendicular", &Vector2::Perpendicular)
            .function("Floor", &Vector2::Floor)
            .function("Ceil", &Vector2::Ceil)
            .function("Zero", &Vector2::Zero);
//            .function("Min", &Vector2::Min)
//            .function("Max", &Vector2::Max)
//            .function("Lerp", &Vector2::Lerp)
//            .function("Add", &Vector2::operator+)
//            .function("Subtract", &Vector2::operator-)
//            .function("Dot", &Vector2::operator*)
//            .function("Add", &Vector2::operator+);


    vector2.auto_wrap_objects();
    vector3.auto_wrap_objects();
    vector4.auto_wrap_objects();

    matrix4.auto_wrap_objects();
}

}

