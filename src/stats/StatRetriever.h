#ifndef __STAT_RETRIEVER_H__
#define __STAT_RETRIEVER_H__

#include <map>
#include <string>

namespace nba {

template<typename Params, typename Data>
class StatRetriever {
  public:
    StatRetriever();

    virtual ~StatRetriever();

    bool get(const Params &params, Data &data);

    virtual std::string determineEndpoint(const Params &params) = 0;

    virtual std::map<std::string, std::string> constructParams(const Params params) = 0;
};

}

#include "StatRetriever_Impl.h"
#endif
