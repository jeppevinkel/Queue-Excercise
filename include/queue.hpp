#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <typeinfo>

template < size_t QUEUE_LEN, class DATA_TYPE >
class Queue
{
private:
    size_t head = 0, tail = 0;
    DATA_TYPE buffer[QUEUE_LEN];
    bool full = false;

    void advancePointer();
    void retreatPointer();
public:
    Queue();
    ~Queue();

    bool take(DATA_TYPE *value);
    void put(DATA_TYPE value);
    bool putSafe(DATA_TYPE value);
    bool isFull();
    bool isEmpty();
    size_t capacity();
    size_t size();
    const std::type_info* type();
};

/**
 * @brief Moves the head to the next element and drags the tail along if it's full
 */
template<size_t QUEUE_LEN, class DATA_TYPE>
void Queue<QUEUE_LEN, DATA_TYPE>::advancePointer()
{
    if (this->full)
    {
        this->tail = (this->tail + 1) % QUEUE_LEN;
    }
    
    this->head = (this->head +1) % QUEUE_LEN;
    this->full = this->head == this->tail;
}

/**
 * @brief Moves the tail to the next element and sets the queue to not full
 */
template<size_t QUEUE_LEN, class DATA_TYPE>
void Queue<QUEUE_LEN, DATA_TYPE>::retreatPointer()
{
    this->full = false;
    this->tail = (this->tail + 1) % QUEUE_LEN;
}

/**
 * @brief Takes from the tail of the buffer and retreats the queue if the queue is not empty
 * 
 * @param *value Pointer to save the value to
 * @return False if the queue is empty
 */
template<size_t QUEUE_LEN, class DATA_TYPE>
bool Queue<QUEUE_LEN, DATA_TYPE>::take(DATA_TYPE *value)
{
    bool r = false;

    if (!this->isEmpty())
    {
        *value =  this->buffer[this->tail];
        this->retreatPointer();

        r = true;
    }

    return r;
}

/**
 * @brief Places a value at the head of the buffer and advances the queue
 * 
 * @param value Value to put in the queue
 */
template<size_t QUEUE_LEN, class DATA_TYPE>
void Queue<QUEUE_LEN, DATA_TYPE>::put(DATA_TYPE value)
{
    this->buffer[this->head] = value;
    this->advancePointer();
}

/**
 * @brief Places a value at the head of the buffer and advances the queue if the queue isn't full
 * 
 * @param value Value to put in the queue
 * @return False if the queue is full
 */
template<size_t QUEUE_LEN, class DATA_TYPE>
bool Queue<QUEUE_LEN, DATA_TYPE>::putSafe(DATA_TYPE value)
{
    bool r = false;

    if (!this->full)
    {
        this->buffer[this->head] = value;
        this->advancePointer();

        r = true;
    }
    
    return r;
}

/**
 * @brief Returns whether the queue is full or not
 * 
 * @return True if the queue is full, false otherwise
 */
template<size_t QUEUE_LEN, class DATA_TYPE>
bool Queue<QUEUE_LEN, DATA_TYPE>::isFull()
{
    return this->full;
}

/**
 * @brief Returns whether the queue is empty or not
 * 
 * @return True if the queue is empty, false otherwise
 */
template<size_t QUEUE_LEN, class DATA_TYPE>
bool Queue<QUEUE_LEN, DATA_TYPE>::isEmpty()
{
    return !this->full && (this->head == this->tail);
}

/**
 * @brief Returns the maximum capacity of the queue
 * 
 * @return The capacity of the queue as defined during initialization
 */
template<size_t QUEUE_LEN, class DATA_TYPE>
size_t Queue<QUEUE_LEN, DATA_TYPE>::capacity()
{
    return QUEUE_LEN;
}

/**
 * @brief Returns the current amount of elements in the queue
 * 
 * @return The number of elements in the queue
 */
template<size_t QUEUE_LEN, class DATA_TYPE>
size_t Queue<QUEUE_LEN, DATA_TYPE>::size()
{
    size_t size = QUEUE_LEN;

    if (!this->isFull())
    {
        if (this->head >= this->tail)
        {
            size = this->head - this->tail;
        }
        else
        {
            size = QUEUE_LEN + this->head - this->tail;
        }
    }
    return size;
}

template<size_t QUEUE_LEN, class DATA_TYPE>
const std::type_info* Queue<QUEUE_LEN, DATA_TYPE>::type()
{
    return &typeid(DATA_TYPE);
}

template<size_t QUEUE_LEN, class DATA_TYPE>
Queue<QUEUE_LEN, DATA_TYPE>::Queue() {}

template<size_t QUEUE_LEN, class DATA_TYPE>
Queue<QUEUE_LEN, DATA_TYPE>::~Queue() {}

#endif