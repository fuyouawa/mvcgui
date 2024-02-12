#pragma once

namespace mvcgui {
class SignalBase;

struct Metadata {

};

class MetaObject {
public:
    class Connection;

    int index_of_signal(const SignalBase* signal) const;
};

class MetaObject::Connection {
public:
    Connection() : data_{ nullptr } {}

private:
    friend class Object;
    friend class ObjectPrivate;
    friend class MetaObject;

    explicit Connection(void* data) : data_{ data } {}

    void* data_;    //ObjectPrivate::Connection*
};
}   // namespace mvcgui