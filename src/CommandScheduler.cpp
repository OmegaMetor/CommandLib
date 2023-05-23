/**
 * @file CommandScheduler.cpp
 * @author Mattie Nash (mnashkittycat@gmail.com)
 * @brief Implementations for the CommandScheduler class.
 */

#include "CommandScheduler.h"
#include <algorithm>
#include <iostream>

namespace Commands {

    CommandScheduler* CommandScheduler::instance = nullptr;
    EventLoop* CommandScheduler::defaultLoop = new EventLoop();
    CommandScheduler& CommandScheduler::getInstance() {
        if (!instance) {
            instance = new CommandScheduler();
        }
        return *instance;
    }

    EventLoop& CommandScheduler::getDefaultEventLoop() {
        if (!defaultLoop) {
            defaultLoop = new EventLoop();
        }
        return *defaultLoop;
    }

    void CommandScheduler::addEventLoop(EventLoop *eventLoop) {
        CommandScheduler::eventLoops.push_back(eventLoop);
    }

    void CommandScheduler::onCommandInit(std::function<void(Command*)> func){
        CommandScheduler::onInit.push_back(func);
    };

    void CommandScheduler::onCommandInterrupt(std::function<void(Command*)> func){
        CommandScheduler::onInterrupt.push_back(func);
    };

    void CommandScheduler::onCommandFinish(std::function<void(Command*)> func){
        CommandScheduler::onFinish.push_back(func);
    };

    void CommandScheduler::onCommandExecute(std::function<void(Command*)> func){
        CommandScheduler::onExecute.push_back(func);
    };

    void CommandScheduler::cancel(Command *command){
        
    };


    void CommandScheduler::run() {
        // Run object periodic functions

        // Poll triggers for new commands to run.
        for (int i = 0; i < CommandScheduler::eventLoops.size(); i++)
        {
            CommandScheduler::eventLoops.at(i)->poll();
        }

        // Run and finish scheduled commands.
        for (int i = 0; i < CommandScheduler::scheduledCommands.size(); i++)
        {
            CommandScheduler::scheduledCommands.at(i)->run();
            for (int handl = 0; handl < CommandScheduler::onExecute.size(); handl++) {
                CommandScheduler::onExecute.at(handl)(CommandScheduler::scheduledCommands.at(i));
            }
            if (CommandScheduler::scheduledCommands.at(i)->isFinished()) {
                for (int handl = 0; handl < CommandScheduler::onFinish.size(); handl++) {
                    CommandScheduler::onFinish.at(handl)(CommandScheduler::scheduledCommands.at(i));
                }
                CommandScheduler::scheduledCommands.at(i)->ended();
                for (int req = 0; req < CommandScheduler::scheduledCommands.at(i)->requirements.size(); req++)
                {
                    CommandScheduler::requirements.erase(CommandScheduler::scheduledCommands.at(i)->requirements.at(req));
                }
                CommandScheduler::scheduledCommands.erase(CommandScheduler::scheduledCommands.begin() + i);
                i -= 1;
            }
        }

    }

    void CommandScheduler::schedule(Command* command) {
        // TODO: Don't schedule commands if in the run loop.

        if (std::find(CommandScheduler::scheduledCommands.begin(), CommandScheduler::scheduledCommands.end(), command) != CommandScheduler::scheduledCommands.end()) return;

        for (int object = 0; object < command->requirements.size(); object++)
        {
            std::cout << object << std::endl;
            if (CommandScheduler::requirements.find(command->requirements.at(object)) != CommandScheduler::requirements.end()) {
                Command* scheduledCommand = CommandScheduler::requirements.at(command->requirements[object]);
                if (!scheduledCommand->interruptible) {
                    return;
                }

            }
        }

        for (int object = 0; object < command->requirements.size(); object++)
        {
            if (CommandScheduler::requirements.find(command->requirements.at(object)) != CommandScheduler::requirements.end()) {
                Command* scheduledCommand = CommandScheduler::requirements.at(command->requirements[object]);
                auto commandIndex = std::find(CommandScheduler::scheduledCommands.begin(), CommandScheduler::scheduledCommands.end(), scheduledCommand);
                if (commandIndex != CommandScheduler::scheduledCommands.end()) {
                    for (int handl = 0; handl < CommandScheduler::onInterrupt.size(); handl++) {
                        CommandScheduler::onInterrupt.at(handl)(scheduledCommand);
                    }
                    CommandScheduler::scheduledCommands.erase(commandIndex);
                }

                for (int requirement = 0; requirement < scheduledCommand->requirements.size(); requirement++)
                {
                    auto requiremetIndex = CommandScheduler::requirements.find(command->requirements.at(requirement));
                    if (requiremetIndex != CommandScheduler::requirements.end()) {
                        CommandScheduler::requirements.erase(requiremetIndex);
                    }
                }

                scheduledCommand->cancelled();

            }
        }

        CommandScheduler::scheduledCommands.push_back(command);
        for (int handl = 0; handl < CommandScheduler::onInit.size(); handl++) {
            CommandScheduler::onInit.at(handl)(command);
        }
        for (int object = 0; object < command->requirements.size(); object++)
        {
            CommandScheduler::requirements.insert(std::make_pair(command->requirements.at(object), command));
        }
    }


}