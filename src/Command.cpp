/**
 * @file Command.cpp
 * @author Mattie Nash (mnashkittycat@gmail.com)
 * @brief Implementations for the Command class.
 */

#include "Command.h"
#include <cstdarg>

namespace Commands {

void Command::addRequirement(void* requirement){

    Command::requirements.push_back(requirement);
}

}