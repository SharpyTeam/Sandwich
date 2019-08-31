//
// Created by Ilya on 29.08.2019.
//

#ifndef SANDWICH_CORE_MODULE_MATH_HPP
#define SANDWICH_CORE_MODULE_MATH_HPP

#include <sw/js_module.hpp>

namespace sw {

class MathModule : public JSModule {
public:
    void Init(v8::Isolate *) override;
};

}

#endif //SANDWICH_CORE_MODULE_MATH_HPP
