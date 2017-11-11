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

bool blobWallCollision(Blob &b1, Wall &w1) {
  double wXmin = (w1.x - (w1.w / 2));
  double wXmax = (w1.x + (w1.w / 2));
  double wYmin = (w1.y - (w1.h / 2));
  double wYmax = (w1.y + (w1.h / 2));
  double tempRadius = b1.getRadius();

  if (
    (b1.x + tempRadius) < wXmin
    || (b1.y + tempRadius) < wYmin
    || (b1.x - tempRadius) > wXmax
    || (b1.y - tempRadius) > wYmax
    ) return false;
  else
    return true;
  // return (b1.distTo(b2) < (b1.mRadius + b2.mRadius));

  // below checks intersection, however one could be inside the other...
  // double tA = b1.angleTo(b2);
  // Point p3 = b1.pointOnCirc(tA, b1.mRadius);
  // if (b2.distTo(p3) < b2.mRadius) return true;
  // else return false;
}

// a bit hacky but a nice non trig solution
// on second thoughts was a lazy but quite efficient solution
// isnt quite correct implementation but will do for now
natfaulk::Direction blobWallCollisionDirection(Blob &b1, Wall &w1) {
  double h_2 = w1.h / 2;
  double w_2 = w1.w / 2;
  double xdiff = w1.x - b1.x;
  double ydiff = w1.y - b1.y;
  double xyProp = w1.h / w1.w;
  xdiff *= xyProp;
  double xProp = xdiff / (h_2);
  double yProp = ydiff / (w_2 * xyProp);
  
  if (xdiff > 0) {
    if (ydiff > 0) {
      if (yProp > xProp) return natfaulk::UP;
      else return natfaulk::LEFT;
    } else {
      if (-yProp > xProp) return natfaulk::DOWN;
      else return natfaulk::LEFT;
    }
  } else {
    if (ydiff > 0) {
      if (yProp > -xProp) return natfaulk::UP;
      else return natfaulk::RIGHT;
    } else {
      if (-yProp > -xProp) return natfaulk::DOWN;
      else return natfaulk::RIGHT;
    }
  }
}