
//Fast abs() for 32 Bit-Integer

static inline __attribute__((always_inline)) int32_t abs32(int32_t val);
int32_t abs(int32_t val)
{
  int32_t result = -val;
  if (result < 0)
    result = val - (((uint32_t)val) >> 31);
  return result;
}



//Fast abs() for 16 Bit-Integer

static inline __attribute__((always_inline)) int16_t abs16(int16_t val);
int16_t abs16(int16_t val)
{
  int16_t result = -val;
  if (result >= 0)
    result -= (result >> 15);
  else
    result = val;
  return result;
}


//Superfast strlen

#define hasNulByte(x) ((x - 0x01010101) & ~x & 0x80808080)
#define SW (sizeof (int) / sizeof (char))

int xstrlen (const char *s) {
const char *p;
int d;

    p = s - 1;
    do {
        p++;
        if ((((int) p) & (SW - 1)) == 0) {
            do {
                d  = *((int *) p);
                p += SW;
            } while (!hasNulByte (d));
            p -= SW;
        }
    } while (*p != 0);
    return p - s;
}


// Teensy systick Restore old behaviour
// https://forum.pjrc.com/threads/46442-Minimal-Blink-fails-with-void-yield()?p=153602&viewfull=1#post153602

void mySystick_isr(void);

void setup(){
    _VectorsRam[15] = mySystick_isr;
}

[...]

extern "C" volatile uint32_t systick_millis_count;
void mySystick_isr(void)
{
    systick_millis_count++;    
}

//smallest software serial : (c) Frank Bösing
#define DEBUG_BAUD (115200)

void _serialDebugPrint(const uint8_t pin, const char * s) {
  const unsigned long bit = F_CPU / DEBUG_BAUD;
  ARM_DEMCR |= ARM_DEMCR_TRCENA;
  ARM_DWT_CTRL |= ARM_DWT_CTRL_CYCCNTENA;
  pinMode(pin, OUTPUT);
  digitalWriteFast(pin, 1);
  
  while (*s) {
   uint16_t c = (0x100 | *s++) << 1; //Add start & stop bits
    noInterrupts(); //<-- not needed in NMI
    unsigned long t = ARM_DWT_CYCCNT;    
    for (int i = 1; i<11; i++) {
      digitalWriteFast(pin, (c & 1) );
      c = c >> 1;      
      while ( ARM_DWT_CYCCNT - t < (i * bit) ) {;}
    }
    interrupts();//<-- not needed in NMI
  }
}
