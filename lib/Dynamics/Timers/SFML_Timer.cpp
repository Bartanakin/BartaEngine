#include "pch.h"
#include <Dynamics/Timers/SFML_Timer.h>

Barta::SFML_Timer::SFML_Timer() :
	sf_clock( sf::Clock() ),
    remainingDeltaTime(sf::Time(sf::Time::Zero)),
    currentDeltaTime(sf::Time(sf::Time::Zero))
{}

Barta::SFML_Timer::~SFML_Timer(){}

float Barta::SFML_Timer::restart(){
	this->remainingDeltaTime = this->sf_clock.restart();
	this->currentDeltaTime = this->remainingDeltaTime;

	return this->remainingDeltaTime.asSeconds();
}

float Barta::SFML_Timer::getElapsedTimeOnRestart() const{
	return this->sf_clock.getElapsedTime().asSeconds();
}

void Barta::SFML_Timer::setCurrentDeltaTime( const float newDeltaTime ){
	this->currentDeltaTime = sf::seconds( newDeltaTime );

	if( this->currentDeltaTime > this->remainingDeltaTime || this->currentDeltaTime < sf::Time::Zero ){
		throw "The current deltaTime must be between 0 and the remaining deltaTime.";
	}
}

float Barta::SFML_Timer::getCurrentDeltaTime() const {
	return this->currentDeltaTime.asSeconds();
}

void Barta::SFML_Timer::forward(){
	this->remainingDeltaTime -= this->currentDeltaTime;
	this->currentDeltaTime = this->remainingDeltaTime;
}

bool Barta::SFML_Timer::finished(){
	return this->remainingDeltaTime == sf::Time::Zero;
}
