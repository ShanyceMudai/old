#include "main.h"
/**
 * print_char - prints character
 *
 * @types: number of variable arguments to be printed
 *
 * @buffer: where the formatted output will be stored
 *
 * @flags: affect how characters are printed
 *
 * @width: specificies the width of the output
 *
 * @precision: how many char are printed
 *
 * @size: size of the output
 *
 * Return: an integer
 *
 */
int print_char(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char ch = va_arg(types, int);

	return (handle_write_char(ch, buffer, flags, width, precision, size));
}

/**
 * print_string - prints string
 *
 * @types: number of variable arguments to be printed
 *
 * @buffer: storage of output
 *
 * @flags: affect how characters are printed
 * @width: width specifier
 *
 * @precision: how many char are printed
 *
 * @size: size of the output
 *
 * Return: an integer
 *
 */
int print_string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int length = 0, a;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
		{
			str = "  ";
		}
		while (str[length] != '\0')
			length++;
		if (precision >= 0 && precision < length)
			length = precision;
		if (width > length)
		{
			if (flags & F_MINUS)
			{
				write(1, &str[0], length);
				for (a = width - length; a > 0; a--)
					write(1, " ", 1);
				return (width);
			}
		}
	}
	return (write(1, str, length));
}

/**
 * print_percent - prints percent
 * @types: variable number of arguments
 * @buffer: storage for array of characters
 * @flags: output specification
 * @width: width specifier
 * @precision: precision specifier
 * @size: size of the output
 * Return: an integer
 */
int print_percent(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%", 1));
}

/**
 * print_int - prints an integer
 * @types: number of arguments
 * @buffer: storage for array of characters
 * @flags: output specifications
 * @width: width specifier
 * @precision: precision specifier
 * @size: size of the output
 * Return: an integer
 */
int print_int(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int a = BUFFER_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[a--] = '0';
	buffer[BUFFER_SIZE - 1] = '\0';
	num = (unsigned long int)n;
	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}
	while (num > 0)
	{
		buffer[a--] = (num % 10) + '0';
		num /= 10;
	}
	a++;

	return (write_number(is_negative, a, buffer, flags, width, precision, size));
}

/**
 * print_binary - prints binary
 * @types: arguments
 * @buffer: storage area
 * @flags: output specification
 * @width: width specification
 * @precision: precision specification
 * @size: size of the output
 * Return: an integer
 */
int print_binary(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	unsigned int n, m, a, sum;
	unsigned int b[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	b[0] = n / m;
	for (a = 1; a < 32; a++)
	{
		m = m / 2;
		b[a] = (n / m) % 2;
	}
	for (a = 0, sum = 0, count = 0; a < 32; a++)
	{
		sum = sum + b[a];
		if (sum || a == 31)
		{
			char z = '0' + b[a];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
