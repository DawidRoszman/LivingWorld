#pragma once

#include "Animal.h"
#include "Organism.h"
#include "Position.h"
#include <memory>
#include <vector>
class Wolf : public Animal {
public:
  Wolf(Position position);
  Wolf();
  shared_ptr<Organism> reproduce(Position position, int currentTurn) override;
  void action(vector<shared_ptr<Organism>> organisms,
              shared_ptr<Organism> current) override;
  void consequences(shared_ptr<Organism> other) override;
  template <class Archive> void serialize(Archive &archive) {
    archive(cereal::base_class<Organism>(this));
  }
};

// Register derived class with Cereal
CEREAL_REGISTER_TYPE(Wolf)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Organism, Wolf)
