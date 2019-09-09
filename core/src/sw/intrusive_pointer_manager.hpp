//
// Created by Ilya on 08.09.2019.
//

#ifndef SANDWICH_INTRUSIVE_POINTER_MANAGER_HPP
#define SANDWICH_INTRUSIVE_POINTER_MANAGER_HPP

#include <v8bind/class.hpp>
#include <ip/intrusive_ptr.hpp>

namespace sw {

template<typename T>
class IntrusivePointerManager : public v8b::PointerManager {
    std::unordered_map<T *, ip::intrusive_ptr<T>> pointers;

public:
    static v8::Local<v8::Object> WrapObject(v8::Isolate *isolate, const ip::intrusive_ptr<T> &ptr) {
        auto &instance = PointerManager::GetInstance<IntrusivePointerManager>();
        return Class<T>::WrapObject(isolate, ptr.get(), &instance);
    }

    static v8::Local<v8::Object> FindObject(v8::Isolate *isolate, const ip::intrusive_ptr<T> &ptr) {
        auto &instance = PointerManager::GetInstance<IntrusivePointerManager>();
        auto object = Class<T>::FindObject(isolate, ptr.get());
        if (instance.pointers.find(ptr.get()) == instance.pointers.end()) {
            Class<T>::SetPointerManager(isolate, ptr.get(), &instance);
        }
        return object;
    }

    static ip::intrusive_ptr<T> UnwrapObject(v8::Isolate *isolate, v8::Local<v8::Value> value) {
        auto &instance = PointerManager::GetInstance<IntrusivePointerManager>();
        auto ptr = Class<T>::UnwrapObject(isolate, value);
        if (instance.pointers.find(ptr) == instance.pointers.end()) {
            Class<T>::SetPointerManager(isolate, ptr, &instance);
        }
        return instance.pointers.find(ptr)->second;
    }

protected:
    void BeginObjectManage(void *ptr) override {
        pointers.emplace(static_cast<T *>(ptr), ip::intrusive_ptr<T>(static_cast<T *>(ptr)));
    }

    void EndObjectManage(void *ptr) override {
        pointers.erase(static_cast<T *>(ptr));
    }
};

}

#endif //SANDWICH_INTRUSIVE_POINTER_MANAGER_HPP
