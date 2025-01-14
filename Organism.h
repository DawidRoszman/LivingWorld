#pragma once
#include "Position.h"
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <cereal/archives/binary.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/vector.hpp>

using namespace std;

class Organism {
private:
  int power;
  int initiative;
  Position position;
  int liveLength;
  int powerToReproduce;
  string species;
  int birthTurn;
  vector<pair<int, int>> ancestorHistory;
  vector<shared_ptr<Organism>> descendants;

public:
  Organism(Position position);
  Organism(const Organism &other);
  Organism &operator=(const Organism &other);
  ~Organism();

  Organism() : power(0), position(0, 0), species("O"){};

  int getPower();
  void setPower(int power);
  Position getPosition();
  void setPosition(Position position);
  string getSpecies();
  void setSpecies(string spec);
  void setAncestorHistory(vector<pair<int, int>> ancestorHistory);
  void addAncestor(int birthTurn, int deathTurn);
  vector<pair<int, int>> getAncestorHistory() const;
  void setInitiative(int initiative);
  int getInitiative();
  void setLiveLength(int liveLength);
  int getLiveLength();
  void setPowerToReproduce(int powerToReproduce);
  int getPowerToReproduce();
  void addDescendant(shared_ptr<Organism> descendant);
  void deleteDescendant(shared_ptr<Organism> descendant);
  void die(int deathTurn);
  void updateAncestorHistory(int index, int deathTurn);
  int getBirthTurn();
  void setBirthTurn(int birthTurn);
  string ancestorHistoryToString();

  string toString();

  virtual shared_ptr<Organism> reproduce(Position position,
                                         int currentTurn) = 0;
  virtual void move(Position position) = 0;
  virtual void action(vector<shared_ptr<Organism>> organismsAround,
                      shared_ptr<Organism> current) = 0;
  virtual void consequences(shared_ptr<Organism> other) = 0;
  template <class Archive> void serialize(Archive &archive) {
    archive(power, initiative, position, liveLength, powerToReproduce, species,
            birthTurn, ancestorHistory, descendants);
  }
};
