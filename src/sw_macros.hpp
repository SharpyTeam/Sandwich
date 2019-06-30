//
// Created by Ilya on 30.06.2019.
//

#ifndef SANDWICH_SW_MACROS_HPP
#define SANDWICH_SW_MACROS_HPP

#define v8_str(s) v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), s).ToLocalChecked()
#define v8_num(n) v8::Number::New(v8::Isolate::GetCurrent(), n).ToLocalChecked()

#endif //SANDWICH_SW_MACROS_HPP
