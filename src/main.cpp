#include <iostream>
#include <SFML/Graphics.hpp>
#include "utils.hpp"

int main(int argc, char const *argv[]) {
  Blob p1;
  Blob p2(1, 1);

  std::cout << p1.distTo(p2) << '\n';

  sf::RenderWindow window(sf::VideoMode(1280, 800), "PL2");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);
  shape.setOrigin(100.f, 100.f);

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
      shape.setPosition(sf::Vector2f(position.x, position.y));
      std::cout << position.x << "," << position.y << '\n';
      window.clear();
      window.draw(shape);
      window.display();
  }

  return 0;
}
