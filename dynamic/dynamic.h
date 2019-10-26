



#pragma once
#include <iostream>
#include <stddef.h>
#include <cstddef>

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <assert.h>

typedef unsigned long size_t;
typedef int ARR_TYPE;


struct TreadData{
	size_t arrSize;
	size_t * answerPtr;
	ARR_TYPE check;
	ARR_TYPE * arr;
};


void* threadFunc(TreadData * treadData);
size_t countInArrThread( ARR_TYPE *arr, const size_t arrSize,
						 ARR_TYPE numberForCheck, const size_t threadCount);

