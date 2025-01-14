#include "Dandelion.h"
#include "Grass.h"
#include "Position.h"
#include "Sheep.h"
#include "Toadstool.h"
#include "Wolf.h"
#include "World.h"
#include <cereal/archives/binary.hpp>
#include <cereal/types/polymorphic.hpp>
#include <fstream>
#include <iostream>
#include <memory>
using namespace std;

CEREAL_REGISTER_ARCHIVE(cereal::BinaryOutputArchive)
CEREAL_REGISTER_ARCHIVE(cereal::BinaryInputArchive)
CEREAL_REGISTER_DYNAMIC_INIT(Grass)
CEREAL_REGISTER_DYNAMIC_INIT(Sheep)
CEREAL_REGISTER_DYNAMIC_INIT(Toadstool)
CEREAL_REGISTER_DYNAMIC_INIT(Dandelion)
CEREAL_REGISTER_DYNAMIC_INIT(Wolf)

int askForInt(string message) {
  int number;
  cout << message;
  cin >> number;
  return number;
}
int main() {
  // Position
  Position p1;
  Position p2{1, 1};
  Position p3{-3, -5};

  // Plant & Animal
  Grass plant{p3};
  Sheep animal{p2};

  cout << plant.toString() << endl;
  cout << animal.toString() << endl;
  cout << plant.toString() << endl;
  cout << animal.toString() << endl;

  // World test
  World world{15, 15};
  Position posG1{14, 13};
  shared_ptr<Grass> plantW1 = make_shared<Grass>(posG1);

  Position posG2{14, 14};
  shared_ptr<Grass> plantW2 = make_shared<Grass>(posG2);

  Position posG3{13, 13};
  shared_ptr<Grass> plantW3 = make_shared<Grass>(posG3);

  Position posG4{12, 14};
  shared_ptr<Grass> plantW4 = make_shared<Grass>(posG4);
  Position posG5{0, 13};
  shared_ptr<Grass> plantW5 = make_shared<Grass>(posG5);

  Position posG6{1, 12};
  shared_ptr<Grass> plantW6 = make_shared<Grass>(posG6);
  Position posS2{14, 14};
  shared_ptr<Sheep> animalW1 = make_shared<Sheep>(posS2);
  Position posS3{11, 11};
  shared_ptr<Sheep> animalW2 = make_shared<Sheep>(posS3);

  Position posW1{3, 3};
  shared_ptr<Wolf> wolf1 = make_shared<Wolf>(posW1);
  Position posW2{5, 5};
  shared_ptr<Wolf> wolf2 = make_shared<Wolf>(posW2);
  Position posD1{14, 11};
  shared_ptr<Dandelion> dandelion1 = make_shared<Dandelion>(posD1);

  Position posD2{10, 13};
  shared_ptr<Dandelion> dandelion2 = make_shared<Dandelion>(posD2);

  Position posD3{11, 12};
  shared_ptr<Dandelion> dandelion3 = make_shared<Dandelion>(posD3);
  Position posD4{12, 0};
  shared_ptr<Dandelion> dandelion4 = make_shared<Dandelion>(posD4);
  Position posT1{14, 12};
  shared_ptr<Toadstool> toadstool1 = make_shared<Toadstool>(posT1);

  Position posT2{14, 11};
  shared_ptr<Toadstool> toadstool2 = make_shared<Toadstool>(posT2);

  Position posT3{11, 14};
  shared_ptr<Toadstool> toadstool3 = make_shared<Toadstool>(posT3);
  world.addOrganism(plantW1);
  world.addOrganism(plantW2);
  world.addOrganism(plantW3);
  world.addOrganism(plantW4);
  world.addOrganism(plantW5);
  world.addOrganism(animalW1);
  world.addOrganism(animalW2);
  world.addOrganism(wolf1);
  world.addOrganism(wolf2);
  world.addOrganism(dandelion1);
  world.addOrganism(dandelion2);
  world.addOrganism(dandelion3);
  world.addOrganism(dandelion4);
  world.addOrganism(toadstool1);
  world.addOrganism(toadstool2);
  world.addOrganism(toadstool3);

  auto positions = world.getVectorOfFreePositionsAround(Position(5, 5));

  for (auto pos : positions)
    cout << pos.toString() << endl;

  // Tura 0
  cout << world.toString() << endl;
  bool playGame = true;
  while (playGame) {
    world.makeTurn();
    cout << world.toString() << endl;
    int finishedUserInput = false;
    while (!finishedUserInput) {
      int x, y;
      shared_ptr<Organism> org = nullptr;
      int userInput = askForInt("1. Next turn\n2. Check organism\n3. Save "
                                "world\n4. Load world\n5. Exit\n");

      switch (userInput) {
      case 1:
        finishedUserInput = true;
        break;
      case 2:
        x = askForInt("Enter x: ");
        y = askForInt("Enter y: ");
        org = world.getOrganismFromPosition(x, y);
        if (org != nullptr)
          cout << org->toString() << endl;
        else
          cout << "No organism on this position" << endl;
        break;
      case 3:
        // Save the world to file
        {
          std::ofstream os("world.cereal", std::ios::binary);
          cereal::BinaryOutputArchive archive(os);
          archive(world);
        }
        break;
      case 4:
        // Load the world from file
        {
          std::ifstream is("world.cereal", std::ios::binary);
          cereal::BinaryInputArchive archive(is);
          archive(world);
        }
        break;
      case 5:
        finishedUserInput = true;
        playGame = false;
        break;
      default:
        break;
      }
    }
  }

  return 0;
}
