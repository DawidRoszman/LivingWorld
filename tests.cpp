#include "Dandelion.h"
#include "Position.h"
#include "Sheep.h"
#include "Toadstool.h"
#include "Wolf.h"
#include <gtest/gtest.h>
#include <memory>

TEST(Position, checkIfCalculatesCorrectDistance) {
  Position *position1 = new Position(5, 6);
  Position *position2 = new Position(1, 3);
  double distance = (*position1).distance(*position2);
  EXPECT_DOUBLE_EQ(distance, 5);
}

TEST(Position, checkIfMovesCorrectly) {
  Position *position = new Position(5, 6);
  Position *newPosition = new Position(6, 8);
  (*position).move(*newPosition);
  EXPECT_EQ((*position).getX(), 6);
  EXPECT_EQ((*position).getY(), 8);
}

TEST(Sheep, checkIfReproducesCorrectly) {
  Sheep *sheep = new Sheep(Position(5, 6));
  Position newPosition = Position{6, 8};
  shared_ptr<Organism> newSheep = sheep->reproduce(newPosition, 5);
  EXPECT_EQ(newSheep->getPosition().getX(), newPosition.getX());
  EXPECT_EQ(newSheep->getPosition().getY(), newPosition.getY());
}

TEST(Toadstool, checkIfConsequencesAreCorrect) {
  Toadstool *toadstool = new Toadstool(Position(5, 6));
  shared_ptr<Sheep> sheep = make_shared<Sheep>(Position(6, 8));
  toadstool->consequences(sheep);
  EXPECT_EQ(toadstool->getLiveLength(), 0);
  EXPECT_EQ(sheep->getLiveLength(), 0);
}

TEST(Wolf, checkIfCanEatSheep) {
  shared_ptr<Wolf> wolf = make_shared<Wolf>(Wolf(Position(5, 6)));
  shared_ptr<Sheep> sheep = make_shared<Sheep>(Position(6, 8));
  wolf->action({sheep}, wolf);
  EXPECT_EQ(sheep->getLiveLength(), 0);
}

TEST(Dandelion, checkIfCanGivePower) {
  shared_ptr<Dandelion> dandelion =
      make_shared<Dandelion>(Dandelion(Position(5, 6)));
  shared_ptr<Sheep> sheep = make_shared<Sheep>(Position(6, 8));
  int sheepPower = sheep->getPower();
  dandelion->consequences(sheep);
  EXPECT_EQ(dandelion->getLiveLength(), 0);
  EXPECT_EQ(sheep->getPower(), sheepPower + 1);
}
