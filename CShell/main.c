#include <stdio.h>  // printf() fprintf() perror getchar() strdeff()
#include <stdlib.h> // malloc() realloc() free() exit() execvp() EXIT_FAILURE EXIT_SUCCESS
#include <unistd.h> // fork() wait() exec() pid_t
#include <string.h> // strcmp() strtok()
#include <error.h>  // error()
#include <time.h>
#include <signal.h>
#include <fcntl.h> // open()
#include <bits/waitflags.h>
#include <sys/wait.h>
void lsh_loop(void);
char *lshReadLine(void);
char **lshSplitLine(char *);
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);
int lshLaunch(char **args);
int lshExecute(char **args);

int main()
{
    lsh_loop();
    return 0;
}
void lsh_loop(void)
{
    char *line;
    char **args;
    int status;
    do
    {
        printf("$ ");
        line = lshReadLine();
        args = lshSplitLine(line);
        status = lshExecute(args);
        free(line);
        free(args);
    } while (status);
}
// Reads a line of input from the standard input stream and returns it as a string.
char *lshReadLine(void)
{
    char *line = NULL;
    size_t len = 0;
    if (getline(&line, &len, stdin) == -1)
    {
        if (feof(stdin))
        {

            exit(EXIT_SUCCESS);
        }
        else
        {
            exit(EXIT_FAILURE);
        }
    }
    printf("\nThe input length is %ld\n", len);
    return line;
}
#define LINESIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char **lshSplitLine(char *line)
{
    int bufsize = LINESIZE;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;
    // Check if tokens is NULL
    if (!tokens)
    {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }
    token = strtok(line, LSH_TOK_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;
        if (position >= bufsize)
        {
            bufsize += LINESIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}
/**
 * Launches a child process to execute the command specified by the `args` array.
 *
 * @param args an array of strings representing the command and its arguments
 *
 * @return 1 if the child process is successfully launched, -1 otherwise
 *
 * @throws None
 */
int lshLaunch(char **args)
{
    pid_t pid, wpid;
    int status;
    pid = fork();
    if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("lsh");
    }
    else
    {
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

// List of built-in commands
char *builtin_str[] = {"cd", "help", "exit"};
int (*builtin_func[])(char **) = {&lsh_cd, &lsh_help, &lsh_exit};
int lsh_num_builtins()
{
    return sizeof(builtin_str) / sizeof(char *);
}

int lsh_cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("lsh");
        }
    }
    return 1;
}
int lsh_help(char **args)
{
    int i;
    printf("Gurkirat Singh's C Shell\n");
    printf("https://github.com/sshgurkiratsingh/C\n");
    printf("Type program names and arguments, and hit enter.\\n");
    printf("The following are built in:\n");

    for (i = 0; i < lsh_num_builtins(); i++)
    {
        printf("  %s\n", builtin_str[i]);
    }
    return 1;
}
int lsh_exit(char **args)
{
    return 0;
}

int lshExecute(char **args)
{
    int i;
    if (args[0] == NULL)
    {
        return 1;
    }
    for (i = 0; i < lsh_num_builtins(); i++)
    {
        if (strcmp(args[0], builtin_str[i]) == 0)
        {
            return (*builtin_func[i])(args);
        }
    }
    return lshLaunch(args);
}