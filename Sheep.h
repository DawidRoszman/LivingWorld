#pragma once
#include "Animal.h"
#include "Organism.h"
#include <memory>
class Sheep : public Animal {
public:
  Sheep(Position position);
  Sheep();
  shared_ptr<Organism> reproduce(Position position, int currentTurn) override;
  void action(vector<shared_ptr<Organism>> organisms,
              shared_ptr<Organism> current) override;
  void consequences(shared_ptr<Organism> other) override;
  template <class Archive> void serialize(Archive &archive) {
    archive(cereal::base_class<Organism>(this));
  }
};

// Register derived class with Cereal
CEREAL_REGISTER_TYPE(Sheep)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Organism, Sheep)
