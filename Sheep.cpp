#include "Sheep.h"
#include "Organism.h"
#include "Plant.h"
#include <iostream>
#include <memory>

Sheep::Sheep(Position position) : Animal(position) {
  setPower(1);
  setInitiative(3);
  setLiveLength(10);
  setPowerToReproduce(5);
  setSpecies("S");
}

Sheep::Sheep() : Animal() {
  setPower(1);
  setInitiative(3);
  setLiveLength(10);
  setPowerToReproduce(5);
  setSpecies("S");
}

void Sheep::action(vector<shared_ptr<Organism>> organisms,
                   shared_ptr<Organism> current) {
  for (auto &organism : organisms) {
    if (organism != nullptr && dynamic_pointer_cast<Plant>(organism) &&
        organism->getLiveLength() > 0) {
      // If there is grass, eat it
      std::cout << "Sheep ate " << organism->getSpecies() << " on position "
                << organism->getPosition().getX() << " "
                << organism->getPosition().getY() << std::endl;
      organism->consequences(current);
      return;
    }
  }
}

shared_ptr<Organism> Sheep::reproduce(Position position, int currentTurn) {
  this->setPower(this->getPower() / 2);
  shared_ptr<Sheep> newOrg = make_shared<Sheep>(position);
  newOrg->setAncestorHistory(this->getAncestorHistory());
  newOrg->addAncestor(this->getBirthTurn(), -1);
  newOrg->setBirthTurn(currentTurn);
  this->addDescendant(newOrg);

  return newOrg;
}

void Sheep::consequences(shared_ptr<Organism> other) {
  this->setLiveLength(0);
  other->setPosition(this->getPosition());
}
