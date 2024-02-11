#pragma once
#include <mvcgui/tools/func_traits.h>
#include <memory>

namespace mvcgui {
class Object;

namespace internal {
class SlotObjectBase
{
public:
    enum class Operation {
        kCall,
        kDestory
    };

    using ImplFn = void(*)(Operation op, SlotObjectBase* this_, Object* receiver, void** args, bool* ret);

    explicit SlotObjectBase(ImplFn fn) : impl_{ fn } {}

    void Call(Object* r, void** a) { impl_(Operation::kCall, this, r, a, nullptr); }

    struct Deleter {
        void operator()(SlotObjectBase* ptr) const noexcept {
            if (ptr) {
                ptr->impl_(Operation::kDestory, ptr, nullptr, nullptr, nullptr);
            }
        }
    };

protected:
    ~SlotObjectBase() = default;

private:
    const ImplFn impl_;
};

using SlotObjectBasePtr = std::shared_ptr<SlotObjectBase>;

template<typename Func, typename Args>
class CallableObject : public SlotObjectBase
{
public:
    explicit CallableObject(Func&& func) : SlotObjectBase{ &Impl }, func_{ std::move(func) } {}
    explicit CallableObject(const Func& func) : SlotObjectBase{ &Impl }, func_{ func } {}

private:
    using FuncType = FunctionTraits<Func>;

    static void Impl(Operation op, SlotObjectBase* this_, Object* receiver, void** args, bool* ret) {
        const auto that = static_cast<CallableObject*>(this_);
        switch (op)
        {
        case Operation::kDestory:
            delete that;
            break;
        case Operation::kCall:
            FuncType::template Call<Args, void>(
                that->func_,
                static_cast<typename FuncType::Object*>(receiver),
                args);
            break;
        default:
            break;
        }
    }

    Func func_;
};

template<typename ProtoFunc, typename Func>
requires std::is_member_function_pointer_v<std::decay_t<Func>>
inline SlotObjectBasePtr MakeCallableObject(Func&& func) {
    using Signature = FunctionTraits<Func>;
    using Arguments = typename Signature::Arguments;
    static_assert(kIsMatchableFunctions<ProtoFunc, Func>, "The type of each parameter and the return type of Func must match ProtoFunc mutually!");
    return std::shared_ptr{new CallableObject<Func, Arguments>(std::forward<Func>(func)),
                           SlotObjectBase::Deleter{}};
}
} // namespace internal
} // namespace mvcgui