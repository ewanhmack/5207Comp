#pragma once
#ifndef BIRD_H
#define BIRD_H

#include <string>
#include <SFML/Graphics.hpp>
#include "Brick.h" // Include Brick for collision handling
#include "Pig.h"
using namespace sf;
using namespace std;

class Bird
{
public:
    // Constructors
    Bird(int birdID, const Texture& texture, Vector2f pos, float rotation = 0.0f);
    Bird(const Sprite& sprite, Vector2f pos, float rotation = 0.0f);
    Bird();
    ~Bird();

    // Getters and Setters
    float getRotation() const;          // Get the rotation
    void setRotation(float rotation);   // Set the rotation
    Vector2f getPosition() const;       // Get the position
    void setPosition(const Vector2f& pos); // Set the position
    bool isActive() const;              // Get the active state
    void setActive(bool isActive);      // Set the active state
    int get_id() const;                 // Get the bird's ID
    Vector2f getVelocity() const;       // Get the velocity
    Sprite getSprite() const;           // Get the bird's sprite

    // Update function
    void update(std::vector<Brick>& bricks, std::vector<Pig>& pigs); // Pass bricks for collision detection

    sf::FloatRect getBoundingBox() const; // Get the global bounding box of the bird

    void setVelocity(const Vector2f& velocity);
    bool isClicked(const Vector2i& mousePos) const;

    bool checkCollision(const sf::Sprite& other) const;

    bool hasBeenFired = false;

    bool isRolling = false;
	float rollingFriction = 0.9f; // Friction for rolling
	float rollingSpeedThreshold = 0.1f; // Stop rolling at this speed

    void startRolling();
    void updateRolling();


    Sprite BDsprite;     // The sprite for rendering the bird
private:
    
    Vector2f pos;        // Position of the bird
    float rotation;      // Rotation of the bird (in degrees)
    bool active;         // Whether the bird is active
    int id;              // Unique ID for the bird
    Vector2f velocity;   // Velocity of the bird
};

#endif