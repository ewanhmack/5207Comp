#include "Brick.h"

// Constructor with position and rotation
Brick::Brick(const Sprite& bsprite, const Vector2f& bPos, float bRotation)
    : BrickSprite(bsprite), BPos(bPos), rotation(bRotation), active(true) // Initialize as active
{
    this->BrickSprite.setPosition(bPos);             // Set position of the sprite
    this->BrickSprite.setRotation(bRotation);        // Set rotation of the sprite

    // Center the origin of the sprite for proper positioning
    sf::FloatRect bounds = this->BrickSprite.getLocalBounds();
    this->BrickSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

// Default constructor
Brick::Brick() : BPos(0.0f, 0.0f), rotation(0.0f), active(true) // Initialize as active
{
    // Default initialization
}

// Destructor
Brick::~Brick()
{
    // No dynamic memory to clean up
}

// Getter for rotation
float Brick::getRotation() const
{
    return this->rotation;
}

// Setter for rotation
void Brick::setRotation(float bRotation)
{
    this->rotation = bRotation;
    this->BrickSprite.setRotation(bRotation); // Update the sprite's rotation
}

// Getter for position
Vector2f Brick::getPosition() const
{
    return this->BPos;
}

// Setter for position
void Brick::setPosition(const Vector2f& bPos)
{
    this->BPos = bPos;
    this->BrickSprite.setPosition(bPos); // Update the sprite's position
}

// Getter for active state
bool Brick::isActive() const
{
    return this->active;
}

// Setter for active state
void Brick::setActive(bool active)
{
    this->active = active;
}

// Get bounding box
sf::FloatRect Brick::getBoundingBox() const
{
    return this->BrickSprite.getGlobalBounds();
}

Sprite Brick::getSprite() const
{
    return this->BrickSprite; // Return the BrickSprite
}