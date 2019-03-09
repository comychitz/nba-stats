#include "PlayerDb.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace nba {

PlayerDb::PlayerDb() {
  players_.reserve(4500);
}

PlayerDb::~PlayerDb() { 
}

static unsigned long strToULong(const std::string &str) {
  std::stringstream ss(str);
  unsigned long val = 0;
  ss >> val;
  return val;
}

bool PlayerDb::init(const std::string &srcPath) {
  std::ifstream f(srcPath.c_str());
  if (!f.good()) {
    std::cout << "ERROR: Unable to open: " << srcPath << std::endl;
    return false;
  }
  std::string line;
  unsigned count = 0;
  while (std::getline(f, line)) {
    parsePlayer_(line, count++);
  }
  return true;
}

bool PlayerDb::getPlayer(const std::string &name, Player &player) const {
  auto playerIter = nameToPlayerId_.find(name);
  if (playerIter != nameToPlayerId_.end()) {
    player = players_.at(playerIter->second);
    return true;
  }
  return false;
}

void PlayerDb::parsePlayer_(const std::string &line, unsigned count) {
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
  Player player;
  player.id = strToULong(tokens.at(0));
  player.lastname = tokens.at(1);
  player.firstname = tokens.at(2);
  player.fullname = tokens.at(3);
  players_.push_back(player);

  nameToPlayerId_[player.fullname] = count;

  // the rest of the tokens are (optional) nick names
  for (size_t i = 4; i < tokens.size(); i++) {
    nameToPlayerId_[tokens.at(i)] = count;
  }
}

}
