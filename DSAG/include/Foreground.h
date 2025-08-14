#pragma once
#include <SFML/Graphics.hpp>

class Foreground
{
public:
    // Constructors
    Foreground();
    Foreground(int ForegroundId, const sf::Texture& texture, sf::Vector2f pos = sf::Vector2f(0, 0));
    Foreground(const sf::Sprite& sprite, sf::Vector2f pos = sf::Vector2f(0, 0), float rotation = 0.0f);
    ~Foreground();

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
};