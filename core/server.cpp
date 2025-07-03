#include "server.hpp"

Server::Server(boost::asio::io_context& io_context, unsigned short port)
    : io_context_(io_context),
      acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
    start_accept();
}

void Server::start_accept() {
    auto socket = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);
    acceptor_.async_accept(*socket, [this, socket](boost::system::error_code ec) {
        if (!ec) {
            std::make_shared<Session>(std::move(*socket))->start();
        }
        start_accept(); // 다음 클라이언트를 위해 반복
    });
}