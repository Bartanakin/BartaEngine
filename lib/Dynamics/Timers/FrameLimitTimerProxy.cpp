#include <pch.h>
#include <Dynamics/Timers/FrameLimitTimerProxy.h>

Barta::FrameLimitTimerProxy::FrameLimitTimerProxy(
	std::unique_ptr<TimerInterface> timer,
	const float frameTime
) :
	timer( std::move(timer) ),
	frameTime( frameTime )
{}

float Barta::FrameLimitTimerProxy::restart(){
	if( this->timer->getElapsedTimeOnRestart() < this->frameTime ){
		return this->timer->getElapsedTimeOnRestart();
	}

	return this->timer->restart();
}

float Barta::FrameLimitTimerProxy::getElapsedTimeOnRestart() const{
	return this->timer->getElapsedTimeOnRestart();
}

void Barta::FrameLimitTimerProxy::setCurrentDeltaTime( const float newDeltaTime ){
	return this->timer->setCurrentDeltaTime( newDeltaTime );
}

float Barta::FrameLimitTimerProxy::getCurrentDeltaTime() const{
	return this->timer->getCurrentDeltaTime();
}

void Barta::FrameLimitTimerProxy::forward(){
	this->timer->forward();
}

bool Barta::FrameLimitTimerProxy::finished(){
	return this->timer->finished();
}

