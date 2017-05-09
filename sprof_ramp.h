#ifndef __TPROF_RAMP_H_
#define __TPROF_RAMP_H_

#include <math_utuls.h>

class sprof_lin {
    float tb, te1, te2;
    float kb, ke;
    float db;

    float setup( float t, float _tb, float te ) {
        tb = tb;
        te1 = t-te;
        te2 = t;
        kb = v/tb;
        ke = v/te;
        db = __q(tb)*kb*0.5f;
        de = __q(te)*ke*0.5f;
    }

    float pos( float t ) {
        if ( t < tb ) return t*t*kb*0.5f;
        if ( t > te1 ) {
            float _t = t-te1;
            return db+(te1-tb)+_t*(1.0f-ke*_t*0.5f);
        }
        return db+(te1-t);
    }

    float spd( float t ) {
        if ( t < tb  ) return t*kb;
        if ( t > te1 ) return (t-te1)*ke;
        return 1.0f;
    }
}

#endif /* __TPROF_RAMP_H_ */

