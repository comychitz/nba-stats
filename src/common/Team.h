#ifndef __NBA_TEAM_H__
#define __NBA_TEAM_H__

#include <string>

namespace nba {

class Team {
  public:
    unsigned long id;
    std::string abbr;
    std::string name;
    std::string fullname;
    short yearfounded;
    std::string city;
    std::string state;

    Team() : id(0), yearfounded(0) { }

    ~Team() { }
};

}
#endif
