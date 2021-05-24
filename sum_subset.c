/*
 * Sum Parallelisation using Threads
 * Thread Function
 * 
 * Copyright (C) 2021 Richi Dubey <richidubey@gmail.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the LICENSE file in the top-level directory.
 */
#include "main.h"
 
void *sum_subset(void *arg) 
{
	 
  int begin = ((thread_data *)arg)->begin;
  int size = ((thread_data *)arg)->size;

  long long int sum=0;
  #if DEBUG_MODE
    printf("Inside thread with starting point %d\n",((thread_data *)arg)->begin);
  #endif

  for (int i=0; i< size; i++) {
    sum += arr[i+begin];
  }
  #if DEBUG_MODE
    printf("Leaving thread with starting point %d and size %d: returned sum %lld\n",((thread_data *)arg)->begin, ((thread_data *)arg)->size, sum);
    fflush(stdout);
  #endif

  ((thread_data *)arg)->subset_sum = sum;
  pthread_exit(NULL);
}
