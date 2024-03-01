#pragma once
#include "../TimerInterface.h"

namespace Barta{

	class FrameLimitTimerProxy : public TimerInterface{
	public:
		/*
			Time in seconds
		*/
		FrameLimitTimerProxy(std::unique_ptr<TimerInterface> timer, float frameTime);

		float restart() override;

		float getElapsedTimeOnRestart() const override;

		void setCurrentDeltaTime( const float newDeltaTime ) override;

		float getCurrentDeltaTime() const override;

		void forward() override;

		bool finished() override;

	private:
		std::unique_ptr<TimerInterface> timer;

		const float frameTime;
	};
}

