#ifndef __NBA_TEAM_DB_H__
#define __NBA_TEAM_DB_H__

#include "Team.h"
#include <string>
#include <vector>
#include <unordered_map>

namespace nba {

class TeamDb {
  public:
    TeamDb();

    ~TeamDb();

    bool init(const std::string &srcPath);

    bool getTeam(const std::string &name, Team &team);

  private:
    void parseTeam_(const std::string &line, int count);

    std::vector<Team> teams_;
    std::unordered_map<std::string, int> nameToTeamId_;
};

}

#endif
