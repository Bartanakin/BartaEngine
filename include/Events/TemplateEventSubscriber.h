#pragma once
#include "../pch.h"

namespace Barta {

template<typename EventType>
class EventSubscriber {
public:
    //		bool handle(EventType& event) { throw "XD"; }

    bool isValid() const noexcept { return true; }
};

#define SUBSCRIBER_INTERFACE_DEFINITION(EVENT_TYPE)                                                                                                  \
    template<>                                                                                                                                       \
    class Barta::EventSubscriber<::EVENT_TYPE> {                                                                                                     \
    public:                                                                                                                                          \
        virtual ~EventSubscriber() noexcept = default;                                                                                               \
        virtual bool handle(::EVENT_TYPE& event) = 0;                                                                                                \
        virtual bool isValid() const noexcept = 0;                                                                                                   \
    };

}
