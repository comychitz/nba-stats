#ifndef __NBA_PLAYER_DB_H__
#define __NBA_PLAYER_DB_H__

#include "Player.h"
#include <string>
#include <vector>
#include <unordered_map>

namespace nba {

class PlayerDb {
  public:
    PlayerDb();

    ~PlayerDb();

    bool init(const std::string &srcPath);

    bool getPlayer(const std::string &name, Player &player) const;

  private:
    void parsePlayer_(const std::string &line, unsigned count);

    std::vector<Player> players_;
    std::unordered_map<std::string, unsigned> nameToPlayerId_;
};

}

#endif
