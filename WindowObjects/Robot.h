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
		ImGui::Text("Linear Velocity: %g", sqrt(pow(velocity.x, 2) + pow(velocity.y, 2)));
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
		float leftMotorValue = (motor[leftMotorPort] / 127.0f) * 80;
		float rightMotorValue = (motor[rightMotorPort] / 127.0f) * 80;

		if(abs(rightMotorValue - leftMotorValue) >= 2) {
			//float L = rectangleShape.getLocalBounds().width;
			float L = 18.0f; // Inches
			float R = (L / 2) * ((leftMotorValue + rightMotorValue) / (rightMotorValue - leftMotorValue));
			float rotationalSpeed = (rightMotorValue - leftMotorValue) / L;
		
			ICCPosition.x = getPosition().x + (sin(GetRadians()) * R);
			ICCPosition.y = getPosition().y - (cos(GetRadians()) * R);

			setRotation(getRotation() - (rotationalSpeed * delta * 360));

			sf::Vector2f position = getPosition();

			position.x = ICCPosition.x + (-sin(GetRadians()) * R);
			position.y = ICCPosition.y + (cos(GetRadians()) * R);

			velocity.x = position.x - getPosition().x;
			velocity.y = position.y - getPosition().y;

			setPosition(position);
		}
		else {
			sf::Vector2f position = getPosition();

			position.x += (leftMotorValue * cos(GetRadians()) * delta) * 5;
			position.y += (leftMotorValue * sin(GetRadians()) * delta) * 5;

			velocity.x = position.x - getPosition().x;
			velocity.y = position.y - getPosition().y;

			setPosition(position);


		
		}
	};

private:
	MotorPort leftMotorPort = port1;
	MotorPort rightMotorPort = port5;

	sf::Vector2f ICCPosition;
	sf::Vector2f velocity;
};