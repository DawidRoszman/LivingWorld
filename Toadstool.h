#pragma once
#include "Organism.h"
#include "Plant.h"
#include "Position.h"
#include <memory>
#include <vector>
class Toadstool : public Plant {
public:
  Toadstool(Position position);
  Toadstool();
  void action(vector<shared_ptr<Organism>> organisms,
              shared_ptr<Organism> current) override;
  shared_ptr<Organism> reproduce(Position position, int currentTurn) override;
  void consequences(shared_ptr<Organism> other) override;
  template <class Archive> void serialize(Archive &archive) {
    archive(cereal::base_class<Organism>(this));
  }
};

// Register derived class with Cereal
CEREAL_REGISTER_TYPE(Toadstool)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Organism, Toadstool)
