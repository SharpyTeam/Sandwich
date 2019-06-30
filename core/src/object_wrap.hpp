//
// Created by selya on 30.06.2019.
//

#ifndef SANDWICH_OBJECT_WRAP_HPP
#define SANDWICH_OBJECT_WRAP_HPP

#include <v8.h>
#include <cassert>

namespace sw {

// Class from nodejs project

class ObjectWrap {
public:
    ObjectWrap() : refs_(0) {}

    virtual ~ObjectWrap() {
        if (GetPersistent().IsEmpty()) return;
        GetPersistent().ClearWeak();
        GetPersistent().Reset();
    }

    virtual v8::Local<v8::FunctionTemplate> GetObjectConstructorTemplate() {
        return v8::Local<v8::FunctionTemplate>();
    }

    virtual v8::Local<v8::ObjectTemplate> GetObjectTemplate() {
        auto ft = GetObjectConstructorTemplate();
        assert(!ft.IsEmpty());
        return ft->InstanceTemplate();
    }

    inline v8::Local<v8::Object> GetHandle() {
        return v8::Local<v8::Object>::New(v8::Isolate::GetCurrent(), GetPersistent());
    }

    inline v8::Persistent<v8::Object> &GetPersistent() {
        return persistent_;
    }

    inline void Wrap(v8::Local<v8::Object> handle) {
        assert(persistent_().IsEmpty());
        assert(handle->InternalFieldCount() > 0);
        handle->SetAlignedPointerInInternalField(0, this);
        GetPersistent().Reset(v8::Isolate::GetCurrent(), handle);
        MakeWeak();
    }

    inline void Wrap() {
        Wrap(GetObjectTemplate()->NewInstance(v8::Isolate::GetCurrent()->GetCurrentContext()).ToLocalChecked());
    }

    /* Ref() marks the object as being attached to an event loop.
     * Refed objects will not be garbage collected, even if
     * all references are lost.
     */
    virtual void Ref() {
        assert(!persistent_().IsEmpty());
        GetPersistent().ClearWeak();
        refs_++;
    }

    /* Unref() marks an object as detached from the event loop.  This is its
     * default state.  When an object with a "weak" reference changes from
     * attached to detached state it will be freed. Be careful not to access
     * the object after making this call as it might be gone!
     * (A "weak reference" means an object that only has a
     * persistent handle.)
     *
     * DO NOT CALL THIS FROM DESTRUCTOR
     */
    virtual void Unref() {
        assert(!persistent_().IsEmpty());
        assert(!persistent_().IsWeak());
        assert(refs_ > 0);
        if (--refs_ == 0) MakeWeak();
    }

    template<class T>
    static inline T *Unwrap(v8::Local<v8::Object> handle) {
        assert(!handle.IsEmpty());
        assert(handle->InternalFieldCount() > 0);
        // Cast to ObjectWrap before casting to T. A direct cast from void
        // to T won't work right when T has more than one base class.
        void *ptr = handle->GetAlignedPointerFromInternalField(0);
        ObjectWrap *wrap = static_cast<ObjectWrap *>(ptr);
        return static_cast<T *>(wrap);
    }

private:
    int refs_;
    v8::Persistent<v8::Object> persistent_;

    inline void MakeWeak() {
        GetPersistent().SetWeak(this, WeakCallback, v8::WeakCallbackType::kParameter);
    }

    static void WeakCallback(const v8::WeakCallbackInfo<ObjectWrap> &data) {
        ObjectWrap *wrap = data.GetParameter();
        assert(wrap->refs_ == 0);
        wrap->persistent_.Reset();
        delete wrap;
    }
};

}  // namespace node

#endif //SANDWICH_OBJECT_WRAP_HPP
