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
                    }
                }
            }

            void ConnectToServer() {};
            bool Disconnect() {
                return true;
            };

            bool IsConnected() {
                return _socket.is_open();
            };

            bool Send(const Message<T>& msg) { return true; };

        protected:


            asio::ip::tcp::socket _socket;
            asio::io_context& _ioContext;

            NetworkQueue<OwnedMessage<T>>& _incomingMessages;
            NetworkQueue<Message<T>> _outgoingMessages;
            Owner _ownerType = Owner::Server;
            uint32_t _id = 0;
    };
}
