#ifndef __TPROF_RAMP_H_
#define __TPROF_RAMP_H_

#include <math_utuls.h>

class sprof_lin {
    float tb, te1, te2;
    float kb, ke;

    float setup( float t, float _tb, float te ) {
        tb = tb;
        te1 = t-te;
        te2 = t;
        kb = v/tb;
        ke = v/te;
    }
    
    float spd( float t ) {
        if ( t < tb  ) return t*kb;
        if ( t > te2 ) return (t-te1)*ke;
        return 1.0f;
    }
}

#endif /* __TPROF_RAMP_H_ */

