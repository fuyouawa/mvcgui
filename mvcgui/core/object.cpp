#include "mvcgui/core/object.h"
#include <stdexcept>
#include <cassert>

namespace mvcgui {
void Object::ConnectImpl(
    const Object* sender,
    SignalBase* signal,
    const Object* receiver,
    internal::SlotObjectBasePtr slot,
    ConnectionType type)
{
    assert(sender);
    assert(signal);
    assert(receiver);
    assert(slot);

    //TODO ConnectImpl
}
} // namespace mvcgui
