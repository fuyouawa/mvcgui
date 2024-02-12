#include "core/object_p.h"
#include "core/object_p_impl.h"
#include "mvcgui/core/object_impl.h"
#include "mvcgui/core/objectdefs.h"
#include <mutex>

namespace mvcgui {
namespace {
std::mutex object_mutex_pool[131];
auto& signal_slot_mutex(const Object* obj) {
    return object_mutex_pool[
            unsigned(uintptr_t(obj)) %
            (sizeof(object_mutex_pool) / sizeof(std::mutex))];
}
}   // namespace


MetaObject::Connection ObjectPrivate::ConnectImpl(
    const Object* sender,
    SignalBase* signal,
    const Object* receiver,
    void** slot_ptr,
    internal::SlotObjectBasePtr slot_obj,
    ConnectionType connection_type,
    InvokeType invoke_type)
{
    const size_t signal_index = 0; //TODO signal_index
    std::scoped_lock lk{ signal_slot_mutex(sender), signal_slot_mutex(receiver) };

    // 如果connection_type是Unique, 表示不重复连接
    // 检测目标Signal中所有Connection的Slot是否有跟当前想连接的Slot重复的
    if (connection_type == ConnectionType::kUnique && slot_obj) {
        const auto conn_manager = sender->data()->connection_manager_.load(std::memory_order_relaxed);
        assert(conn_manager);
        // 获取当前链接的Signal Connection List
        const auto signal_vec = conn_manager->signal_vector.load(std::memory_order_relaxed);
        if (signal_vec && signal_vec->count() > signal_index) {
            // 获取signal_index对应的Signal Connection
            const auto* signal_conn_list = signal_vec->at(signal_index).first.load(std::memory_order_relaxed);
            // 循环迭代检查是否有重复Slot
            while (signal_conn_list) {
                if (signal_conn_list->receiver.load(std::memory_order_relaxed) == receiver &&
                    signal_conn_list->slot_obj->Compare(slot_ptr))
                {
                    return MetaObject::Connection{};
                }
                signal_conn_list = signal_conn_list->next_connection.load(std::memory_order_relaxed);
            }
        }
    }

    // 构建Connection对象
    auto conn = std::make_unique<ObjectPrivate::Connection>();
    conn->sender = const_cast<Object*>(sender);
    conn->signal_index = signal_index;
    conn->receiver_thread_data.store(
            receiver->data()->thread_data_.load(std::memory_order_relaxed),
            std::memory_order_relaxed);
    conn->receiver.store(const_cast<Object*>(receiver), std::memory_order_relaxed);
    conn->slot_obj = slot_obj;
    const_cast<Object*>(sender)->data()->AddConnection(signal_index, std::move(conn));

    return MetaObject::Connection{conn.release()};
}

void ObjectPrivate::AddConnection(int signal_index, ObjectPrivate::ConnectionPtr conn) {

}
}   // namespace mvcgui