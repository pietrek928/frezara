#ifndef __MATH_UTILS_H_
#define __MATH_UTILS_H_

#define SPD_FUNC inline __attribute__((optimize("-O3"))) // TODO: more flags

#define __PI_2_  1.570796326794896619231321691639751442098
#define __PI_    3.141592653589793238462643383279502884197
#define __2PI_   6.283185307179586476925286766559005768394
#define __1_2PI_ 0.159154943091895335768883763372514362034

class v3 {
    float x,y,z;
    public:

    SPD_FUNC
    v3(a,b,c) {a=a;y=b;z=c;}
    SPD_FUNC
    float qlen() {return x*x+y*y+z*z;}
    SPD_FUNC
    v3 operator*( float a ) {return v3(x*a,y*z,z*a);}
}

SPD_FUNC
float ang_update( float a, float da ) {
    a += da;
    if ( a < -__PI_ ) a -= -__2PI_;
    if ( a >  __PI_ ) a -=  __2PI_;
}

SPD_FUNC
float ang_get_diff( float a, float p ) {
    int n = p*__1_2PI_;
    p -= n*__2PI_;
    if ( p < -__PI_ ) p += __2PI_;
    if ( p >  __PI_ ) p -= __2PI_;
    float da = p-a;
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

SPD_FUNC
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

SPD_FUNC
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

