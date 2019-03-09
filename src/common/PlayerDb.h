#ifndef __NBA_PLAYER_DB_H__
#define __NBA_PLAYER_DB_H__

#include "Player.h"
#include <string>
#include <unordered_map>

namespace nba {

class PlayerDb {
  public:
    PlayerDb();

    ~PlayerDb();

    bool init(const std::string &srcPath);

    bool getPlayer(const std::string &fullname, Player &player) const;

  private:
    std::unordered_map<std::string, Player> players_;
};

}

#endif
