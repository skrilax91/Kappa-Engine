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
            Connection() {};
            virtual ~Connection() {};

            virtual bool Connect();
            virtual bool Disconnect();
            virtual bool IsConnected() const;

            bool SendMessage(const Message<T>& msg);

        protected:
            asio::ip::tcp::socket _socket;
            asio::io_context _ioContext;

            NetworkQueue<OwnedMessage<T>> _incomingMessages;
            NetworkQueue<Message<T>> _outgoingMessages;
    };
}
