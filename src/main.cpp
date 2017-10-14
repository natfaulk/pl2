#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>
#include "utils.hpp"

const double BLOB_RADIUS = 15;

int main(int argc, char const *argv[]) {
  const double COLLISION_BORDER_PX = 0.01;

  Blob mouseBlob;
  mouseBlob.setRadius(20);
  Blob p2(20, 60, 400, 400);
  Point p3;
  Blob p4(5, 10, 0, 0);

  std::cout << mouseBlob.distTo(p2) << '\n';

  sf::RenderWindow window(sf::VideoMode(1280, 800), "PL2");

  window.setFramerateLimit(30);

  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_real_distribution<> dis(0, 1);

  std::vector<Blob> blobs;

  // auto add blobs
  const double BLOBS_TO_AUTO_ADD = 100;
  for (size_t i = 0; i < BLOBS_TO_AUTO_ADD; i++) {
    blobs.push_back(Blob(BLOB_RADIUS, 2.2 * BLOB_RADIUS, 700 + 300 * dis(gen), 300 + 300 * dis(gen)));
  }

  bool jitter = false;

  Blob destTest(BLOB_RADIUS, 2.2 * BLOB_RADIUS, 100, 100);
  destTest.setDestination(1180, 500);
  blobs.push_back(destTest);

  Blob destination(BLOB_RADIUS * 0.5, BLOB_RADIUS * 0.5, 1180, 500);

  while (window.isOpen())
  {
      sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

      sf::Event event;
      while (window.pollEvent(event))
      {
          if (event.type == sf::Event::Closed) window.close();
          if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::R) {
              jitter = !jitter;
            }
          }
          if (event.type == sf::Event::MouseButtonPressed) {
            blobs.push_back(Blob(BLOB_RADIUS, 2.2 * BLOB_RADIUS, mousePosition.x, mousePosition.y));
            std::cout << "blob added" << '\n';
          }
      }


      mouseBlob.x = mousePosition.x;
      mouseBlob.y = mousePosition.y;
      double test = p2.angleTo(mouseBlob);
      // std::cout << "Angle: " << test << '\n';

      window.clear();
      mouseBlob.draw(window);
      p2.draw(window);

      p3 = p2.pointOnCirc(test, 50);
      p4.x = p3.x;
      p4.y = p3.y;
      p4.draw(window);

      destination.draw(window);

      for (int i = 0; i < blobs.size(); i++) {
        if (jitter) {
          double tA = (dis(gen) - 0.5) * 2 * M_PI;
          double tR = dis(gen) * 10;
          blobs.at(i).velocity.setMag(tR);
          blobs.at(i).velocity.setAngle(tA);
        }
        blobs.at(i).tick();

        // if (blobCollision(blobs.at(i), p1)) blobs.at(i).setColor(sf::Color::Red);
        // else blobs.at(i).setColor(sf::Color::Green);
        //
        // if (blobs.at(i).withinSOI(p1)) blobs.at(i).setOutlineColor(sf::Color::Red);
        // else blobs.at(i).setOutlineColor(sf::Color::Green);

        bool tCol = false;
        bool tSoi = false;

        for (int j = 0; j < blobs.size(); j++) {
          if (i != j) {
            if (blobCollision(blobs.at(i), blobs.at(j))) {
              // if blobs exact same position move one across a fraction
              // otherwise move in same direction infinitely
              if (blobs.at(i).x == blobs.at(j).x && blobs.at(i).y == blobs.at(j).y) {
                blobs.at(j).x += COLLISION_BORDER_PX;
              }
              double tca1 = blobs.at(i).angleTo(blobs.at(j));
              double tca2 = blobs.at(j).angleTo(blobs.at(i)); // could just invert tca1
              double tcd = COLLISION_BORDER_PX + ((blobs.at(i).getRadius() + blobs.at(i).getRadius()) - blobs.at(i).distTo(blobs.at(j)));
              blobs.at(i).moveToAR(tca2, tcd / 2);
              blobs.at(j).moveToAR(tca1, tcd / 2);

              tCol = true;
            }

            if (blobs.at(i).withinSOI(blobs.at(j))) tSoi = true;
          }
        }

        if (tCol) blobs.at(i).setColor(sf::Color::Red);
        else blobs.at(i).setColor(sf::Color::Green);

        if (tSoi) blobs.at(i).setOutlineColor(sf::Color::Red);
        else blobs.at(i).setOutlineColor(sf::Color::Green);

        blobs.at(i).draw(window);

      }

      window.display();
  }

  return 0;
}
