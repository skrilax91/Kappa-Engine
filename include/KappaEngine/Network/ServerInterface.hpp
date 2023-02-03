//
// Created by leo_b on 30/01/2023.
//

#pragma once

#include <cstdint>
#include <memory>
#include <asio.hpp>

#include "net_message.h"
#include "NetworkConnection.hpp"
#include "NetworkQueue.hpp"

namespace Network {
    class ServerInterface {

        public:
            ServerInterface( uint16_t port ): _acceptor( _ioContext, asio::ip::tcp::endpoint( asio::ip::tcp::v4(), port )) {

            };
            virtual ~ServerInterface() {
                Stop();
            };

            bool Start() {
                try {
                    WaitForClient();
                    _threadContext = std::thread([this]() { _ioContext.run(); });
                }catch (std::exception& e) {
                    std::cerr << "Server Exception: " << e.what() << std::endl;
                    return false;
                }

                std::cout << "[SERVER] started" << std::endl;
                return true;
            };

            void Stop() {
                _ioContext.stop();
                if (_threadContext.joinable()) {
                    _threadContext.join();
                }
                std::cout << "[SERVER] stopped" << std::endl;
            };

            /**
             * @brief Wait for a client to connect
             * ASYNC FUNCTION
             */
            void WaitForClient() {
                _acceptor.async_accept(
                        [this](std::error_code ec, asio::ip::tcp::socket socket) {
                            if (!ec) {
                                std::cout << "[SERVER] New connection: " << socket.remote_endpoint() << std::endl;

                                std::shared_ptr<Connection> newConnection = std::make_shared<Connection>(
                                        Connection::Owner::Server,
                                        _ioContext,
                                        std::move(socket),
                                        _incomingMessages
                                        );


                                std::cout << "[DEBUG] Testing client connection approval" << std::endl;
                                if (OnClientConnect(newConnection)) {
                                    std::cout << "[DEBUG] Connection approved, pushing back in connection pool" << std::endl;
                                    _connections.push_back(std::move(newConnection));
                                    _connections.back()->ConnectToClient(_idCounter++);
                                    std::cout << "[" << _connections.back()->GetID() << "] Connection approved" << std::endl;
                                }else {
                                    std::cout << "[-----] Connection refused" << std::endl;
                                }
                            }else {
                                std::cerr << "[SERVER] New connection error: " << ec.message() << std::endl;
                            }
                            WaitForClient();
                        });
            };

            void MessageClient(std::shared_ptr<Connection>& client, const Message& msg ) {
                if (client && client->IsConnected()) {
                    client->Send(msg);
                }else {
                    OnClientDisconnect(client);
                    client.reset();
                    _connections.erase(std::remove(_connections.begin(), _connections.end(), client), _connections.end());
                }
            };

            void MessageAllClients( const Message& msg, const std::shared_ptr<Connection>& ignore = nullptr ) {
                bool invalidClientExists = false;
                for (auto& client : _connections) {
                    if (client && client->IsConnected()) {
                        if (client != ignore) {
                            client->Send(msg);
                        }
                    }else {
                        OnClientDisconnect(client);
                        client.reset();
                        invalidClientExists = true;
                    }
                }

                if (invalidClientExists) {
                    _connections.erase(std::remove(_connections.begin(), _connections.end(), nullptr), _connections.end());
                }
            };


            /**
             * @brief Allow the server to update the network
             * @param maxMessages Maximum number of messages to process
             */
            void Update(size_t maxMessages = -1) {
                size_t messageCount = 0;
                while (messageCount < maxMessages && !_incomingMessages.empty()) {
                    auto msg = _incomingMessages.popFront();
                    OnMessage(msg.remote, msg.msg);
                    messageCount++;
                }
            };

            /////////////////////////////////
            // Server Console Commands
            /////////////////////////////////




        protected:

            /**
             * @brief Incoming messages from the clients
             */
            NetworkQueue<OwnedMessage> _incomingMessages;

            /**
             * @brief List of active client connections
             */
            std::deque<std::shared_ptr<Connection>> _connections;

            /**
             * @brief Context for the asio network operations
             */
            asio::io_context _ioContext;

            /**
             * @brief Thread context for the asio network operations
             */
            std::thread _threadContext;

            /**
             * @brief Acceptor for incoming connections
             */
            asio::ip::tcp::acceptor _acceptor;

            /**
             * @brief Counter for the client IDs
             */
            uint32_t _idCounter = 4;



        protected:
            /**
             * @brief Called when a client connects
             * @param client
             * @return true if the client is accepted, false otherwise
             */
            virtual bool OnClientConnect( std::shared_ptr<Connection> client ) {
                return false;
            };

            /**
             * @brief Called when a client disconnects
             * @param client
             */
            virtual void OnClientDisconnect( std::shared_ptr<Connection> client ) {

            };

            /**
             * @brief Called when a message is received from a client
             * @param client
             * @param msg
             */
            virtual void OnMessage( std::shared_ptr<Connection> client, Message& msg ) {

            };

    };
}
