#include "shell.h"
char *_strncpy(char *fen, char *source, int lakk)
{
	int i, j;
	char *fafi = fen;

	i = 0;
	while (source[i] != '\0' && i < lakk- 1)
	{
		fen[i] = source[i];
		i++;
	}
	if (i < lakk)
	{
		j = i;
		while (j < lakk)
		{
			fen[j] = '\0';
			j++;
		}
	}
	return (fafi);
}
char *_strncat(char *fen, char *source, int lakk)
{
	int i, j;
	char *fafi = fen;

	i = 0;
	j = 0;
	while (fen[i] != '\0')
		i++;
	while (source[j] != '\0' && j < lakk)
	{
		fen[i] = source[j];
		i++;
		j++;
	}
	if (j < lakk)
		fen[i] = '\0';
	return (fafi);
}
char *_strchr(char *fafi, char wusha)
{
	do {
		if (*fafi == wusha)
			return (fafi);
	} while (*fafi++ != '\0');

	return (NULL);
}
char **get_environ(info_t *idea)
{
	if (!idea->environ || idea->env_changed)
	{
		idea->environ = list_to_strings(idea->env);
		idea->env_changed = 0;
	}

	return (idea->environ);
}
int _unsetenv(info_t *idea, char *mehal)
{
	list_t *neteb = idea->env;
	size_t i = 0;
	char *gado;

	if (!neteb || !mehal)
		return (0);

	while (neteb)
	{
		gado = starts_with(neteb->were, mehal);
		if (gado && *gado == '=')
		{
			idea->env_changed = delete_node_at_index(&(idea->env), i);
			i = 0;
			neteb = idea->env;
			continue;
		}
		neteb= neteb->next;
		i++;
	}
	return (idea->env_changed);
}
int _setenv(info_t *idea, char *mehal, char *waga)
{
	char *ebab= NULL;
	list_t *neteb;
	char *gado;

	if (!mehal || !waga)
		return (0);

	ebab= malloc(_strlen(mehal) + _strlen(waga) + 2);
	if (!ebab)
		return (1);
	_strcpy(ebab ,mehal);
	_strcat(ebab, "=");
	_strcat(ebab, waga);
	neteb = idea->env;
	while (neteb)
	{
		gado = starts_with(neteb->were, mehal);
		if (gado && *gado == '=')
		{
			free(neteb->were);
			neteb->were= ebab;
			idea->env_changed = 1;
			return (0);
		}
		neteb= neteb->next;
	}
	add_node_end(&(idea->env),ebab, 0);
	free(ebab);
	idea->env_changed = 1;
	return (0);
}
void clear_info(info_t *idea)
{
	idea->arg = NULL;
	idea->argv = NULL;
	idea->path = NULL;
	idea->argc = 0;
}
void set_info(info_t *idea, char **mid)
{
	int i = 0;

	idea->fname = mid[0];
	if (idea->arg)
	{
		idea->argv = strtow(idea->arg, " \t");
		if (!idea->argv)
		{

			idea->argv = malloc(sizeof(char *) * 2);
			if (idea->argv)
			{
				idea->argv[0] = _strdup(idea->arg);
				idea->argv[1] = NULL;
			}
		}
		for (i = 0; idea->argv && idea->argv[i]; i++)
			;
		idea->argc = i;

		replace_alias(idea);
		replace_vars(idea);
	}
}
void free_info(info_t *idea, int hulun)
{
	ffree(idea->argv);
	idea->argv = NULL;
	idea->path = NULL;
	if (hulun)
	{
		if (!idea->cmd_buf)
			free(idea->arg);
		if (idea->env)
			free_list(&(idea->env));
		if (idea->history)
			free_list(&(idea->history));
		if (idea->alias)
			free_list(&(idea->alias));
		ffree(idea->environ);
			idea->environ = NULL;
		bfree((void **)idea->cmd_buf);
		if (idea->readfd > 2)
			close(idea->readfd);
		_putchar(BUF_FLUSH);
	}
}
