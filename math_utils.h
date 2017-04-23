#ifndef __MATH_UTILS_H_
#define __MATH_UTILS_H_

#define __PI_2_ 1.570796326794896619231321691639751442098
#define __PI_   3.141592653589793238462643383279502884197
#define __2PI_  6.283185307179586476925286766559005768394

float ang_update( float a, float da ) {
    a += da;
    if ( a < -__PI_ ) a -= -__2PI_;
    if ( a >  __PI_ ) a -=  __2PI_;
}

/* 
 * WARNING: uses division
 * */
float ang_get_diff( float p, float a ) {
    int n = p/__2PI_;
    p -= n*__2PI_;
    if ( p < -__PI_ ) p += __2PI_;
    if ( p >  __PI_ ) p -= __2PI_;
    float da = a-p;
    if ( da >  __PI_ ) da -= __2PI_;
    if ( da < -__PI_ ) da += __2PI_;
    return da;
}

typedef struct {
    float c, s;
} cs_t;

inline cs_t cs_t_create( float c, float s ) {
    cs_t r;
    r.c = c;
    r.s = s;
    return r;
}

cs_t csf( float x ) {
    float x1 = x;
    float x2 = x*x;
    float rc, rs;
    rc = rs = 1;

    x = x2;
    rc += x*( -1.0f / 2 );
    rs += x*( -1.0f / 6 );

    x *= x2;
    rc += x*( 1.0f / 24 );
    rs += x*( 1.0f / 120 );

    // v--- to mozna wyjebac zeby bylo szybsze
    x *= x2;
    rc += x*( -1.0f / 720 );
    rs += x*( -1.0f / 5040 );

    return cs_t_create( rc, rs*x1 );
}

cs_t cs_2pi( float a ) {
    float a = c->a;
    a += c->w*dt;
    if ( a < -__PI_ ) a -= -__2PI_;
    if ( a >  __PI_ ) a -=  __2PI_;
    c->a = a;
    cs_t r;
    if ( a > 0.0f ) {
        if ( a > __PI_2_ ) {
            a -= __PI_2_;
            r = csf( a );
            return cs_t_create( -r.s, r.c );
        } else return csf( a );
    } else {
        if ( a < -__PI_2_ ) {
            a -= -__PI_2_;
            r = csf( a );
            return cs_t_create( r.s, -r.c );
        } else return csf( a );
    }
}

#endif /* __MATH_UTILS_H_ */

