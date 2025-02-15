//
// Created by Matthew Good on 24/7/21.
//

#ifndef GRAPHICAL_TOOL_KIT_ARRAY_H
#define GRAPHICAL_TOOL_KIT_ARRAY_H

#include "MemoryAllocator.h"

template<typename T>
class Array {
    MemoryAllocator::MemoryAllocation<T> data;
    bool empty = true;
public:

    Array() = default;

    Array(const Array<T> &other) : data(other.data), empty(other.empty) {}

    template<typename U>
    Array(const Array<U> &other) : data(other.data), empty(other.empty) {}

    Array<T> &operator=(const Array<T> &other) {
        data = other.data;
        empty = other.empty;
        return *this;
    }

    template<typename U>
    Array<T> &operator=(const Array<U> &other) {
        data = other.data;
        empty = other.empty;
        return *this;
    }

    Array(Array<T> &&other) : data(std::move(other.data)) {
        std::swap(empty, other.empty);
    }

    template<typename U>
    Array(Array<U> &&other) : data(std::move(other.data)) {
        std::swap(empty, other.empty);
    }

    Array<T> &operator=(Array<T> &&other) {
        data = std::move(other.data);
        std::swap(empty, other.empty);
        return *this;
    }

    template<typename U>
    Array<T> &operator=(Array<U> &&other) {
        data = std::move(other.data);
        std::swap(empty, other.empty);
        return *this;
    }

    bool isEmpty() const {
        return empty;
    }

    size_t getCapacity() const {
        return data.getCapacity();
    }

    size_t increaseCapacityBy(size_t amount) {
        return resize(data.getCapacity()+amount);
    }

    size_t increaseCapacityBy(size_t amount, const T & initializer) {
        return resize(data.getCapacity()+amount, initializer);
    }

    size_t decreaseCapacityBy(size_t amount) {
        return resize(data.getCapacity()-amount);
    }

    size_t resize(size_t newCapacity) {
        empty = newCapacity <= 0;
        size_t oldCapacity = data.getCapacity();
        data.reallocate(newCapacity);
        if (empty) return 0;
        return oldCapacity;
    }
    
    size_t resize(size_t newCapacity, const T & initializer) {
        empty = newCapacity <= 0;
        size_t oldCapacity = data.getCapacity();
        data.reallocate(newCapacity, initializer);
        if (empty) return 0;
        return oldCapacity;
    }

    template <typename U>
    void copyFrom(Array<U> & array) {
        data.copyFrom(array.data);
    }

    template <typename U>
    void copyTo(Array<U> & array) {
        data.copyTo(array.data);
    }

    template <typename U>
    void moveFrom(Array<U> & array) {
        data.moveFrom(array.data);
    }

    template <typename U>
    void moveTo(Array<U> & array) {
        data.moveTo(array.data);
    }

    template<typename TAG = T>
    typename std::enable_if<std::is_pointer<TAG>::value, T&>::type operator[](size_t index) {
        return data[index];
    }

    template<typename TAG = T>
    typename std::enable_if<!std::is_pointer<TAG>::value, T&>::type operator[](size_t index) {
        return data[index];
    }

    template<typename TAG = T>
    typename std::enable_if<std::is_pointer<TAG>::value, T const&>::type operator[](size_t index) const {
        return data[index];
    }

    template<typename TAG = T>
    typename std::enable_if<!std::is_pointer<TAG>::value, T const&>::type operator[](size_t index) const {
        return data[index];
    }

    T *getData() {
        return data.getData();
    }

    T *getData() const {
        return data.getData();
    }

    void remove(size_t index) {
        data.remove(index);
    }

    T* begin() {
        return data.begin();
    }

    const T* begin() const {
        return data.begin();
    }

    T* end() {
        return data.end();
    }

    const T* end() const {
        return data.end();
    }
};

#endif //GRAPHICAL_TOOL_KIT_ARRAY_H
