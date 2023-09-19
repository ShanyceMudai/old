#include "main.h"
/**
 * print_pointer - prints pointer
 * @types: arguments
 * @buffer: storage for an array
 * @flags: formatting output
 * @width: width of the output
 * @precision: control output
 * @size: size of the output
 * Return: an integer
 */
int print_pointer(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int index = BUFFER_SIZE - 2, length = 2, padd_start = 1;
	unsigned long number_address;
	char map_to[] = "0123456789abcdef";
	void *address = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (address == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFFER_SIZE - 1] = '\0';
	UNUSED(precision);

	number_address = (unsigned long)address;

	while (number_address > 0)
	{
		buffer[index--] = map_to[number_address % 16];
		number_address /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;
	index++;
	return (write_pointer(buffer, index, length,
				width, flags, padd, extra_c, padd_start));
}

/**
 * print_non_printable - prints non printable values
 * @types: arguments
 * @buffer: storage buffer
 * @flags: formatting flags
 * @width: width of the output
 * @precision: precision of the output
 * @size: size of output
 * Return: an integer
 */
int print_non_printable(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int a = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[a] != '\0')
	{
		if (is_printable(str[a]))
			buffer[a + offset] = str[a];
		else
			offset = offset + append_hexa_code(str[a], buffer, a + offset);
		a++;
	}
	buffer[a + offset] = '\0';

	return (write(1, buffer, a + offset));
}
/**
 * print_reverse - prints string in reverse
 * @types: arguments
 * @buffer: storage buffer
 * @flags: formatting flags
 * @width: width of output
 * @precision: control output
 * @size: size of output
 * Return: an integer
 */
int print_reverse(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char *str;
	int a, c = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (a = 0; str[a]; a++)
	{
		;
	}
	for (a = a - 1; a >= 0; a--)
	{
		char y = str[a];

		write(1, &y, 1);
		c++;
	}
	return (c);
}

/**
 * print_rot13string - string in rot13
 * @types: arguments
 * @buffer: storage buffer
 * @flags: formatting output
 * @width: width output
 * @precision: control output
 * @size: size of output
 * Return: an integer
 */
int print_rot13string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char i;
	char *str;
	unsigned int a, b;
	int c = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (a = 0; str[a]; a++)
	{
		for (b = 0; in[b]; b++)
		{
			if (in[b] == str[a])
			{
				i = out[b];
				write(1, &i, 1);
				c++;
				break;
			}
		}
		if (!in[b])
		{
			i = str[a];
			write(1, &i, 1);
			c++;
		}
	}
	return (c);
}
