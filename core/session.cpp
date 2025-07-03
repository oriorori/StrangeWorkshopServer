#include "session.hpp"
#include <iostream>

Session::Session(boost::asio::ip::tcp::socket socket)
    : socket_(std::move(socket)) {}

void Session::start() {
    do_read();
}

// async_read_some: 클라이언트로부터 비동기적으로 데이터를 읽어오는 함수
void Session::do_read() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, 1024),
        [this, self](boost::system::error_code ec, std::size_t length) {
            std::cout << "데이터 수신 완료: " << std::string(data_, length) << std::endl;

            if (!ec) {
                do_write(length); // 받은 내용을 그대로 돌려줌 (Echo)
            }
        });
}

// async_write: 클라이언트에게 비동기적으로 데이터를 보내는 함수
void Session::do_write(std::size_t length) {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/) {
            std::cout << "데이터 전송 완료" << std::endl;

            if (!ec) {
                do_read(); // 다시 읽기 대기
            }
        });
}