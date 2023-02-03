//
// Created by leo_b on 30/01/2023.
//

#pragma once

#include <asio.hpp>

#include "NetworkQueue.hpp"
#include "net_message.h"
#include "NetworkConnection.hpp"


namespace Network {

    class ClientInterface {
        public:

            ClientInterface() {

            }

            virtual ~ClientInterface() {
                Disconnect();
            }

            bool Connect(const std::string& host, const uint16_t port) {
                try {

                    // Resolve the host name into an IP address
                    asio::ip::tcp::resolver resolver(_ioContext);
                    asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

                    _connection = std::make_unique<Connection>(
                        Connection::Owner::Client,
                        _ioContext,
                        asio::ip::tcp::socket(_ioContext),
                        _incomingMessages
                            );

                    _connection->ConnectToServer(endpoints);

                    _threadContext = std::thread([this]() { _ioContext.run(); });

                }catch (std::exception& e) {
                    std::cerr << "Client Exception: " << e.what() << std::endl;
                    return false;
                }

                return true;
            }

            void Disconnect() {
                if (IsConnected()) {
                    _connection->Disconnect();
                }
                _ioContext.stop();
                if (_threadContext.joinable()) {
                    _threadContext.join();
                }
                _connection.release();
            }

            bool IsConnected() const {
                return _connection && _connection->IsConnected();
            }

            void Send(const Message& msg) {
                if (IsConnected()) {
                    _connection->Send(msg);
                }
            }

            void Update(size_t maxMessages = -1) {

                size_t messageCount = 0;
                while ((maxMessages == -1 || messageCount < maxMessages) && !_incomingMessages.empty()) {
                    auto msg = _incomingMessages.popFront().msg;
                    // TODO: Handle message
                    messageCount++;
                }
            }

            NetworkQueue<OwnedMessage>& GetIncomingMessages() {
                return _incomingMessages;
            }

        protected:
            asio::io_context _ioContext;
            std::thread _threadContext;
            std::unique_ptr<Connection> _connection;

        private:
            NetworkQueue<OwnedMessage> _incomingMessages;
    };
}
