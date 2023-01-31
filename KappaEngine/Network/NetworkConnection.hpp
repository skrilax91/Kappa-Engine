//
// Created by leo_b on 30/01/2023.
//

#pragma once

#include <memory>
#include <asio.hpp>

#include "KappaEngine/Network/net_message.h"
#include "KappaEngine/Network/NetworkQueue.hpp"

namespace Network {

    template<typename T>
    class Connection: public std::enable_shared_from_this<Connection<T>> {
        public:
            enum class Owner {
                Server,
                Client
            };

            Connection(Owner parent, asio::io_context& context, asio::ip::tcp::socket socket, NetworkQueue<OwnedMessage<T>>& qin)
            : _socket(std::move(socket)), _ioContext(context), _incomingMessages(qin) {
                _ownerType = parent;
            };
            virtual ~Connection() = default;

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


            void Disconnect() {
                if (IsConnected()) {
                    _ioContext.post([this]() { _socket.close(); });
                }
            };

            bool IsConnected() {
                return _socket.is_open();
            };

            void Send(const Message<T>& msg) {
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

            NetworkQueue<OwnedMessage<T>>& _incomingMessages;
            Message<T> _tmpMessage;

            NetworkQueue<Message<T>> _outgoingMessages;
            Owner _ownerType = Owner::Server;
            uint32_t _id = 0;


        private:

            /**
             * @brief Read the header of the message
             * ASYNC FUNCTION
             */
            void ReadHeader() {
                asio::async_read(_socket, asio::buffer(&_tmpMessage.header, sizeof(MessageHeader<T>)),
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
                asio::async_write(_socket, asio::buffer(&_outgoingMessages.front().header, sizeof(MessageHeader<T>)),
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
