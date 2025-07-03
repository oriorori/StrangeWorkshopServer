#include "core/server.hpp"
#include <boost/asio.hpp>
#include <iostream>

int main() {
    try {
        boost::asio::io_context io_context;
        Server server(io_context, 12345); // 포트 12345에서 수신 대기
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "예외 발생: " << e.what() << std::endl;
    }
}