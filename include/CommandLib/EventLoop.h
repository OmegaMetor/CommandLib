/**
 * @file EventLoop.h
 * @author Mattie Nash (mnashkittycat@gmail.com)
 * @brief Definitions for the EventLoop class.
 */
#pragma once
#include <vector>
#include "Trigger.h"
#include <functional>

namespace Commands {
    /**
     * @brief Used to run functions each iteration of the scheduler.
     * 
     */
    class EventLoop{
    /**
     * @brief Contains the functions to be run each iteration of the scheduler.
     * 
     */
        std::vector<std::function<void()>> events = {};
    public:
    /**
     * @brief Construct a new Event Loop object
     * 
     */
        EventLoop(){};
    /**
     * @brief Polls the event loop. Essentially, runs all contained events.
     * 
     */
        void poll();
    /**
     * @brief Adds a function to the event loop.
     * 
     * @param event The function to be ran.
     */
        void add(std::function<void()> event);
    };
}