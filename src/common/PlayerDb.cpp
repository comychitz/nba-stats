#include "PlayerDb.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

namespace nba {

PlayerDb::PlayerDb() { 
}

PlayerDb::~PlayerDb() { 
}

static unsigned long strToULong(const std::string &str) {
  std::stringstream ss(str);
  unsigned long val = 0;
  ss >> val;
  return val;
}

static void parsePlayer(const std::string &line, Player &player) {
  std::vector<std::string> tokens;
  size_t pos = 0, pos2 = std::string::npos;
  while ((pos2 = line.find(",", pos)) != std::string::npos) {
    tokens.push_back(line.substr(pos, pos2-pos)); 
    pos = pos2+1;
  }
  tokens.push_back(line.substr(pos, pos2-pos));
  if (tokens.size() < 4) {
    std::cout << "WARNING: Unexpected number of tokens: " << line << std::endl;
    return;
  }
  player.id = strToULong(tokens.at(0));
  player.lastname = tokens.at(1);
  player.firstname = tokens.at(2);
  player.fullname = tokens.at(3);
  // some players have additional nick names in the db file, but for now we 
  // will ignore those. maybe add later
}

bool PlayerDb::init(const std::string &srcPath) {
  std::ifstream f(srcPath.c_str());
  if (!f.good()) {
    std::cout << "ERROR: Unable to open: " << srcPath << std::endl;
    return false;
  }
  std::string line;
  while (std::getline(f, line)) {
    Player player;
    parsePlayer(line, player);
    players_[player.fullname] = player;
  }
  return true;
}

bool PlayerDb::getPlayer(const std::string &fullname, Player &player) const {
  auto playerIter = players_.find(fullname);
  if (playerIter != players_.end()) {
    player = playerIter->second;
    return true;
  }
  return false;
}

}
