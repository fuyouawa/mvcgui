#pragma once
#include <mvcgui/core/global.h>
#include <mvcgui/core/object_impl.h>
#include <mvcgui/core/objectdefs.h>
#include <mvcgui/tools/property.h>
#include <memory>
#include <vector>

namespace mvcgui {
class Object;
class SignalBase;
class ObjectPrivate;
struct MetaObject;

template<typename... Args>
class Signal;

class ObjectData : NonMoveable {
public:
    ObjectData() = default;
    virtual ~ObjectData() = 0;

    Object* owner_ = nullptr;
    Object* parent_ = nullptr;
    std::vector<Object*> children_;
/*    size_t is_widget_ : 1;
    size_t block_sig_ : 1;
    size_t was_deleted_ : 1;
    size_t is_deleting_children_ : 1;
    size_t send_child_events_ : 1;
    size_t receive_child_events_ : 1;
    size_t is_window_ : 1;
    size_t delete_later_called_ : 1;
    size_t is_quick_item_ : 1;
    size_t will_be_widget_ : 1;
    size_t was_widget : 1;
    std::atomic_size_t posted_events_;*/
};

class Object
{
public:
    template<typename Func, typename... Args>
    requires std::is_member_function_pointer_v<Func>
    static MetaObject::Connection Connect(
            const Object* sender,
            Signal<Args...>* signal,
            const Object* receiver,
            Func&& slot,
            ConnectionType connection_type,
            InvokeType invoke_type) {
        using ProtoFunc = void(Args...);
        auto slot_obj = internal::MakeCallableObject<ProtoFunc, Func>(std::forward<Func>(slot));
        auto slot_ptr = reinterpret_cast<void**>(slot);
        return ConnectImpl(sender, signal, receiver, slot_ptr, slot_obj, connection_type, invoke_type);
    }

private:
    MVCGUI_DECLARE_PRIVATE(Object)

    static MetaObject::Connection ConnectImpl(
        const Object* sender,
        SignalBase* signal,
        const Object* receiver,
        void** slot_ptr,
        internal::SlotObjectBasePtr slot_obj,
        ConnectionType connection_type,
        InvokeType invoke_type);

    std::unique_ptr<ObjectData> data_;
};
}   // namespace mvcgui
