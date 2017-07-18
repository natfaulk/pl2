#ifndef UTILS_HPP
#define UTILS_HPP

class Point {
public:
  Point();
  Point(double _x, double _y);
  double distTo(Point& p2);
  double angleTo(Point &p2);
  double x;
  double y;
};

class Blob: public Point {
public:
  Blob();
  Blob(double _x, double _y);
private:
  double mRadius;
  double mSOI; // sphere of influence
};

#endif /* end of include guard: UTILS_HPP */
