/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fichier.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:20:17 by mokhalil          #+#    #+#             */
/*   Updated: 2023/02/14 23:35:45 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main()
{
    //P :x => C: x *4 => P 
    if (pipe(p1) == -1) {return 1;}
    int p2[2];
    if (pipe(p2) == -1) {return 1;}
    int pid = fork();
    if (pid == -1) {return 2;}
    
    if (pid == 0)
    {
        //child prcess
        close(p1[0]);
        close(p2[1]);
        int x;
        if(read(p2[0], &x, sizeof(x)) == -1) {return 3;}
        printf("recieved : %d\n",x);
        x *= 4;
        if (write(p1[1], &x, sizeof(x)) == -1) {return 4;}
        printf("wrote %d\n",x);
        close(p2[0]);
        close(p1[1]);
    }
    else
    {
        //parent process
        close(p1[1]);
        close(p2[0]);
        srand(time(NULL));
        int y = rand() % 10;
        if (write(p2[1], &y, sizeof(y)) == -1) {return 5;}
        printf("wrote %d\n", y);
        if(read(p1[0], &y, sizeof(y)) == -1) {return 6;}
        printf("result is %d\n",y);
        close(p1[0]);
        close(p2[1]);
        wait(NULL);
    }
    
    return 0;
}