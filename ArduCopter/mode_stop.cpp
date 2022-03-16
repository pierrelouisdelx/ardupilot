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
    if (motors->armed()) {
        // Motors should be Stopped
        motors->set_desired_spool_state(AP_Motors::DesiredSpoolState::SHUT_DOWN);
        copter.arming.disarm(AP_Arming::Method::LANDED);
    }
}