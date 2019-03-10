#include "TeamDb.h"
#include "Util.h"
#include <fstream>
#include <iostream>

namespace nba {

TeamDb::TeamDb() {
  teams_.reserve(50);
}

TeamDb::~TeamDb() {
}

bool TeamDb::init(const std::string &srcPath) {
  std::ifstream f(srcPath.c_str());
  if (!f.good()) {
    std::cout << "ERROR: Unable to open: " << srcPath << std::endl;
    return false;
  }
  std::string line;
  unsigned count = 0;
  while (std::getline(f, line)) {
    parseTeam_(line, count++);
  }
  return true;
}

bool TeamDb::getTeam(const std::string &name, Team &team) {
  auto teamIter = nameToTeamId_.find(name);
  if (teamIter != nameToTeamId_.end()) {
    team = teams_.at(teamIter->second);
    return true;
  }
  return false;
}

void TeamDb::parseTeam_(const std::string &line, int count) {
  std::vector<std::string> tokens = Util::tokenize(line, ",");
  if (tokens.size() < 7) {
    std::cout << "WARNING: Unexpected number of tokens: " << line << std::endl;
    return;
  }
  Team team;
  team.id = Util::strToULong(tokens.at(0));
  team.abbr = tokens.at(1);
  team.name = tokens.at(2);
  team.yearfounded = (short)Util::strToULong(tokens.at(3));
  team.city = tokens.at(4);
  team.fullname = tokens.at(5);
  team.state = tokens.at(6);

  teams_.push_back(team);

  nameToTeamId_[team.abbr] = count;
  nameToTeamId_[team.name] = count;
  nameToTeamId_[team.fullname] = count;
  nameToTeamId_[team.city] = count;
}

}
