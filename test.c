#include <stm32f446xx.h>
#include <dbg.h>

#define PWM_FREQ 256 //1024
void SystemInit() {
}

#include <stdio.h>

#define __PI_2_ 1.570796326794896619231321691639751442098
#define __PI_   3.141592653589793238462643383279502884197
#define __2PI_  6.283185307179586476925286766559005768394

typedef struct {
    float c, s;
} cs_t;

inline cs_t cs_t_create( float c, float s ) {
    cs_t r;
    r.c = c;
    r.s = s;
    return r;
}

typedef struct {
    float a, w;
} trg_ctx;

void trg_ctx_init( trg_ctx * c, float w ) {
    c->a = 0;
    c->w = w;
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

float ang_update( float a, float da ) {
    a += da;
    if ( a < -__PI_ ) a -= -__2PI_;
    if ( a >  __PI_ ) a -=  __2PI_;
}

float get_ang_diff( float p, float a ) {
    int n = p/__2PI_;
    p -= n*__2PI_;
    if ( p < 0.0f ) p += __2PI_;
    if ( p >  __PI_ ) p -= __2PI_;
    float da = a-p;
    if ( da >  __PI_ ) da -= __2PI_;
    if ( da < -__PI_ ) da += __2PI_;
    return da;
}

cs_t cs_calc( float a ) {
    cs_t r;
    if ( a > 0.0f ) {
        if ( a > __PI_2_ ) {
            a -= __PI_2_;
            r = csf( a );
            return  cs_t_create( -r.s, r.c );
        } else return csf( a );
    } else {
        if ( a < -__PI_2_ ) {
            a -= -__PI_2_;
            r = csf( a );
            return cs_t_create( r.s, -r.c );
        } else return csf( a );
    }
}

int recv_b() {
    while( !( SPI1->SR & SPI_SR_RXNE ) );
    return SPI1->DR;
}

void send_b( int b ) {
    while( !( SPI1->SR  & SPI_SR_TXE ) );
    SPI1->DR = b;
}

trg_ctx ctx;
uint32_t last_s = 0;
void TIM2_IRQHandler() {
    uint32_t a = SysTick->VAL;
    uint32_t b = last_s - a;
    last_s = a;
    b &= 0x00FFFFFF;
    float w_max = 20;
    w_max *= 0.00001f;
    cs_t v = cs_calc( &ctx, b );
    float kk =  10000000.0f; //8500000.0f;// 300.0f/0.00003f;
    float u = ( kk*ctx.w + 50 ) * (1.0f/4.0f) * ( 12.0f/30.0f );
    int cc = PWM_FREQ/2 + v.c*u;
    if ( cc < 0 ) cc = 0;
    if ( cc > PWM_FREQ ) cc = PWM_FREQ;
    int ss = PWM_FREQ/2 + v.s*u;
    if ( ss < 0 ) ss = 0;
    if ( ss > PWM_FREQ ) ss = PWM_FREQ;
    TIM2->CCR1 = cc; // wypelnienie 
    TIM2->CCR2 = ss;
    if ( ctx.w < w_max )
        ctx.w += 0.000000001f;
}

int main (void)
{
    dbg_init();
    SCB->CPACR |= 0xF<<20;
    trg_ctx_init( &ctx, 0 );
#if 0
//RCC
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 
    //RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; 
    //RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; 
    //RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    RCC->AHB1ENR |= RCC_APB2ENR_SPI1EN;
    
    GPIOA->AFR[0] |= (5<<(4*5))  // AF5 SPI1
                  |  (5<<(4*6))  //AF6 SPI1
                  |  (5<<(4*7)); //AF7 SPI1
    GPIOA->MODER |= GPIO_MODER_MODER5_1 // afio
                 |  GPIO_MODER_MODER6_1
                 |  GPIO_MODER_MODER7_1;

    SPI1->CR1 = /*SPI_CR2_DFF /*|*/ ( SPI_CR1_BR_0*4 /* /32 */ ) | SPI_CR1_SPE | SPI_CR1_MSTR;

    while( 1 ) send_b( 0x04 );
    //send_b(  );
    while ( 1 ) JPUTI( recv_b() ); //*/
#endif

    SysTick->LOAD = 0x00FFFFFF;
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk
                  | SysTick_CTRL_CLKSOURCE_Msk;
                  //| SysTick_CTRL_TICKINT_Msk;


    NVIC_EnableIRQ( TIM2_IRQn );

    //*
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // zegar tim 

//GPIO 
    GPIOA->MODER &= ~( GPIO_MODER_MODER0 | GPIO_MODER_MODER1 | GPIO_MODER_MODER2 | GPIO_MODER_MODER3 );
    GPIOA->MODER |= GPIO_MODER_MODER0_1  // general purpus out
                 | GPIO_MODER_MODER1_1  // general purpus out
                 | GPIO_MODER_MODER2_1  // general purpus out
                 | GPIO_MODER_MODER3_1; // general purpus out

    GPIOA->AFR[0] |= (1<<(4*0)) // AF1 TIM2 0010
                  | (1<<(4*1)) // AF1 TIM2 0010
                  | (1<<(4*2)) // AF1 TIM2 0010
                  | (1<<(4*3));// AF1 TIM2 0010
    
    //GPIOA->ODR = 3;
    GPIOA->OTYPER = 0;

//TIM2
    //TIM2->PSC = 0; // dzieli czas przez 0
    TIM2->ARR = PWM_FREQ-1;

    TIM2->CCR1 = PWM_FREQ/2; // wypelnienie 
    TIM2->CCR2 = PWM_FREQ/2;
    TIM2->CCR3 = PWM_FREQ/2;
    TIM2->CCR4 = PWM_FREQ/2; 
    
    TIM2->CCMR1 = (TIM_CCMR1_OC1M_0*6)  // TIM2_CH1 PWM OC1M
                | (TIM_CCMR1_OC2M_0*6); // TIM2_CH2 PWM OC2M
    TIM2->CCMR2 = (TIM_CCMR2_OC3M_0*6)  // TIM2_CH3 PWM OC3M
                | (TIM_CCMR2_OC4M_0*6); // TIM2_CH4 PWM OC4M
    TIM2->DIER = TIM_DIER_UIE;

    TIM2->CCER = TIM_CCER_CC1E  // PWM ch1 en 
               | TIM_CCER_CC2E  // PWM ch2 en
               | TIM_CCER_CC3E  // PWM ch3 en
               | TIM_CCER_CC4E; // PWM ch4 en

    TIM2->CR1 = TIM_CR1_CEN  // TIM2 wlaczenie licznika
              | TIM_CR1_DIR; // zlicza w dół

    while ( 1 ) asm("");
    /*volatile int aa = 0;
    while(1)
    {
        if ( !aa ) {
            JPUTI(TIM2->CNT);
            aa=1000000;
        }
        aa--;
    } //*/
}
