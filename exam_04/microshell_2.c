/*Assignment name  : microshell
Expected files   : *.c *.h
Allowed functions: malloc, free, write, close, fork, waitpid, signal, kill, exit, chdir, execve, dup, dup2, pipe, strcmp, strncmp
--------------------------------------------------------------------------------------

Ecrire un programme qui aura ressemblera à un executeur de commande shell
- La ligne de commande à executer sera passer en argument du programme
- Les executables seront appelés avec un chemin relatif ou absolut mais votre programme ne devra pas construire de chemin 
	(en utilisant la variable d environment PATH par exemple)

- Votre programme doit implementer "|" et ";" comme dans bash
	- Nous n'essaierons jamais un "|" immédiatement suivi ou précédé par rien ou un autre "|" ou un ";"

- Votre programme doit implementer la commande "built-in" cd et seulement avec un chemin en argument (pas de '-' ou sans argument)
	- si cd n'a pas le bon nombre d'argument votre programme devra afficher dans STDERR "error: cd: bad arguments" suivi d'un '\n'
	- si cd a echoué votre programme devra afficher dans STDERR "error: cd: cannot change directory to path_to_change" suivi d'un '\n'
		avec path_to_change remplacer par l'argument à cd
	- une commande cd ne sera jamais immédiatement précédée ou suivie par un "|"

- Votre programme n'a pas à gerer les "wildcards" (*, ~ etc...)

- Votre programme n'a pas à gerer les variables d'environment ($BLA ...)

- Si un appel systeme, sauf execve et chdir, retourne une erreur votre programme devra immédiatement afficher dans STDERR "error: fatal" suivi d'un '\n' 
	et sortir

- Si execve echoue votre programme doit afficher dans STDERR "error: cannot execute executable_that_failed" suivi d'un '\n'
	en ayant remplacé executable_that_failed avec le chemin du programme qui n'a pu etre executé (ca devrait etre le premier argument de execve)

- Votre programme devrait pouvoir accepter des centaines de "|" meme si la limite du nombre de "fichier ouvert" est inferieur à 30.

Par exemple, la commande suivante doit marcher:
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
microshell
i love my microshell
$>

Conseils:
N'oubliez pas de passer les variables d'environment à execve

Conseils:
Ne fuitez pas de file descriptor!*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define READ 0
#define WRITE 1

int	fd_stdin;
int ret;
int haspipe;


void write_error(char *str)
{
	int j = 0;

	while(str[j])
		write(2, &str[j++], 1);
}

void write_error_fatal(char *str)
{
	int j = 0;

	while(str[j])
		write(2, &str[j++], 1);
	exit(EXIT_FAILURE);
}

int	cmd_size(char **cmd)
{
	int j = 0;
	while (cmd[j])
		j++;
	return (j);
}

void	builtin_cd (char **cmd)
{
	if (cmd_size(cmd) != 2)
	{
		write_error("error: cd: bad arguments\n");
		ret = 1;	
		return ;
	}
	if (chdir(cmd[1]) == -1)
	{
		write_error("error: cd: cannot change directory to ");
		write_error(cmd[1]);
		write_error("\n");
		ret = 1;	
		return ;
	}
}

void open_pipe(int pipefd[2])
{
	if (haspipe)
	{
		if (close(pipefd[READ]) < 0)
			write_error_fatal("error: fatal\n");
		if (dup2(pipefd[WRITE], STDOUT_FILENO) < 0)
			write_error_fatal("error: fatal\n");
		if (close(pipefd[WRITE]) < 0)
			write_error_fatal("error: fatal\n");
	}
}

void close_pipe(int pipefd[2])
{
	if (haspipe)
	{
		if (dup2(pipefd[READ], STDIN_FILENO) < 0)
			write_error_fatal("error: fatal\n");
		if (close(pipefd[READ]) < 0)
			write_error_fatal("error: fatal\n");
		if (close(pipefd[WRITE]) < 0)
			write_error_fatal("error: fatal\n");
	}
}

void	execute(char **cmd, char **env)
{
	pid_t id;
	int fdpipe[2];

	if (cmd && !strcmp(cmd[0], "cd"))
			return (builtin_cd(cmd));
	if (haspipe)
		if (pipe(fdpipe) < 0 || (id = fork()) < 0)
			write_error_fatal("error: fatal\n");
	if (id == 0)
	{
		open_pipe(fdpipe);
		if (execve(cmd[0], cmd, env) < 0)
		{
			write_error("error: cannot execute ");
			write_error(cmd[0]);
			write_error("\n");
			exit (1);
		}
	}
	else
		close_pipe(fdpipe);
}

void exec_cmd(char **cmd, char **env)
{
	int i = -1;
	int start = 0;
	int	count = 0;

	while (cmd[i++])
	{
		if (!strcmp(cmd[i], "|") || cmd[i + 1] == NULL)
		{
			haspipe = 0;
			if (!strcmp(cmd[i], "|"))
			{
				haspipe = 1;
				cmd[i] = NULL;
			}
			execute(cmd + start, env);
			start = i + 1;
			count++;
		}
	}
	while (count-- > 0)
	{
		waitpid(-1, 0, 0);
	}
}

void get_fd(void)
{
	int tmp;

	tmp = dup(STDIN_FILENO);
	if (dup2(fd_stdin, STDIN_FILENO) < 0)
		write_error_fatal("error: fatal\n");
	if (close(tmp) < 0)
		write_error_fatal("error: fatal\n");
}

int main(int argc, char **argv, char **env)
{
	int	i = 0;
	int start = 1;
	fd_stdin = dup(STDIN_FILENO);	
	if (argc < 2)
		return (0);
	while (argv[i++])
	{
		if (!strcmp(argv[i], ";") || argv[i + 1] == NULL)
		{
			if (!strcmp(argv[i], ";"))
				argv[i] = NULL;
			exec_cmd(argv + start, env);
			start = i + 1;
		}
		ret = 0;
		get_fd();
	}
	return (ret);
}

