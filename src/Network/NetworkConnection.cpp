//
// Created by leo_b on 04/02/2023.
//

#include <KappaEngine/Network/NetworkConnection.hpp>
#include <KappaEngine/Network/ServerInterface.hpp>

namespace Network {
    void Connection::ReadValidation(ServerInterface *server)  {
        asio::async_read(_socket, asio::buffer(&_handshakeIn, sizeof(uint64_t)),
             [this, server](std::error_code ec, std::size_t length) {
                 if (!ec) {
                     if (_ownerType == Owner::Server) {
                         if (_handshakeIn == _handshakeCheck) {
                             std::cout << "[SERVER] Client validated" << std::endl;
                             WriteID(this->_id);
                             server->OnClientValidated(this->shared_from_this());
                         } else {
                             std::cout << "[SERVER] Client failed validation" << std::endl;
                             _socket.close();
                         }
                     } else {
                         _handshakeOut = scramble(_handshakeIn);
                         WriteValidation();
                     }
                 } else {
                     _socket.close();
                 }
             }
        );
    }
}