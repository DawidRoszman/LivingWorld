#include "Dandelion.h"
#include "Organism.h"
#include <memory>
Dandelion::Dandelion(Position position) : Plant(position) {
  setPower(0);
  setInitiative(0);
  setLiveLength(3);
  setPowerToReproduce(1);
  setSpecies("D");
}

Dandelion::Dandelion() : Plant() {
  setPower(0);
  setInitiative(0);
  setLiveLength(3);
  setPowerToReproduce(1);
  setSpecies("D");
}

void Dandelion::action(vector<shared_ptr<Organism>> organisms,
                       shared_ptr<Organism> current) {}
shared_ptr<Organism> Dandelion::reproduce(Position position, int currentTurn) {
  this->setPower(this->getPower() / 2);
  shared_ptr<Dandelion> newOrg = make_shared<Dandelion>(position);
  newOrg->setAncestorHistory(this->getAncestorHistory());
  newOrg->addAncestor(this->getBirthTurn(), -1);
  newOrg->setBirthTurn(currentTurn);
  this->addDescendant(newOrg);
  return newOrg;
}

void Dandelion::consequences(shared_ptr<Organism> other) {
  this->setLiveLength(0);
  other->setPower(other->getPower() + 1);
  other->setPosition(this->getPosition());
}
