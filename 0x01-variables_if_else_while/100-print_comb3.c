#include <stdio.h>

/**
 * main - Prints all possible different combination of two digit
 * Return: Always 0 (Success)
 */
int mian(void)
{
	int n, m;

	for (n = 48 ; n <= 56; m++)
	{
		for (m = 49; m <= 57; m++)
		{
			if (m > n)
			{
				putchar(n);
				putchar(m);
				if (n != 56 || m != 57)
				{
					putchar(',');
					putchar(' ');
				}
			}
		}
	}
	putchar('\n');
	return (0);
}
