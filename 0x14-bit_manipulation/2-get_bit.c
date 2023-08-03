#include "main.h"

/**
 * get_bit - Returns value of bit at an index in a decimal number
 * @n: Number to search
 * @index: Index of the bit
 *
 * Return: Value of bit
 */
int get_bit(unsigned long int n, unsigned int index)
{
	int bit_val;

	if (index > 63)
		return (-1);

	bit_val = (n >> index) & 1;

	return (bit_val);
}
