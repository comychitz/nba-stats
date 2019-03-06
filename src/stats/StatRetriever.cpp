#include "StatRetriever.h"
#include <curl/curl.h>
#include <iostream>

namespace nba {

StatRetriever::StatRetriever() {
}

StatRetriever::~StatRetriever() {
}

static size_t writeDataCallback(char *contents, size_t size, 
                                size_t nmemb, void *userp) {
  std::string* response = static_cast<std::string*>(userp);
  response->append((char*)contents, size*nmemb);
  return size*nmemb;
}

bool StatRetriever::get_(const std::map<std::string, std::string> &params,
                         std::string &response) {
  CURL *curl = curl_easy_init();
  if (!curl) {
    std::cout << "CURL INIT ERROR" << std::endl;
    return false;
  }
  const std::string &baseurl = "http://stats.nba.com/stats/";

  endpoint = "playerprofilev2";

  // construct full url, with query string 
  std::string url(base + endpoint + "?");
  for (auto param = params.begin(); param != params.end(); ++param) {
    if (param != params.begin()) {
      url += "&";
    }
    url += param.first + "=" + param.second;
  }
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION, writeDataCallback);
  curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, &response);

  CURLcode res = curl_easy_perform(curl);

  bool retVal = true;
  if (res != CURLE_OK) {
    std::cout << "CURL ERROR: " << curl_easy_strerror(res) << std::endl;
    retVal = false;
  }
  curl_easy_cleanup(curl);

  return retVal;
}

}
