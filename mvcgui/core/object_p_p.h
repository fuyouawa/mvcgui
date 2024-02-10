#pragma once
#include <core/object_p.h>
#include <atomic>
#include <assert.h>

namespace mvcgui {
class Object;

namespace internal {
struct ObjectPrivate::ConnectionList {
    std::atomic<Connection*> first;
    std::atomic<Connection*> last;
};
static_assert(std::is_trivially_destructible_v<ObjectPrivate::ConnectionList>);

struct ObjectPrivate::TaggedSignalVector
{
    uintptr_t addr;

    TaggedSignalVector() = default;
    TaggedSignalVector(std::nullptr_t) noexcept : addr(0) {}
    TaggedSignalVector(Connection* v) noexcept 
        : addr(reinterpret_cast<uintptr_t>(v))
    {
        assert(v && (reinterpret_cast<uintptr_t>(v) & 0x1) == 0);
    }
    TaggedSignalVector(SignalVector* v) noexcept 
        : addr(reinterpret_cast<uintptr_t>(v) | uintptr_t(1u))
    {
        assert(v);
    }

    explicit operator SignalVector* () const noexcept {
        if (addr & 0x1)
            return reinterpret_cast<SignalVector*>(addr & ~uintptr_t(1u));
        return nullptr;
    }

    explicit operator Connection* () const noexcept {
        return reinterpret_cast<Connection*>(addr);
    }

    operator uintptr_t() const noexcept { return addr; }
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

};
}
}