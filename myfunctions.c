#include "main.h"

/**
 * _printf - function that produces output according to a format
 * @format: a character string for the function
 * Return: Always 0
 */

int _printf(const char *format, ...)
{
	int myChar = 0;
	va_list args;

	if (format == NULL)
		return (-1);

	va_start(args, format);

	while (*format && *format != '\0')
	{
		if (*format != '%')
		{
			write(1, format, 1);
			myChar++;
		}
		else
		{
			if (*format == 'c')
			{
				char c = va_arg(args, int);

				write(1, &c, 1);
				myChar++;
			}
			else if (*format == 's')
			{
				char *str = va_arg(args, char*);
				int str_len = 0;

				while (str[str_len] != '\0')
					str_len++;
				write(1, str, str_len);
				myChar += str_len;
			}
		}
		format++;
	}
	va_end(args);
	return (myChar);
}
