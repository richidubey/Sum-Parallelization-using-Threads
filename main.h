/*
 * Sum Parallelisation using Threads 
 * Header File 
 *
 * Copyright (C) 2021 Richi Dubey <richidubey@gmail.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the LICENSE file in the top-level directory.
 */
 
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<pthread.h>
#include <sys/time.h>
#define DEBUG_MODE 0

int *arr; //Global array that stores the input

typedef struct {
  int           begin;
  int           size;
  long long int subset_sum;
} thread_data;

void *sum_subset(void *arg);
