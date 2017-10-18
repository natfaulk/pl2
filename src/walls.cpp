#include "walls.hpp"

static const sf::Color DEFAULT_WALL_COLOR = sf::Color::Magenta;

// uses default point ctor
Wall::Wall(): w(0), h(0), mColor(DEFAULT_WALL_COLOR) {
}

Wall::Wall(double _x, double _y, double _w, double _h):
  Point(_x, _y),
  w(_w),
  h(_h),
  mColor(DEFAULT_WALL_COLOR)
{}

void Wall::draw(sf::RenderWindow &window) {
  sf::RectangleShape rectangle(sf::Vector2f(w, h));
  rectangle.setFillColor(mColor);
  rectangle.setOrigin(w / 2, h / 2);
  rectangle.setPosition(sf::Vector2f(x, y));
  window.draw(rectangle);
}
