/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:16:33 by mokhalil          #+#    #+#             */
/*   Updated: 2023/02/20 00:55:16 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "pipex.h"
int main(int ac, char **av, char** env) {
    int fd[2];
    pid_t pid1, pid2;
    int fd1;
    int fd2;
    
    if (ac != 5)
    {
        write(2, "arguments different than 5\n", 27);
        exit(1);
    }
    fd1 = open(av[1],O_RDONLY);
    if (fd1 == -1)
    {
        write(2, "infile not found\n", 17);
        exit(1);
    }
    fd2 = open(av[4],O_TRUNC |O_CREAT|O_RDWR, 0644);
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(1);
    } else if (pid1 == 0) { // child process 1
        close (fd2);
        close(fd[0]); // close unused read end of the pipe
        dup2(fd[1], 1); // redirect stdout to the write end of the pipe
        dup2(fd1,0);//redirect stdin to the first argument
        char    **sp = split_path(env);
        char *cp = check_path(sp, av[2]);
        if (!cp)
        {
            write(2,"command not found\n",19);
            exit(1);
        } 
        char **k =ft_split(av[2], ' ');
        execve(cp, k, NULL); // execute "ls" command
        perror("execve");
        exit(EXIT_FAILURE);
    } else { // parent process
        pid2 = fork();
        if (pid2 == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid2 == 0) { // child process 2
            close(fd[1]); // close unused write end of the pipe
            close(fd1);
           dup2(fd[0], 0); // redirect stdin to the read end of the pipe
           dup2(fd2, 1);
            char    **sp = split_path(env);
            char *cp = check_path(sp, av[3]);
        if (!cp)
        {
            write(2,"command not found\n",19);
            exit(1);
        } 
        char **k =ft_split(av[2], ' ');
            execve(cp,ft_split(av[3], ' '), NULL); // execute "wc -l" command
            perror("execve");
            exit(EXIT_FAILURE);
        } else { // parent process
            
            int status;
            close(fd[0]); // close unused read end of the pipe
            close(fd[1]); // close unused write end of the pipe
            waitpid(pid1, NULL, 0); // wait for child process 1 to complete
            waitpid(pid2, &status, 0); // wait for child process 2 to complete
            if (WIFEXITED(status))
                printf("Child process 2 exited with status %d\n", WEXITSTATUS(status));
            close(fd1);
            close(fd2);
            exit(EXIT_SUCCESS);
        }
    }
    
}
