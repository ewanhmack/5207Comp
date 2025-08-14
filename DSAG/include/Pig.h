#pragma once
#include <SFML/Graphics.hpp>

class Pig
{
public:
    // Constructors
    Pig();
    Pig(int pigID, const sf::Texture& texture, sf::Vector2f pos = sf::Vector2f(0, 0));
    Pig(const sf::Sprite& sprite, sf::Vector2f pos = sf::Vector2f(0, 0), float rotation = 0.0f);
    ~Pig();

    // Attributes
    int id;
    sf::Sprite sprite;
    sf::Vector2f pos;
    sf::Vector2f scale;
    float rotation;
    bool active;

    // Methods
    void update();
    bool contains(sf::Vector2f point) const;

    bool isActive() const;                 // Check if pig is active
    void setActive(bool activeStatus);     // Set pig active/inactive
    sf::FloatRect getBoundingBox() const;  // Get the bounding box for collision detection

	bool Scored = false; // True if the pig has been hit
};