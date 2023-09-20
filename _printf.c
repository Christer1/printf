#include "main.h"

/**
 * _printf - Printf function
 * @format: format.
 * Return: output chars.
 */
int _printf(const char *format, ...)
{
	int i, output = 0, output_chars = 0;
	int flags, width, precision, size, buffCount = 0;
	va_list arg;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(arg, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buffCount++] = format[i];
			if (buffCount == BUFF_SIZE)
				_buffer(buffer, &buffCount);
			/* write(1, &format[i], 1);*/
			output_chars++;
		}
		else
		{
			_buffer(buffer, &buffCount);
			flags = getFlags(format, &i);
			width = getWidth(format, &i, arg);
			precision = getPrecision(format, &i, arg);
			size = getSize(format, &i);
			++i;
			output = handle_print(format, &i, arg, buffer,
				flags, width, precision, size);
			if (output == -1)
				return (-1);
			output_chars += output;
		}
	}

	_buffer(buffer, &buffCount);
	va_end(arg);

	return (output_chars);
}

/**
 * _buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buffCount: Index at which to add next char, represents the length.
 */
void _buffer(char buffer[], int *buffCount)
{
	if (*buffCount > 0)
		write(1, &buffer[0], *buffCount);

	*buffCount = 0;
}
