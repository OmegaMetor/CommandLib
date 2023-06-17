/**
 * @file Trigger.h
 * @author Mattie Nash (mnashkittycat@gmail.com)
 * @brief Definitions for the Trigger class.
 */
#pragma once
#include <functional>
#include "Command.h"

namespace Commands {
    /**
     * @brief Trigger Class
     * 
     * Used to schedule commands when boolean conditions change.
     * 
     */
    class Trigger {
    private:
    /**
     * @brief The state of the condition on the previous iteration of the loop.
     * Used for while(True|False)
     * 
     */
        bool prev_triggered = false;
    /**
     * @brief A function returning a boolean, used for the state of the trigger.
     * 
     */
        std::function<bool()> condition;
    public:
    /**
     * @brief Construct a new Trigger object
     * 
     * @param condition A function that takes no arguments and returns a boolean. Used as the condition for the trigger.
     */
        Trigger(std::function<bool()> condition): condition(condition) {};
    /**
     * @brief Add a command to schedule when the trigger's condition becomes true.
     * 
     * @param toSchedule The command to be scheduled.
     * @return self 
     */
        Trigger* onTrue(Command* toSchedule); 
    /**
     * @brief Add a command to schedule when the trigger's condition becomes false.
     * 
     * @param toSchedule The command to be scheduled.
     * @return self
     */
        Trigger* onFalse(Command* toSchedule);
    /**
     * @brief Schedules the command when the condition is true, and cancels it when it becomes false.
     * 
     * If the command ends, it will ***not*** be rescheduled.
     * 
     * @param toSchedule The command to be scheduled.
     * @return Self
     */
        Trigger* whileTrue(Command* toSchedule);
    /**
     * @brief Schedules the command when the condition is false, and cancels it when it becomes true.
     * 
     * If the command ends, it will ***not*** be rescheduled.
     * 
     * @param toSchedule The command to be scheduled.
     * @return Self
     */
        Trigger* whileFalse(Command* toSchedule);
    };
}