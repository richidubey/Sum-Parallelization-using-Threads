/*
 * Sum Parallelisation using Threads
 * Main
 * 
 * Copyright (C) 2021 Richi Dubey <richidubey@gmail.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the LICENSE file in the top-level directory.
 */

#include "main.h"

int main(int argc, char **argv) 
{

  int            num_thread;  	
  int            inp_size;     //Size of input array
  int            ret;          //Return value of thread creation.
  int            time_result;
  FILE          *inp_file;
  pthread_t     *t_id;         //Thread id of threads
  thread_data   *param;        //Params to pass to each thread
  struct timeval current_time;
  long long int  final_sum_t;
  long long int  final_sum_no_t;
  long long int  expected_sum;
  /*
   * To store time variables, for comparison between
   * summing with threads (*_t) and summing without threads (*_no_t)
   */
  long long int  start_sec_t;
  long long int  start_microsec_t;
  long long int  start_sec_no_t;
  long long int  start_microsec_no_t;
  long long int  finish_sec_t;
  long long int  finish_microsec_t;
  long long int  finish_sec_no_t;
  long long int  finish_microsec_no_t;
  long long int  start_time_t;
  long long int  start_time_no_t;
  long long int  finish_time_t;
  long long int  finish_time_no_t;

  if(argc==1) {
    printf("Error!! No arguments provided. Atleast input file name must be passed\n");
    exit(1);
  }

  inp_file = fopen(argv[1], "r");
  
  if(inp_file == NULL) {
  	perror("Error in opening file");
  	exit(1);
  }

  if(argc>=3) {
    sscanf(argv[2],"%d", &num_thread);
    
    if( num_thread <=0 ) {
      printf("Error. Number of threads can not be 0 or negative\n");
      exit(1);
    }
    
    printf("Using %d threads for parallelization\n", num_thread);
  } else {
    printf("No parameter provided for number of threads.\nUsing 10 threads (default value) for parallelization\n");
    num_thread = 10;
  }

 /* 
  * Read the first integer from the file corresponds
  * to the number of integers in the file.
  */
  fscanf(inp_file,"%d", &inp_size); 
  
  printf("Number of elements in input: %d\n\n", inp_size);

  //Allocate space for the array.
  arr = (int *)malloc(inp_size*sizeof(int));

  for(int i=0; i<inp_size; i++) { //Populate the array arr 
    fscanf(inp_file,"%d", (arr+i));
  }
  
  //Last value in the file is the expected sum
   fscanf(inp_file,"%lld", &expected_sum);
  
 /*
  * Allocate as many thread_data structure as the num of threads to 
  * be created. Creates same number of thread ids.
  */
  param   = (thread_data *)   malloc( (sizeof(thread_data)) * (num_thread) );
  t_id    = (pthread_t *)     malloc( (sizeof(pthread_t))   * (num_thread) );

  //Configure the params to be passed to each thread
  for(int i=0; i<num_thread;i++) {
    param[i].begin = i*(inp_size/num_thread);
    param[i].size = (inp_size/num_thread);
    
    //Allot the remaining number to sum, for the last thread
    if( i==(num_thread - 1) ) {
      param[i].size += (inp_size % num_thread); 
    }
  }
  
  time_result = gettimeofday( &current_time, NULL );
  assert( time_result == 0 );  //Checks for error.
  
  start_sec_t = current_time.tv_sec;
  start_microsec_t = current_time.tv_usec;
  
 /*
  * Create the threads. 
  * This also dispatches them (makes them available for scheduling)
  * instantly 
  */
  for(int i=0; i<num_thread; i++) {
   ret = pthread_create(&t_id[i], NULL, sum_subset, &param[i]);
  }

  //Wait for all the threads to finish
  for(int i=0; i<num_thread; i++) {
    //pthread_join(t_id[i], &ret_sum[i]);
    pthread_join(t_id[i], NULL);
    #if DEBUG_MODE
      printf("Joined thread %d return value is %lld\n", i, param[i].subset_sum);
    #endif
  }
  #if DEBUG_MODE
    printf("All threads joined\n");
  #endif
  
  final_sum_t=0;
  
  for(int i=0; i<num_thread; i++) {
    final_sum_t += param[i].subset_sum;
  }
  
  //Calculation of sum using threads is done, save finish time
  time_result = gettimeofday( &current_time, NULL );
  assert( time_result == 0 );  //Checks for error.
  
  finish_sec_t = current_time.tv_sec;
  finish_microsec_t = current_time.tv_usec;
  
  //Calculate the sum without using threads
  time_result = gettimeofday( &current_time, NULL );
  assert( time_result == 0 );  //Checks for error.
  
  start_sec_no_t = current_time.tv_sec;
  start_microsec_no_t = current_time.tv_usec;
  
  final_sum_no_t = 0;
  
  for(int i=0; i<inp_size; i++) {
    final_sum_no_t += arr[i];
  }
  
  time_result = gettimeofday( &current_time, NULL );
  assert( time_result == 0 );  //Checks for error.
  
  finish_sec_no_t = current_time.tv_sec;
  finish_microsec_no_t = current_time.tv_usec;
  
  
  printf("-----------------------------------------------------------------\n");
  printf("Expected sum: %lld \n",expected_sum);
  printf("Sum calculated with help of threads: %lld\n",final_sum_t);
  printf("Sum calculated with help of threads: %lld\n",final_sum_no_t);
  
  start_time_t = (start_sec_t * 1000000) + start_microsec_t;
  start_time_no_t = (start_sec_no_t * 1000000) + start_microsec_no_t;
  
  finish_time_t = (finish_sec_t * 1000000) + finish_microsec_t;
  finish_time_no_t = (finish_sec_no_t * 1000000) + finish_microsec_no_t;
  
  printf("\n================================================================\n");
  printf("    TASK              TIME TAKEN(in micro seconds)");
  printf("\n================================================================");
  printf("\n  With %d Threads       %lld", num_thread, finish_time_t-start_time_t);
  printf("\n  Without Thread       %lld",finish_time_no_t-start_time_no_t);
               
  printf("\n----------------------------------------------------------------\n");
  
return 0;
}
