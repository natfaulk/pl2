#ifndef BLOB_HPP
#define BLOB_HPP

#include <SFML/Graphics.hpp>
#include <cstdint>
#include "utils.hpp"

class Blob: public Point {
public:
  Blob();
  Blob(double _radius, double _soi, double _x, double _y);
  void draw(sf::RenderWindow &window);
  void setRadius(double _radius);
  void setColor(sf::Color c);
  void setOutlineColor(sf::Color c);
  void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
  void setOutlineColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
  void tick(void);
  bool withinSOI(Blob other);
  double getRadius(void);
  void setDestination(double _x, double _y);

  Point velocity;

  friend bool blobCollision(Blob &b1, Blob &b2);
private:
  double mRadius;
  double mSOI; // sphere of influence
  sf::Color mColor;
  sf::Color mOutlineColor;

  bool mHasDestination;
  Point mDestination;
};

#endif /* end of include guard: BLOB_HPP */