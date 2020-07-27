#pragma once
#include <SFML\Graphics.hpp>
#include "../Utility/TextureSprite.h"
#include "../Utility/DeltaClock.h"
#include "../stdafx.h"
#include "../RobotC.h"

using namespace RobotC::Peripherals;
using namespace RobotC::Types;



class Robot : public TextureSprite {
public:

	Robot() {

		LoadTextureFromFile("Assets/Clawbot.png");
		SetRectSize(sf::Vector2f(50, 50));

		setOrigin(sf::Vector2f(25, 25));
		setPosition(sf::Vector2f(1000, 500));
	};

	float GetRadians() {
		return getRotation() * (M_PI / 180.0f);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		TextureSprite::draw(target, states);
		
		ImGui::Begin("Robot");
		ImGui::Text("Position x: %g", getPosition().x);
		ImGui::Text("Position y: %g", getPosition().y);
		ImGui::End();


		sf::CircleShape ICC;
		ICC.setRadius(2.0f);
		ICC.setOrigin(sf::Vector2f(2.0f, 2.0f));
		ICC.setPosition(ICCPosition);
		ICC.setFillColor(sf::Color::Red);

		target.draw(ICC);
	}

	void Update() override {
		auto delta = DeltaClock::GetDelta();
		//float leftMotorValue = 100.0f;
		//float rightMotorValue = 127.0f;
		float leftMotorValue = motor[leftMotorPort];
		float rightMotorValue = motor[rightMotorPort];
		sf::Vector2f velocity(0, 0);

		if((rightMotorValue - leftMotorValue) != 0) {
			float L = rectangleShape.getLocalBounds().width;
			float R = (L / 2) * ((leftMotorValue + rightMotorValue) / (rightMotorValue - leftMotorValue));
			float rotationalSpeed = (rightMotorValue - leftMotorValue) / L;
		
			//setRotation(45.0f);

			ICCPosition.x = getPosition().x + (sin(GetRadians()) * R);
			ICCPosition.y = getPosition().y - (cos(GetRadians()) * R);
			//ICCPosition = sf::Vector2f(900, 500);

			setRotation(getRotation() - (rotationalSpeed * delta * 30));

			sf::Vector2f position = getPosition();
			float xDif = position.x - ICCPosition.x;
			float yDif = position.y - ICCPosition.y;
			float distance = sqrt(pow(xDif, 2) + pow(yDif, 2));

			position.x = ICCPosition.x + (-sin(GetRadians()) * R);
			position.y = ICCPosition.y + (cos(GetRadians()) * R);

			setPosition(position);
		}


		
		setPosition(getPosition() + velocity);
	};

private:
	MotorPort leftMotorPort = port1;
	MotorPort rightMotorPort = port5;

	sf::Vector2f ICCPosition;
};