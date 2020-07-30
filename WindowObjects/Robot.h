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

	Robot() : SPEED(50), renderICC(false) {
		LoadTextureFromFile("Assets/Clawbot.png");
		SetRectSize(sf::Vector2f(50, 100));

		// Origin defines the midpoint of the wheels. 
		setOrigin(sf::Vector2f(rectangleShape.getLocalBounds().width / 2, rectangleShape.getLocalBounds().height / 2));
		setPosition(sf::Vector2f(1000, 500));
	};

	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		TextureSprite::draw(target, states);

		if(renderICC) {
			sf::CircleShape ICC;
			ICC.setRadius(2.0f);
			ICC.setOrigin(sf::Vector2f(2.0f, 2.0f));
			ICC.setPosition(ICCPosition);
			ICC.setFillColor(sf::Color::Red);
			target.draw(ICC);
		}
	}

	void ImGuiDraw() override {
		auto delta = DeltaClock::GetDelta();
		ImGui::Begin("Robot");
		ImGui::Text("Position x (px): %g", getPosition().x);
		ImGui::Text("Position y (px): %g", getPosition().y);
		ImGui::Text("Velocity (px/s): %g", sqrt(pow(velocity.x, 2) + pow(velocity.y, 2)) / delta);
		ImGui::Checkbox("Render ICC: ", &renderICC);
		ImGui::End();
	}

	float GetRadians() {
		return getRotation() * (M_PI / 180.0f);
	}

	sf::Vector2f GetWrappedPosition(sf::Vector2f position) {
		// Wrap the robot's position so it's always in view.
		sf::VideoMode windowMode = sf::VideoMode::getDesktopMode();

		if(position.x > windowMode.width) {
			position.x = 0;
		}
		if (position.x < 0) {
			position.x = windowMode.width;
		}
		
		if (position.y > windowMode.height) {
			position.y = 0;
		}
		if (position.y < 0) {
			position.y = windowMode.height;
		}

		return position;
	}

	sf::Vector2f CalculateNewTurnPosition(float leftMotorValue, float rightMotorValue) {
		auto position = getPosition();
		auto delta = DeltaClock::GetDelta();

		// Use a modified formula of tangetial velocity to find circle center (ICC) + rotational speed.
		float width = rectangleShape.getLocalBounds().width;
		float distanceToICC = (width / 2) * ((leftMotorValue + rightMotorValue) / (rightMotorValue - leftMotorValue));
		float rotationalSpeed = (rightMotorValue - leftMotorValue) / width;
		
		// Make a turn around a pivot (ICC) based on rotational speed.
		ICCPosition.x = getPosition().x + (sin(GetRadians()) * distanceToICC);
		ICCPosition.y = getPosition().y - (cos(GetRadians()) * distanceToICC);

		setRotation(getRotation() - (rotationalSpeed * delta * 360));

		position.x = ICCPosition.x + (-sin(GetRadians()) * distanceToICC);
		position.y = ICCPosition.y + (cos(GetRadians()) * distanceToICC);
		
		return position;
	}

	void Update() override {

		// Scale raw motor values down to emulate speed
		float leftMotorValue = (motor[leftMotorPort] / 127.0f)  * SPEED;
		float rightMotorValue = (motor[rightMotorPort] / 127.0f) * SPEED;

		SensorValue[leftEncoderPort] += leftMotorValue;
		SensorValue[rightEncoderPort] += rightMotorValue;

		sf::Vector2f position = getPosition();

		// Turn or go straight based on motor velocities.
		if(abs(rightMotorValue - leftMotorValue) >= 2) {
			position = CalculateNewTurnPosition(leftMotorValue, rightMotorValue);
		}
		else {
			auto delta = DeltaClock::GetDelta();
			position.x += (leftMotorValue * cos(GetRadians()) * delta) * 5;
			position.y += (leftMotorValue * sin(GetRadians()) * delta) * 5;
		}

		velocity.x = position.x - getPosition().x;
		velocity.y = position.y - getPosition().y;

		setPosition(GetWrappedPosition(position));
	};

private:
	MotorPort leftMotorPort = port1;
	MotorPort rightMotorPort = port5;

	SensorPort leftEncoderPort = dgtl1;
	SensorPort rightEncoderPort = dgtl3;

	sf::Vector2f ICCPosition;
	sf::Vector2f velocity;

	bool renderICC;

	const int SPEED;
};