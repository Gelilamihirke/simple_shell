#include "shell.h"
int main(int bas, char **mid)
{
	info_t idea[] = { INFO_INIT };
	int kuter = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (kuter)
		: "r" (kuter));

	if (bas == 2)
	{
		kuter = open(mid[1], O_RDONLY);
		if (kuter == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(mid[0]);
				_eputs(": 0: Can't open ");
				_eputs(mid[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		idea->readfd = kuter;
	}
	populate_env_list(idea);
	read_history(idea);
	hsh(idea, mid);

	return (EXIT_SUCCESS);
}
