#pragma once
#include <boost/asio.hpp>
#include <memory>

class Session : public std::enable_shared_from_this<Session> {
public:
    explicit Session(boost::asio::ip::tcp::socket socket);
    void start();

private:
    void do_read();
    void do_write(std::size_t length);

    boost::asio::ip::tcp::socket socket_;
    char data_[1024];
};