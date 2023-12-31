#include "main.h"
/**
 * handle_print - Prints an argument based on its type
 * @fmt: Formatted string in which to print the arguments.
 * @arg: arg of arguments to be output.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int handle_print(const char *fmt, int *ind, va_list arg, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unknow_len = 0, output_chars = -1;
	fmt_t fmt_types[] = {
		{'c', _char}, {'s', _string}, {'%', _percent},
		{'i', _int}, {'d', _int}, {'b', _binary},
		{'u', _unsigned}, {'o', _octal}, {'x', _hexadecimal},
		{'X', _hexa_upper}, {'p', _pointer}, {'S', _non_printable},
		{'r', _reverse}, {'R', _rot13string}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(arg, buffer, flags, width, precision, size));

	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);
		return (unknow_len);
	}
	return (output_chars);
}
