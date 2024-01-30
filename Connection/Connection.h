/*
  连接类
  一个新socket对应一个连接类用于通信
*/

#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>

// 重命名名字空间
namespace beast = boost::beast;		// from <boost/beast.hpp>
namespace http = beast::http;			// from <boost/beast/http.hpp>
namespace net = boost::asio;			// from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

class Connection : public std::enable_shared_from_this<Connection>
{
public:
  Connection(tcp::socket socket);

  // 开始函数
  void start();

  // 读请求
  void read_request();

  // 处理请求
	void process_request();

  // 处理get响应
	void create_get_response();

  //// 处理post响应
	void create_post_response();

  // 发送响应
	void write_response();

  // 超时检查
  void check_deadline();

private:
  tcp::socket _socket; // 用于通信的socket
  beast::flat_buffer _buffer{8192}; // 用于存储请求的缓冲区
  http::request<http::dynamic_body> _request; // 存储请求信息
  http::response<http::dynamic_body> _response; // 存储响应信息
  net::steady_timer _deadline{
    _socket.get_executor(), std::chrono::seconds(15)
  }; // 定时器15s
};