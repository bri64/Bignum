```
// Main functions
void printBignum(bignum array);	                            // Prints the bignum and newline
bignum newBignum();	                                        // Returns a bignum set to 0
bignum cloneBignum(bignum array);	                        // Copies a bignum
bignum stringToBignum(char * string);	                    // Returns a bignum, takes a string
bignum intToBignum(unsigned long long int value);	        // Returns a bignum, takes an int
unsigned long long int bignumToInt(bignum array);	        // Converts bignum to int if possible

// Math functions, takes a (bignum *) and a (bignum), returns to the first argument
bignum * bigIncrement(bignum * array);	                    // bignum++
bignum * bigDecrement(bignum * array);	                    // bignum--
bignum * bigSum(bignum * array1, bignum array2);	        // bignum + bignum
bignum * bigDiff(bignum * array1, bignum array2);           // bignum - bignum
bignum * bigMulti(bignum * array1, bignum array2);	        // bignum * bignum
bignum * bigExponent(bignum * base, bignum exp);	        // bignum ^ bignum

// Boolean functions, takes bignums
char bigEquals(bignum array1, bignum array2);	            // Returns true(1) if bignums are equal, otherwise false(0)
char bigGreaterThan(bignum array1, bignum array2);          // Returns true(1) if bignum1 is greater than bignum2, otherwise false(0) 
char bigLessThan(bignum array1, bignum array2);             // Returns true(1) if bignum1 is less than bignum2, otherwise false(0)

// Utility functions
unsigned long long int getSize(bignum array);	            // Returns number of digits in bignum
bignum newSizedBignum(unsigned long long int size);	        // Returns a bignum set to 0 with number of digits [size]
bignum * setSize(bignum * array, unsigned long long int size);	// Adds leading zeros or removes digit places from bignum
```
