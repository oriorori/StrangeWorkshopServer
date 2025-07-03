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
        // 원래는 this->start_accept();를 호출해야 하지만,
        // 람다에서 this를 캡처하고 있으므로 start_accept()만 호출해도 this->start_accept()로 해석해준다.
        start_accept(); // 다음 클라이언트를 위해 반복
    });
}

/*
acceptor_: TCP 소켓을 수신 대기하는 acceptor 객체입니다. 지정된 포트에서 클라이언트 연결을 기다립니다.
start_accept(): 클라이언트 연결을 수락하기 위한 비동기 작업을 시작합니다. 클라이언트가 연결되면 새로운 세션을 생성하고 시작합니다.
socket: 클라이언트와의 연결을 관리하는 소켓 객체입니다. 클라이언트가 연결되면 이 소켓을 사용하여 데이터를 송수신합니다.

async_accept(): 비동기적으로 클라이언트 연결 요청을 처리합니다. 두번째 파라미터는 콜백 함수로, 클라이언트의 연결 요청 처리 이후 호출됩니다.
이 때, 콜백은 연결 성공 여부와 관계없이 마지막에 무조건 실행됩니다.
그래서 error code가 없을 때만 Session 객체를 생성하고 start 메서드를 호출하는 것을 확인할 수 있습니다.
콜백 함수에 다시 start_accept()를 호출하여 다음 클라이언트 연결 요청을 기다립니다.

*/