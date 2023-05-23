/**
 * @file EventLoop.cpp
 * @author Mattie Nash (mnashkittycat@gmail.com)
 * @brief Implementations for the EventLoop class.
 */
#include "EventLoop.h"

namespace Commands
{
    void EventLoop::poll(){
        for (int i = 0; i < EventLoop::events.size(); i++)
        {
            EventLoop::events.at(i)();
        }
        
    }

    void EventLoop::add(std::function<void()> event){
        EventLoop::events.push_back(event);
    }
}
