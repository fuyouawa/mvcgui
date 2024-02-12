#pragma once

namespace mvcgui {
class NonCopyable {
public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

class NonMoveable : NonCopyable {
public:
    NonMoveable() = default;
    NonMoveable(NonMoveable&&) = delete;
    NonMoveable& operator=(NonMoveable&&) = delete;
};

template<class T>
class Singleton : NonMoveable
{
public:
    static T& instance()
    {
        static T inst;
        return inst;
    }

    virtual ~Singleton() = default;

protected:
    Singleton() = default;
};
}   // namespace mvcgui