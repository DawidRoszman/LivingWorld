#include "Organism.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

Organism::Organism(Position position) {
  setPosition(position);
  setAncestorHistory(vector<pair<int, int>>());
  setSpecies("O");
}
Organism::Organism(const Organism &other) {
  setPower(other.power);

  setPosition(other.position);
  setSpecies(other.species);
  setAncestorHistory(other.ancestorHistory);
}

Organism &Organism::operator=(const Organism &other) {
  if (this != &other) {
    setPower(other.power);
    setPosition(other.position);
    setSpecies(other.species);
    setAncestorHistory(other.ancestorHistory);
  }
  return *this;
}

// After death loop through other organism with the same type with list of
// ancestors longer that the current organism and update pair with index
// len(thisOrganismAncestorList)
Organism::~Organism() {}

int Organism::getPower() { return this->power; }

void Organism::setPower(int power) { this->power = power; }

Position Organism::getPosition() { return this->position; }

void Organism::setPosition(Position position) { this->position = position; }

string Organism::toString() {
  return "{ species: " + this->getSpecies() +
         ", power: " + to_string(getPower()) +
         ", position: " + getPosition().toString() +
         " ancestorHistory: " + ancestorHistoryToString() + " }";
}

string Organism::ancestorHistoryToString() {
  string result = "";
  for (auto ancestor : this->ancestorHistory) {
    result +=
        to_string(ancestor.first) + " " + to_string(ancestor.second) + ", ";
  }
  return result;
}

string Organism::getSpecies() { return this->species; }

void Organism::setSpecies(string spec) { this->species = spec; }

void Organism::setAncestorHistory(vector<pair<int, int>> ancestorHistory) {
  this->ancestorHistory = ancestorHistory;
}

void Organism::addAncestor(int birthTurn, int deathTurn) {
  this->ancestorHistory.push_back(make_pair(birthTurn, deathTurn));
}

vector<pair<int, int>> Organism::getAncestorHistory() const {
  return this->ancestorHistory;
}

void Organism::setInitiative(int initiative) { this->initiative = initiative; }
int Organism::getInitiative() { return this->initiative; }
void Organism::setLiveLength(int liveLength) { this->liveLength = liveLength; }
int Organism::getLiveLength() { return this->liveLength; }
void Organism::setPowerToReproduce(int powerToReproduce) {
  this->powerToReproduce = powerToReproduce;
}
int Organism::getPowerToReproduce() { return this->powerToReproduce; }
void Organism::addDescendant(shared_ptr<Organism> descendant) {
  this->descendants.push_back(descendant);
}

void Organism::deleteDescendant(shared_ptr<Organism> descendant) {
  // Check if descendant is in the list
  auto it =
      find(this->descendants.begin(), this->descendants.end(), descendant);
  if (it != this->descendants.end()) {
    this->descendants.erase(it);
  }
}
void Organism::updateAncestorHistory(int index, int deathTurn) {
  this->ancestorHistory[index].second = deathTurn;
}
void Organism::die(int deathTurn) {
  for (auto descendant : this->descendants) {
    // std::cout << "Descendant: " << descendant->getSpecies() << " " <<
    // descendant->getPosition().getX() << " " <<
    // descendant->getPosition().getY() << std::endl;
    descendant->updateAncestorHistory(this->ancestorHistory.size(), deathTurn);
  }
}
int Organism::getBirthTurn() { return this->birthTurn; }
void Organism::setBirthTurn(int birthTurn) { this->birthTurn = birthTurn; }
