#include "Copter.h"

#if MODE_TEST_ENABLED == ENABLED

// initialize test mode
bool ModeTest::init(const bool ignore_checks)
{
    // initialise the vertical position controller
    if (!pos_control->is_active_z()) {
        pos_control->init_z_controller();
    }

    // set vertical speed and acceleration limits
    pos_control->set_max_speed_accel_z(-get_pilot_speed_dn(), g.pilot_speed_up, g.pilot_accel_z);
    pos_control->set_correction_speed_accel_z(-get_pilot_speed_dn(), g.pilot_speed_up, g.pilot_accel_z);

    // disable throttle and gps failsafe
    g.failsafe_throttle = FS_THR_DISABLED;
    g.failsafe_gcs = FS_GCS_DISABLED;
    g.fs_ekf_action = 0;

    // arm
    motors->armed(true);
    hal.util->set_soft_armed(true);

    return true;
}

void ModeTest::run()
{
    // Max Height in cm
    float max = 100.0;
    float v_speed = 0.0;

    // set vertical speed and acceleration limits
    pos_control->set_max_speed_accel_z(-get_pilot_speed_dn(), g.pilot_speed_up, g.pilot_accel_z);

    // apply SIMPLE mode transform to pilot inputs
    update_simple_mode();

    if (pos_control->get_pos_target_z_cm() > 100)
        pos_control->input_pos_vel_accel_z(max, v_speed, 0);
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
