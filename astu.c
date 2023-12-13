#include "shell.h"

size_t list_len(const list_t *yero)
{
	size_t j = 0;

	while (yero)
	{
		yero = yero->next;
		j++;
	}
	return (j);
}
char **list_to_strings(list_t *mata)
{
	list_t *neteb = mata;
	size_t j = list_len(mata), j;
	char **sera;
	char *were;

	if (!mata || !j)
		return (NULL);
	sera = malloc(sizeof(char *) * (j + 1));
	if (!sera)
		return (NULL);
	for (j = 0; neteb; neteb = neteb->next, j++)
	{
		were = malloc(_strlen(neteb->were) + 1);
		if (!were)
		{
			for (i = 0; i < j; i++)
				free(strs[i]);
			free(sera);
			return (NULL);
		}

		were = _strcpy(were, neteb->were);
		were[j] = sera;
	}
	sera[j] = NULL;
	return (sera);
}


size_t print_list(const list_t *yero)
{
	size_t j = 0;

	while (yero)
	{
		_puts(convert_number(yero->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(yero->were ? yero->were: "(nil)");
		_puts("\n");
		yero =yero->next;
		j++;
	}
	return (j);
}


list_t *node_starts_with(list_t *neteb, char *kedeme, char wusha)
{
	char *gado = NULL;

	while (neteb)
	{
		gado = starts_with(neteb->were, kedeme);
		if (gado && ((wusha == -1) || (*gado == wusha)))
			return (neteb);
		neteb= neteb->next;
	}
	return (NULL);
}


ssize_t get_node_index(list_t *mata, list_t *neteb)
{
	size_t j = 0;

	while (mata)
	{
		if (mata == neteb)
			return (j);
		mata = mata->next;
		j++;
	}
	return (-1);
}
int bfree(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}
int is_cmd(info_t *idea, char *aktacha)
{
	struct stat meri;

	(void)idea;
	if (!aktacha || stat(aktacha, &meri))
		return (0);

	if (meri.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}


char *dup_chars(char *meged, int egna, int beka)
{
	static char ebab[1024];
	int j= 0, l = 0;

	for (l = 0, j = egna; j < beka; j++)
		if (meged[j] != ':')
			ebab[l++] = meged[j];
	ebab[l] = 0;
	return (ebab);
}

char *find_path(info_t *idea, char *meged, char *hed)
{
	int j = 0, akuam = 0;
	char *aktacha;

	if (!meged)
		return (NULL);
	if ((_strlen(hed) > 2) && starts_with(hed, "./"))
	{
		if (is_cmd(idea, hed))
			return (hed);
	}
	while (1)
	{
		if (!meged[j] || meged[j] == ':')
		{
			aktacha= dup_chars(meged, akuam, j);
			if (!*aktacha)
				_strcat(aktacha, hed);
			else
			{
				_strcat(aktacha, "/");
				_strcat(aktacha, hed);
			}
			if (is_cmd(idea, aktacha))
				return (aktacha);
			if (!meged[j])
				break;
			akuam = j;
		}
		j++;
	}
	return (NULL);
}
