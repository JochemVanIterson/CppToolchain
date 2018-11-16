#include "jsoncurl/jsoncurl.hpp"
#include <iostream>

int main() {
  jsonCurl getter("http://date.jsontest.com/");
  int result = getter.get();
  if(result != 0){
    if(result==1)std::cout << "Could not parse HTTP data as JSON" << std::endl;
    else if(result==2)std::cout << "Couldn't GET data" << std::endl;
    exit(0);
  }

  std::cout << "Successfully parsed JSON data" << std::endl;
  std::string httpData = getter.getHttpData();
  std::cout << "httpData: " << httpData << std::endl;

  Json::Value jsonData = getter.getJsonData();
  std::cout << "jsonData: " << jsonData.toStyledString() << std::endl;

  const std::string dateString(jsonData["date"].asString());
  const std::size_t unixTimeMs(jsonData["milliseconds_since_epoch"].asUInt64());
  const std::string timeString(jsonData["time"].asString());

  std::cout << "Natively parsed:" << std::endl;
  std::cout << "\tDate string: " << dateString << std::endl;
  std::cout << "\tUnix timeMs: " << unixTimeMs << std::endl;
  std::cout << "\tTime string: " << timeString << std::endl;
  std::cout << std::endl;

  return 0;
}
