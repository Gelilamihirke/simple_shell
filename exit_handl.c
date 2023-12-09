#include "main.h"


void handle_signal(int signal)
{

    
        
          
    

        
        Expand All
    
    @@ -13,13 +8,7 @@ void handle_signal(int signal)
  
  (void) signal;
  prints("\n$ ");
  fflush(stdout);
}


int *_error(char *argv, int count, char *args)
{
  char *number;

    
        
          
    

        
        Expand All
    
    @@ -36,12 +25,7 @@ int *_error(char *argv, int count, char *args)
  
  number = _itoa(count, 10);
  write(2, argv, _strlen(argv));
  write(2, ": ", 2);
  write(2, number, _strlen(number));
  write(2, ": ", 2);
  write(2, args, _strlen(args));
  perror(" ");
  return (0);
}


int _stat(char **cmd, char **menged)
{
  char *concat_str = NULL, *new_concat = NULL;

    
          
            
    

          
          Expand Down
    
    
  
  int kotari;
  struct stat sb;
  if (menged == NULL)
  {
    free(menged);
    free(cmd);
    return (0);
  }
  for (kotari = 0; menged[kotari] != NULL ; kotari++)
  {
    concat_str = str_concat(menged[kotari], "/");
    new_concat = str_concat(concat_str, cmd[0]);
    if (stat(new_concat, &sb) == 0 && (sb.st_mode & S_IXUSR))
    {
      cmd[0] = new_concat;
      free(concat_str);
      free(menged[0]);
      free(menged);
      return (1);
    }
    free(concat_str);
    free(new_concat);
  }
  free(menged[0]);
  free(menged);
  return (0);
}

