#ifndef __MOTOR_H_
#define __MOTOR_H_

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
};

#endif /* __MOTOR_H_ */

