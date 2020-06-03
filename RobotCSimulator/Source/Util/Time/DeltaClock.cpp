#include "DeltaClock.h"

sf::Clock DeltaClock::deltaTime;
float DeltaClock::bufferDelta = 0.0f;


void DeltaClock::Update() {
	bufferDelta = deltaTime.restart().asSeconds();
}

float DeltaClock::GetDelta() {
	return bufferDelta;
}