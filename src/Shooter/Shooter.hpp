#include <SFML/Graphics.hpp>
#include <cmath>
#include <numbers>

struct Shooter : sf::Drawable {
    sf::Vector2f position {};
    sf::RectangleShape cannon { sf::Vector2f(50.f, 10.f) };
    sf::CircleShape wheel1 { 10.f };
    sf::CircleShape wheel2 { 10.f };
    float wheelDist { 10.f };

    Shooter();
    Shooter(float x, float y);
    Shooter(const sf::Vector2f& pos);

    void setAngleinRadians(float angle);
    void setAngleinRadians(float x, float y);
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f& pos);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};