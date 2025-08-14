#include "Bird.h"
#include "Pig.h"
#include <iostream> // For debugging output

// Constructor with position and rotation
Bird::Bird(int birdID, const sf::Texture& texture, sf::Vector2f pos, float rotation)
    : id(birdID), pos(pos), rotation(rotation), active(false), velocity(0.0f, 0.0f)
{
    this->BDsprite.setTexture(texture);          // Set the texture of the bird sprite
    this->BDsprite.setPosition(pos);             // Set the position of the sprite
    this->BDsprite.setRotation(rotation);        // Set the rotation of the sprite

    // Center the origin of the sprite for proper positioning
    sf::FloatRect bounds = this->BDsprite.getLocalBounds();
    this->BDsprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

// Constructor with sprite
Bird::Bird(const sf::Sprite& sprite, sf::Vector2f pos, float rotation)
    : BDsprite(sprite), pos(pos), rotation(rotation), active(false), velocity(0.0f, 0.0f)
{
    this->BDsprite.setPosition(pos);             // Set position of the sprite
    this->BDsprite.setRotation(rotation);        // Set rotation of the sprite

    // Center the origin of the sprite for proper positioning
    sf::FloatRect bounds = this->BDsprite.getLocalBounds();
    this->BDsprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

// Default constructor
Bird::Bird() : id(0), pos(0.0f, 0.0f), rotation(0.0f), active(false), velocity(0.0f, 0.0f)
{
    // Default initialization
}

// Destructor
Bird::~Bird()
{
    // No dynamic memory to clean up
}

// Getter for rotation
float Bird::getRotation() const
{
    return this->rotation;
}

// Setter for rotation
void Bird::setRotation(float rotation)
{
    this->rotation = rotation;
    this->BDsprite.setRotation(rotation); // Update the sprite's rotation
}

// Getter for position
sf::Vector2f Bird::getPosition() const
{
    return this->pos;
}

// Setter for position
void Bird::setPosition(const sf::Vector2f& position)
{
    this->pos = position;
    this->BDsprite.setPosition(position); // Update the sprite's position
}

// Getter for active state
bool Bird::isActive() const
{
    return this->active;
}

// Setter for active state
void Bird::setActive(bool isActive)
{
    this->active = isActive;
}

// Getter for ID
int Bird::get_id() const
{
    return this->id;
}

// Getter for velocity
sf::Vector2f Bird::getVelocity() const
{
    return this->velocity;
}

// Setter for velocity
void Bird::setVelocity(const sf::Vector2f& velocity)
{
    this->velocity = velocity;
}

// Update function
void Bird::update(std::vector<Brick>& bricks, std::vector<Pig>& pigs)
{
    if (active)
    {
        // Move the bird
        this->pos += this->velocity;

        // Simulate gravity
        const float gravity = 9.8f;
        this->velocity.y += gravity * 0.016f; // Assuming 60 FPS (1/60 seconds per frame)

        // Collision detection with bricks
        for (Brick& brick : bricks)
        {
            if (brick.isActive() && this->checkCollision(brick.getSprite()))
            {
                std::cout << "Bird collided with a brick!" << std::endl;
                brick.setActive(false); // Deactivate the brick
                //this->active = false;   // Stop the bird
                if (!this->isRolling) // Only stop the bird if not rolling
                {
                    this->startRolling();
                }
				else 
                {
					this->updateRolling();
				}
                //this->velocity = sf::Vector2f(0.0f, 0.0f);
                return; // Stop further updates
            }
        }

        // Collision detection with pigs
        for (Pig& pig : pigs)
        {
            if (pig.isActive() && this->checkCollision(pig.sprite))
            {
                std::cout << "Bird collided with a pig!" << std::endl;
                pig.setActive(false); // Deactivate the pig
                //this->active = false; // Stop the bird
                if (!this->isRolling) // Only stop the bird if not rolling
                {
                    this->startRolling();
                }
                else
                {
                    this->updateRolling();
                }
                //this->velocity = sf::Vector2f(0.0f, 0.0f);
                return; // Stop further updates
            }
        }

        // Bounds check: stops bird if it hits the ground
        const float groundLevel = 625.0f; // Current max height of foreground
        if (this->pos.y > groundLevel)
        {
            this->pos.y = groundLevel;
            //this->velocity = sf::Vector2f(0.0f, 0.0f); // Stop bird movement
            if (!this->isRolling) // Only stop the bird if not rolling
            {
                this->startRolling();
            }
            else
            {
                this->updateRolling();
            }
            std::cout << "Bird has hit the ground. Stopping movement." << std::endl;
        }

        // Update the bird's position and rotation
        this->BDsprite.setPosition(pos);
        this->BDsprite.setRotation(rotation);

        // Debugging output for bird state
        //std::cout << "Bird Position: X = " << this->pos.x << ", Y = " << this->pos.y << std::endl;
        //std::cout << "Bird Velocity: X = " << this->velocity.x << ", Y = " << this->velocity.y << std::endl;
    }
}

// Get bounding box
sf::FloatRect Bird::getBoundingBox() const
{
    return this->BDsprite.getGlobalBounds();
}

// Get sprite
Sprite Bird::getSprite() const
{
    return this->BDsprite;
}

// Check if the bird is clicked
bool Bird::isClicked(const sf::Vector2i& mousePos) const
{
    // Convert mouse position to world coordinates
    sf::Vector2f worldPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    // Check if the mouse position is within the bounds of the bird sprite
    return this->BDsprite.getGlobalBounds().contains(worldPos);
}

bool Bird::checkCollision(const sf::Sprite& other) const
{
    // Skip collision detection if the bird is not moving
    if (this->velocity == sf::Vector2f(0.0f, 0.0f))
    {
        return false;
    }

    // Check if the bird's sprite intersects with the other sprite (currently only set up for bricks)
    return this->BDsprite.getGlobalBounds().intersects(other.getGlobalBounds());
}

void Bird::startRolling()
{
	this->isRolling = true;
	this->velocity.y = 0.0f; // Stop vertical movement
}

void Bird::updateRolling()
{
    // Apply friction to reduce velocity
    this->velocity.x *= rollingFriction;

    // Stop rolling if the speed is below the threshold
    if (std::abs(this->velocity.x) < rollingSpeedThreshold)
    {
        this->velocity.x = 0.0f;
        this->isRolling = false; // Stop rolling
        this->setActive(false); // Mark the bird as inactive
    }

    // Update the bird's position
    this->pos.x += this->velocity.x;

    // Apply rotation to simulate rolling
    this->rotation += this->velocity.x * 5.0f; // Adjust rotation speed as needed
    this->setRotation(this->rotation);
}
