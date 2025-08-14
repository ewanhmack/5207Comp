#include "Pig.h"

// Constructor with texture
Pig::Pig(int pigId, const sf::Texture& texture, sf::Vector2f pos)
    : id(pigId), pos(pos), rotation(0), scale(1.f, 1.f), active(true)
{
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
    sprite.setPosition(pos);
}

// Constructor with sprite, position, and rotation
Pig::Pig(const sf::Sprite& sprite, sf::Vector2f pos, float rotation)
    : sprite(sprite), pos(pos), rotation(rotation), scale(1.f, 1.f), active(true)
{
    this->sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
    this->sprite.setPosition(pos);
    this->sprite.setRotation(rotation);
}

// Default constructor
Pig::Pig() : id(0), pos(0.f, 0.f), rotation(0), scale(1.f, 1.f), active(false)
{
}

// Destructor
Pig::~Pig()
{
}

// Update method
void Pig::update()
{
    if (active)
    {
        sprite.setPosition(pos);
        sprite.setRotation(rotation);
        sprite.setScale(scale);
    }
}

// Contains method
bool Pig::contains(sf::Vector2f point) const
{
    return active && sprite.getGlobalBounds().contains(point);
}


// COLLISIONS METHODS 

// isActive method
bool Pig::isActive() const
{
    return active;
}

// setActive method
void Pig::setActive(bool activeStatus)
{
    active = activeStatus;
}

// getBoundingBox method
sf::FloatRect Pig::getBoundingBox() const
{
    return sprite.getGlobalBounds();
}