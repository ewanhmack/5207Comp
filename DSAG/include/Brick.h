#pragma once
#ifndef BRICK_H
#define BRICK_H

#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Brick
{
public:
    // Constructors
    Brick(const Sprite& bsprite, const Vector2f& bPos, float bRotation = 0.0f); // Constructor with rotation
    Brick();
    ~Brick();

    // Getters and Setters
    float getRotation() const;              // Get the rotation
    void setRotation(float bRotation);      // Set the rotation
    Vector2f getPosition() const;           // Get the position
    void setPosition(const Vector2f& bPos); // Set the position
    bool isActive() const;                  // Check if the brick is active
    void setActive(bool active);            // Set the active state

    bool Scored = false;

    Sprite getSprite() const;

    sf::FloatRect getBoundingBox() const; // Get the global bounding box of the brick

    // ------- Data --------
    Sprite BrickSprite;  // The sprite for rendering the brick
    Vector2f BPos;       // Position of the brick
    float rotation;      // Rotation of the brick (in degrees)



private:
    bool active;         // Whether the brick is active (visible)
};

#endif