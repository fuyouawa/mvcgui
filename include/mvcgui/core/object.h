#pragma once
#include <mvcgui/core/global.h>
#include <mvcgui/core/object_impl.h>
#include <mvcgui/tools/property.h>
#include <memory>

namespace mvcgui {
class SignalBase;
class ObjectPrivate;
struct MateObject;

template<typename... Args>
class Signal;
class SlotObjectBase;

using SlotObjectBasePtr = std::shared_ptr<SlotObjectBase>;

class ObjectData : NonMoveable {
public:
    MateObject* meta_obj_;
};

class Object
{
    MVCGUI_DECLARE_PRIVATE(Object)
public:
    template<typename Func, typename... Args>
    requires std::is_member_function_pointer_v<Func>
    static void Connect(const Object* sender, Signal<Args...>* signal, const Object* receiver, Func&& slot, ConnectionType type) {
        using ProtoFunc = void(Args...);
        auto slot_obj = internal::MakeCallableObject<ProtoFunc, Func>(std::forward<Func>(slot));
        ConnectImpl(sender, signal, receiver, slot_obj, type);
    }

private:
    static void ConnectImpl(
        const Object* sender,
        SignalBase* signal,
        const Object* receiver,
        SlotObjectBasePtr slot,
        ConnectionType type);

    std::unique_ptr<ObjectData> data_;
};
} // namespace mvcgui
