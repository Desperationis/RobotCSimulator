#pragma once
#include <SFML/Graphics.hpp>
#include <Debug/Log.h>
#include <Debug/Debug.h>
#include <memory>
#include "System.h"
#include "../ECS.h"
#include "../Components/Components.h"

/*
	Textures entities that have not loaded their assigned textures.
*/

class TextureSystem : public System {
public:
	void update(std::shared_ptr<ECS> ecs) override {
		for (auto const& entity : entities) {
			auto& texture = ecs->getComponent<TextureComponent>(entity);
			auto& drawable = ecs->getComponent<DrawableComponent>(entity);
			auto& info = ecs->getComponent<InfoComponent>(entity);

			if (!texture.isLoaded) {
				if (!texture.tex.loadFromFile(texture.fileName)) {
					texture.tex.loadFromFile("Assests\\missing.jpg");
				}

				if (info.drawableType == "Shape") {
					auto shape = std::dynamic_pointer_cast<sf::Shape>(drawable.drawable);
					shape->setTexture(&texture.tex);
				}
				else if (info.drawableType == "Sprite") {
					auto sprite = std::dynamic_pointer_cast<sf::Sprite>(drawable.drawable);
					sprite->setTexture(texture.tex);
				}

				texture.isLoaded = true;
			}
		}
	};
};
