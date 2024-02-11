#pragma once
#include "mvcgui/core/object.h"

namespace mvcgui {
class ThreadData;

class ObjectPrivate : public ObjectData
{
public:
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
                            ConnectionType type);
};
} // namespace mvcgui
