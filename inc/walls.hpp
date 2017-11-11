#ifndef WALLS_HPP
#define WALLS_HPP

#include "utils.hpp"
#include <SFML/Graphics.hpp>

class Wall: public Point {
public:
  Wall();
  Wall(double _x, double _y, double _w, double _h);
  void draw(sf::RenderWindow &window);
  double w;
  double h;
private:
  sf::Color mColor;
};

bool blobWallCollision(Blob &b1, Wall &w1);

#endif /* end of include guard: WALLS_HPP */
