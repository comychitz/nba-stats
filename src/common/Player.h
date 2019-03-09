#ifndef __NBA_PLAYER_H__
#define __NBA_PLAYER_H__

#include <string>

namespace nba {

class Player {
  public:
    std::string firstname;
    std::string lastname;
    std::string fullname;
    unsigned long id;

    Player() : id(0) { }

    ~Player() { }
};

}
#endif
