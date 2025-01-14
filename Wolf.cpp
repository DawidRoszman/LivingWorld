#include "Wolf.h"
#include "Animal.h"
#include "Organism.h"
#include <iostream>
#include <memory>
Wolf::Wolf(Position position) : Animal(position) {
  setPower(8);
  setInitiative(5);
  setLiveLength(20);
  setPowerToReproduce(16);
  setSpecies("W");
}

Wolf::Wolf() : Animal() {
  setPower(8);
  setInitiative(5);
  setLiveLength(20);
  setPowerToReproduce(16);
  setSpecies("W");
}

void Wolf::action(vector<shared_ptr<Organism>> organisms,
                  shared_ptr<Organism> current) {
  for (auto &organism : organisms) {
    if (organism != nullptr &&
        (organism->getSpecies() == "S" || organism->getSpecies() == "T") &&
        organism->getLiveLength() > 0) {
      std::cout << "Wolf ate " << organism->getSpecies() << " on position "
                << organism->getPosition().getX() << " "
                << organism->getPosition().getY() << std::endl;
      organism->consequences(current);
      return;
    }
  }
}

shared_ptr<Organism> Wolf::reproduce(Position position, int currentTurn) {
  this->setPower(this->getPower() / 2);
  shared_ptr<Wolf> newOrg = make_shared<Wolf>(position);
  newOrg->setAncestorHistory(this->getAncestorHistory());
  newOrg->addAncestor(this->getBirthTurn(), -1);
  newOrg->setBirthTurn(currentTurn);
  this->addDescendant(newOrg);

  return newOrg;
}

void Wolf::consequences(shared_ptr<Organism> other) {
  this->setLiveLength(0);
  other->setPosition(this->getPosition());
}
