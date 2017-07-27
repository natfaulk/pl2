#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>
#include "utils.hpp"

int main(int argc, char const *argv[]) {
  Blob p1;
  p1.setRadius(20);
  Blob p2(20, 60, 400, 400);
  Point p3;
  Blob p4(5, 10, 0, 0);

  std::cout << p1.distTo(p2) << '\n';

  sf::RenderWindow window(sf::VideoMode(1280, 800), "PL2");

  window.setFramerateLimit(30);

  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_real_distribution<> dis(0, 1);

  std::vector<Blob> blobs;

  for (size_t i = 0; i < 10; i++) {
    blobs.push_back(Blob(40, 95, 1280 * dis(gen), 600  * dis(gen)));
  }

  bool jitter = true;

  while (window.isOpen())
  {
      sf::Event event;
      while (window.pollEvent(event))
      {
          if (event.type == sf::Event::Closed) window.close();
          if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::R) {
              jitter = !jitter;
            }
          }
      }

      sf::Vector2i position = sf::Mouse::getPosition(window);
      p1.x = position.x;
      p1.y = position.y;

      double test = p2.angleTo(p1);
      // std::cout << "Angle: " << test << '\n';

      window.clear();
      p1.draw(window);
      p2.draw(window);

      p3 = p2.pointOnCirc(test, 50);
      p4.x = p3.x;
      p4.y = p3.y;
      p4.draw(window);

      for (int i = 0; i < blobs.size(); i++) {
        if (jitter) {
          double tA = (dis(gen) - 0.5) * 2 * M_PI;
          double tR = dis(gen) * 10;
          blobs.at(i).velocity.setMag(tR);
          blobs.at(i).velocity.setAngle(tA);
          blobs.at(i).tick();
        }

        if (blobCollision(blobs.at(i), p1)) blobs.at(i).setColor(sf::Color::Red);
        else blobs.at(i).setColor(sf::Color::Green);

        if (blobs.at(i).withinSOI(p1)) blobs.at(i).setOutlineColor(sf::Color::Red);
        else blobs.at(i).setOutlineColor(sf::Color::Green);

        blobs.at(i).draw(window);

      }

      window.display();
  }

  return 0;
}
