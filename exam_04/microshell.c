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

int	i = 0;

void print_tab(char **tab)
{
	int j = 0;
	while (tab[j])
		printf("%s", tab[j++]);
	printf("\n");
}

size_t	get_size(char **argv)
{
	size_t j = 0;
	if (!argv)
		return (0);
	while (argv[i])
	{
		if (!strcmp(argv[i], ";"))
			return (j);
		j++;
		i++;
	}
	return(j);
}

char **cmd_maker(char **argv)
{
	size_t size = 0;
	size_t len = 0;
	char **cmd = NULL;
	size_t	j = 0;

	size = get_size(argv);
	if (size == 0)
		return (NULL);	
	cmd = malloc(sizeof(*cmd) * size + 1);
	if (cmd == NULL)
		return (NULL);
	len = i - size;
	while (j < size)
	{
		cmd[j] = argv[len];
		j++;
		len++;
	}
	cmd[j] = NULL;
	// print_tab(cmd);
	return (cmd);
}

void write_error(char *str)
{
	int j = 0;

	while(str[j])
		write(2, &str[j++], 1);
}

int	cmd_size(char **cmd)
{
	int j = 0;
	while (cmd[j])
		j++;
	return (j);
}

int	builtin_cd (char **cmd)
{
	char	c[200];
	int	ch;
//	printf("%d\n", cmd_size(cmd));
	if (cmd_size(cmd) != 2)
	{
		write_error("error: cd: bad arguments\n");
		return (-1);
	}
	ch = chdir(cmd[1]);
	//printf("%s\n", getcwd(c, sizeof(c)));
	if (ch == -1)
	{
		write_error("error: cd: cannot change directory to ");
		write_error(cmd[1]);
		write_error("\n");
		return (-1);
	}
	else
		return (0);
}

int check_for_pipe(char **cmd)
{
	int j = 0;
	while (cmd[j])
	{
		if (!strcmp(cmd[j], "|"))
			return (1);
		j++;
	}
	return (0);
}

int	exec_cmd(char **cmd, char **env)
{
	pid_t id;

	id = fork();
	if (id < 0)
		return (-1);
	if (id == 0)
	{
		if (execve(cmd[0], cmd, env) < 0)
		{
			write_error("error: cannot execute ");
			write_error(cmd[0]);
			write_error("\n");
		}
	}
	waitpid(0, NULL, 0);
	return (0);
}

char **get_next_pipe(char **cmd)
{
	int j = 0;
	while (cmd[j])
	{
		if (!strcmp(cmd[j], "|"))
			return (&cmd[j + 1]);
		j++;
	}
	return (NULL);
}

int	exec_child(char **cmd, char **tmp, char **env, int pipefd[2], int fd_stdin)
{

	if (dup2(STDIN_FILENO, fd_stdin) < 0)
		return (write_error_fatal("error: fatal\n"));
	if (check_for_pipe(tmp) && dup2(pipefd[1], STDOUT_FILENO) < 0)
		return (write_error_fatal("error: fatal\n"));
	close(fd_stdin);
	close(pipefd[0]);
	close(pipefd[1]);
	tmp[get_size(tmp, "|")] = NULL;
	exec_cmd(tmp, env);
	free(cmd);
	return (0);
}

int	exec(char **cmd, char**env)
{
	int	pipefd[2];
	int	fd_stdin;
	pid_t id;
	int count = 0;
	char **tmp = cmd;
	 
	if (!check_for_pipe(cmd))
		return(exec_cmd(cmd, env));

	fd_stdin = dup(STDIN_FILENO);
	if (fd_stdin < 0)
		return (write_error_fatal("error: fatal\n"));
	while (tmp)
	{
		if (pipe(pipefd) < 0 || (id = fork()) < 0)
			write_error_fatal("error: fatal\n");
		if (id == 0)
			exec_child(cmd, tmp, env, pipefd, fd_stdin);
		else if (dup2(fd_stdin, pipefd[0]) < 0)
			write_error_fatal("error: fatal\n");
		close(pipefd[0]);
		close(pipefd[1]);
		count++;
		tmp = get_next_pipe(tmp);
	}
	close(fd_stdin);
	while (count >= 0)
	{
		waitpid(0, NULL, 0);
		count--;
	}
	return (0);
}


int	main (int argc, char **argv, char **env)
{
	char **cmd;

	cmd = NULL;
	if (argc < 2)
		return (0);
	argv++;
	printf("ARGC %d\n", argc);
	while (i < argc - 1)
	{
		cmd = cmd_maker(argv);
		if (cmd && !strcmp(cmd[0], "cd"))
			builtin_cd(cmd);
		else if (cmd)
			exec(cmd, env);
		print_tab(cmd);
		free(cmd);
		cmd = NULL;
		i++;
	}
	return (0);
}
