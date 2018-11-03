
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
