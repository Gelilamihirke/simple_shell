#include "main.h"

/
 * _putchar - writes the character c to stdout
  @@ -11,3 +11,22 @@ int _putchar(char c)
{
  return (write(1, &c, 1));
}



/
 * prints - Prints a string
 * @str: Pointer to the string to print
 *
 * Return: void
 */
void prints(char *str)
{
  int i = 0;

  while (str[i])
  {
    _putchar(str[i]);
    i++;
  }
}

