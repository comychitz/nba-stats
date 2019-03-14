#ifndef __STAT_PROCESSOR_JSON_H__
#define __STAT_PROCESSOR_JSON_H__

#include "StatProcessor.h"
#include <json/json.h>

namespace nba {

class StatProcessorJson : public StatProcessor {
  public:
    StatProcessorJson();

    virtual ~StatProcessorJson();

    void process(const std::string &raw,
                 std::vector<StatMap> &stats);
};

}

#endif
