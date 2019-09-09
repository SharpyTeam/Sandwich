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
            .ctor<double, double>()
            .function("length", &Vector2::Length)
            .function("dot", [](v8::FunctionCallbackInfo<v8::Value> const &args) {
                auto *self = v8pp::class_<Vector2>::unwrap_object(args.GetIsolate(), args.This());
                switch (args.Length()) {
                    case 1: {
                        auto *v = v8pp::from_v8<Vector2 *>(args.GetIsolate(), args[0]);
                        if (v) {
                            args.GetReturnValue().Set(self->Dot(*v));
                        } else {
                            args.GetReturnValue().Set(v8::Null(args.GetIsolate()));
                            std::cerr << "Argument 0 in 'Vector2.dot' cannot be null" << std::endl;
                        }
                        break;
                    }
                    case 2: {
                        double x = v8pp::from_v8<double>(args.GetIsolate(), args[0]);
                        double y = v8pp::from_v8<double>(args.GetIsolate(), args[1]);
                        args.GetReturnValue().Set(self->Dot(x, y));
                        break;
                    }
                    default: {
                        args.GetReturnValue().Set(v8::Null(args.GetIsolate()));
                        std::cerr << "Arguments mismatch in 'Vector2.dot'" << std::endl;
                        break;
                    }
                }
            })
            .function("distance", [](v8::FunctionCallbackInfo<v8::Value> const &args) {
                auto *self = v8pp::class_<Vector2>::unwrap_object(args.GetIsolate(), args.This());
                switch (args.Length()) {
                    case 1: {
                        auto *v = v8pp::from_v8<Vector2 *>(args.GetIsolate(), args[0]);
                        if (v) {
                            args.GetReturnValue().Set(self->Distance(*v));
                        } else {
                            args.GetReturnValue().Set(v8::Null(args.GetIsolate()));
                            std::cerr << "Argument 0 in 'Vector2.distance' cannot be null" << std::endl;
                        }
                        break;
                    }
                    case 2: {
                        double tox = v8pp::from_v8<double>(args.GetIsolate(), args[0]);
                        double toy = v8pp::from_v8<double>(args.GetIsolate(), args[1]);
                        args.GetReturnValue().Set(self->Distance(tox, toy));
                        break;
                    }
                    default: {
                        args.GetReturnValue().Set(v8::Null(args.GetIsolate()));
                        std::cerr << "Arguments mismatch in 'Vector2.distance'" << std::endl;
                        break;
                    }
                }
            })
            .function("distanceSquared", [](v8::FunctionCallbackInfo<v8::Value> const &args) {
                auto *self = v8pp::class_<Vector2>::unwrap_object(args.GetIsolate(), args.This());
                switch (args.Length()) {
                    case 1: {
                        auto *v = v8pp::from_v8<Vector2 *>(args.GetIsolate(), args[0]);
                        if (v) {
                            args.GetReturnValue().Set(self->DistanceSquared(*v));
                        } else {
                            args.GetReturnValue().Set(v8::Null(args.GetIsolate()));
                            std::cerr << "Argument 0 in 'Vector2.distanceSquared' cannot be null" << std::endl;
                        }
                        break;
                    }
                    case 2: {
                        double tox = v8pp::from_v8<double>(args.GetIsolate(), args[0]);
                        double toy = v8pp::from_v8<double>(args.GetIsolate(), args[1]);
                        args.GetReturnValue().Set(self->DistanceSquared(tox, toy));
                        break;
                    }
                    default: {
                        args.GetReturnValue().Set(v8::Null(args.GetIsolate()));
                        std::cerr << "Arguments mismatch in 'Vector2.distanceSquared'" << std::endl;
                        break;
                    }
                }
            })
            .function("angle", [](v8::FunctionCallbackInfo<v8::Value> const &args) {
                auto *self = v8pp::class_<Vector2>::unwrap_object(args.GetIsolate(), args.This());
                switch (args.Length()) {
                    case 1: {
                        auto *v = v8pp::from_v8<Vector2 *>(args.GetIsolate(), args[0]);
                        if (v) {
                            args.GetReturnValue().Set(self->Angle(*v));
                        } else {
                            args.GetReturnValue().Set(v8::Null(args.GetIsolate()));
                            std::cerr << "Argument 0 in 'Vector2.angle' cannot be null" << std::endl;
                        }
                        break;
                    }
                    case 2: {
                        double x = v8pp::from_v8<double>(args.GetIsolate(), args[0]);
                        double y = v8pp::from_v8<double>(args.GetIsolate(), args[1]);
                        args.GetReturnValue().Set(self->Angle(x, y));
                        break;
                    }
                    default: {
                        args.GetReturnValue().Set(v8::Null(args.GetIsolate()));
                        std::cerr << "Arguments mismatch in 'Vector2.angle'" << std::endl;
                        break;
                    }
                }
            })
            .function("set", [](v8::FunctionCallbackInfo<v8::Value> const &args) {
                auto *self = v8pp::class_<Vector2>::unwrap_object(args.GetIsolate(), args.This());
                switch (args.Length()) {
                    case 1: {
                        if (args[0]->IsNumber()) {
                            double scalar = v8pp::from_v8<double>(args.GetIsolate(), args[0]);
                            args.GetReturnValue().Set(v8pp::to_v8<Vector2>(args.GetIsolate(), self->Set(scalar)));
                        } else {
                            auto *v = v8pp::from_v8<Vector2 *>(args.GetIsolate(), args[0]);
                            if (v) {
                                args.GetReturnValue().Set(v8pp::to_v8<Vector2>(args.GetIsolate(), self->Set(*v)));
                            } else {
                                args.GetReturnValue().Set(v8::Null(args.GetIsolate()));
                                std::cerr << "Argument 0 in 'Vector2.angle' cannot be null" << std::endl;
                            }
                        }

                        break;
                    }
                    case 2: {
                        double x = v8pp::from_v8<double>(args.GetIsolate(), args[0]);
                        double y = v8pp::from_v8<double>(args.GetIsolate(), args[1]);
                        args.GetReturnValue().Set(v8pp::to_v8<Vector2>(args.GetIsolate(), self->Set(x, y)));
                        break;
                    }
                    default: {
                        args.GetReturnValue().Set(v8::Null(args.GetIsolate()));
                        std::cerr << "Arguments mismatch in 'Vector2.set'" << std::endl;
                        break;
                    }
                }
            })

//            .function("Determinant", &Vector2::Determinant)
//            .function("Angle", &Vector2::Angle)
            .function("normalized", &Vector2::Normalized)
            .function("normalize", &Vector2::Normalize)
            .function("lengthSquared", &Vector2::LengthSquared)
//            .function("DistanceSquared", &Vector2::LengthSquared)
            .function("perpendicular", &Vector2::Perpendicular)
            .function("floor", &Vector2::Floor)
            .function("ceil", &Vector2::Ceil)
            .function("zero", &Vector2::Zero);
            // TODO: Implement all functions

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

