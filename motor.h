#ifndef __MOTOR_H_
#define __MOTOR_H_

#include <math_utils.h>

// TODO: python ?

class motor {
    uint32_t *reg;
    uint32_t *freq_reg; // TODO: prescaler ?
    float k_pwm;

    void setup_regs( uint32_t *fr, uint32_t *r ) {
        freq_reg = fr;
        reg = r;
    }
    
    void setup_cnt( float cnt ) {
        *freq_reg = ((int)cnt)-1;
        k_pwm = cnt*0.5f;
    }

    SPD_FUNC
    void pwm_set( int n, float v ) {
        v += 1.0f;
        if ( v < 0.0f ) v = 0.0f;
        if ( v > 2.0f ) v = 2.0f;
        v *= k_pwm;
        reg[n] = (int)v;
    }
};

#endif /* __MOTOR_H_ */

