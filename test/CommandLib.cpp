#include "Command.h"
#include "CommandScheduler.h"
#include "Trigger.h"
#include <iostream>

class PrintCommand : public Commands::Command{
    int timesRun = 0;
    int timesToRun;
public:
    PrintCommand(int timesToRun): timesToRun(timesToRun-1){

    }
    void run(){
        std::cout << "Printed " << this->timesRun+1 <<" times." << std::endl;
        this->timesRun+= 1;
    }
    bool isFinished(){return this->timesRun > this->timesToRun;}
};

int main() {
    PrintCommand* command1 = new PrintCommand(10);
    command1->interruptible = true;
    int i = 3;
    float x = 43.234;
    command1->addRequirement(&i);
    


    PrintCommand* command2 = new PrintCommand(5);
    command2->interruptible = true;
    command2->addRequirement(&i);
    for (int i = 0; i < 32; i++)
    {
        Commands::CommandScheduler::getInstance().schedule(command1);
        Commands::CommandScheduler::getInstance().schedule(command2);
    }

    for (int timesRun = 0; timesRun < 12; timesRun++){
        Commands::CommandScheduler::getInstance().run();
    }
    return 0;
}