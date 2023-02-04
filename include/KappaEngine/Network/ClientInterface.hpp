//
// Created by leo_b on 30/01/2023.
//

#pragma once

#include <asio.hpp>

#include "NetworkQueue.hpp"
#include "net_message.h"
#include "NetworkConnection.hpp"


namespace Network {

    /**
     * @brief The ClientInterface class is the class that will manage the client.
     */
    class ClientInterface {
        public:

            /**
             * @brief ClientInterface Constructor of the ClientInterface class.
             *
             * This function will construct the ClientInterface class.
             */
            ClientInterface() {

            }

            virtual ~ClientInterface() {
                Disconnect();
            }

            /**
             * @brief Connect to a server.
             *
             * This function will connect the client to a server.
             *
             * @param host The host of the server.
             * @param port The port of the server.
             * @return True if the client is connected to the server, false otherwise.
             */
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

            /**
             * @brief Disconnect the client from the server.
             *
             * This function will disconnect the client from the server.
             */
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

            /**
             * @brief Check if the client is connected to the server.
             *
             * This function will check if the client is connected to the server.
             *
             * @return True if the client is connected to the server, false otherwise.
             */
            bool IsConnected() const {
                return _connection && _connection->IsConnected();
            }

            /**
             * @brief Send a message to the server.
             *
             * This function will send a message to the server.
             *
             * @param msg The message to send.
             */
            void Send(const Message& msg) {
                if (IsConnected()) {
                    _connection->Send(msg);
                }
            }

            /**
             * @brief Update the client.
             *
             * This function will update the client.
             * It will handle the incoming messages.
             *
             * @param maxMessages The maximum number of messages to handle.
             */
            void Update(size_t maxMessages = -1) {

                size_t messageCount = 0;
                while ((maxMessages == -1 || messageCount < maxMessages) && !_incomingMessages.empty()) {
                    auto msg = _incomingMessages.popFront().msg;
                    // TODO: Handle message
                    messageCount++;
                }
            }

            /**
             * @brief Get the incoming messages.
             *
             * This function will return the incoming messages.
             *
             * @return The incoming messages.
             */
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
