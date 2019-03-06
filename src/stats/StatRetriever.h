#ifndef __STAT_RETRIEVER_H__
#define __STAT_RETRIEVER_H__

#include <map>
#include <string>

namespace nba {

class StatRetriever {
  public:
    StatRetriever();

    virtual ~StatRetriever();

  protected:
    bool get_(const std::map<std::string, std::string> &params,
              std::string &response);

    std::string endpoint;
};

}
#endif
