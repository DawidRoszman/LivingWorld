#pragma once
#include "Organism.h"

class Plant : public Organism
{
public:
	Plant(Position position);
	Plant();

	void move(Position position) override;
};
