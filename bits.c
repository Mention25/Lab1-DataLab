/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  /* 将最低位的 1 移到最高位 */
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	/* 异或等价于“不能同时为 1，且不能同时为 0” */
	return ~(x & y) & ~(~x & ~y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  /* 负数的符号掩码为全 1，非负数的符号掩码为全 0 */
  int mask = x >> 31;
  return (~x + 1) & mask;
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  /* 先取出源字节，再清空并覆盖目标字节 */
  int src8 = src << 3;
  int dst8 = dst << 3;
  int copy_byte = (x >> src8) & 0xFF;
  int mask = 0xFF << dst8;
  return (x & ~mask) | (copy_byte << dst8);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  /* 用掩码清除算术右移补入的符号位 */
  int mask = ~(((1 << 31) >> n) << 1);
  return (x >> n) & mask;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  /* 构造每个字节低四位为 1 的掩码，并交换两组半字节 */
  int mask = 0x0F | (0x0F << 8);
  mask = mask | (mask << 16);
  return ((x & mask) << 4) | ((x >> 4) & mask);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  /* 把 0 位视作 1，清除最低的 1 后再提取新的最低位 */
  int zeros = ~x;
  int rest = zeros & (zeros + ~0);
  return rest & (~rest + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  /* 逐级折叠异或，最低位最终表示全部位的奇偶性 */
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);
  return !(x & 1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  /* 位数对 32 取模，并分别拼接逻辑右移和左移部分 */
  int shift = n & 31;
  int leftShift = (~shift + 1) & 31;
  int mask = ~(((1 << 31) >> shift) << 1);
  return ((x >> shift) & mask) | (x << leftShift);
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  /* 半程减一作为偏置，商为奇数时再补一，实现中点取偶 */
  int half = 1 << (n + ~0);
  int bias = half + ~0 + ((x >> n) & 1);
  return ((x + bias) >> n) << n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  /* 先求向下取整且不溢出的均值，再按参数次序修正半整数 */
  int different = x ^ y;
  int floorMean = (x & y) + (different >> 1);
  int sx = x >> 31;
  int sy = y >> 31;
  int signDiff = sx ^ sy;
  int diff = y + ~x + 1;
  int xGreater = (sy & ~sx) | (~signDiff & (diff >> 31));
  int correction = (different & 1) & (xGreater & 1);
  return floorMean + correction;
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  /* 分别判断 x 是否同时小于两端点或同时大于两端点 */
  int sx = x >> 31;
  int sa = a >> 31;
  int sb = b >> 31;
  int signXA = sx ^ sa;
  int signXB = sx ^ sb;
  int diffXA = x + ~a + 1;
  int diffXB = x + ~b + 1;
  int xLessA = ((signXA & sx) | (~signXA & (diffXA >> 31))) & 1;
  int xLessB = ((signXB & sx) | (~signXB & (diffXB >> 31))) & 1;
  int xGreaterA = (!xLessA) & !!(x ^ a);
  int xGreaterB = (!xLessB) & !!(x ^ b);
  return !((xLessA & xLessB) | (xGreaterA & xGreaterB));
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  /* 与最大安全绝对值比较，溢出时按原符号选择饱和值 */
  int pattern = (0x99 << 8) | 0x99;
  int tmin = 1 << 31;
  int limit;
  int lower;
  int sx;
  int positiveOverflow;
  int negativeOverflow;
  int overflow;
  int saturated;
  int product = (x << 2) + x;
  pattern = pattern | (pattern << 16);
  limit = pattern ^ tmin;
  lower = ~limit + 1;
  sx = x >> 31;
  positiveOverflow = ~sx & ((limit + ~x + 1) >> 31);
  negativeOverflow = sx & ((x + ~lower + 1) >> 31);
  overflow = positiveOverflow | negativeOverflow;
  saturated = tmin ^ ~sx;
  return (overflow & saturated) | (~overflow & product);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  /* 两次加法的有向溢出量相加，反向溢出会彼此抵消 */
  int first = x + y;
  int firstOverflow = (~(x ^ y) & (x ^ first)) >> 31;
  int firstDirection = firstOverflow & ((x >> 31) | 1);
  int second = first + z;
  int secondOverflow = (~(first ^ z) & (first ^ second)) >> 31;
  int secondDirection = secondOverflow & ((first >> 31) | 1);
  return firstDirection + secondDirection;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  /* 拆出符号、阶码和尾数，用整数完成乘法与就近取偶 */
  unsigned sign = uf & 0x80000000u;
  unsigned exp = (uf >> 23) & 0xFFu;
  unsigned frac = uf & 0x7FFFFFu;
  unsigned significand;
  unsigned product;
  unsigned result;
  unsigned remainder;

  if (exp == 0xFFu)
    return uf;

  if (exp == 0) {
    product = frac * 3u;
    result = product >> 1;
    if ((product & 3u) == 3u)
      result++;
    return sign | result;
  }

  significand = (1u << 23) | frac;
  product = significand * 3u;
  if (product < (1u << 25)) {
    result = product >> 1;
    if ((product & 3u) == 3u)
      result++;
  } else {
    result = product >> 2;
    remainder = product & 3u;
    if (remainder > 2u || (remainder == 2u && (result & 1u)))
      result++;
    exp++;
    if (exp == 0xFFu)
      return sign | 0x7F800000u;
  }
  return sign | (exp << 23) | (result & 0x7FFFFFu);
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  /* 按实际指数定位小数位，比较被舍弃部分与半程值 */
  unsigned sign = uf & 0x80000000u;
  unsigned exp = (uf >> 23) & 0xFFu;
  unsigned frac = uf & 0x7FFFFFu;
  unsigned shift;
  unsigned mask;
  unsigned remainder;
  unsigned half;
  unsigned result;

  if (exp == 0xFFu || exp >= 150u)
    return uf;
  if (exp < 126u)
    return sign;
  if (exp == 126u) {
    if (frac == 0)
      return sign;
    return sign | 0x3F800000u;
  }

  shift = 150u - exp;
  mask = (1u << shift) - 1u;
  remainder = uf & mask;
  half = 1u << (shift - 1u);
  result = uf & ~mask;
  if (remainder > half ||
      (remainder == half && ((uf >> shift) & 1u)))
    result += 1u << shift;
  return result;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  /* 先定位最高有效位，再对需要丢弃的低位执行就近取偶 */
  unsigned sign = 0;
  unsigned magnitude;
  unsigned scan;
  unsigned exp;
  unsigned significand;
  unsigned shift;
  unsigned remainder;
  unsigned halfway;
  int highest = 0;

  if (x == 0)
    return 0;
  if (x < 0) {
    sign = 0x80000000u;
    magnitude = ~x + 1;
  } else {
    magnitude = x;
  }

  scan = magnitude;
  while (scan >> 1) {
    scan >>= 1;
    highest++;
  }
  exp = highest + 127;

  if (highest <= 23) {
    significand = magnitude << (23 - highest);
  } else {
    shift = highest - 23;
    significand = magnitude >> shift;
    remainder = magnitude & ((1u << shift) - 1u);
    halfway = 1u << (shift - 1u);
    if (remainder > halfway ||
        (remainder == halfway && (significand & 1u)))
      significand++;
    if (significand == (1u << 24)) {
      significand >>= 1;
      exp++;
    }
  }
  return sign | (exp << 23) | (significand & 0x7FFFFFu);
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  /* 用分治法依次统计每 2、4、8、16、32 位中的 1 */
  int mask1 = 0x55 | (0x55 << 8);
  int mask2 = 0x33 | (0x33 << 8);
  int mask4 = 0x0F | (0x0F << 8);
  mask1 = mask1 | (mask1 << 16);
  mask2 = mask2 | (mask2 << 16);
  mask4 = mask4 | (mask4 << 16);
  x = (x & mask1) + ((x >> 1) & mask1);
  x = (x & mask2) + ((x >> 2) & mask2);
  x = (x + (x >> 4)) & mask4;
  x = x + (x >> 8);
  x = x + (x >> 16);
  return x & 0x3F;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  /* 先反转字节内的位，再一次性颠倒四个字节的次序 */
  int mask4 = 0x0F | (0x0F << 8);
  int mask2;
  int mask1;
  int byteMask;
  mask4 = mask4 | (mask4 << 16);
  mask2 = mask4 ^ (mask4 << 2);
  mask1 = mask2 ^ (mask2 << 1);
  x = ((x >> 1) & mask1) | ((x & mask1) << 1);
  x = ((x >> 2) & mask2) | ((x & mask2) << 2);
  x = ((x >> 4) & mask4) | ((x & mask4) << 4);
  byteMask = 0xFF << 8;
  return (x << 24) | ((x & byteMask) << 8) |
         ((x >> 8) & byteMask) | ((x >> 24) & 0xFF);
}
