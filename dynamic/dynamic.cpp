#include "dynamic.h"


typedef unsigned long size_t;
typedef int ARR_TYPE;

//потоковая функция
void* threadFunc( void * treadData){

	TreadData * t = (TreadData*) treadData;

	ARR_TYPE * arr = t->arr;
	size_t arrSize = t->arrSize;
	ARR_TYPE check = t->check;
	size_t * answerPtr = t->answerPtr;



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
	*answerPtr = answer;

	//завершаем поток
	pthread_exit(0);
}




size_t countInArrThread( ARR_TYPE *arr, const size_t arrSize,
 						  ARR_TYPE numberForCheck, const  size_t threadCount) {

	if (threadCount > 10 || threadCount == 0){
		printf("thread must be [1..10]");
		assert(false);
		return 0;
	}

	//создаем идентификатор потока
	pthread_t threads[threadCount];
	size_t ** answerArr = (size_t **)calloc(threadCount, sizeof(size_t *) );
	for (size_t i = 0; i < threadCount;i++)
		answerArr[i] =  (size_t *)calloc(threadCount, sizeof(size_t) );
 
	//создаем поток по идентификатору thread и функции потока threadFunc
	//и передаем потоку указатель на данные thread_data
	size_t partSize = arrSize / threadCount;


	//сколько потоков - столько и структур с потоковых данных
	TreadData* TD = (TreadData*) malloc(threadCount * sizeof(TreadData));


	for (size_t i = 0; i < threadCount;i++){
		TD[i].arr = arr + (partSize * i);
		TD[i].arrSize = partSize;
		TD[i].check = numberForCheck;
		TD[i].answerPtr = answerArr[i];
		pthread_create( &(threads[i]), NULL, threadFunc, &TD[i]  );
	}
	
	//ждем завершения потока
	for (size_t i = 0; i < threadCount;i++)
		pthread_join(threads[i], NULL);


	size_t answer = 0;
	for (size_t i = 0; i < threadCount;i++){
		answer += *(answerArr[i]);
		free(answerArr[i]);
	}
			
	free(TD);
	free(answerArr);


	return answer;
	
}