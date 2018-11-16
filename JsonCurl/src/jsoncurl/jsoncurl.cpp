#define CURL_STATICLIB
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>

#include <curl/curl.h>
#include <json/json.h>

#include "jsoncurl.hpp"

namespace {
  std::size_t callback(const char* in, std::size_t size, std::size_t num, char* out){
    std::string data(in, (std::size_t) size * num);
    *((std::stringstream*) out) << data;
    return size * num;
  }
}

jsonCurl::jsonCurl(std::string inputurl){
  url = inputurl;

  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // Set remote URL.

  // Disable ipv6, will increase response time
  // curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

  // Don't wait forever, time out after 10 seconds.
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

  // Follow HTTP redirects if necessary.
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

  // Response information.
  httpCode = 0;

  // Hook up data handling function.
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

  // Response container
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &httpData);
}
int jsonCurl::get(){
  curl_easy_perform(curl);
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
  curl_easy_cleanup(curl);

  if (httpCode == 200) {
    Json::CharReaderBuilder jsonReader;
    std::string errs;

    if (Json::parseFromStream(jsonReader, httpData, &jsonData, &errs)) {
      return 0;
    } else {
      return 1;
    }
  } else {
    return 2;
  }
}
std::string jsonCurl::getHttpData(){
  return httpData.str();
}

Json::Value jsonCurl::getJsonData(){
  return jsonData;
}
