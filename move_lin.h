#ifndef __MOVE_LIN_H_
#define __MOVE_LIN_H_

#include <math_utils.h>

class move_lin {
    v3 v;
    public:
    move_lin(v3 _v) v(_v) {} 

    v3 spd( float t ) {
        return v;
    }
    v3 pos( float t ) {
        return v*t;
    }
    float qlen( float t ) {
        return get_pos(t).qlen();
    }
};

#endif /* __MOVE_LIN_H_ */

