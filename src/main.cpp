#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>
#include "utils.hpp"
#include "walls.hpp"
#include "blob.hpp"
#include "buildWorld.hpp"
#include "constants.hpp"
#include "pathfinding.hpp"

const double BLOB_RADIUS = 15;

int main(int argc, char const *argv[]) {
  const double COLLISION_BORDER_PX = 0.01;

  Blob mouseBlob;
  mouseBlob.setRadius(20);
  Blob p2(20, 60, 400, 400);
  Point p3;
  Blob p4(5, 10, 0, 0);

  std::cout << mouseBlob.distTo(p2) << '\n';

  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), WINDOW_TITLE);

  window.setFramerateLimit(30);

  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_real_distribution<> dis(0, 1);

  std::vector<Blob> blobs;
  std::vector<Wall> walls;

  buildWorld(walls);

  // auto add blobs
  const double BLOBS_TO_AUTO_ADD = 20;
  for (size_t i = 0; i < BLOBS_TO_AUTO_ADD; i++) {
    blobs.push_back(Blob(BLOB_RADIUS, 2.2 * BLOB_RADIUS, 700 + 300 * dis(gen), 250 + 300 * dis(gen)));
  }

  bool jitter = false;

  // Blob destTest(BLOB_RADIUS, 2.2 * BLOB_RADIUS, 100, 100);
  // destTest.setDestination(1180, 800);
  // blobs.push_back(destTest);

  for (size_t i = 0; i < 50; i++) {
    Blob tempBlob(BLOB_RADIUS, 2.2 * BLOB_RADIUS, 100, 100);
    tempBlob.setDestination(1180, 700);
    blobs.push_back(tempBlob);
  }

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

      for (int i = 0; i < walls.size(); i++) {
        walls.at(i).draw(window);
      }

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

        for (int j = 0; j < walls.size(); j++) {
          if (blobWallCollision(blobs.at(i), walls.at(j))) {
            
          #ifdef DEBUG_DRAW_BLOB_WALL_COLLISION
            blobs.at(i).setColor(sf::Color::Blue);
          #endif

            natfaulk::Direction tempDir = blobWallCollisionDirection(blobs.at(i), walls.at(j));

            // move blob away from wall
            // double tempAngle = walls.at(j).angleTo(blobs.at(i));
            Point tempPoint(blobs.at(i).x, blobs.at(i).y);
            
          #ifdef DEBUG_DRAW_WALL_NORMAL
            sf::Vertex line[2];
            line[0].position = sf::Vector2f(tempPoint.x, tempPoint.y);
            line[0].color  = sf::Color::White;
          #endif

            double tempRadius = blobs.at(i).getRadius();

            if (tempDir == natfaulk::LEFT) {
              tempPoint.moveToAR(M_PI, 50);
              blobs.at(i).moveToAR(M_PI, tempRadius + COLLISION_BORDER_PX + (walls.at(j).w / 2 - (walls.at(j).x - blobs.at(i).x)));
            } else if (tempDir == natfaulk::RIGHT) {
              tempPoint.moveToAR(0, 50);
              blobs.at(i).moveToAR(0, tempRadius + COLLISION_BORDER_PX + (walls.at(j).w / 2 - (blobs.at(i).x - walls.at(j).x)));              
            } else if (tempDir == natfaulk::UP) {
              tempPoint.moveToAR(-M_PI_2, 50);
              blobs.at(i).moveToAR(-M_PI_2, tempRadius + COLLISION_BORDER_PX + (walls.at(j).h / 2 - (walls.at(j).y - blobs.at(i).y)));              
            } else {
              tempPoint.moveToAR(M_PI_2, 50);
              blobs.at(i).moveToAR(M_PI_2, tempRadius + COLLISION_BORDER_PX + (walls.at(j).h / 2 - (blobs.at(i).y - walls.at(j).y)));                            
            }
          
          #ifdef DEBUG_DRAW_WALL_NORMAL          
            line[1].position = sf::Vector2f(tempPoint.x, tempPoint.y);
            line[1].color = sf::Color::White;
            window.draw(line, 2, sf::Lines);
          #endif          
          }
        }


        if (tSoi) blobs.at(i).setOutlineColor(sf::Color::Red);
        else blobs.at(i).setOutlineColor(sf::Color::Green);

        blobs.at(i).draw(window);

      }
    
      PF_Draw(window);

      window.display();
  }

  return 0;
}
