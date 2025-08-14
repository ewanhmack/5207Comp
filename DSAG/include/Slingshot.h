#pragma once
#ifndef SLINGSHOT_H
#define SLINGSHOT_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <Bird.h>

using namespace sf;
using namespace std;

class Slingshot
{
public:
    // Constructors
    Slingshot(); // Default constructor
    Slingshot(int birdID, const Texture& texture, Vector2f pos, float rotation = 0.0f); // Constructor with rotation
    Slingshot(const Sprite& sprite, Vector2f pos, float rotation = 0.0f);
    ~Slingshot();

    Sprite sprite;

    // Getters and Setters
    Vector2f getPosition() const;               // Get the position
    void setPosition(const Vector2f& pos);      // Set the position
    void setElasticity(float elasticity);       // Set the elasticity of the slingshot
    void setProjectile(Bird* projectile);       // Set the projectile to be launched

    // Interaction Methods
    void startDragging(const Vector2i& mousePos); // Start dragging the slingshot
    void updateDragging(const Vector2i& mousePos); // Update the dragging position
    void release();                                // Release the slingshot to launch the projectile

    // Update and render
    void update();                                 // Update the slingshot state
    void render(RenderWindow& window);            // Render the slingshot
    void drawTrajectory(RenderWindow& window);    // Draw the trajectory line 

private:
    Sprite SlingshotSprite;   // The sprite for rendering the slingshot
    Vector2f initialPosition; // The initial position of the slingshot
    Vector2f currentPosition; // Current position during dragging
    Vector2f force;           // Force applied to the projectile
    float elasticity;         // Elasticity factor for the slingshot
    bool isDragging;          // Whether the slingshot is being dragged
    Bird* currentProjectile;  // The projectile to be launched

    sf::RectangleShape leftRope;   // Rope from the left arm
    sf::RectangleShape rightRope;  // Rope from the right arm

    Vector2f leftAnchor;  // Anchor point for the left rope
    Vector2f rightAnchor; // Anchor point for the right rope

    static constexpr float maxDragDistance = 90.0f; // Maximum drag distance
    std::vector<sf::Vertex> trajectoryPoints; // Trajectory line
};

#endif