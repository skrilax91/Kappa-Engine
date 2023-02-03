//
// Created by leo_b on 30/01/2023.
//

#pragma once

#include <cstdint>
#include <vector>
#include <iostream>

namespace Network {

    struct MessageHeader {
        uint32_t id = 0;
        uint32_t size = 0;
    };

    struct Message {
        MessageHeader header{};
        std::vector<uint8_t> body;

        size_t size() const {
            return sizeof(MessageHeader) + body.size();
        }

        friend std::ostream& operator<<(std::ostream& os, const Message& msg) {
            os << "ID: " << msg.header.id << " Size: " << msg.header.size;
            return os;
        }

        template<typename DataType>
        friend Message& operator<<(Message& msg, const DataType& data) {
            static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed into vector");

            size_t i = msg.body.size();
            msg.body.resize(msg.body.size() + sizeof(DataType));
            std::memcpy(msg.body.data() + i, &data, sizeof(DataType));
            msg.header.size = msg.body.size();
            return msg;
        }

        template<typename DataType>
        friend Message& operator>>(Message& msg, DataType& data) {
            static_assert(std::is_standard_layout<DataType>::value, "Data is too complex to be pushed into vector");

            size_t i = msg.body.size() - sizeof(DataType);
            std::memcpy(&data, msg.body.data() + i, sizeof(DataType));
            msg.body.resize(i);
            msg.header.size = msg.body.size();
            return msg;
        }

    };

    class Connection;

    struct OwnedMessage {
        std::shared_ptr<Connection> remote = nullptr;
        Message msg;

        friend std::ostream& operator<<(std::ostream& os, const OwnedMessage& msg) {
            os << msg.msg;
            return os;
        }
    };

}
