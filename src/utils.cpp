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

double Point::getMag(void) {
  return sqrt(x*x + y*y);
}

void Point::setMag(double mag) {
  double tAng = this->getAngle();
  x = cos(tAng) * mag;
  y = sin(tAng) * mag;
}

double Point::getAngle(void) {
  return atan2(y, x);
}

void Point::setAngle(double angle) {
  double tMag = this->getMag();
  x = cos(angle) * tMag;
  y = sin(angle) * tMag;
}
