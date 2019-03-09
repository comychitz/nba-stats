#include "StatProcessorJson.h"
#include <iostream>
#include <sstream>
#include <json/reader.h>

namespace nba {

StatProcessorJson::StatProcessorJson() {
}

StatProcessorJson::~StatProcessorJson() {
}

void StatProcessorJson::process(const std::string &raw) {
  std::istringstream ss(raw);

  JSONCPP_STRING errs;
  Json::CharReaderBuilder builder;
  if(!parseFromStream(builder, ss, &root, &errs)) {
    std::cout << "ERROR: Failed to read json : " << raw << std::endl;
    return;
  }

  std::cout << root.toStyledString() << std::endl;
}

}
