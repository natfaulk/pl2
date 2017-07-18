#include "utils.hpp"
#include <cmath>

Point::Point(): x(0), y(0) {
}

Point::Point(double _x, double _y): x(_x), y(_y) {
}

double Point::distTo(Point& p2) {
  double tdx = x - p2.x;
  double tdy = y - p2.y;
  return sqrt(tdx*tdx + tdy*tdy);
}

double angleTo(Point &p2) {
  return 0;
}

// default point ctor called
Blob::Blob(): mRadius(0), mSOI(0) {
}

// overloaded point ctor called
Blob::Blob(double _radius, double _x, double _y): Point(_x, _y), mRadius(_radius), mSOI(0) {
}

void Blob::draw(sf::RenderWindow &window) {
  sf::CircleShape shape(mRadius);
  shape.setFillColor(sf::Color::Red);
  shape.setOrigin(mRadius, mRadius);
  shape.setPosition(sf::Vector2f(x, y));
  window.draw(shape);
}

void Blob::setRadius(double _radius) {
  mRadius = _radius;
}
