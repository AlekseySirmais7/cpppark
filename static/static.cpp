

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef unsigned long size_t;
typedef  int ARR_TYPE;


size_t countInArr(ARR_TYPE * arr, size_t arrSize, ARR_TYPE check ) {

    register size_t answer __attribute( (aligne(64)) );
     
	ARR_TYPE *p = NULL;
    int errflag;
	
	long l1dcls = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
	
	if (l1dcls == -1)
  		l1dcls = sizeof(void*);
	errflag = posix_memalign((void**)&p, l1dcls, arrSize * sizeof(ARR_TYPE) );

	if (!errflag) { // если все норм
		size_t parts = 10;
		size_t totalSize = arrSize * sizeof(arr[0]);
		ARR_TYPE *temp = p;

  		p = (ARR_TYPE * )memcpy(p, arr, arrSize * sizeof(arr[0]) );

 		//printf("\ninP: ");
  		answer = 0; // сама проверка по массиву
		for (size_t i = 0; i < arrSize ; i++){
			//printf("%d ", p[i]);
			if ( p[i] < check)
				answer++;
		}

  		free(p);
}
else{
	printf("posix_memalign error: %d\n", errflag);
	assert(false);
}
	return answer;
}