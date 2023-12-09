#ifndef MAIN_H
#define MAIN_H
#define MAX_INPUT_SIZE 256
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/wait.h>
void getline_fun(int argc, char *argv[]);
void token_fun(void);
void ex_command(char **args);
int _putchar(char c);
char *my_getline();
char *path_barbadi(const char *command);
void exit_handle(void);
void display_prompt(void);
char *my_strtok(char *str, const char *delimiters);
size_t _strcspn(const char *jch, const char *bal);
size_t _strspn(const char *jch, const char *gal);
#endif

