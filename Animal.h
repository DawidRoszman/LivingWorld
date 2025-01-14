#pragma once
#include "Organism.h"

using namespace std;

class Animal : public Organism
{
public:
	Animal(Position position);
	Animal();
	void move(Position position) override;
};
