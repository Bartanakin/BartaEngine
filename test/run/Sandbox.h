#pragma once
#include <Application.h>
#include "Constants.h"

class Sandbox : public Barta::Application{
public:
	Sandbox();
    Sandbox(const Sandbox&) = delete;
    Sandbox(Sandbox&&) = delete;
    Sandbox& operator=(const Sandbox&) = delete;
	~Sandbox() noexcept;

private:
    static std::unique_ptr<Barta::TimerInterface> gameTimer;
};

