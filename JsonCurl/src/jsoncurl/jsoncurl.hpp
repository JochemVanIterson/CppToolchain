#include <curl/curl.h>
#include <json/json.h>
#include <sstream>

class jsonCurl {
public:
  jsonCurl(std::string url);
  int get();
  std::string getHttpData();
  Json::Value getJsonData();
private:
  std::string url;
  CURL* curl;
  int httpCode;
  std::stringstream httpData;
  Json::Value jsonData;
};
