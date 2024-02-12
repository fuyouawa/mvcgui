
namespace mvcgui {
enum class ConnectionType {
    kUnique,        // ͬһ��Slotֻ�ܱ�����һ��
    kReplace,       // һ��Object��ֻ����һ��Slot���ӵ���Ӧ��Signal��, ���Signal������һ����ǰObject��Slot, ���滻
};

enum class InvokeType {
    kAuto,
    kDirect,
    kQueued
};

template <typename T> inline T *GetPointer(T *ptr) noexcept {
    return ptr;
}
template <typename Ptr> inline auto GetPointer(Ptr &ptr) noexcept -> decltype(ptr.get()) {
    static_assert(noexcept(ptr.get()), "Smart data pointers for MVCGUI_DECLARE_PRIVATE must have noexcept get()");
    return ptr.get();
}
}   // namespace mvcgui

#define MVCGUI_DECLARE_PRIVATE(cls) MVCGUI_DECLARE_PRIVATE_D(data_, cls)
#define MVCGUI_DECLARE_PRIVATE_D(d, cls) \
    inline auto data() { \
        return reinterpret_cast<cls##Private*>(mvcgui::GetPointer(d)); \
    } \
    inline auto data() const { \
        return reinterpret_cast<const cls##Private*>(mvcgui::GetPointer(d)); \
    } \
    friend class cls##Private;

#define MVCGUI_DECLARE_PUBLIC(cls) MVCGUI_DECLARE_PUBLIC_D(owner_, cls)
#define MVCGUI_DECLARE_PUBLIC_D(o, cls) \
    inline auto owner() { \
        return reinterpret_cast<cls*>(mvcgui::GetPointer(o)); \
    } \
    inline auto owner() const { \
        return reinterpret_cast<const cls*>(mvcgui::GetPointer(o)); \
    } \
    friend class cls;