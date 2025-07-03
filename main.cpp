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

/*
    Server는 Boost.asio에서 제공하는 io_context라는 비동기 작업 관리자를 이용해서 
    클라이언트의 연결 요청을 비동기적으로 수락한다.
    각 클라이언트는 Session을 이용해서 별도로 비동기 작업을 처리한다.
    이 때, io_context는 클라이언트로부터 들어오는 비동기 작업들을 관리하고 실행하는 루프 역할을 하며
    io_context.run()이 호출되면 이 루프가 시작된다.
*/ 
