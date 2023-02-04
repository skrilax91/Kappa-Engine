//
// Created by leo_b on 30/01/2023.
//

#pragma once

#include <memory>
#include <asio.hpp>

#include "net_message.h"
#include "NetworkQueue.hpp"

namespace Network {

    /**
     * @brief The Connection class is the class that will manage the connection between the server and the client.
     */
    class Connection: public std::enable_shared_from_this<Connection> {
        public:

            /**
             * @brief The Owner enum is the enum that will define the owner of the connection.
             */
            enum class Owner {
                Server,
                Client
            };

            /**
             * @brief Connection Constructor of the Connection class.
             *
             * This function will construct the Connection class.
             *
             * @param parent The owner of the connection.
             * @param context The context of the connection.
             * @param socket The socket of the connection.
             * @param qin The queue of the incoming messages.
             */
            Connection(Owner parent, asio::io_context& context, asio::ip::tcp::socket socket, NetworkQueue<OwnedMessage>& qin)
            : _socket(std::move(socket)), _ioContext(context), _incomingMessages(qin) {
                _ownerType = parent;
            };

            virtual ~Connection() = default;

            /**
             * @brief Get the id of the connection.
             *
             * This function will return the id of the connection.
             *
             * @return The id of the connection.
             */
            uint32_t GetID() {
                return _id;
            }

            /**
             * @brief Connect to a client
             * @param id The id of the client
             */
            void ConnectToClient(uint32_t id = 0) {
                if (_ownerType == Owner::Server) {
                    if (_socket.is_open()) {
                        _id = id;
                        ReadHeader();
                    }
                }
            }

            /**
             * @brief Connect to a server
             * @param endpoints The endpoints of the server
             */
            void ConnectToServer(const asio::ip::tcp::resolver::results_type& endpoints) {
                if (_ownerType == Owner::Client) {
                    asio::async_connect(_socket, endpoints,
                        [this](std::error_code ec, asio::ip::tcp::endpoint endpoint) {
                            if (!ec) {
                                ReadHeader();
                            }
                        }
                    );
                }
            };

            /**
             * @brief Disconnect the connection.
             *
             * This function will disconnect the connection.
             */
            void Disconnect() {
                if (IsConnected()) {
                    _ioContext.post([this]() { _socket.close(); });
                }
            };

            /**
             * @brief Check if the connection is connected.
             *
             * This function will check if the connection is connected.
             *
             * @return True if the connection is connected, false otherwise.
             */
            bool IsConnected() {
                return _socket.is_open();
            };

            /**
             * @brief Send a message to the connection.
             *
             * This function will send a message to the connection.
             *
             * @param msg The message to send.
             */
            void Send(const Message& msg) {
                if (IsConnected()) {
                    _ioContext.post([this, msg]() {
                        bool writeInProgress = !_outgoingMessages.empty();
                        _outgoingMessages.pushBack(msg);
                        if (!writeInProgress) {
                            WriteHeader();
                        }
                    });
                }
            };

        protected:


            asio::ip::tcp::socket _socket;
            asio::io_context& _ioContext;

            NetworkQueue<OwnedMessage>& _incomingMessages;
            Message _tmpMessage;

            NetworkQueue<Message> _outgoingMessages;
            Owner _ownerType = Owner::Server;
            uint32_t _id = 0;


        private:

            /**
             * @brief Read the header of the message
             * ASYNC FUNCTION
             */
            void ReadHeader() {
                asio::async_read(_socket, asio::buffer(&_tmpMessage.header, sizeof(MessageHeader)),
                     [this](std::error_code ec, std::size_t length) {
                         if (!ec) {
                             if (_tmpMessage.header.size > 0) {
                                 _tmpMessage.body.resize(_tmpMessage.header.size);
                                 ReadBody();
                             } else {
                                 AddToIncomingMessageQueue();
                             }
                         } else {
                             std::cout << "[CLIENT::" << _id << "] Failed to read header" << std::endl;
                             _socket.close();
                         }
                     }
                );
            };

            /**
             * @brief Read the body of the message
             * ASYNC FUNCTION
             */
            void ReadBody() {
                asio::async_read(_socket, asio::buffer(_tmpMessage.body.data(), _tmpMessage.body.size()),
                     [this](std::error_code ec, std::size_t length) {
                         if (!ec) {
                             AddToIncomingMessageQueue();
                         } else {
                             std::cout << "[CLIENT::" << _id << "] Failed to read body" << std::endl;
                             _socket.close();
                         }
                     }
                );
            };

            /**
             * @brief Write the header of the message
             * ASYNC FUNCTION
             */
            void WriteHeader() {
                asio::async_write(_socket, asio::buffer(&_outgoingMessages.front().header, sizeof(MessageHeader)),
                     [this](std::error_code ec, std::size_t length) {
                         if (!ec) {
                             if (_outgoingMessages.front().header.size > 0) {
                                 WriteBody();
                             } else {
                                 _outgoingMessages.popFront();
                                 if (!_outgoingMessages.empty()) {
                                     WriteHeader();
                                 }
                             }
                         } else {
                             std::cout << "[CLIENT::" << _id << "] Failed to write header" << std::endl;
                             _socket.close();
                         }
                     }
                );
            };

            /**
             * @brief Write the body of the message
             * ASYNC FUNCTION
             */
            void WriteBody() {
                asio::async_write(_socket, asio::buffer(_outgoingMessages.front().body.data(), _outgoingMessages.front().header.size),
                     [this](std::error_code ec, std::size_t length) {
                         if (!ec) {
                             _outgoingMessages.popFront();
                             if (!_outgoingMessages.empty()) {
                                 WriteHeader();
                             }
                         } else {
                             std::cout << "[CLIENT::" << _id << "] Failed to write body" << std::endl;
                             _socket.close();
                         }
                     }
                );
            };

            /**
             * @brief Add the message to the incoming message queue
             */
            void AddToIncomingMessageQueue() {
                if (_ownerType == Owner::Server) {
                    _incomingMessages.pushBack({this->shared_from_this(), _tmpMessage});
                } else {
                    _incomingMessages.pushBack({nullptr, _tmpMessage});
                }

                ReadHeader();
            };
    };
}