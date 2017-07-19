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

double Point::angleTo(Point &p2) {
  return atan2(p2.y - y, p2.x - x);
}

Point Point::pointOnCirc(double angle, double radius) {
  return Point(x + cos(angle) * radius, y + sin(angle) * radius);
}

void Point::moveToAR(double angle, double radius) {
  x += cos(angle) * radius;
  y += sin(angle) * radius;
}

// default point ctor called
Blob::Blob(): mRadius(0), mSOI(0), mColor(sf::Color::Red) {
}

// overloaded point ctor called
Blob::Blob(double _radius, double _soi, double _x, double _y): Point(_x, _y), mRadius(_radius), mSOI(_soi), mColor(sf::Color::Red) {
}

void Blob::draw(sf::RenderWindow &window) {
  sf::CircleShape shape(mRadius);
  shape.setFillColor(mColor);
  shape.setOrigin(mRadius, mRadius);
  shape.setPosition(sf::Vector2f(x, y));
  window.draw(shape);

  shape.setFillColor(sf::Color::Transparent);
  shape.setRadius(mSOI);
  shape.setOrigin(mSOI, mSOI);
  shape.setOutlineColor(sf::Color::Blue);
  shape.setOutlineThickness(5);
  window.draw(shape);
}

void Blob::setRadius(double _radius) {
  mRadius = _radius;
}

void Blob::setColor(sf::Color c) {
  mColor = c;
}

void Blob::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  mColor = sf::Color(r, g, b, a);
}

bool blobCollision(Blob b1, Blob b2) {
  return (b1.distTo(b2) < (b1.mRadius + b2.mRadius));

  // below checks intersection, however one could be inside the other...
  // double tA = b1.angleTo(b2);
  // Point p3 = b1.pointOnCirc(tA, b1.mRadius);
  // if (b2.distTo(p3) < b2.mRadius) return true;
  // else return false;
}
