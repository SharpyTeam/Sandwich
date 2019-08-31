//
// Created by Ilya on 29.08.2019.
//

#ifndef SANDWICH_CORE_JS_MODULE_HPP
#define SANDWICH_CORE_JS_MODULE_HPP

namespace sw {

class JSModule {
public:
    virtual void Init(v8::Isolate *) = 0;
};

}

#endif //SANDWICH_CORE_JS_MODULE_HPP
