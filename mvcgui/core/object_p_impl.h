#pragma once
#include "core/object_p.h"
#include "mvcgui/core/object.h"
#include <atomic>
#include <cassert>

namespace mvcgui {
struct ObjectPrivate::ConnectionList {
    std::atomic<Connection*> first;
    std::atomic<Connection*> last;
};
static_assert(std::is_trivially_destructible_v<ObjectPrivate::ConnectionList>);

struct ObjectPrivate::TaggedSignalVector
{
    uintptr_t addr;

    TaggedSignalVector() = default;
    explicit TaggedSignalVector(std::nullptr_t) : addr{0} {}

    explicit TaggedSignalVector(Connection* v) noexcept
        : addr(reinterpret_cast<uintptr_t>(v))
    { assert(v && (reinterpret_cast<uintptr_t>(v) & 0x1) == 0); }

    explicit TaggedSignalVector(SignalVector* v) noexcept
        : addr(reinterpret_cast<uintptr_t>(v) | uintptr_t(1u))
    { assert(v); }

    explicit operator SignalVector* () const noexcept {
        if (addr & 0x1)
            return reinterpret_cast<SignalVector*>(addr & ~uintptr_t(1u));
        return nullptr;
    }

    explicit operator Connection* () const noexcept {
        return reinterpret_cast<Connection*>(addr);
    }

    explicit operator uintptr_t() const noexcept { return addr; }
};


struct ObjectPrivate::ConnectionOrSignalVector
{
    union {
        TaggedSignalVector next_in_orphan_list;
        Connection* next;
    };
};
static_assert(std::is_trivial_v<ObjectPrivate::ConnectionOrSignalVector>);


struct ObjectPrivate::Connection : public ConnectionOrSignalVector
{
    Connection** prev;
    std::atomic<Connection*> next_connection_list;
    Connection* prev_connection_list;

    Object* sender;
    std::atomic<Object*> receiver;
    std::atomic<ThreadData*> receiver_thread_data;
    SlotObjectBasePtr slot_obj;
    uint32_t id;
    int signal_index;
    ConnectionType conn_type;
};


struct ObjectPrivate::SignalVector : public ConnectionOrSignalVector
{
    size_t allocated;
    auto& at(int i) {
        //TODO 暂时不知道为什么要i+1
        return reinterpret_cast<ConnectionList *>(this + 1)[i + 1];
    }
    auto& at(int i) const {
        return reinterpret_cast<const ConnectionList *>(this + 1)[i + 1];
    }
    auto count() const { return allocated; }
};


struct ObjectPrivate::ConnectionData {
    std::atomic_uint current_connection_id;
    std::atomic<SignalVector*> signal_vector;
    Connection* senders;
    Sender* current_sender;
    std::atomic<TaggedSignalVector> orphaned;

    ~ConnectionData();
    void RemoveConnection(Connection* conn);
    void ResizeSignalVector(size_t size);
    static void DeleteOrphaned(TaggedSignalVector o);
};
} // namespace mvcgui