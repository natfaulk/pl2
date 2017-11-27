#include "pathfinding.hpp"
#include "constants.hpp"

void PF_Astar(Point &_start, Point &_finish) {

}

void PF_Draw(sf::RenderWindow &_window) {
#ifdef DEBUG_DRAW_PF_GRID
  for (int x = 0; x < SCREEN_WIDTH; x += PF_GRID_SIZE) {
    sf::Vertex line[2];
    line[0].position = sf::Vector2f(x, 0);
    line[0].color  = sf::Color::White;
    line[1].position = sf::Vector2f(x, SCREEN_HEIGHT);
    line[1].color = sf::Color::Yellow;
    _window.draw(line, 2, sf::Lines);
  }

  for (int y = 0; y < SCREEN_HEIGHT; y += PF_GRID_SIZE) {
    sf::Vertex line[2];
    line[0].position = sf::Vector2f(0, y);
    line[0].color  = sf::Color::White;
    line[1].position = sf::Vector2f(SCREEN_WIDTH, y);
    line[1].color = sf::Color::Yellow;
    _window.draw(line, 2, sf::Lines);
  }
#endif
}

