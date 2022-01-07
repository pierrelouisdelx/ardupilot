#include "Copter.h"

#if MODE_TEST_ENABLED == ENABLED

// initialize test mode
bool ModeTest::init(const bool ignore_checks)
{
    // disable throttle and gps failsafe
    g.failsafe_throttle = FS_THR_DISABLED;
    g.failsafe_gcs = FS_GCS_DISABLED;
    g.fs_ekf_action = 0;

    // arm
    motors->armed(true);
    hal.util->set_soft_armed(true);

    return true;
}

void ModeTest::exit()
{
    // disarm
    motors->armed(false);
    hal.util->set_soft_armed(false);

    // re-enable failsafes
    g.failsafe_throttle.load();
    g.failsafe_gcs.load();
    g.fs_ekf_action.load();
}

#endif
