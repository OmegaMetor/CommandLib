/**
 * @file CommandScheduler.h
 * @author Mattie Nash (mnashkittycat@gmail.com)
 * @brief Definitions for the CommandScheduler class.
 */

#pragma once
#include "Command.h"
#include <functional>
#include <vector>
#include "EventLoop.h"
#include <map>

/**
 * @brief Main Namespace for CommandLib. All members are in this namespace.
 * 
 */
namespace Commands {
    /**
     * @brief Used to schedule commands and run the command loop.
     * 
     */
    class CommandScheduler {
    private:
    /**
     * @brief Stores the command scheduler instance.
     * 
     */
        static CommandScheduler* instance;
    /**
     * @brief Stores all currently scheduled and running commands.
     * 
     */
        std::vector<Command*> scheduledCommands = {};
    /**
     * @brief Cancels the given command.
     * 
     * @param command The command to cancel.
     * @param interrupted If the command was interrupted or not. Used to decide which function to call.
     */
        void cancel(Command* command, bool interrupted);
    /**
     * @brief Stores the default event loop, used for triggers and similar.
     * 
     */
        static EventLoop* defaultLoop;
    /**
     * @brief Stores all event loops.
     * 
     */
        std::vector<EventLoop*> eventLoops = {defaultLoop};
    /**
     * @brief Stored list of functions to be run when a command is initialized.
     * 
     */
        std::vector<std::function<void(Command*)>> onInit = {};
    /**
     * @brief Stores list of functions to be run when a command is interrupted.
     * 
     */
        std::vector<std::function<void(Command*)>> onInterrupt = {};
    /**
     * @brief Stores list of functions to be run when a command finishes.
     * 
     */
        std::vector<std::function<void(Command*)>> onFinish = {};
    /**
     * @brief Stores list of functions to be run when a command executes.
     * 
     */
        std::vector<std::function<void(Command*)>> onExecute = {};
    /**
     * @brief Maps currently used requirements to commands.
     * Used to check if a requirement is in use and what is using it.
     * 
     */
        std::map<void*, Command*> requirements = {};
    /**
     * @brief CommandScheduler Constructor
     * 
     */
        CommandScheduler() {};
    public:
    /**
     * @brief Get the instance of the command scheduler.
     * 
     * @return CommandScheduler& 
     */
        static CommandScheduler& getInstance();
    /**
     * @brief Runs the command scheduler once.
     * 
     */
        void run();
    /**
     * @brief Schedules a command.
     * 
     * @param command The command to schedule.
     */
        void schedule(Command* command);
    /**
     * @brief Cancels a command
     * 
     * @param command The command to cancel.
     */
        void cancel(Command* command);
    /**
     * @brief Adds an event loop to be polled every iteration of the scheduler.
     * 
     * @param eventLoop The event loop to add.
     */
        void addEventLoop(EventLoop* eventLoop);
    /**
     * @brief Adds a callback to be run when a command is scheduled.
     * 
     * @param function The callback function to run. Takes in one @ref Command "Command*" argument, the command being scheduled.
     */
        void onCommandInit(std::function<void(Command*)> function);
    /**
     * @brief Adds a callback to be run when a command is interrupted.
     * 
     * @param function The callback function to run. Takes in one @ref Command "Command*" argument, the command that was interrupted.
     */
        void onCommandInterrupt(std::function<void(Command*)> function);
    /**
     * @brief Adds a callback to be run when a command finishes.
     * 
     * @param function The callback function to run. Takes in one @ref Command "Command*" argument, the command that finished.
     */
        void onCommandFinish(std::function<void(Command*)> function);
    /**
     * @brief Adds a callback to be run when a command is executed.
     * 
     * @param function The callback function to run. Takes in one @ref Command "Command*" argument, the command being executed.
     */
        void onCommandExecute(std::function<void(Command*)> function);
    /**
     * @brief Get the Default Event Loop.
     * This event loop is typically used for triggers.
     * 
     * @return EventLoop& 
     */
        static EventLoop& getDefaultEventLoop();

    };
}