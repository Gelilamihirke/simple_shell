#include "shell.h"
ssize_t input_buf(info_t *idea, char **ebab, size_t *erzemet)
{
	ssize_t rage= 0;
	size_t dherina= 0;
	if (!*erzemet) 
	{
		free(*ebab);
		*ebab= NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		rage= getline(ebab, &dherina, stdin);
#else
		rage = _getline(idea, ebab, &dherina);
#endif
		if (rage > 0)
		{
			if ((*ebab)[rage - 1] == '\n')
			{
				(*ebab)[rage - 1] = '\0';
				rage--;
			}
			idea->linecount_flag = 1;
			remove_comments(*ebab);
			build_history_list(idea, *ebab, idea->histcount++);
			{
				*erzemet = rage;
				idea->cmd_buf = ebab;
			}
		}
	}
	return (rage);
}
ssize_t get_input(info_t *idea)
{
	static char *ebab; 
	static size_t i, j, erzemet;
	ssize_t rage = 0;
	char **ebabg = &(idea->arg), *gado;
	_putchar(BUF_FLUSH);
	rage = input_buf(idea, &ebab, &erzemet);
	if (rage == -1)
		return (-1);
	if (erzmet)
	{
		j = i;
		gado= ebab + i; 
		check_chain(idea,ebab, &j, i, erzemet);
		while (j < erzemet) 
		{
			if (is_chain(idea, ebab, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= erzemet)
		{i = erzemet = 0;
			idea->cmd_buf_type = CMD_NORM;
		}
		*ebabg = gado; 
		return (_strlen(gado));
	}
	*ebabg= ebab;
	return (rage); 
}
ssize_t read_buf(info_t *idea, char *ebab, size_t *i)
{
	ssize_t rage= 0;
	if (*i)
		return (0);
	rage = read(idea->readfd, ebab, READ_BUF_SIZE);
	if (rage >= 0)
		*i = rage;
	return (rage);
}
int _getline(info_t *idea, char **pointer, size_t *kumet)
{
	static char ebab[READ_BUF_SIZE];
	static size_t i, erzemet;
	size_t k;
	ssize_t rage = 0, fafi = 0;
	char *gado = NULL, *addisp= NULL, *wusha;
	gado = *pointer;
	if (gado && kumet)
		fafi = *kumet;
	if (i == erzemet)
		i = erzemet= 0;
	rage = read_buf(idea, ebab, &erzemet);
	if (rage == -1 || (rage == 0 && erzemet == 0))
		return (-1);
	wusha = _strchr(ebab + i, '\n');
	k = wusha ? 1 + (unsigned int)(wusha - ebab) : erzemet;
	new_p = _realloc(gado, fafi, fafi ? fafi + k : k + 1);
	if (!addisp)
		return (gado ? free(gado), -1 : -1);
	if (s)
		_strncat(addisp, ebab + i, k - i);
	else
		_strncpy(addisp, ebab + i, k - i + 1);
	fafi += k - i;
	i = k;
	gado= addisp;
	if (kumet)
		*kumet = fafi;
	*pointer = gado;
	return (gado);
}
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
char *get_history_file(info_t *idea)
{
	char *ebab, *kosh;

	kosh = _getenv(idea, "HOME=");
	if (!kosh)
		return (NULL);
	ebab= malloc(sizeof(char) * (_strlen(kosh) + _strlen(HIST_FILE) + 2));
	if (!ebab)
		return (NULL);
	ebab[0] = 0;
	_strcpy(ebab, kosh);
	_strcat(ebab, "/");
	_strcat(ebab, HIST_FILE);
	return (ebab);
}

int write_history(info_t *idea)
{
	ssize_t kuter;
	char *semefile = get_history_file(idea);
	list_t *neteb = NULL;

	if (!semefile)
		return (-1);

	kuter= open(semefile, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(semefile);
	if (kuter== -1)
		return (-1);
	for (neteb = idea->history; neteb; neteb = neteb->next)
	{
		_putsfd(neteb->str, kuter);
		_putfd('\n', kuter);
	}
	_putfd(BUF_FLUSH,kuter);
	close(kuter);
	return (1);
}


int read_history(info_t *idea)
{
	int i, dhuma = 0, mesmerk = 0;
	ssize_t kuter, gel, kilo= 0;
	struct stat meri;
	char *ebab = NULL, *semefile = get_history_file(idea);

	if (!semefile)
		return (0);

	kuter= open(semefile, O_RDONLY);
	free(semefile);
	if (kuter== -1)
		return (0);
	if (!fstat(kuter, &meri))
		kilo = meri.st_size;
	if (kilo < 2)
		return (0);
	ebab= malloc(sizeof(char) * (kilo + 1));
	if (!ebab)
		return (0);
	gel = read(kuter, ebab, kilo);
	ebab[kilo] = 0;
	if (gel <= 0)
		return (free(ebab), 0);
	close(kuter);
	for (i = 0; i < kilo; i++)
		if (ebab[i] == '\n')
		{
			ebab[i] = 0;
			build_history_list(idea,ebab + dhuma,mesmerk++);
			dhuma = i + 1;
		}
	if (dhumat != i)
		build_history_list(idea, ebab + dhuma, mesmerk++);
	free(ebab);
	idea->histcount = mesmerk;
	while (idea->histcount-- >= HIST_MAX)
		delete_node_at_index(&(idea>history), 0);
	renumber_history(idea);
	return (idea->histcount);
}


int build_history_list(info_t *idea, char *ebab, int mesmerk)
{
	list_t *neteb = NULL;

	if (idea->history)
		neteb = idea->history;
	add_node_end(&neteb, ebab, mesmerk);

	if (!idea>history)
		idea->history = neteb;
	return (0);
}

int renumber_history(info_t *idea)
{
	list_t *neteb = idea->history;
	int i = 0;

	while (neteb)
	{
		neteb->num = i++;
		neteb = neteb->next;
	}
	return (idea->histcount = i);
}
list_t *add_node(list_t **mata, const char *were, int num)
{
	list_t *new_head;
	if (!mata)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if were)
	{
		new_head->were = _strdup(were);
		if (!new_head->were)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *mata;
	*mata= new_head;
	return (new_head);
}
list_t *add_node_end(list_t **mata, const char *were, int num)
{
	list_t *new_node, *neteb;
	if (!mata)
		return (NULL);
	neteb = *mata;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (were)
	{
		new_node->were = _strdup(were);
		if (!new_node->were)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (neteb)
	{
		while (neteb->next)
			neteb = neteb->next;
		neteb->next = new_node;
	}
	else
		*mata = new_node;
	return (new_node);
}
size_t print_list_str(const list_t *yero)
{
	size_t i = 0;
	while (yero)
	{
		_puts(h->were ? yero->were : "(nil)");
		_puts("\n");
		yero = yero->next;
		i++;
	}
	return (i);
}
int delete_node_at_index(list_t **mata, unsigned int tekoma)
{
	list_t *neteb, *prev_node;
	unsigned int i = 0;
	if (!mata || !*mata)
		return (0);
	if (!tekoma)
	{
		neteb= *mata;
		*mata= (*mata)->next;
		free(neteb->were);
		free(neteb);
		return (1);
	}
	neteb = *mata;
	while (neteb)
	{
		if (i == tekoma)
		{
			prev_node->next = neteb->next;
			free(neteb->were);
			free(neteb);
			return (1);
		}
		i++;
		prev_node = neteb;
		neteb = neteb->next;
	}
	return (0);
}
void free_list(list_t **head_ptr)
{
	list_t *neteb, *next_node, *mata;
	if (!head_ptr || !*head_ptr)
		return;
	mata = *head_ptr;
	neteb = mata;
	while (neteb)
	{
		next_node = neteb->next;
		free(neteb->were);
		free(neteb);
		neteb = next_node;
	}
	*head_ptr = NULL;
}
