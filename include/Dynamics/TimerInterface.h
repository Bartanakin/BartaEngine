#pragma once
#include <pch.h>

namespace Barta {

class TimerInterface {
public:
    TimerInterface() = default;
    virtual ~TimerInterface() = default;

    virtual void restart() = 0;

    virtual float getElapsedTimeOnRestart() const = 0;

    virtual void setCurrentDeltaTime(float newDeltaTime) = 0;

    virtual float getCurrentDeltaTime() const = 0;

    virtual void forward() = 0;

    /*
        Returns true if there is still time left for the frame to go.
    */
    virtual bool finished() = 0;
};
}
