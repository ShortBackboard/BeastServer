/*
	服务器类

	监听客户端，接受到一个连接就创建一个Connection类
*/

#include <iostream>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <memory.h>

#include "./Connection/Connection.h"

void Server(boost::asio::ip::tcp::acceptor &acceptor, boost::asio::ip::tcp::socket &socket)
{
	acceptor.async_accept(socket,
												[&](boost::beast::error_code ec)
												{
													if (!ec)
														std::make_shared<Connection>(std::move(socket))->start();
													Server(acceptor, socket);
												});
}

int main()
{
	try
	{
		auto const address = boost::asio::ip::make_address("127.0.0.1");
		unsigned short port = static_cast<unsigned short>(10000);

		std::cout << "Server start on port : " << port << std::endl;

		boost::asio::io_context ioc{1};

		boost::asio::ip::tcp::acceptor acceptor{ioc, {address, port}};
		boost::asio::ip::tcp::socket socket{ioc};
		Server(acceptor, socket);

		ioc.run();
	}
	catch (std::exception const &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return 0;
}