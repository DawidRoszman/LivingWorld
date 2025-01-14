#pragma once

#include "Organism.h"
#include <algorithm>
#include <cereal/archives/binary.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <ctime>
#include <map>
#include <memory>
#include <vector>

using namespace std;

class World {
private:
  int worldX;
  int worldY;
  int turn = 0;
  vector<shared_ptr<Organism>> organisms;
  char separator = '.';

  bool isPositionOnWorld(int x, int y);
  bool isPositionFree(Position position);

public:
  World(int worldX, int worldY);
  World() : World(6, 6){};

  int getWorldX();
  void setWorldX(int worldX);
  int getWorldY();
  void setWorldY(int worldY);
  vector<shared_ptr<Organism>> getOrganismsAroundPosition(Position position);
  shared_ptr<Organism> getOrganismFromPosition(int x, int y);

  int getTurn();

  void addOrganism(shared_ptr<Organism> organism);
  vector<Position> getVectorOfFreePositionsAround(Position position);
  void makeTurn();
  void deleteOrganism(shared_ptr<Organism> organism);
  void moveOrganism(shared_ptr<Organism> organism);

  // void writeWorld(string fileName);
  // void readWorld(string fileName);
  template <class Archive> void serialize(Archive &archive) {
    archive(worldX, worldY, turn, organisms, separator);
  }
  string toString();
};
