#pragma once
#include <mvcgui/core/global.h>
#include <mvcgui/core/object_impl.h>
#include <memory>

namespace mvcgui {
class SignalBase;
template<typename... Args>
class Signal;
namespace internal {
class SlotObjectBase;
using SlotObjectBasePtr = std::shared_ptr<SlotObjectBase>;
} // namespace internal

class Object
{
public:
    template<typename Func, typename... Args>
    requires std::is_member_function_pointer_v<Func>
    static void Connect(const Object* sender, Signal<Args...>* signal, const Object* receiver, Func&& slot, ConnectionType type) {
        using ProtoFunc = void(Args...);
        ConnectImpl(
            sender,
            signal,
            receiver,
            internal::MakeCallableObject<ProtoFunc, Func>(std::forward<Func>(slot)),
            type);
    }

private:
    static void ConnectImpl(
        const Object* sender,
        SignalBase* signal,
        const Object* receiver,
        internal::SlotObjectBasePtr slot,
        ConnectionType type);
};
} // namespace mvcgui
