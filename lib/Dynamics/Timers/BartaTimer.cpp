#include <Dynamics/Timers/BartaTimer.h>

namespace Barta::Dynamics::Timers {

BartaTimer::BartaTimer():
    lastFrameRenderedTime(std::chrono::steady_clock::now()),
    currentDeltaTime(0),
    remainingDeltaTime(0) {}

void BartaTimer::restart() {
    this->currentDeltaTime = this->getElapsedTimeOnRestart();
    this->remainingDeltaTime = this->currentDeltaTime;
    this->lastFrameRenderedTime = std::chrono::steady_clock::now();
}

float BartaTimer::getElapsedTimeOnRestart() const {
    return static_cast<float>(
               std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - this->lastFrameRenderedTime).count()
           )
           / 1000000000.f;
}

void BartaTimer::setCurrentDeltaTime(
    const float newDeltaTime
) {
    this->currentDeltaTime = newDeltaTime;

    if (this->currentDeltaTime > this->remainingDeltaTime || this->currentDeltaTime < 0.f) {
        throw "The current deltaTime must be between 0 and the remaining deltaTime.";
    }
}

float BartaTimer::getCurrentDeltaTime() const {
    return this->currentDeltaTime;
}

void BartaTimer::forward() {
    this->remainingDeltaTime -= this->currentDeltaTime;
    this->currentDeltaTime = this->remainingDeltaTime;
}

bool BartaTimer::finished() {
    return this->remainingDeltaTime <= 0.f;
}
}
