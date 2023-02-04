//
// Created by leo_b on 30/01/2023.
//

#pragma once

#include <cstdint>
#include <vector>
#include <iostream>

namespace Network {

    /**
     * @brief The MessageHeader struct is the header of the message.
     * It contains the id of the message and the size of the message.
     * The size of the header is 8 bytes.
     */
    struct MessageHeader {
        uint32_t id = 0;
        uint32_t size = 0;
    };

    /**
     * @brief The Message struct is the message that will be sent between the server and the client.
     * It contains the header and the body of the message.
     */
    struct Message {

        /**
         * @brief The header of the message.
         */
        MessageHeader header{};

        /**
         * @brief The body of the message.
         */
        std::vector<uint8_t> body;

        /**
         * @brief Get the size of the message.
         *
         * This function will return the size of the message.
         *
         * @return The size of the message.
         */
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
