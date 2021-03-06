#ifndef __STAT_RETRIEVER_H__
#define __STAT_RETRIEVER_H__

#include <map>
#include <string>
#include "StatProcessor.h"

namespace nba {

class StatRetriever {
  public:
    StatRetriever(StatProcessor &processor);

    virtual ~StatRetriever();

    bool get(const std::string &endpoint,
             const std::map<std::string, std::string> &params,
             std::vector<StatMap> &stats);

  private:
    StatProcessor &processor_;
};

}
#endif
