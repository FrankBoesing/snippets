
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
