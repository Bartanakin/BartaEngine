#pragma once
#include <Dynamics/TimerInterface.h>
#include <pch.h>

namespace Barta::Dynamics::Timers {
class BartaTimer: public Barta::TimerInterface {
public:
    BartaTimer();

    void restart() override;

    float getElapsedTimeOnRestart() const override;

    void setCurrentDeltaTime(float newDeltaTime) override;

    float getCurrentDeltaTime() const override;

    void forward() override;

    bool finished() override;

private:
    std::chrono::steady_clock::time_point lastFrameRenderedTime;
    float currentDeltaTime;
    float remainingDeltaTime;
};
}
