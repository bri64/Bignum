#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "bignum.h"

// Main functions
void printBignum(bignum array) {
	ulli num = getSize(array);
	ulli i;
	for (i = 0; i < num; i++) {
		printf("%d", array[i]);
	}
	printf("\n");
}

bignum newBignum() {
	bignum temp = (bignum) malloc(2 * sizeof(char));
	temp[0] = 0;
	temp[1] = -1;
	return temp;
}

bignum cloneBignum(bignum array) {
	ulli size = getSize(array);
	bignum temp = (bignum) malloc((size + 1) * sizeof(char));
	memcpy(temp, array, size + 1);
	temp[size] = -1;

	return temp;
}

bignum stringToBignum(char * string) {
	ulli size = strlen(string);
	bignum temp = newSizedBignum(size);
	int i;
	for (i = 0; i < size; i++) {
		temp[i] = string[i] - 48;
	}

	return temp;
}

bignum intToBignum(ulli value) {
	bignum temp;
	if (value != 0) {
		ulli digits = (log10(value)) + 1;
		ulli num = value;
		temp = newSizedBignum(digits);
		long long int i;
		for (i = digits - 1; i >= 0; i--) {
			temp[i] = num % 10;
			num /= 10;
		}	
		temp[digits] = -1;
	}
	else {
		temp = newBignum();
	}

	return temp;
}

ulli bignumToInt(bignum array) {
	ulli result = 0;
	bignum temp = newBignum();
	while(!bigEquals(array, temp)) {
		bigIncrement(&temp);
		result++;
	}

	return result;
}

// Math functions
bignum * bigIncrement(bignum * array) {
	ulli size = getSize(*array);
	long long int i;
	bignum temp = cloneBignum(*array);

	temp[size - 1] += 1;
	for (i = size - 1; i >= 0; i--) {
		if (temp[i] > 9 && i != 0) {
			temp[i] -= 10;
			temp[i - 1] += 1;
		}
		else if (temp[i] > 9 && i == 0) {
			temp[i] -= 10;
			size++;
			setSize(&temp, size);
			temp[0] = 1;
		}
	}
	
	// Set Array Delimiter
	temp[size] = -1;

	// Free Allocated Memory
	free(*array);
	*array = temp;

	return array;
}

bignum * bigDecrement(bignum * array) {
	ulli size = getSize(*array);
	long long int i;
	bignum temp = cloneBignum(*array);

	temp[size - 1] -= 1;
	for (i = size - 1; i >= 0; i--) {
		if (temp[i] < 0 && i != 1) {
			temp[i] += 10;
			temp[i - 1] -= 1;
		}
		else if (temp[i] < 0 && i == 1) {
			temp[i] += 10;
			size--;
			setSize(&temp, size);
		}
	}
	
	// Set array delimeter
	temp[size] = -1;

	// Free Allocated Memory
	free(*array);
	*array = temp;

	return array;
}

bignum * bigSum(bignum * array1, bignum array2) {
	ulli size1 	= getSize(*array1);
	ulli size2 	= getSize(array2);
	ulli sizeall 	= 0;
	long long int i;
	bignum temp 			= 0;

	if (size1 >= size2) {
		// Create Temp, Copy array2 contents, Set temp size to size1
		temp = cloneBignum(array2);
		setSize(&temp, size1);

		// Add Digits Together (ignore >9 for now)
		for (i = 0; i < size1; i++) {
			temp[i] += array1[0][i];
		}
		
		sizeall = size1;
	}
	else {
		// Create Temp, Copy array1 contents, Set temp size to size2
		temp = cloneBignum(*array1);
		setSize(&temp, size2);

		// Add Digits Together (ignore >9 for now)
		for (i = 0; i < size2; i++) {
			temp[i] += array2[i];
		}

		sizeall = size2;
	}

	// Check for carries (temp[i] > 9)
	for (i = sizeall - 1; i >= 0; i--) {
		if (temp[i] > 9 && i != 0) {
			temp[i] -= 10;
			temp[i - 1] += 1;
		}
		else if (temp[i] > 9 && i == 0) {
			temp[0] -= 10;
			sizeall++;
			setSize(&temp, sizeall);
			temp[0] = 1;
		}
	}

	// Free Allocated Memory
	free(*array1);
	*array1 = temp;

	return array1;
}

bignum * bigDiff(bignum * array1, bignum array2) {
	ulli size1 	= getSize(*array1);
	ulli size2 	= getSize(array2);
	ulli sizeall 	= 0;
	long long int i;
	bignum temp 			= 0;
	bignum result			= 0;

	if (size1 >= size2) {
		// Create Temp, Copy array2 contents, Set temp size to size1
		temp = cloneBignum(array2);
		setSize(&temp, size1);
		result = newSizedBignum(size1);

		// Flip-Flop if needed
		if (bigGreaterThan(*array1, array2)) {
			for (i = 0; i < size1; i++) {
				result[i] = array1[0][i] - temp[i];
			}
		} 
		else {
			for (i = 0; i < size1; i++) {
				result[i] = temp[i] - array1[0][i];
			}
		}
			
		sizeall = size1;
	}
	else {
		// Create Temp, Copy array1 contents, Set temp size to size2
		temp = cloneBignum(*array1);
		setSize(&temp, size2);
		result = newSizedBignum(size2);

		// Flop-Flip if needed
		if (bigGreaterThan(*array1, array2)) {
			for (i = 0; i < size2; i++) {
				result[i] = temp[i] - array2[i];
			}
		} 
		else {
			for (i = 0; i < size2; i++) {
				result[i] = array2[i] - temp[i];
			}
		}

		sizeall = size2;
	}

	// Check for negatives (temp[i] < 0)
	for (i = sizeall - 1; i >= 0; i--) {
		if (result[i] < 0 && i != 0) {
			result[i] += 10;
			result[i - 1] -= 1;
		}
	}

	// Negative conditioning
	if (bigLessThan(*array1, array2)) {
		result[0] *= -1;
	}
	
	// Free Allocated Memory
	free(*array1);
	*array1 = result;

	return array1;
}

bignum * bigMulti(bignum * array1, bignum array2) {
	bignum result = newBignum();
	ulli size1 = getSize(*array1);
	ulli size2 = getSize(array2);
	ulli i, j;

	ulli placeI = 0;
	for (i = size1; i > 0; i--) {
		ulli i_index = i - 1;
		ulli placeJ = 0;
		for (j = size2; j > 0; j--) {
			ulli j_index = j - 1;
			bignum temp = intToBignum(array1[0][i_index] * array2[j_index]);
			ulli size3 = getSize(temp);
			bignum temp2 = newSizedBignum(size3 + placeI + placeJ);
			
			if (size3 == 2) {
				temp2[0] = temp[0];
				temp2[1] = temp[1];
			}
			else {
				temp2[0] = temp[0];
			}

			bigSum(&result, temp2);
			free(temp);
			free(temp2);
			placeJ++;
		}
		placeI++;
	}

	free(*array1);
	*array1 = result;

	return array1;
}

bignum * bigExponent(bignum * base, bignum exp) {
	bignum temp = cloneBignum(*base);

	bignum counter = newBignum();
	counter[0] = 1;

	while (!bigEquals(counter, exp)) {
		bigMulti(&temp, *base);
		bigIncrement(&counter);
	}

	free(counter);
	free(*base);
	*base = temp;

	return base;
}

// Boolean functions
char bigEquals(bignum array1, bignum array2) {
	if (getSize(array1) != getSize(array2)) {
		return 0;
	}
	long long int i, size = getSize(array1);
	for (i = 0; i < size; i++) {
		if (array1[i] != array2[i]) {
			return 0;
		}
	} 
	return 1;
}

char bigGreaterThan(bignum array1, bignum array2) {
	if (bigEquals(array1, array2)) {
		return 0;
	}

	if (getSize(array1) > getSize(array2)) {
		return 1;
	} 
	else if (getSize(array1) < getSize(array2)) {
		return 0;
	}

	ulli i;
	for (i = 0; i < getSize(array1); i++) {
		if (array1[i] > array2[i]) {
			return 1;
		} 
		else if (array1[i] == array2[i]) {
			continue;
		} 
		else {
			return 0;
		}
	}

	return 0;
}

char bigLessThan(bignum array1, bignum array2) {
	if (bigEquals(array1, array2)) {
		return 0;
	}

	if (getSize(array1) < getSize(array2)) {
		return 1;
	} 
	else if (getSize(array1) > getSize(array2)) {
		return 0;
	}

	ulli i;
	for (i = 0; i < getSize(array1); i++) {
		if (array1[i] < array2[i]) {
			return 1;
		} 
		else if (array1[i] == array2[i]) {
			continue;
		} 
		else {
			return 0;
		}
	}
	return 0;
}


// Utility functions
ulli getSize(bignum array) {
	ulli num = 0;
	ulli i = 0;
	while (array[i] != -1) {
		num++;
		i++;
	}
	return num;
}

bignum newSizedBignum(ulli size) {
	bignum temp = (bignum) calloc(size + 1, sizeof(char));
	temp[size] = -1;
	return temp;
}

bignum * setSize(bignum * array, ulli size) {
	bignum temp = newSizedBignum(size);
	//bignum temp = (bignum) malloc((size + 1) * sizeof(char));
	temp[size] = -1;
	ulli size2 = getSize(*array);
	if (size >= size2) {
		ulli num = sizeof(char) * (size - size2);
		memcpy(temp + num, *array, size2);
		//ulli i;
		//for (i = 0; i < num; i++) {
		//	temp[i] = 0;
		//}
	}
	else {
		memcpy(temp, *array + (sizeof(char) * (size2 - size)), size);
	}
	free(*array);
	temp[size] = -1;
	*array = temp;

	return array;
}
