#include <iostream>
#include <SFML/Graphics.hpp>
#include "utils.hpp"

int main(int argc, char const *argv[]) {
  Blob p1;
  p1.setRadius(20);
  Blob p2(20, 400, 400);

  std::cout << p1.distTo(p2) << '\n';

  sf::RenderWindow window(sf::VideoMode(1280, 800), "PL2");

  window.setFramerateLimit(60);

  while (window.isOpen())
  {
      sf::Event event;
      while (window.pollEvent(event))
      {
          if (event.type == sf::Event::Closed)
              window.close();
      }

      sf::Vector2i position = sf::Mouse::getPosition(window);
      p1.x = position.x;
      p1.y = position.y;

      double test = p2.angleTo(p1);
      std::cout << "Angle: " << test << '\n';

      window.clear();
      p1.draw(window);
      p2.draw(window);
      window.display();
  }

  return 0;
}
