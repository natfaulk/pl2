#include "blob.hpp"
#include "constants.hpp"

// default point ctor called
Blob::Blob(): mRadius(0), mSOI(0), mColor(sf::Color::Red) {
}

// overloaded point ctor called
Blob::Blob(double _radius, double _soi, double _x, double _y):
  Point(_x, _y),
  mRadius(_radius),
  mSOI(_soi),
  mColor(sf::Color::Red),
  mHasDestination(false)
{}

void Blob::draw(sf::RenderWindow &window) {
  sf::CircleShape shape(mRadius);
  shape.setFillColor(mColor);
  shape.setOrigin(mRadius, mRadius);
  shape.setPosition(sf::Vector2f(x, y));
  window.draw(shape);

#ifdef DEBUG_DRAW_SOI
  shape.setFillColor(sf::Color::Transparent);
  shape.setRadius(mSOI);
  shape.setOrigin(mSOI, mSOI);
  shape.setOutlineColor(mOutlineColor);
  shape.setOutlineThickness(5);
  window.draw(shape);
#endif

#ifdef DEBUG_DRAW_BLOB_WAYPOINT
  if (mHasDestination) {
    sf::Vertex line[2];
    line[0].position = sf::Vector2f(x, y);
    line[0].color  = sf::Color::White;
    line[1].position = sf::Vector2f(mDestination.x, mDestination.y);
    line[1].color = sf::Color::White;
    window.draw(line, 2, sf::Lines);
  }
#endif
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

void Blob::setOutlineColor(sf::Color c) {
  mOutlineColor = c;
}

void Blob::setOutlineColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  mOutlineColor = sf::Color(r, g, b, a);
}

bool Blob::withinSOI(Blob other) {
  return (this->distTo(other) < (this->mSOI + other.mRadius));
}

bool blobCollision(Blob &b1, Blob &b2) {
  return (b1.distTo(b2) < (b1.mRadius + b2.mRadius));

  // below checks intersection, however one could be inside the other...
  // double tA = b1.angleTo(b2);
  // Point p3 = b1.pointOnCirc(tA, b1.mRadius);
  // if (b2.distTo(p3) < b2.mRadius) return true;
  // else return false;
}

void Blob::tick(void) {
  const double DEST_MARGIN_ERROR = 1;
  const double MAX_VELOCITY = 5;
  const double ACCELERATION = 1;

  if (mHasDestination) {

    double tempMag = this->velocity.getMag();
    if (tempMag < MAX_VELOCITY) {
      tempMag+= ACCELERATION;
      if (tempMag > MAX_VELOCITY) tempMag = MAX_VELOCITY;
      velocity.setMag(tempMag);
    }

    double tempDist = this->distTo(mDestination);
    if (tempDist < MAX_VELOCITY) {
      velocity.setMag(tempDist);
    }

    velocity.setAngle(this->angleTo(this->mDestination));
  }

  x += velocity.x;
  y += velocity.y;
  if (this->distTo(mDestination) < DEST_MARGIN_ERROR) {
    mHasDestination = false;
    velocity = Point();
  }
}

double Blob::getRadius(void) {
  return mRadius;
}

void Blob::setDestination(double _x, double _y) {
  mHasDestination = true;
  mDestination = Point(_x, _y);
}