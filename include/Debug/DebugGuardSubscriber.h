//
// Created by bartanakin on 11/10/24.
//

#pragma once
#include <Events/Events/KeyPressedEvent.h>

namespace Barta::Debug {

class DebugGuardSubscriber: virtual public KeyPressedSubscriberInterface {
public:
    static bool debugGuard;
    DebugGuardSubscriber() noexcept = default;

    bool handle(KeyPressedEvent& event) override;

    bool isValid() const noexcept override;

private:
};

} // Barta::Debug
