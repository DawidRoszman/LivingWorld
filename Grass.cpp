#include "Grass.h"
#include "Organism.h"
#include "Plant.h"
#include <memory>

Grass::Grass(Position position) : Plant(position) {
  setSpecies("G");
  setPosition(position);
  setPower(0);
  setInitiative(0);
  setLiveLength(6);
  setPowerToReproduce(3);
}
Grass::Grass() : Plant() {
  setSpecies("G");
  setPower(0);
  setInitiative(0);
  setLiveLength(6);
  setPowerToReproduce(3);
}

void Grass::action(vector<shared_ptr<Organism>> organisms,
                   shared_ptr<Organism> current) {
  // Grass doesn't do anything
}

shared_ptr<Organism> Grass::reproduce(Position position, int currentTurn) {
  this->setPower(this->getPower() / 2);
  shared_ptr<Grass> newOrg = make_shared<Grass>(position);
  newOrg->setAncestorHistory(this->getAncestorHistory());
  newOrg->addAncestor(this->getBirthTurn(), -1);
  newOrg->setBirthTurn(currentTurn);
  this->addDescendant(newOrg);

  return newOrg;
}

void Grass::consequences(shared_ptr<Organism> other) {
  this->setLiveLength(0);
  other->setPosition(this->getPosition());
}
