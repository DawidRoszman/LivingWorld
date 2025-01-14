#include "Toadstool.h"
#include "Organism.h"
#include "Position.h"
#include <iostream>
#include <memory>
#include <vector>
Toadstool::Toadstool(Position position) : Plant(position) {
  setPower(0);
  setInitiative(0);
  setLiveLength(6);
  setPowerToReproduce(3);
  setSpecies("T");
}

Toadstool::Toadstool() : Plant() {
  setPower(0);
  setInitiative(0);
  setLiveLength(6);
  setPowerToReproduce(3);
  setSpecies("T");
}

void Toadstool::action(vector<shared_ptr<Organism>> organisms,
                       shared_ptr<Organism> current) {}

shared_ptr<Organism> Toadstool::reproduce(Position position, int currentTurn) {
  this->setPower(this->getPower() / 2);
  shared_ptr<Toadstool> newOrg = make_shared<Toadstool>(position);
  newOrg->setAncestorHistory(this->getAncestorHistory());
  newOrg->addAncestor(this->getBirthTurn(), -1);
  newOrg->setBirthTurn(currentTurn);
  this->addDescendant(newOrg);

  return newOrg;
}

void Toadstool::consequences(shared_ptr<Organism> other) {
  this->setLiveLength(0);
  other->setLiveLength(0);
  cout << "Toadstool killed " << other->getSpecies() << "on postion "
       << other->getPosition().getX() << " " << other->getPosition().getY()
       << endl;
}
