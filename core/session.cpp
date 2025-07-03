#include "session.hpp"
#include <iostream>

Session::Session(boost::asio::ip::tcp::socket socket)
    : socket_(std::move(socket)) {}

void Session::start() {
    do_read();
}

void Session::do_read() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, 1024),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                do_write(length); // 받은 내용을 그대로 돌려줌 (Echo)
            }
        });
}

void Session::do_write(std::size_t length) {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/) {
            if (!ec) {
                do_read(); // 다시 읽기 대기
            }
        });
}