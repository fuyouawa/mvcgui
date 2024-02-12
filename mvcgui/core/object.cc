#include "mvcgui/core/object.h"
#include "core/object_p.h"
#include <cassert>

namespace mvcgui {
    MetaObject::Connection Object::ConnectImpl(
    const Object* sender,
    SignalBase* signal,
    const Object* receiver,
    void** slot_ptr,
    internal::SlotObjectBasePtr slot_obj,
    ConnectionType connection_type,
    InvokeType invoke_type)
{
    assert(sender);
    assert(signal);
    assert(receiver);
    assert(slot_ptr);
    assert(slot_obj);
    return ObjectPrivate::ConnectImpl(sender, signal, receiver, slot_ptr, slot_obj, connection_type, invoke_type);
}
}   // namespace mvcgui
