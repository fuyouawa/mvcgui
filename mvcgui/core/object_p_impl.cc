#include "core/object_p_impl.h"

namespace mvcgui {
ObjectPrivate::ConnectionManager::~ConnectionManager()  {
    if (auto o = orphaned.exchange(
            TaggedSignalVector(nullptr),
            std::memory_order_relaxed); o.addr)
    {
        DeleteOrphaned(o);
    }
    if (auto v = signal_vector.load(std::memory_order_relaxed)) {
        v->~SignalVector();
        free(v);
    }
}

void ObjectPrivate::ConnectionManager::RemoveConnection(ObjectPrivate::Connection *conn) {
    //TODO RemoveConnection
}

void ObjectPrivate::ConnectionManager::ResizeSignalVector(size_t size) {
    //TODO ResizeSignalVector
}

void ObjectPrivate::ConnectionManager::DeleteOrphaned(ObjectPrivate::TaggedSignalVector o) {
    //TODO DeleteOrphaned
}
}   // namespace mvcgui