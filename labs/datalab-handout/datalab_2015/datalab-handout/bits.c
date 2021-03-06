/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 */

/* Instructions to Students:

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  long Funct(long arg1, long arg2, ...) {
      // brief description of how your implementation works
      long var1 = Expr1;
      ...
      long varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. (Long) integer constants 0 through 255 (0xFFL), inclusive. You are
      not allowed to use big constants such as 0xffffffffL.
  3. Function arguments and local variables (no global variables).
  4. Local variables of type int and long
  5. Unary integer operations ! ~
     - Their arguments can have types int or long
     - Note that ! always returns int, even if the argument is long
  6. Binary integer operations & ^ | + << >>
     - Their arguments can have types int or long
  7. Casting from int to long and from long to int

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting other than between int and long.
  7. Use any data type other than int or long.  This implies that you
     cannot use arrays, structs, or unions.

  You may assume that your machine:
  1. Uses 2s complement representations for int and long.
  2. Data type int is 32 bits, long is 64.
  3. Performs right shifts arithmetically.
  4. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31 (int) or 63 (long)

EXAMPLES OF ACCEPTABLE CODING STYLE:
  //
  // pow2plus1 - returns 2^x + 1, where 0 <= x <= 63
  //
  long pow2plus1(long x) {
     // exploit ability of shifts to compute powers of 2
     // Note that the 'L' indicates a long constant
     return (1L << x) + 1L;
  }

  //
  // pow2plus4 - returns 2^x + 4, where 0 <= x <= 63
  //
  long pow2plus4(long x) {
     // exploit ability of shifts to compute powers of 2
     long result = (1L << x);
     result += 4L;
     return result;
  }

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

CAUTION:
  Do not add an #include of <stdio.h> (or any other C library header)
  to this file.  C library headers almost always contain constructs
  that dlc does not understand.  For debugging, you can use printf,
  which is declared for you just below.  It is normally bad practice
  to declare C library functions by hand, but in this case it's less
  trouble than any alternative.

  dlc will consider each call to printf to be a violation of the
  coding style (function calls, after all, are not allowed) so you
  must remove all your debugging printf's again before submitting your
  code or testing it with dlc or the BDD checker.  */

extern int printf(const char *, ...);

/* Edit the functions below.  Good luck!  */
// 2
/*
 * copyLSB - set all bits of result to least significant bit of x
 *   Examples:
 *     copyLSB(5L) = 0xFFFFFFFFFFFFFFFFL,
 *     copyLSB(6L) = 0x0000000000000000L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
long copyLSB(long x) {
    return (x << 63) >> 63;
}
/*
 * dividePower2 - Compute x/(2^n), for 0 <= n <= 62
 *  Round toward zero
 *   Examples: dividePower2(15L,1L) = 7L, dividePower2(-33L,4L) = -2L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
long dividePower2(long x, long n) {
    // if x >= 0 || x == 0x800...0 , just return x >> n.
    // else if x < 0, should return -(-x >> n).
    // we could use '~x+1' to implement -x, but how to distinguish
    // between these two cases without using an if-else sentence?

    // Special case: 0x8000...0
    // Normally, ~x+1 != x. However 0x8000...0 is an exception,
    //  let's take advantage of that.
    // '000...0' for x==0x8000...0, otherwise it's '111...1'.
    long x_is_smallest_pos = (x ^ (~x + 1)) >> 63;

    long mask = x >> 63; // '1111..1' if x is negative
    // for 0x800...0 or positive, mask should be '000...0'
    mask = mask & x_is_smallest_pos;

    long plus_one_or_none = !!mask; // '1' if x is negative
    // if x >= 0, then x^mask == x^0000...0 == x
    // otherwise x^mask == x^1111...1 == ~x
    long result = ((x ^ mask) + plus_one_or_none) >> n;
    result = (result ^ mask) + plus_one_or_none;
    return result;
}
/*
 * distinctNegation - returns 1 if x != -x.
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 5
 *   Rating: 2
 */
long distinctNegation(long x) {
    return !!((~x + 1) ^ x);
}
/*
 * anyEvenBit - return 1 if any even-numbered bit in word set to 1
 *   where bits are numbered from 0 (least significant) to 63 (most significant)
 *   Examples anyEvenBit(0xAL) = 0L, anyEvenBit(0xEL) = 1L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 14
 *   Rating: 2
 */
long anyEvenBit(long x) {
    // Not allowed to use big constants?
    long mask = 0x55; // even numbered bits mask: [0101 0101]
    mask = (mask << 8) | mask;
    mask = (mask << 16) | mask;
    mask = (mask << 32) | mask;
    long result = mask & x;
    return !!(result);
}
// 3
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4L,5L) = 1L.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
long isLessOrEqual(long x, long y) {
    // Case1: If x and y don't have the same sign, check the sign
    //        of x to see if x>=0.
    // Case2: Else, check the sign of x_minus_y

    long x_sign = !!(x >> 63); // '0' if x>=0,  else '1'
    long y_sign = !!(y >> 63);
    long diff_sign = x_sign ^ y_sign; // '1' if x and y have different signs
    long case_1 =
        diff_sign & (!y_sign); // '1' if and only if y>=0 and x is negative.
    long y_minus_x =
        y + (~x + 1); // This won't overflow since x and y have the same signs
    long case_2 =
        (!diff_sign) & !(y_minus_x >> 63); // '1' if it's not case_1 and y>=x
    return case_1 | case_2;                // Put these two cases together
}
/*
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 7 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
long replaceByte(long x, long n, long c) {
    long bits = n << 3;
    long mask = ~(0xFFL << bits);
    long result = (x & mask) | (c << bits);
    return result;
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4L,5L) = 4L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
long conditional(long x, long y, long z) {
    long bool_x = !!x;
    long mask = bool_x << 63 >> 63;
    return (mask & y) | (~mask & z);
}
/*
 * bitMask - Generate a mask consisting of all 1's
 *   between lowbit and highbit
 *   Examples: bitMask(5L,3L) = 0x38L
 *   Assume 0 <= lowbit < 64, and 0 <= highbit < 64
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
long bitMask(long highbit, long lowbit) {
    // For x=111..1, x <<= 64 would return -1L (since shifted 64-64==0)
    // For x=111..1, x <<= 63 (Tmin), then x <<= 1, would return 0L (000..00)

    // Test scripts:
    // printf("Case1: mask << 64: %ld\n", mask << (highbit + 1));
    // printf("Case2: mask << 63, then << 1: ");
    // mask <<= highbit;
    // mask <<= 1;
    // printf("%ld\n", mask);
    // ./btest -f bitMask -1 63L -2 0L

    long mask = ~0x00L;
    long high = mask << highbit;
    high = ~(high << 1);
    long low = mask << lowbit;
    return low & high;
}
// 4
/*
 * isPalindrome - Return 1 if bit pattern in x is equal to its mirror image
 *   Example: isPalindrome(0x6F0F0123c480F0F6L) = 1L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4
 */
long isPalindrome(long x) {
    // Check:
    // https://stackoverflow.com/questions/4245936/mirror-bits-of-a-32-bit-word

    // idea: Take the lower 32 bits, do a bit-wise reversal,
    // then right shift the higer 32 bits, see if they are identical.

    // The most tricky thing is to avoid breaking the long constant limit
    // or the ops count limit.
    int reverse = x; // cast to INT, since we only need the lower 32 bits.

    // Create some masks.
    int constant_1_left = 0xAA;
    constant_1_left |= constant_1_left << 8;
    constant_1_left |= constant_1_left << 16;
    int constant_1_right = ~constant_1_left;

    int constant_2_left = 0xCC;
    constant_2_left |= constant_2_left << 8;
    constant_2_left |= constant_2_left << 16;
    int constant_2_right = ~constant_2_left;

    int constant_3_left = 0xF0;
    constant_3_left |= constant_3_left << 8;
    constant_3_left |= constant_3_left << 16;
    int constant_3_right = ~constant_3_left;

    int constant_4_left = 0xFF << 8;
    constant_4_left |= constant_4_left << 16;
    int constant_4_right = ~constant_4_left;

    int constant_6 = ~0x00;
    int mask = ~(0x01 << 31); // 01111111..1
    // Reverse those bits.
    reverse =
        (((reverse & constant_1_left) >> 1) & mask) | // logical right shift
        ((reverse & constant_1_right) << 1);

    reverse = (((reverse & constant_2_left) >> 2) & (mask >> 1)) |
              ((reverse & constant_2_right) << 2);

    reverse = (((reverse & constant_3_left) >> 4) & (mask >> 3)) |
              ((reverse & constant_3_right) << 4);

    reverse = (((reverse & constant_4_left) >> 8) & (mask >> 7)) |
              ((reverse & constant_4_right) << 8);

    reverse = (((reverse & constant_6) >> 16) & (mask >> 15)) |
              ((reverse & constant_6) << 16);

    // NOTICE: ALL THE CODE ABOVE IS TO DO THE FOLLOWING
    // WITHOUT BREAKING THE 'LONG CONSTANT' LIMIT.
    //--------------------------------------------------------------------
    // reverse = ((reverse & 0xAAAAAAAAAAAAAAAA) >> 1) |  // reversal for LONG
    //           ((reverse & 0x5555555555555555) << 1);

    // reverse = ((reverse & 0xCCCCCCCCCCCCCCCC) >> 2) |
    //           ((reverse & 0x3333333333333333) << 2);

    // reverse = ((reverse & 0xF0F0F0F0F0F0F0F0) >> 4) |
    //           ((reverse & 0x0F0F0F0F0F0F0F0F) << 4);

    // reverse = ((reverse & 0xFF00FF00FF00FF00) >> 8) |
    //           ((reverse & 0x00FF00FF00FF00FF) << 8);

    // reverse = ((reverse & 0xFFFF0000FFFF0000) >> 16) |
    //           ((reverse & 0x0000FFFF0000FFFF) << 16);
    //--------------------------------------------------------------------

    // see if they match
    return !((x >> 32) ^ reverse);
}
/*
 * trueFiveEighths - multiplies by 5/8 rounding toward 0,
 *  avoiding errors due to overflow
 *  Examples:
 *    trueFiveEighths(11L) = 6L
 *    trueFiveEighths(-9L) = -5L
 *    trueFiveEighths(0x3000000000000000L) = 0x1E00000000000000L (no overflow)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 20
 *  Rating: 4
 */
long trueFiveEighths(long x) {
    long sign = x >> 63;
    long x_div8 = x >> 3;
    long x_div8_mul5 = x_div8 + (x_div8 << 2);
    long remain = x & 0x07L; // Get least significant 3 bits.
    long remain_mul5 = remain + (remain << 2);
    // For positive, just add remain_mul5 / 8.
    // For negative, should add (remain_mul5 / 8) + 1, since 'x_div8' rounds
    // towards the smaller way. But why use (remain_mul5 + 7) / 8 instead of
    // (remain_mul5 + 8) / 8 ? Answer: Consider the case where x==0x8000..0, by
    // using the former one, the remain part would be zero(which is correct),
    // otherwise would be one in which case the answer is wrong.
    long result = (remain_mul5 + (sign & 0x07L)) >> 3;
    return result + x_div8_mul5;
}
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3L) = 0L, logicalNeg(0L) = 1L
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
long logicalNeg(long x) {
    long mask = x | (~x + 1);
    mask = mask >> 63;
    return mask + 1;
}
