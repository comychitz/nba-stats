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

bool StatRetriever::get(const std::string &endpoint,
                        const std::map<std::string, std::string> &params,
                        StatProcessor &processor) {
  CURL *curl = curl_easy_init();
  if (!curl) {
    return false;
  }
  const std::string &baseurl = "https://stats.nba.com/stats/";

  // construct full url, with query string 
  std::string url(baseurl + endpoint + "?");
  for (auto param = params.begin(); param != params.end(); ++param) {
    if (param != params.begin()) {
      url += "&";
    }
    url += param->first + "=" + param->second;
  }

  // setup custom header
  struct curl_slist *header = NULL;
  header = curl_slist_append(header, "Host: stats.nba.com");
  header = curl_slist_append(header, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:61.0) Gecko/20100101 Firefox/61.0");
  header = curl_slist_append(header, "Accept: application/json, text/plain, */*");
  header = curl_slist_append(header, "Accept-Language: en-US,en;q=0.5");
  header = curl_slist_append(header, "Connection: keep-alive");
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);


  std::string response;
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeDataCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
 
  CURLcode res = curl_easy_perform(curl);

  bool retVal = true;

  if (res != CURLE_OK) {
    retVal = false;
  } else {
    processor.process(response); 
  }

  curl_easy_cleanup(curl);
  curl_slist_free_all(header);

  return retVal;
}

}

