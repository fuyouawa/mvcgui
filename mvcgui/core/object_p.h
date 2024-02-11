#pragma once
#include "mvcgui/core/object.h"

namespace mvcgui {
class ThreadData;

class ObjectPrivate : public ObjectData
{
public:
    MVCGUI_DECLARE_PUBLIC(Object)

    struct Connection;
    struct ConnectionData;
    struct ConnectionList;
    struct ConnectionOrSignalVector;
    struct SignalVector;
    struct Sender;
    struct TaggedSignalVector;

    static void ConnectImpl(const Object* sender,
                            SignalBase* signal,
                            const Object* receiver,
                            SlotObjectBasePtr slot,
                            const MateObject* sender_mate_obj,
                            ConnectionType connection_type,
                            InvokeType invoke_type);

    Object* owner_;
    std::atomic<ConnectionData*> connections_;
};
} // namespace mvcgui
