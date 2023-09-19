#include "main.h"

void print_buffer(char buffer[], int *bufferindex);

/**
 * _printf - produces output according to a format
 *
 * @format: character string
 *
 * Return: number of characters excluding the null
 *
 */
int _printf(const char *format, ...)
{
	int a, count = 0, printed = 0;
	int flags, width, precision, size, bufferindex = 0;
	va_list bag;
	char buffer[BUFFER_SIZE];

	if (format == NULL)
		return (-1);
	va_start(bag, format);

	for (a = 0; format && format[a] != '\0'; a++)
	{
		if (format[a] != '%')
		{
			buffer[bufferindex++] = format[a];
			if (bufferindex == BUFFER_SIZE)
				print_buffer(buffer, &bufferindex);
			printed++;
		}
		else
		{
			print_buffer(buffer, &bufferindex);
			flags = take_flags(format, &a);
			width = take_width(format, &a, bag);
			precision = take_precision(format, &a, bag);
			size = take_size(format, &a);
			a++;
			count = handle_print(format, &a, bag, buffer,
					flags, width, precision, size);
			if (count == -1)
				return (-1);
			printed = printed + count;
		}
	}
	print_buffer(buffer, &bufferindex);
	va_end(bag);
	return (printed);
}

/**
 * print_buffer - print character array
 *
 * @buffer: array of characters to be printed
 *
 * @bufferindex: keeps track of the current position within the buffer
 *
 */
void print_buffer(char buffer[], int *bufferindex)
{
	if (*bufferindex > 0)
	{
		write(1, &buffer[0], *bufferindex);
	}
	*bufferindex = 0;
}

