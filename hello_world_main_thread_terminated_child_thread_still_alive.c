/*
 * compile using 
 * gcc -g -c hello_world.c -o hello_world.o
 * gcc -g hello_world.o -o hello_world -lpthread
 * Run:
 * ./hello_world
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <pthread.h>
 #include <unistd.h> //for pause() and sleep()
 
 void thread1_create();
 
void *thread_fn_callback(void * arg);
 
 int main(int argc, char **argv)
 {
	 
	 thread1_create();
	 printf("Main thread had an advantage over the child threads in the sense that when it completes, all the child threads get terminated too. The viceversa is not available. When the child thread terminates, then it does not affect the main thread at all..\n");
	 pthread_exit(0); //by terminating the execution of the main thread with pthread_exit(0) , then the child threads maintain their execution independently
	 return 0;
	 
 }
	 
void thread1_create()
{
	pthread_t pthread1; //this is a data structure is associated to threads = thread handle
	static char *thread_input1="I am the thread number 1."; //This must be static memory or memory on the heap
	
	//Returns 0 on success, otherwise returns an error code, all pthread functions return -ve error code on failure, they do no set a global 'errno' variable
	int returned_value=pthread_create(&pthread1,NULL,thread_fn_callback, (void *) thread_input1);
	
	if(returned_value!=0)
	{
		printf("Error encountered when creating a thread. The error number is %d.\n",returned_value);
		exit(0);
	}
     
}

 void *thread_fn_callback(void * arg)
{
	char *input=(char *) arg;
	int i=0;
	while(i<10)
	{
		printf("The input string is: %s.\n", input);
		sleep(1);
		i++;
    }
    //The thread terminates after it returns, so to say it executes completely after a finite number of steps
}
