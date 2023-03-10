//
// Created by leo_b on 30/01/2023.
//

#pragma once

#include <deque>
#include <mutex>

namespace Network {

    /**
     * @brief The NetworkQueue class is a thread-safe queue
     * @tparam T The type of the queue
     */
    template<typename T>
    class NetworkQueue {
        public:
            /**
             * @brief NetworkQueue Constructor of the NetworkQueue class.
             *
             * This function will construct the NetworkQueue class.
             */
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

            /**
             * @brief Pop the first element of the queue
             * @return The first element of the queue
             */
            T popFront() {
                std::scoped_lock lock(_mutex);
                auto t = _queue.front();
                _queue.pop_front();
                return t;
            }

            /**
             * @brief Pop the last element of the queue
             * @return The last element of the queue
             */
            T popBack() {
                std::scoped_lock lock(_mutex);
                auto t = _queue.back();
                _queue.pop_back();
                return t;
            }

            /**
             * @brief Push an element at the end of the queue
             * @param item The element to push
             */
            void pushBack(const T& item) {
                std::scoped_lock lock(_mutex);
                _queue.emplace_back(item);
            }

            /**
             * @brief Push an element at the beginning of the queue
             * @param item The element to push
             */
            void pushFront(const T& item) {
                std::scoped_lock lock(_mutex);
                _queue.emplace_front(item);
            }


        private:
            std::deque<T> _queue;
            std::mutex _mutex;
    };
}
