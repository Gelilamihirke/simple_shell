include "main.h"
/**
 *ex_command - is function that execute commands
 *@args: is our input form command line
 *Return: Nothing
 */
void ex_command(char **args)
{
  char *command = NULL;
  char *command_kan = NULL;
  int status;
  if (args && args[0])
  {
    pid_t pid = fork();
    if (pid == -1)
    {
      perror("fork error");
      exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
      command = args[0];
      if (strchr(command, '/') != NULL)
      {
        command_kan = strdup(command);
      }
      else
      {
        char *path = getenv("PATH");
        char *path_copy = strdup(path);
        char *dir = strtok(path_copy, ":");

        while(dir != NULL)
        {
          command_kan = malloc(strlen(dir) + strlen(command) + 2);
          sprintf(command_kan, "%s/%s", dir, command);
          if(access(command_kan, X_OK) == 0)
          {
            break;
          }
          free(command_kan);
          dir = strtok(NULL, ":");
        }
        if (dir == NULL)
        {
          fprintf(stderr, "command not found in PATH: %s\n", command);
          free(path_copy);
          exit(EXIT_SUCCESS);
        }
        free(path_copy);
      }
      if (strcmp(command, "exit") == 0)
      {
        exit_handle();
      }
      if  (execve(command_kan, args, NULL) == -1)
      {
        perror("execve error");
        exit(EXIT_FAILURE);
    }
    free(command_kan);
  }

}
