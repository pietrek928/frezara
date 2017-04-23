#ifndef __STEPER_MOTOR_H_
#define __STEPER_MOTOR_H_

class stepper_motor {
    float max_w, max_a;
    float kfi, kw, ka;
    float k_pwm;
    uint32_t *reg;

    void set_regs( float fi, float w, float a ) {
        float k = 1.0f + w*kw + a*ka;
        cs_t v = cs_2pi( fi );
        pwm_setup( reg+0, v.c* );
        pwm_setup( reg+1, v.s* );
    }
};

#endif /* __STEPER_MOTOR_H_ */

