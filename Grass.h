#pragma once
#include "Organism.h"
#include "Plant.h"
#include <memory>

class Grass : public Plant {
public:
  Grass(Position position);
  Grass();
  void action(vector<shared_ptr<Organism>> organisms,
              shared_ptr<Organism> current) override;
  shared_ptr<Organism> reproduce(Position position, int currentTurn) override;
  void consequences(shared_ptr<Organism> other) override;
  template <class Archive> void serialize(Archive &archive) {
    archive(cereal::base_class<Organism>(this));
  }
};

// Register derived class with Cereal
CEREAL_REGISTER_TYPE(Grass)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Organism, Grass)
