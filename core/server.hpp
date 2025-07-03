#pragma once
#include <boost/asio.hpp>
#include <memory>
#include "session.hpp"

class Server {
public:
    Server(boost::asio::io_context& io_context, unsigned short port);

private:
    void start_accept();

    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::io_context& io_context_;
};