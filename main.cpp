#include <iostream>
#include <jsoncpp/json/json.h> // JSON库
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>

using namespace std;

int main()
{
  Json::Value root;
  root["id"] = 1001;
  root["data"] = "hello world";
  
  // 序列化
  // 结果保存在request中
  std::string request = root.toStyledString();
  std::cout << "request is " << request << std::endl;


  // 反序列化
  Json::Value ans;
  Json::Reader reader;
  // 结果保存在对象ans中
  reader.parse(request, ans);
  std::cout << "msg id is " << ans["id"] << " msg is " << ans["data"] << std::endl;

  return 0;
}