/**
 * @file Command.h
 * @author Mattie Nash (mnashkittycat@gmail.com)
 * @brief Definitions for the Command class.
 */
#pragma once
#include <vector>

namespace Commands {
    /**
     * @brief Command to be scheduled. Virtual, subclass and implement required functions to use.
     * 
     */
    class Command {
    /**
     * @brief The requirements of the class.
     * 
     */
        std::vector<void*> requirements = {};
    /**
     * @brief Used so the scheduler can access @ref requirements without exposing it.
     * 
     */
        friend class CommandScheduler;
    public:
    /**
     * @brief The function to run every iteration of the command being scheduled.
     * 
     */
        virtual void run() = 0;
    /**
     * @brief Run to check if the command is finished.
     * If the command is finished, it will no longer be run and it's requirements will be freed.
     * 
     * @return true 
     * @return false 
     */
        virtual bool isFinished() = 0;
    /**
     * @brief Run when the command is cancelled by another command using the same requirements, when @ref interruptible is true.
     * 
     */
        virtual void cancelled() {}
    /**
     * @brief Run after isFinished returns true.
     * 
     */
        virtual void ended() {}
    /**
     * @brief If the command can be interrupted by other commands that share requirements.
     * 
     */
        bool interruptible = false;
    /**
     * @brief Adds the given requirement to the command.
     * 
     * @arg requirement The object to add as a requirement.
     */
        void addRequirement(void* requirement);
    };
}