#define TIMER1_PRESCALE_1 1
#define TIMER1_PRESCALE_8 2
#define TIMER1_PRESCALE_64 3
#define TIMER1_PRESCALE_256 4
#define TIMER1_PRESCALE_1024 5

// We use these macros because binary constants arent always supported. ugh.
#define HEX__(n) 0x##n##UL
#define B8__(x) ((x&0x0000000FLU)?1:0)  \
               +((x&0x000000F0LU)?2:0)  \
               +((x&0x00000F00LU)?4:0)  \
               +((x&0x0000F000LU)?8:0)  \
               +((x&0x000F0000LU)?16:0) \
               +((x&0x00F00000LU)?32:0) \
               +((x&0x0F000000LU)?64:0) \
               +((x&0xF0000000LU)?128:0)
#define B8(d) ((unsigned char)B8__(HEX__(d)))

#define NUM_ELEM(x) (sizeof (x) / sizeof (*(x)))
