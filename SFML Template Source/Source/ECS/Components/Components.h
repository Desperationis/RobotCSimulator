#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../Namespaces.h"

class System;

struct Component {
	Component() = default;
};

// flags
struct InputComponent : public Component { };
struct DebugComponent : public Component { };
struct LoopComponent : public Component {};
struct WallCollisionComponent : public Component {};

struct InfoComponent : public Component {
	std::string drawableType;
};

class DimensionSystem;
struct DrawableComponent : public Component {
	const sf::Vector2i getDimension() { return dimension; }
	std::shared_ptr<sf::Drawable> drawable;

private:
	friend DimensionSystem;
	bool isMeasured = false;
	sf::Vector2i dimension; // x - width  y - height
};

struct PositionComponent : public Component {
	sf::Vector2f pos;
	sf::Vector2f pastPos;
	float angle = 0.0f;
};

struct MovementComponent : public Component {
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float angularSpeed = 0.0f;
};

class TextureSystem;
struct TextureComponent : public Component {
	std::string fileName;

private:
	friend TextureSystem;
	sf::Texture tex;
	bool isLoaded = false;
};

class ColorSystem;
struct ColorComponent : public Component {
	void setColor(sf::Color _color_) {
		color = _color_;
		isApplied = false;
	}
	const sf::Color getColor() { return color; }

private:
	friend ColorSystem;
	sf::Color color;
	bool isApplied = false;
};


struct CollisionEvent {
	// tells information of a collision
	Entity target;
	bool active = false;
};

struct CollisionComponent : public Component {
	std::shared_ptr<CollisionEvent> event; // tells the entities involved during the collision
	sf::FloatRect hitBox;
};

struct RenderCollisionComponent : public Component {
	sf::VertexArray hitBoxRender;
};

