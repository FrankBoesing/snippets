

//-------------------------------------------------------

boolean summertime_EU(int year, byte month, byte day, byte hour, byte tzHours)
// European Daylight Savings Time calculation by "jurs" for German Arduino Forum
// input parameters: "normal time" for year, month, day, hour and tzHours (0=UTC, 1=MEZ)
// return value: returns true during Daylight Saving Time, false otherwise
{
  if (month<3 || month>10) return false; // keine Sommerzeit in Jan, Feb, Nov, Dez
  if (month>3 && month<10) return true; // Sommerzeit in Apr, Mai, Jun, Jul, Aug, Sep
  if (month==3 && (hour + 24 * day)>=(1 + tzHours + 24*(31 - (5 * year /4 + 4) % 7)) || month==10 && (hour + 24 * day)<(1 + tzHours + 24*(31 - (5 * year /4 + 1) % 7)))
    return true;
  else
    return false;
}


//https://forum.arduino.cc/index.php?topic=481251.0

__asm__ __volatile__(
  ".macro NOPX      P1          \n\t"
  ".rept &P1                    \n\t"
  "NOP                          \n\t"
  ".endr                        \n\t"   // End of Repeat
  ".endm                        \n\t"   // End of macro
);

void setup() {
  __asm__ __volatile__("NOPX 82");  
}

//nanos()
inline __attribute__((always_inline)) uint32_t nanos(void) {  
  return (1000ull * ARM_DWT_CYCCNT) / (F_CPU / 1000000) ;
}


//LDREX/STREX detects interrupts
#include "arm_math.h"
#include "core_cmInstr.h"

void setup() { delay(1000); }

void loop() {
static uint32_t a = 0;
static uint32_t b = 0;
uint32_t c,d, dummy;
 do {
  __LDREXW(&dummy);
  c = a;
  d = b;
  if (c==10) {delay(2);a++;}//<- interrupt happens most likely here   
 } while ( __STREXW(0, &dummy));
 Serial.printf("c: %d, c:%d\n",c,d);
 delay(500);
 a++;b++;
}


