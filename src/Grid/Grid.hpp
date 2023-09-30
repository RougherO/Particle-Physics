#pragma once
#include <SFML/Graphics.hpp>
#include "../Particles/Particles.hpp"
#include <vector>

struct Grid : sf::Drawable {
    size_t divs { 50 };
    size_t rows {};
    size_t cols {};
    std::vector<std::vector<Particles*>> gridOfParticles;

    Grid(const sf::Vector2u& size);

    std::pair<size_t, size_t> getIndex(Particles* particle) const;

    void addParticle(
        size_t row,
        size_t col,
        Particles* particle);

    void removeParticle(
        size_t row,
        size_t col,
        std::vector<Particles*>::iterator particle);

    void updateGrid();

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};