#include "mvcgui/core/object.h"
#include "core/object_p.h"
#include <cassert>

namespace mvcgui {
void Object::ConnectImpl(
    const Object* sender,
    SignalBase* signal,
    const Object* receiver,
    SlotObjectBasePtr slot,
    ConnectionType type)
{
    assert(sender);
    assert(signal);
    assert(receiver);
    assert(slot);
    ObjectPrivate::ConnectImpl(sender, signal, receiver, slot, sender->data()->meta_obj_, type);
}
} // namespace mvcgui
