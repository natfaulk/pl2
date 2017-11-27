#include "buildWorld.hpp"
#include "constants.hpp"

void buildWorld(std::vector<Wall> &_walls) {
  // _walls.push_back(Wall(200, 200, 100, 100));
  // _walls.push_back(Wall(850, 200, 350, 20));
  // _walls.push_back(Wall(850, 560, 400, 20));
  // _walls.push_back(Wall(200, 650, 300, 100));
  // _walls.push_back(Wall(650, 400, 20, 350));
  // _walls.push_back(Wall(1050, 400, 20, 350));

  // outside walls
  _walls.push_back(Wall(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH + 20, 20));
  _walls.push_back(Wall(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH + 20, 20));
  _walls.push_back(Wall(0, SCREEN_HEIGHT / 2, 20, SCREEN_HEIGHT + 20));
  _walls.push_back(Wall(SCREEN_WIDTH, SCREEN_HEIGHT / 2, 20, SCREEN_HEIGHT + 20));
  
  // other walls
  _walls.push_back(Wall(200, 200, 100, 100));
  _walls.push_back(Wall(500, 100, 50, 300));
  

  
}
