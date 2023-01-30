//
// Created by leo_b on 30/01/2023.
//

#pragma once

#include <asio.hpp>

#include "KappaEngine/Network/NetworkQueue.hpp"
#include "KappaEngine/Network/net_message.h"


namespace Network {

    template<typename T>
    class ClientInterface {
        public:

            ClientInterface() : _socket(_ioContext) {

            }

            virtual ~ClientInterface() {
                Disconnect();
            }

            bool Connect(const std::string& host, const uint16_t port) {
                try {
                    _connection = std::make_unique<Connection<T>>();
                    asio::ip::tcp::resolver resolver(_ioContext);
                    asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

                    _connection->ConnectToServer(endpoints);

                    _threadContext = std::thread([this]() { _ioContext.run(); });

                }catch (std::exception& e) {
                    std::cerr << "Client Exception: " << e.what() << std::endl;
                    return false;
                }

                return true;
            }

            bool Disconnect() {
                if (IsConnected()) {
                    _connection->Disconnect();
                }
                _ioContext.stop();
                if (_threadContext.joinable()) {
                    _threadContext.join();
                }
                _connection.release();
                return true;
            }

            bool IsConnected() const {
                return _connection && _connection->IsConnected();
            }

            NetworkQueue<OwnedMessage<T>>& GetIncomingMessages() {
                return _incomingMessages;
            }

        protected:
            asio::io_context _ioContext;
            std::thread _threadContext;
            asio::ip::tcp::socket _socket;
            std::unique_ptr<Connection<T>> _connection;

        private:
            NetworkQueue<OwnedMessage<T>> _incomingMessages;
    };
}
