#pragma once

namespace mvcgui {
class SignalBase;

struct Matedata {

};

class MateObject {
public:
    int index_of_signal(const SignalBase* signal) const;
};
}//namespace mvcgui