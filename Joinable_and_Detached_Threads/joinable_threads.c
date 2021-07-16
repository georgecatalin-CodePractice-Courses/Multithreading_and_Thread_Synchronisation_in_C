#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //For working with POSIX Threads
#include <unistd.h> //For pause and sleep
#include <errno.h> //For accessing the global variable errno

pthread_t pthread2;
pthread_t pthread3;

void thread_create(pthread_t *, int);
void *thread_fn_callback(void *arg);

int main(int argc, char **argv)
{
	void *thread_result2;
	void *thread_result3;
	
	thread_create(&pthread2,2); //this is a user defined function, and not a POSIX standard function
	thread_create(&pthread3,10);
	
	puts("Main function is blocked on pthread_join() API with thread_number 2");
	pthread_join(pthread2,&thread_result2);
	
	if(thread_result2)
	{
		printf("The returned result from thread 2 is %d.\n", * (int *) thread_result2);
		free(thread_result2); //release the memory after extracting the value from that memory
		thread_result2=NULL;
	}
	
	puts("Main function is blocked on pthread_join() API with thread number 10");
	pthread_join(pthread3,&thread_result3);
	
	if(thread_result3)
	{
		printf("The returned result from thread 3 is %d.\n", * (int *) thread_result3);
		free(thread_result3);
		thread_result3=NULL;
	}
	
	return 0;
}

void thread_create(pthread_t *pthread_handle, int thread_number_to_pass)
{
	pthread_attr_t attributes; //properties of the new thread
	
	int *_thread_number_to_pass=calloc(1,sizeof(int)); //set a new variable on the heap
	*_thread_number_to_pass=thread_number_to_pass;
	

	pthread_attr_setdetachstate(&attributes,PTHREAD_CREATE_JOINABLE);
	/* PTHREAD_CREATE_DETACHED */
	
	pthread_create(pthread_handle,&attributes,thread_fn_callback, (void *) _thread_number_to_pass); 
}

void *thread_fn_callback(void *arg)
{
	int number=* (int *) arg;
	free(arg);
	
	int rc=0;
	
	while(rc!=number)
	{
		printf("The thread %d is doing some work.\n",number);
		sleep(1);
		rc++;
	}
	
	int *result=calloc(1,sizeof(int)); //allocate in a continuous zone on the heap space for 1 element of type int ; result is a pointer to an integer existing on the heap
	*result=number*number;
	
	return (void *) result;
}
