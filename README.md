# CommandLib Documentation!

### Purpose
This library is meant to provide a simple and extensible framework to possibly help simplify iteration based logic.

It is modeled after [WPILib's Command Based framework](https://docs.wpilib.org/en/stable/docs/software/commandbased/what-is-command-based.html) for programming FRC robots. This allows for loop based iteration logic to be written as a series of steps that begin and end based on their conditions.

### Structure
This library contains a singleton [CommandScheduler](@ref Commands::CommandScheduler) class that provides the main functionality. The scheduler, accessed with [Commands::CommandScheduler.getInstance()](@ref Commands::CommandScheduler.getInstance), is used to run commands each iteration of the loop, manage scheduling commands, and prevent conflicting command dependencies.

There are 2 ways of creating commands. Both can be used together in the same project without problems. However, each method has it's own benifits.

#### Subclassing

Commands can be made by subclassing [Commands::Command](@ref Commands::Command). Commands have a `void run()` function that is run every loop of the scheduler. This is where all the main functionality of the command should go. In addition to this, the command has a `bool isFinished()` function. When this function returns true, the command will be ended and no longer ran.

#### Functional

The functional method for command creation is not yet complete and will be documented in the near future.

### Requirements

Requirements are used to limit problems caused by dependencies shared between commands. A command will only be scheduled when either all of it's requirements are not being used or all the commands using a them can be cancelled. In the second case, the commands will be cancelled and the command will be scheduled.

All requirements are void* referencing the object that is required by the command.