#ifndef __STEPER_MOTOR_H_
#define __STEPER_MOTOR_H_

#include <motor.h>

class stepper_motor : motor {
    float max_w, max_a;
    float kpos, kw, kf;

    void reg_spd( float fi, float w, float f ) {
        float k = (w+f*kf)*kw;
        cs_t v = cs_2pi( fi );
        pwm_setup( reg+0, v.c*k );
        pwm_setup( reg+1, v.s*k );
    }
};

#endif /* __STEPER_MOTOR_H_ */

