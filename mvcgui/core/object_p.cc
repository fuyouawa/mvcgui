#include "core/object_p.h"
#include "core/objectdefs.h"
#include <mutex>

namespace mvcgui {
namespace {
std::mutex object_mutex_pool[131];
auto& signal_slot_mutex(const Object* obj) {
    return object_mutex_pool[uintptr_t(obj) % (sizeof(object_mutex_pool) / sizeof(std::mutex))];
}
}//namespace


void ObjectPrivate::ConnectImpl(
        const Object *sender,
        SignalBase* signal,
        const Object *receiver,
        SlotObjectBasePtr slot,
        const MateObject* sender_mate_obj,
        ConnectionType connection_type,
        InvokeType invoke_type)
{
    auto signal_index = sender_mate_obj->index_of_signal(signal);
    std::scoped_lock lk{ signal_slot_mutex(sender), signal_slot_mutex(receiver) };

}
}//namespace mvcgui