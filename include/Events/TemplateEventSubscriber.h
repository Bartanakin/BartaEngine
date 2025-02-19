#pragma once
#include "../pch.h"

namespace Barta {

template<typename EventType>
class EventSubscriber {
public:
    //		bool handle(EventType& event) { throw "XD"; }

    bool isToBeDeleted() const noexcept { return false; }
};

#define SUBSCRIBER_INTERFACE_DEFINITION(EVENT_TYPE)                                                                                                  \
    template<>                                                                                                                                       \
    class Barta::EventSubscriber<::EVENT_TYPE> {                                                                                                     \
    public:                                                                                                                                          \
        virtual ~EventSubscriber() noexcept = default;                                                                                               \
        virtual bool handle(::EVENT_TYPE& event) = 0;                                                                                                \
        virtual bool isToBeDeleted() const noexcept = 0;                                                                                             \
    };
}
