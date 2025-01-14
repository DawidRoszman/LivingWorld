#include "Animal.h"

Animal::Animal(Position position) : Organism(position)
{
	setSpecies("A");
}

Animal::Animal() : Organism()
{
	setSpecies("A");
}

void Animal::move(Position position)
{
	// Animals move randomly
	setPosition(position);
}
