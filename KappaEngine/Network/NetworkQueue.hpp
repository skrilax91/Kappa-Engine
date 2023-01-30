//
// Created by leo_b on 30/01/2023.
//

#pragma once

#include <deque>
#include <mutex>

namespace Network {
    template<typename T>
    class NetworkQueue {
        public:
            NetworkQueue() = default;
            NetworkQueue(const NetworkQueue<T>&) = delete;
            ~NetworkQueue() { clear(); };

            /**
             * @brief Return and maintain the first element of the queue
             * @return The first element of the queue
             */
            const T& front() {
                std::scoped_lock lock(_mutex);
                return _queue.front();
            }

            /**
             * @brief Return and maintain the last element of the queue
             * @return The last element of the queue
             */
            const T& back() {
                std::scoped_lock lock(_mutex);
                return _queue.back();
            }

            /**
             * @brief Check if the queue is empty
             * @return True if the queue is empty, false otherwise
             */
            bool empty() {
                std::scoped_lock lock(_mutex);
                return _queue.empty();
            }

            /**
             * @brief Return the queue size
             * @return The queue size
             */
            size_t size() {
                std::scoped_lock lock(_mutex);
                return _queue.size();
            }

            /**
             * @brief Clear the queue
             */
            void clear() {
                std::scoped_lock lock(_mutex);
                _queue.clear();
            }

            T popFront() {
                std::scoped_lock lock(_mutex);
                auto t = std::move(_queue.front());
                _queue.pop_front();
                return t;
            }

            T popBack() {
                std::scoped_lock lock(_mutex);
                auto t = std::move(_queue.back());
                _queue.pop_back();
                return t;
            }


        private:
            std::deque<T> _queue;
            std::mutex _mutex;
    };
}
