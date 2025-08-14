#include "Slingshot.h"
#include <cmath> // For math operations
#include <iostream>

// Default constructor
Slingshot::Slingshot()
    : initialPosition(0.0f, 0.0f), currentPosition(0.0f, 0.0f), elasticity(1.0f), isDragging(false), currentProjectile(nullptr),
    leftAnchor(0.0f, 0.0f), rightAnchor(0.0f, 0.0f)
{
    // Initialize the ropes
    leftRope.setSize(sf::Vector2f(8.5f, 0.0f));
    leftRope.setFillColor(sf::Color(139, 69, 19));
    leftRope.setOrigin(2.5f, -2.0f); 

    rightRope.setSize(sf::Vector2f(8.5f, 0.0f));
    rightRope.setFillColor(sf::Color(139, 69, 19));
    rightRope.setOrigin(2.5f, 0.0f);
}

// Constructor with sprite and position
Slingshot::Slingshot(const sf::Sprite& sprite, sf::Vector2f pos, float rotation)
    : sprite(sprite), initialPosition(pos + sf::Vector2f(0.f, -60.f)),
    currentPosition(pos + sf::Vector2f(0.f, -60.f)), elasticity(1.2f), isDragging(false), currentProjectile(nullptr)
{
    this->sprite.setPosition(pos);
    this->sprite.setRotation(rotation);

    sf::FloatRect bounds = this->sprite.getLocalBounds();
    this->sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    // Adjust the anchor points to match the arms of the slingshot
    leftAnchor = pos + sf::Vector2f(-15.f, -63.f);  // Adjust these values to match the left arm
    rightAnchor = pos + sf::Vector2f(27.f, -65.f);  // Adjust these values to match the right arm

    // Initialize the ropes
    leftRope.setSize(sf::Vector2f(8.0f, 0.0f)); 
    leftRope.setFillColor(sf::Color(139, 69, 19)); 
    leftRope.setOrigin(2.5f, 0.0f); 

    rightRope.setSize(sf::Vector2f(8.0f, 0.0f)); 
    rightRope.setFillColor(sf::Color(139, 69, 19));
    rightRope.setOrigin(2.5f, 0.0f); 
}

// Destructor
Slingshot::~Slingshot()
{
    // No dynamic memory or resources to release
}

// Update the slingshot state
void Slingshot::update()
{
    sf::Vector2f anchorPoint = isDragging ? currentPosition : initialPosition;

    // Update the left rope
    sf::Vector2f leftVector = anchorPoint - leftAnchor;
    float leftLength = std::sqrt(leftVector.x * leftVector.x + leftVector.y * leftVector.y);
    leftRope.setSize(sf::Vector2f(5.0f, leftLength));
    leftRope.setRotation(std::atan2(leftVector.y, leftVector.x) * 180 / 3.14159f - 90.0f);
    leftRope.setPosition(leftAnchor);

    // Update the right rope
    sf::Vector2f rightVector = anchorPoint - rightAnchor;
    float rightLength = std::sqrt(rightVector.x * rightVector.x + rightVector.y * rightVector.y);
    rightRope.setSize(sf::Vector2f(5.0f, rightLength));
    rightRope.setRotation(std::atan2(rightVector.y, rightVector.x) * 180 / 3.14159f - 90.0f);
    rightRope.setPosition(rightAnchor);
}

// Draw the slingshot and the projectile
void Slingshot::render(sf::RenderWindow& window)
{
    // Draw the ropes first
    window.draw(leftRope);
    window.draw(rightRope);

    // Draw the slingshot sprite
    window.draw(sprite);

    // Draw the projectile if it exists
    if (currentProjectile)
    {
        window.draw(currentProjectile->BDsprite); // Draw the bird's sprite
    }
}

// Update dragging
void Slingshot::updateDragging(const sf::Vector2i& mousePos)
{
    if (this->isDragging)
    {
        // Convert mouse position to world coordinates
        sf::Vector2f dragPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        // Calculate the vector between the initial and drag positions
        sf::Vector2f dragVector = dragPosition - this->initialPosition;

        // Calculate the length of the drag vector
        float dragDistance = std::sqrt((dragVector.x * dragVector.x) + (dragVector.y * dragVector.y));

        // If the drag distance exceeds the maximum, cap it
        if (dragDistance > maxDragDistance)
        {
            dragVector /= dragDistance; // Normalize
            dragVector *= maxDragDistance; // Scale
            dragPosition = this->initialPosition + dragVector; // Set new drag position
        }

        // Update current position
        this->currentPosition = dragPosition;

        // Update the projectile's position if it exists
        if (this->currentProjectile)
        {
            this->currentProjectile->setPosition(this->currentPosition);
        }
    }
}

// Release the slingshot
void Slingshot::release()
{
    if (this->isDragging && this->currentProjectile)
    {
        this->isDragging = false;

        // Calculate the drag vector (direction and magnitude)
        sf::Vector2f dragVector = this->initialPosition - this->currentPosition; // Drag direction
        float dragDistance = std::sqrt((dragVector.x * dragVector.x) + (dragVector.y * dragVector.y)); // Drag length

        // Apply a larger scaling factor to amplify the force
        const float scalingFactor = 0.2f; // Increased scaling factor for stronger velocity
        this->force = dragVector * scalingFactor;

        // Debugging output
        std::cout << "Slingshot Released!" << std::endl;
        std::cout << "Drag Distance: " << dragDistance << std::endl;
        std::cout << "Force applied: X = " << this->force.x << ", Y = " << this->force.y << std::endl;

        // Apply the force to the bird
        if (this->currentProjectile)
        {
            this->currentProjectile->setVelocity(this->force); // Set bird's velocity
            this->currentProjectile->setActive(true);         // Activate the bird
			this->currentProjectile->hasBeenFired = true;     // Mark the bird as fired

            // Debug bird initial velocity
            std::cout << "Bird Velocity: X = " << this->currentProjectile->getVelocity().x
                << ", Y = " << this->currentProjectile->getVelocity().y << std::endl;
        }
    }
}

void Slingshot::setProjectile(Bird* projectile)
{
    this->currentProjectile = projectile;
    if (projectile)
    {
        projectile->setPosition(this->initialPosition + sf::Vector2f(0.f, -20.f));
    }
}

void Slingshot::startDragging(const sf::Vector2i& mousePos)
{
    this->isDragging = true;
    this->currentPosition = Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

void Slingshot::drawTrajectory(sf::RenderWindow& window)
{
    if (this->isDragging && this->currentProjectile)
    {
        // Simulate trajectory points
        std::vector<sf::Vector2f> trajectoryPoints;

        sf::Vector2f simulatedPosition = this->currentPosition;
        sf::Vector2f simulatedVelocity = (this->initialPosition - this->currentPosition) * this->elasticity;
        const float gravity = 5.0f;
        const float timeStep = 0.1f;
        const int maxSteps = 50;

        for (int i = 0; i < maxSteps; ++i)
        {
            sf::Vector2f nextPosition = simulatedPosition + simulatedVelocity * timeStep;
            simulatedVelocity.y += gravity * timeStep;
            trajectoryPoints.push_back(nextPosition);
            simulatedPosition = nextPosition;
        }

        // Draw the trajectory as a thicker dotted line
        const float dotRadius = 4.0f; // Thickness of each dot
        const int dotSpacing = 2;     // Space between dots (skip every nth point)
        sf::Color dotColour(255, 255, 240); // Custom RGB colour of the dots

        for (size_t i = 0; i < trajectoryPoints.size(); i += dotSpacing)
        {
            sf::CircleShape dot(dotRadius);
            dot.setPosition(trajectoryPoints[i]);
            dot.setOrigin(dotRadius, dotRadius); // Center the dot
            dot.setFillColor(dotColour);  // Set the color of the dots
            window.draw(dot);
        }
    }
}