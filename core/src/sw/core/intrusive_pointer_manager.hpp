//
// Created by Ilya on 08.09.2019.
//

#ifndef SANDWICH_INTRUSIVE_POINTER_MANAGER_HPP
#define SANDWICH_INTRUSIVE_POINTER_MANAGER_HPP

#include <ip/intrusive_ptr.hpp>

#include <v8bind/class.hpp>
#include <v8bind/convert.hpp>

namespace v8b {

template<typename T>
struct IsWrappedClass<ip::intrusive_ptr<T>> : std::false_type {};

template<typename T>
class IntrusivePointerManager : public v8b::PointerManager {
    std::unordered_map<T *, ip::intrusive_ptr<T>> pointers;

public:
    static v8::Local<v8::Object> WrapObject(v8::Isolate *isolate, const ip::intrusive_ptr<T> &ptr) {
        auto &instance = PointerManager::GetInstance<IntrusivePointerManager>();
        auto res = Class<T>::WrapObject(isolate, ptr.get(), &instance);
        instance.pointers.emplace(ptr.get(), ptr);
        return res;
    }

    static v8::Local<v8::Object> FindObject(v8::Isolate *isolate, const ip::intrusive_ptr<T> &ptr) {
        auto &instance = PointerManager::GetInstance<IntrusivePointerManager>();
        auto object = Class<T>::FindObject(isolate, ptr.get());
        if (instance.pointers.find(ptr.get()) == instance.pointers.end()) {
            Class<T>::SetPointerManager(isolate, ptr.get(), &instance);
            instance.pointers.emplace(ptr.get(), ptr);
        }
        return object;
    }

    static ip::intrusive_ptr<T> UnwrapObject(v8::Isolate *isolate, v8::Local<v8::Value> value) {
        auto &instance = PointerManager::GetInstance<IntrusivePointerManager>();
        auto ptr = Class<T>::UnwrapObject(isolate, value);
        if (instance.pointers.find(ptr) == instance.pointers.end()) {
            Class<T>::SetPointerManager(isolate, ptr, &instance);
            instance.pointers.emplace(ptr, ip::intrusive_ptr<T>(ptr));
        }
        return instance.pointers.find(ptr)->second;
    }

protected:
    void EndObjectManage(void *ptr) override {
        pointers.erase(static_cast<T *>(ptr));
    }
};


template<typename T>
struct Convert<ip::intrusive_ptr<T>, typename std::enable_if_t<IsWrappedClass<T>::value>> {
    using CType = ip::intrusive_ptr<T>;
    using V8Type = v8::Local<v8::Object>;

    static bool IsValid(v8::Isolate *isolate, v8::Local<v8::Value> value) {
        return Convert<T>::IsValid(isolate, value);
    }

    static CType FromV8(v8::Isolate *isolate, v8::Local<v8::Value> value) {
        if (!IsValid(isolate, value)) {
            throw std::runtime_error("Value is not a valid object");
        }
        return PointerManager<std::remove_cv_t<T>>::UnwrapObject(isolate, value);
    }

    static V8Type ToV8(v8::Isolate *isolate, CType value) {
        return PointerManager<std::remove_cv_t<T>>::FindObject(isolate, value);
    }
};

}

#endif //SANDWICH_INTRUSIVE_POINTER_MANAGER_HPP
