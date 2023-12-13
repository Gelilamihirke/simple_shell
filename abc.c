#include "shell.h"
char *_memset(char *fafi, char fayo, unsigned int num)
{
	unsigned int j;
	for (j = 0; j < num; j++)
		fafi[j] = fayo;
	return (fafi);
}
void ffree(char **pro)
{
	char **game = pro;
	if (!pro)
		return;
	while (*pro)
		free(*pro++);
	free(game);
}
void *_realloc(void *pointer, unsigned int prev_size, unsigned int curr_size)
{
	char *gado;
	if (!pointer)
		return (malloc(curr_size));
	if (!curr_size)
		return (free(pointer), NULL);
	if (curr_size == prev_size)
		return (pointer);
	gado = malloc(curr_size);
	if (!gado)
		return (NULL);
	prev_size = prev_size < curr_size ? prev_size : curr_size;
	while (prev_size--)
		gado[prev_size] = ((char *)pointer)[prev_size];
	free(pointer);
	return (gado);
}
int hsh(info_t *idea, char **mid)
{
	ssize_t rage = 0;
	int inside = 0;
	while (rage != -1 && inside != -2)
	{
		clear_info(idea);
		if (interactive(idea))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		rage = get_input(idea);
		if (rage != -1)
		{
			set_info(idea, mid);
			inside= find_builtin(idea);
			if (inside == -1)
				find_cmd(idea);
		}
		else if (interactive(idea))
			_putchar('\n');
		free_info(idea, 0);
	}
	write_history(idea);
	free_info(idea, 1);
	if (!interactive(idea) && idea->status)
		exit(idea->status);
	if (inside == -2)
	{
		if (idea->err_num == -1)
			exit(idea->status);
		exit(idea->err_num);
	}
	return (inside);
}
int find_builtin(info_t *idea)
{
	int j, insidein = -1;
	builtin_table insideb1[] = {
		{"exitu", _myexit},
		{"envu", _myenv},
		{"history1", _myhistory},
		{"setenv9", _mysetenv},
		{"unsetenv8", _myunsetenv},
		{"cd3", _mycd},
		{"alias8", _myalias},
		{NULL, NULL}
	};

	for (j = 0; insideb1[j].type; j++)
		if (_strcmp(idea->argv[0], insideb1[j].type) == 0)
		{
			idea->line_count++;
			insidein = insideb1[j].func(idea);
			break;
		}
	return (insidein);
}



void find_cmd(info_t *idea)
{
	char *path= NULL;
	int j, l;
	idea->path = idea->argv[0];
	if (idea->linecount_flag == 1)
	{
		idea->line_count++;
		idea->linecount_flag = 0;
	}
	for (j = 0, l = 0; idea->arg[j]; j++)
		if (!is_delim(idea->arg[j], " \t\n"))
			l++;
	if (!l)
		return;
path= find_path(idea, _getenv(idea, "PATH="), idea->argv[0]);
	if (path)
	{
		idea->path = path;
		fork_cmd(idea);
	}
	else
	{
		if ((interactive(idea) || _getenv(idea, "PATH=")
			|| idea->argv[0][1] == '/') && is_cmd(idea, idea->argv[0]))
			fork_cmd(idea);
		else if (*(idea->arg) != '\n')
		{
			idea->status = 127;
			print_error(idea, "not found\n");
		}
	}
}
void fork_cmd(info_t *idea)
{
	pid_t lej;
	lej = fork();
	if (lej== 1)
	{
		perror("Error:");
		return;
	}
	if (lej == 0)
	{
		if (execve(idea->path, idea->argv, get_environ(idea)) == -1)
		{
			free_info(idea, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(idea->status));
		if (WIFEXITED(idea->status))
		{
			idea->status = WEXITSTATUS(idea->status);
			if (idea->status == 126)
				print_error(idea, "Permission denied\n");
		}
	}
}
int _strlen(char *fafi)
{
	int j = 0;
	if (!fafi)
		return (0);
	while (*fafi++)
		j++;
	return (j);
}
int _strcmp(char *fafi1, char *fafi2)
{
	while (*fafi1 && *fafi2)
	{
		if (*fafi1 != *fafi2)
			return (*fafi1 - *fafi2);
		fafi1++;
		fafi2++;
	}
	if (*fafi1 == *fafi2)
		return (0);
	else
		return (*fafi1 < *fafi2 ? -1 : 1);
}
char *starts_with(const char *guddaa, const char *melach)
{
	while (*melach)
		if (*melach++ != *guddaa++)
			return (NULL);
	return ((char *)guddaa);
}
char *_strcat(char *fen, char *source)
{
	char *meten = fen;
	while (*fen)
		fen++;
	while (*source)
		*fen++ = *source++;
	*fen = *source;
	return (meten);
}
