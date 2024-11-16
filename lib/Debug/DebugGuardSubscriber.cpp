//
// Created by bartanakin on 11/10/24.
//

#include <Debug/DebugGuardSubscriber.h>

namespace Barta::Debug {
bool DebugGuardSubscriber::debugGuard = false;

bool DebugGuardSubscriber::handle(
    KeyPressedEvent& event
) {
    if (event.key == BartaKeyMap::SPACEBAR) {
        debugGuard = true;
    }

    return false;
}

bool DebugGuardSubscriber::isValid() const noexcept {
    return true;
}
} // Barta
