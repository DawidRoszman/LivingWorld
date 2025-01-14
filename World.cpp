#include "World.h"
shared_ptr<Organism> World::getOrganismFromPosition(int x, int y) {
  for (auto org : organisms)
    if (org->getPosition().getX() == x && org->getPosition().getY() == y)
      return org;
  return nullptr;
}

bool World::isPositionOnWorld(int x, int y) {
  return (x >= 0 && y >= 0 && x < getWorldX() && y < getWorldY());
}

bool World::isPositionFree(Position position) {
  return this->getOrganismFromPosition(position.getX(), position.getY()) ==
         nullptr;
}

void World::deleteOrganism(shared_ptr<Organism> organism) {
  // Delete organism from vector
  organisms.erase(remove(organisms.begin(), organisms.end(), organism),
                  organisms.end());
}

vector<Position> World::getVectorOfFreePositionsAround(Position position) {
  int pos_x = position.getX(), pos_y = position.getY();
  vector<Position> result;
  for (int x = -1; x < 2; ++x)
    for (int y = -1; y < 2; ++y)
      if ((x != 0 || y != 0) && isPositionOnWorld(pos_x + x, pos_y + y)) {
        result.push_back(Position(pos_x + x, pos_y + y));
      }
  auto iter = remove_if(result.begin(), result.end(),
                        [this](Position pos) { return !isPositionFree(pos); });
  result.erase(iter, result.end());

  return result;
}

vector<shared_ptr<Organism>>
World::getOrganismsAroundPosition(Position position) {
  int pos_x = position.getX(), pos_y = position.getY();
  vector<shared_ptr<Organism>> result;
  for (int x = -1; x < 2; ++x)
    for (int y = -1; y < 2; ++y)
      if ((x != 0 || y != 0) && isPositionOnWorld(pos_x + x, pos_y + y)) {
        result.push_back(getOrganismFromPosition(pos_x + x, pos_y + y));
      }
  return result;
}

World::World(int worldX, int worldY) {
  setWorldX(worldX);
  setWorldY(worldY);
}

int World::getWorldX() { return this->worldX; }

void World::setWorldX(int worldX) { this->worldX = worldX; }

int World::getWorldY() { return this->worldY; }

void World::setWorldY(int worldY) { this->worldY = worldY; }

int World::getTurn() { return this->turn; }

void World::addOrganism(shared_ptr<Organism> organism) {
  this->organisms.push_back(organism);
}

void World::moveOrganism(shared_ptr<Organism> org) {
  vector<Position> newPositions;
  int numberOfNewPositions;
  int randomIndex;
  newPositions = getVectorOfFreePositionsAround(org->getPosition());
  numberOfNewPositions = newPositions.size();
  if (numberOfNewPositions > 0) {
    randomIndex = rand() % numberOfNewPositions;
    org->move(newPositions[randomIndex]);
    vector<shared_ptr<Organism>> orgsAround =
        getOrganismsAroundPosition(org->getPosition());
    org->action(orgsAround, org);
  }
}

void World::makeTurn() {
  map<int, vector<shared_ptr<Organism>>> initiatives;
  vector<shared_ptr<Organism>> organismsToDelete;
  for (auto org : organisms) {
    initiatives[org->getInitiative()].push_back(org);
  }
  for (auto it = initiatives.rbegin(); it != initiatives.rend(); ++it) {
    vector<shared_ptr<Organism>> organismsToReproduce;
    for (auto org : it->second) {

      if (org->getPower() >= org->getPowerToReproduce()) {
        vector<Position> newPositions =
            getVectorOfFreePositionsAround(org->getPosition());
        int numberOfNewPositions = newPositions.size();
        if (numberOfNewPositions > 0) {
          int randomIndex = rand() % numberOfNewPositions;
          shared_ptr<Organism> newOrg =
              org->reproduce(newPositions[randomIndex], turn);
          if (newOrg != nullptr) {
            // cout << "newOrg: " << newOrg->getPosition().getX()
            //      << newOrg->getPosition().getY() << endl;
            // addOrganism(newOrg);
            organismsToReproduce.push_back(newOrg);
            continue;
          }
        }
      }
      if (org != nullptr) {
        org->setLiveLength(org->getLiveLength() - 1);
        // cout << "Org: " << org->getSpecies() << " " <<
        // org->getPosition().getX()
        //      << " " << org->getPosition().getY() << " " << org->getPower()
        //      << endl;
        org->setPower(org->getPower() + 1);
        moveOrganism(org);
      }
    }

    for (auto org : organismsToReproduce) {
      addOrganism(org);
    }

    srand(time(0));
  }
  for (auto org : organisms) {
    if (org->getLiveLength() <= 0) {
      organismsToDelete.push_back(org);
      continue;
    }
  }
  for (auto org : organismsToDelete) {
    org->die(turn);
    deleteOrganism(org);
    for (auto org2 : organisms) {
      org2->deleteDescendant(org);
    }
  }
  turn++;
}

// void World::writeWorld(string fileName)
// {
//   fstream my_file;
//   my_file.open(fileName, ios::out | ios::binary);
//   if (my_file.is_open())
//   {
//     my_file.write((char *)&this->worldX, sizeof(int));
//     my_file.write((char *)&this->worldY, sizeof(int));
//     my_file.write((char *)&this->turn, sizeof(int));
//     int orgs_size = this->organisms.size();
//     my_file.write((char *)&orgs_size, sizeof(int));
//     for (int i = 0; i < orgs_size; i++)
//     {
//       int data;
//       data = this->organisms[i].getPosition().getX();
//       my_file.write((char *)&data, sizeof(int));
//       data = this->organisms[i].getPosition().getY();
//       my_file.write((char *)&data, sizeof(int));
//       string s_data = this->organisms[i].getSpecies();
//       int s_size = s_data.size();
//       my_file.write((char *)&s_size, sizeof(int));
//       my_file.write(s_data.data(), s_data.size());
//     }
//     my_file.close();
//   }
// }

// void World::readWorld(string fileName)
// {
//   fstream my_file;
//   my_file.open(fileName, ios::in | ios::binary);
//   if (my_file.is_open())
//   {
//     int result;
//     my_file.read((char *)&result, sizeof(int));
//     this->worldX = (int)result;
//     my_file.read((char *)&result, sizeof(int));
//     this->worldY = (int)result;
//     my_file.read((char *)&result, sizeof(int));
//     this->turn = (int)result;
//     my_file.read((char *)&result, sizeof(int));
//     int orgs_size = (int)result;
//     vector<Organism> new_organisms;
//     for (int i = 0; i < orgs_size; i++)
//     {
//       int pos_x;
//       my_file.read((char *)&result, sizeof(int));
//       pos_x = (int)result;
//       int pos_y;
//       my_file.read((char *)&result, sizeof(int));
//       pos_y = (int)result;
//       Position pos{pos_x, pos_y};

//       int s_size;
//       my_file.read((char *)&result, sizeof(int));
//       s_size = (int)result;

//       string species;
//       species.resize(s_size);
//       my_file.read((char *)&species[0], s_size);

//       // Organism org(pos);
//       // org.setSpecies(species);
//       // new_organisms.push_back(org);
//     }
//     this->organisms = new_organisms;
//     my_file.close();
//   }
// }
//

string World::toString() {
  string result = "\nturn: " + to_string(getTurn()) + "\n";
  string spec;

  result += "   ";
  for (int wX = 0; wX < getWorldX(); ++wX) {
    result += to_string(wX) + " ";
    if (wX < 10) {
      result += " ";
    }
  }
  result += "\n";
  for (int wY = 0; wY < getWorldY(); ++wY) {
    result += to_string(wY);
    if (wY < 10) {
      result += "  ";
    } else {
      result += " ";
    }
    for (int wX = 0; wX < getWorldX(); ++wX) {
      shared_ptr<Organism> org = getOrganismFromPosition(wX, wY);
      if (org != nullptr) {
        spec = org->getSpecies();
        result += spec;
      } else {
        result += separator;
      }
      result += "  ";
    };
    result += "\n";
  }
  return result;
}
