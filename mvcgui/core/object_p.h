#pragma once
#include "mvcgui/core/object.h"

namespace mvcgui {
class ThreadData;

class ObjectPrivate : public ObjectData
{
public:
    MVCGUI_DECLARE_PUBLIC(Object)

    struct Connection;
    struct ConnectionManager;
    struct ConnectionList;
    struct ConnectionOrSignalVector;
    struct SignalVector;
    struct Sender;
    struct TaggedSignalVector;

    using ConnectionPtr = std::unique_ptr<Connection>;

    static MetaObject::Connection ConnectImpl(const Object* sender,
                            SignalBase* signal,
                            const Object* receiver,
                            void** slot_ptr,
                            internal::SlotObjectBasePtr slot_obj,
                            ConnectionType connection_type,
                            InvokeType invoke_type);

    void AddConnection(int signal_index, ConnectionPtr conn);

    Object* owner_;
    std::atomic<ConnectionManager*> connection_manager_;
    std::atomic<ThreadData*> thread_data_;
};
}   // namespace mvcgui
