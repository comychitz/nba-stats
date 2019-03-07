#ifndef __STAT_PROCEESSOR_H__
#define __STAT_PROCEESSOR_H__

#include <string>

namespace nba {

class StatProcessor {
  public:
    virtual ~StatProcessor() { }

    virtual void process(const std::string &raw) = 0; 
};

}

#endif
