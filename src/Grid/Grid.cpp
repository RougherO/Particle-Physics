#include "Grid.hpp"
#include <cmath>
#include <utility>

Grid::Grid(const sf::Vector2u& size)
    : rows { size.y / divs }
    , cols { size.x / divs }
    , gridOfParticles { rows * cols, std::vector<Particles*> {} }
{
}

std::pair<size_t, size_t> Grid::getIndex(Particles* particle) const
{
    auto pos = particle->getPosition();
    size_t row = std::floor(pos.y / divs);
    size_t col = std::floor(pos.x / divs);
    return { row, col };
}

void Grid::addParticle(
    size_t row,
    size_t col,
    Particles* particle)
{
    if (row < rows && col < cols)
        gridOfParticles[row * cols + col].push_back(particle);
}

void Grid::removeParticle(
    size_t row,
    size_t col,
    std::vector<Particles*>::iterator particle)
{
    std::iter_swap(particle, gridOfParticles[row * cols + col].end() - 1);
    gridOfParticles[row * cols + col].pop_back();
}

void Grid::updateGrid()
{
    for (size_t row {}; row < rows; ++row) {

        for (size_t col {}; col < cols; ++col) {

            for (auto particleIter = gridOfParticles[row * cols + col].begin(); particleIter < gridOfParticles[row * cols + col].end();) {

                // all particle position updated in Physics
                // Getting all particle positions after they have been updated

                (*particleIter)->setPosition((*particleIter)->Pos);
                auto [newRow, newCol] = getIndex(*particleIter);
                if (newRow != row || newCol != col) {
                    addParticle(newRow, newCol, *particleIter);
                    removeParticle(row, col, particleIter);
                } else {
                    ++particleIter;
                }
            }
        }
    }
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (size_t row {}; row < rows; ++row) {

        for (size_t col {}; col < cols; ++col) {

            // auto rect = sf::RectangleShape(sf::Vector2f(divs, divs));
            // rect.setFillColor(sf::Color::Black);
            // rect.setOutlineColor(sf::Color::White);
            // rect.setOutlineThickness(1);
            // rect.setPosition(col * divs, row * divs);
            // target.draw(rect);

            for (auto particle : gridOfParticles[row * cols + col]) {
                target.draw(*particle, states);
            }
        }
    }
}
