#include "DeltaClock.h"

sf::Clock DeltaClock::deltaTime;
sf::Time DeltaClock::bufferTime;

void DeltaClock::Update() {
	bufferTime = deltaTime.restart();
}

float DeltaClock::GetDelta() {
	return bufferTime.asSeconds();
}

sf::Clock DeltaClock::GetClock() {
	return deltaTime;
}

sf::Time DeltaClock::GetTime() {
	return bufferTime;
}