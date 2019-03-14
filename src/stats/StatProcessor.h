#ifndef __STAT_PROCEESSOR_H__
#define __STAT_PROCEESSOR_H__

#include "StatMap.h"

namespace nba {

class StatProcessor {
  public:
    virtual ~StatProcessor() { }

    virtual void process(const std::string &raw,
                         std::vector<StatMap> &stats) = 0; 
};

}

#endif
