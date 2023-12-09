#include "main.h"


int main(int ac attribute((unused)), char **av, char **env)
{
  char *line;
  char **args, **path;
  int kotari = 0, huneta = 0;
  (void) av;
  signal(SIGINT, handle_signal);

  for (;;)
  {
    prompt();
    line = read_input();
    args = split_str(line, env);
    if ((_strcmp(args[0], "\n") != 0) && (_strcmp(args[0], "env") != 0))
    {
      kotari += 1;
      path = search(env); /* Search for PATH in the environment variable */
      huneta = _stat(args, path);
      execute_cmd(av, args, env, huneta, kotari);
    }
    else
    {
      free(args);
    }
    free(line);
  }
  return (0);
}
