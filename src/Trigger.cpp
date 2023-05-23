/**
 * @file Trigger.cpp
 * @author Mattie Nash (mnashkittycat@gmail.com)
 * @brief Implementations for the Trigger class.
 */

#include "Trigger.h"
#include "CommandScheduler.h"

namespace Commands{
    Trigger* Trigger::onTrue(Command* toSchedule){
        CommandScheduler::getDefaultEventLoop().add([this, toSchedule](){
            bool triggered = this->condition();
            if(triggered && !this->prev_triggered){
                CommandScheduler::getInstance().schedule(toSchedule);
            }
            this->prev_triggered = triggered;
        });
        return this;
    }

    Trigger* Trigger::onFalse(Command* toSchedule){
        CommandScheduler::getDefaultEventLoop().add([this, toSchedule](){
            bool triggered = this->condition();
            if(!triggered && this->prev_triggered){
                CommandScheduler::getInstance().schedule(toSchedule);
            }
            this->prev_triggered = triggered;
        });
        return this;
    }

}