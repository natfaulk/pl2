#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics.hpp>
#include <cstdint>

class Point {
public:
  Point();
  Point(double _x, double _y);
  double distTo(Point& p2);
  double angleTo(Point &p2);
  Point pointOnCirc(double angle, double radius);
  void moveToAR(double angle, double radius);
  double getMag(void);
  void setMag(double);
  double getAngle(void);
  void setAngle(double);

  double x;
  double y;
};

#endif /* end of include guard: UTILS_HPP */
