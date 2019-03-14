#include "StatProcessorJson.h"
#include <iostream>
#include <sstream>
#include <json/reader.h>

namespace nba {

StatProcessorJson::StatProcessorJson() {
}

StatProcessorJson::~StatProcessorJson() {
}

void StatProcessorJson::process(const std::string &raw,
                                std::vector<StatMap> &stats) {
  std::istringstream ss(raw);
  JSONCPP_STRING errs;
  Json::Value root;
  Json::CharReaderBuilder builder;
  if(!parseFromStream(builder, ss, &root, &errs)) {
    std::cout << "ERROR: Failed to read json : " << raw << std::endl;
    return;
  }

  if (!root.isMember("resultSets")) {
    return;
  }

  for (unsigned i = 0; i < root["resultSets"].size(); i++) {
    const Json::Value &resultSet = root["resultSets"][i];
    std::string name = resultSet["name"].asString();
    const Json::Value &headers = resultSet["headers"];
    for (unsigned j = 0; j < resultSet["rowSet"].size(); j++) {
      const Json::Value &rowSet = resultSet["rowSet"][j];
      StatMap statmap(name);
      for (unsigned k = 0; k < rowSet.size(); k++) {
        statmap.add(headers[k].asString(), rowSet[k].asString());
      }
      stats.push_back(statmap);
    }
  }
}

}
