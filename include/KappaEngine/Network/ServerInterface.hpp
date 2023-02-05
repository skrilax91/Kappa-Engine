//
// Created by leo_b on 30/01/2023.
//

#pragma once

#include <cstdint>
#include <memory>
#include <asio.hpp>
#include <utility>
#include <map>

#include "net_message.h"
#include "NetworkConnection.hpp"
#include "NetworkQueue.hpp"

namespace Network {

    /**
     * @brief The ServerInterface class is the class that will manage the server.
     */
    class ServerInterface {

        public:
            /**
             * @brief ServerInterface Constructor of the ServerInterface class.
             *
             * This function will construct the ServerInterface class.
             *
             * @param port The port of the server.
             */
            ServerInterface( uint16_t port ): _acceptor( _ioContext, asio::ip::tcp::endpoint( asio::ip::tcp::v4(), port )) {

            };
            virtual ~ServerInterface() {
                Stop();
            };

            /**
             * @brief Start the server.
             *
             * This function will start the server.
             * It will also start the thread that will manage the server.
             *
             * @return True if the server is started, false otherwise.
             */
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

            /**
             * @brief Stop the server.
             *
             * This function will stop the server.
             * It will also stop the thread that is managing the server.
             */
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
                                _connections.back()->ConnectToClient(this, _idCounter++);
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

            /**
             * @brief Send a message to a client
             * @param client Client to send message to
             * @param msg Message to send
             */
            void MessageClient(std::shared_ptr<Connection>& client, const Message& msg ) {
                if (client && client->IsConnected()) {
                    client->Send(msg);
                }else {
                    OnClientDisconnect(client);
                    client.reset();
                    _connections.erase(std::remove(_connections.begin(), _connections.end(), client), _connections.end());
                }
            };

            /**
             * @brief Send a message to all clients
             * @param msg Message to send
             * @param ignoreClient Client to ignore
             */
            void MessageAllClients( const Message& msg, const std::shared_ptr<Connection>& ignore = nullptr ) {
                bool invalidClientExists = false;
                for (auto& client : _connections) {
                    if (client == ignore)
                        continue;

                    if (client && client->IsConnected()) {
                        client->Send(msg);
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

            /**
             * @brief Get the number of connected clients
             * @return Number of connected clients
             */
            size_t GetClientCount() const {
                return _connections.size();
            };

            /**
             * @brief Get all connected clients
             * @return Vector of connected clients
             */
            std::deque<std::shared_ptr<Connection>> GetClients() const {
                return _connections;
            };


            /**
             * @brief Get the client at the specified ID
             * @param id ID of the client
             * @return Pointer to the client
             */
            std::shared_ptr<Connection> GetClient(uint32_t id) {
                for (auto& client : _connections) {
                    if (client->GetID() == id) {
                        return client;
                    }
                }
                return nullptr;
            };

            /**
            * @brief Set the callback for when a client connects
            * @param callback Callback function
            *
            * The callback should return true if the client is accepted, false otherwise
            */
            void SetOnClientConnect( std::function<bool(std::shared_ptr<Connection>)> callback ) {
                _onClientConnect = callback;
            };


            /**
             * @brief Set the callback for when a client disconnects
             * @param callback Callback function
             */
            void SetOnClientDisconnect( std::function<void(std::shared_ptr<Connection>)> callback ) {
                _onClientDisconnect = callback;
            };

            /**
             * @brief Set the callback for when a client is validated
             * @param callback Callback function
             */
            void setOnClientValidated( std::function<void(std::shared_ptr<Connection>)> callback ) {
                _onClientValidated = callback;
            };


            /**
             * @brief Add a callback for when a message is received
             * @param id Message ID
             * @param callback Callback function
             *
             * The callback function should take a shared pointer to the client and a reference to the message
             */
            void AddOnMessageCallback( uint32_t id, std::function<void(std::shared_ptr<Connection>, Message&)> callback ) {
                if (_onMessageMap.find(id) != _onMessageMap.end()) {
                    return;
                }

                _onMessageMap[id] = callback;
            };

            /**
             * @brief Called when a client validates and is accepted
             * @param client Client that validated
             */
            void OnClientValidated( std::shared_ptr<Connection> client ) {
                std::cout << "[" << client->GetID() << "] Connection Validated" << std::endl;

                if (_onClientValidated) {
                    _onClientValidated(client);
                }
            };



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
            bool OnClientConnect( std::shared_ptr<Connection> client ) {
                if (_onClientConnect) {
                    return _onClientConnect(client);
                }
                return false;
            };

            /**
             * @brief Called when a client disconnects
             * @param client
             */
            void OnClientDisconnect( std::shared_ptr<Connection> client ) {
                if (_onClientDisconnect) {
                    _onClientDisconnect(client);
                }
            };

            /**
             * @brief Called when a message is received from a client
             * @param client Client that sent the message
             * @param msg Message received
             */
            void OnMessage( std::shared_ptr<Connection> client, Message& msg ) {
                uint32_t id = msg.header.id;
                auto iter = _onMessageMap.find(id);

                if (iter != _onMessageMap.end()) {
                    iter->second(client, msg);
                }
            };

        private:
            std::function<bool(std::shared_ptr<Connection>)> _onClientConnect = nullptr;
            std::function<void(std::shared_ptr<Connection>)> _onClientDisconnect = nullptr;
            std::function<void(std::shared_ptr<Connection>)> _onClientValidated = nullptr;

            std::map<uint32_t, std::function<void(std::shared_ptr<Connection>, Message&)> > _onMessageMap;

    };
}
