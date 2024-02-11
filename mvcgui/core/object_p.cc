#include "core/object_p.h"
#include "core/objectdefs.h"

namespace mvcgui {
void ObjectPrivate::ConnectImpl(
        const Object *sender,
        SignalBase* signal,
        const Object *receiver,
        SlotObjectBasePtr slot,
        const MateObject* sender_mate_obj,
        ConnectionType type)
{
    auto signal_index = sender_mate_obj->index_of_signal(signal);
}
}//namespace mvcgui