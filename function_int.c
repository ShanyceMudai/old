#include "main.h"
/**
 * print_unsigned - prints unsigned integer
 * @types: arguments
 * @buffer: storage for array
 * @flags: determines output
 * @width: width specifier
 * @precision: controls output
 * @size: size of the output
 * Return: an integer
 */
int print_unsigned(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int a = BUFFER_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsignd(num, size);

	if (num == 0)
		buffer[a--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = (num % 10) + '0';
		num = num / 10;
	}
	a++;
	return (write_unsignd(0, a, buffer, flags, width, precision, size));
}
/**
 * print_octal - prints integer in octal notation
 * @types: arguments
 * @buffer: storage for array
 * @flags: determine output
 * @width: width for output
 * @precision: controls output format
 * @size: size of the output
 * Return: an integer
 */
int print_octal(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int a = BUFFER_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int nit_num = num;

	UNUSED(width);

	num = convert_size_unsignd(num, size);

	if (num == 0)
		buffer[a--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = (num % 8) + '0';
		num = num / 8;
	}
	if (flags & F_HASH && nit_num != 0)
		buffer[a--] = '0';
	a++;
	return (write_unsignd(0, a, buffer, flags, width, precision, size));
}

/**
 * print_hexadecimal - print an integer in hexadecimal notation
 * @types: arguments
 * @buffer: storage for array
 * @flags: determines output
 * @width: width specifier
 * @precision: controls output
 * @size: size of the output
 * Return: an integer
 */
int print_hexadecimal(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
				flags, 'x', width, precision, size));
}
/**
 * print_hexa_upper - print an integer in hexadecimal notation in uppercase
 * @types: arguments
 * @buffer: storage for an array
 * @flags: determines output
 * @width: width specifier
 * @precision: controls output
 * @size: size of the output
 * Return: an integer
 */
int print_hexa_upper(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
				flags, 'X', width, precision, size));
}
/**
 * print_hexa - prints a hexadecimal in lower or uppercase
 * @types: arguments
 * @map_to: array of values
 * @buffer: storage for the array
 * @flags: determine output
 * @flag_ch: gets active flags
 * @width: width specifier
 * @precision: controls output
 * @size: size of the output
 * Return: an integer
 */
int print_hexa(va_list types, char map_to[], char buffer[],
		int flags, char flag_ch, int width, int precision, int size)
{
	int a = BUFFER_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int nit_num = num;

	UNUSED(width);

	num = convert_size_unsignd(num, size);

	if (num == 0)
		buffer[a--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[a--] = map_to[num % 16];
		num /= 16;
	}
	if (flags & F_HASH && nit_num != 0)
	{
		buffer[a--] = flag_ch;
		buffer[a--] = '0';
	}
	a++;

	return (write_unsignd(0, a, buffer, flags, width, precision, size));
}
