// Simple Fork and Exec Example
// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <sys/wait.h>
// void main()
// {
//         int forkresult;

//         printf("I am the parent. Remember My Process-id! : %d\n", getpid());
//         printf("Parent now going to fork ... \n");

//         forkresult=fork();

//         if(forkresult==-1)
//         {
//                 printf("Fork failed\n");
//                 exit(0);
//         }
//         else if(forkresult!=0)
//         {
//                 printf("Parent will execute this code\n");
//                 printf("Parent prints:My child's pid is %d\n", forkresult);
//                 wait(NULL);
//                 printf("Parent executes pwd\n");
//                 execlp("pwd","pwd",NULL);
//                 printf("This line gets printed when the above exec statement pwd fails\n");
//         }
//         else
//         {
//                 printf("Hi ! I am the child with process-id %d.\n",getpid());
//                 printf("I'm now going to execute ls!\n\n\n");
//                 execlp ("ls", "ls", NULL);
//                 printf ("Child prints %d: AAAAH ! ! My EXEC failed ! ! ! !\n", getpid());
//                 exit(1);
//         }
//         printf ("Process id %d prints : like father like son. \n", getpid());
// }


// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <pthread.h>

// // Let us create a global variable to change it in threads
// int g = 0;

// // The function to be executed by all threads
// void *myThreadFun(void *vargp)
// {
//     int a=10;
//     // Store the value argument passed to this thread
//     int *myid = (int *)vargp;

//     // Let us create a static variable to observe its changes
//     static int s = 0;

//     // Change static and global variables
//     ++s; ++g; ++a;

//     // Print the argument, static and global variables
//     printf("Thread ID: %d, Static: %d, Global: %d  Local: %d \n", *myid, ++s, ++g, ++a);
//         ++a;
// }


    
// int main()
// {
//     int i;
//     pthread_t tid1,tid2,tid3;

//     // Let us create three threads
//     pthread_create(&tid1, NULL, myThreadFun, (void *)&tid1);
//     pthread_create(&tid2, NULL, myThreadFun, (void *)&tid2);
//     pthread_create(&tid3, NULL, myThreadFun, (void *)&tid3);

//     pthread_join(tid1, NULL);
//     pthread_join(tid2, NULL);
//     pthread_join(tid3, NULL);
//     return 0;
// }


// #include<unistd.h>
// #include<sys/wait.h>
// #include<stdio.h>
// #include<sys/types.h>
// #include<fcntl.h>
// #include<unistd.h>
// #include<stdlib.h>

// int main()
// {
//         int pipe1fd[2];

//         pid_t pid;
//         int status;

//         pipe(pipe1fd);

//         switch(pid=fork())
//         {
//                 case -1:  printf("can't fork");
//                           exit(-1);
//                 case 0:
//                           dup2(pipe1fd[1],1);
//                           close(pipe1fd[0]);
//                           execlp("pwd","pwd",NULL);
//                 default:
//                           wait(&status);
//                           dup2(pipe1fd[0],0);
//                           close(pipe1fd[1]);
//                           execlp("wc","wc",NULL);
//         }
// }




