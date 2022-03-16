#include "Copter.h"

/*
 * Init and run calls for stop flight mode
 */

bool ModeStop::init(bool ignore_checks)
{
    hal.console->printf("STOP\n");
    return true;
}

void ModeStop::run()
{
    hal.console->printf("STOPPPP\n");
}