#include "Plant.h"

Plant::Plant(Position position) : Organism(position)
{
	setSpecies("P");
}

Plant::Plant() : Organism()
{
	setSpecies("P");
}

void Plant::move(Position position)
{
	// Plants don't move
}