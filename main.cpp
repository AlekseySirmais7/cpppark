// IZ_2.cpp: определяет точку входа для приложения.
/*
ИЗ2 посвящено приобретению навыков системной разработки на C и работе с внешними библиотеками.
 В качестве результата ИЗ2 ожидается:
* грамотное разбиение проекта на файлы;
* наличие двух реализаций – последовательной и параллельной, оформленных в виде статической и
*  динамической библиотеки,
а также тестирующей программы, которая будет сравнивать на разных входных данных результаты
 обеих реализаций между собой;
* максимальная утилизация ресурсов процессора при параллельной обработке данных
*  путём использования нескольких процессов или потоков;
* продуманные структуры данных в целях экономии оперативной памяти;
* реализация алгоритмов, эффективно взаимодействующих с кэш-памятью.

В вашем распоряжении — массив из 100 млн. чисел. Необходимо подсчитать количество таких чисел,
которые обращают в истину заданный предикат (например, x < 157).
 Реализуйте наивный алгоритм последовательного подсчёта
и параллельный алгоритм, использующий несколько потоков, с учётом оптимизации работы с кэш-памятью.
*/

#include "main.h"


void test_5() {

	int * arr = (int *)calloc(MAX_ARR_SIZE, sizeof(int));

	for (size_t i = 0; i < MAX_ARR_SIZE; i++){
		arr[i] = 12 ; 
	}
	arr[99999999] = 5;
	arr[99919999] = 5;
	arr[0] = 5;
	arr[20000000] = 5;
	// итого 4 шт под условие
	size_t answer = 0;
	// get time
	clock_t start = clock();
	answer = countInArr(arr, MAX_ARR_SIZE, NUMBER_FOR_CHECK);
	clock_t f = clock();
	double time = (double) (f - start)/CLOCKS_PER_SEC;

	size_t threadCount = 5;
	size_t answerD = 0;

	start = clock();
	answerD = countInArrThread(arr, MAX_ARR_SIZE, NUMBER_FOR_CHECK, threadCount);
	f = clock();
	double timeD = (double) (f - start)/CLOCKS_PER_SEC/threadCount;

	if (answer != answerD)
		assert(false);


	std::cout<<"5 STATIC time:"<<time<<"\n";
	std::cout<<"5 DYNAMIC time:"<<timeD<<"\n";

	free(arr);
}

void test_99999995() {

	int * arr = (int *)calloc(MAX_ARR_SIZE, sizeof(int));

	for (size_t i = 0; i < MAX_ARR_SIZE; i++){
		arr[i] = 120 ; 
	}
	arr[4567] = 340;
	arr[994199] = 340;
	arr[3] = 340;
	arr[20000000] = 3340;
	arr[20066000] = 340;


	int number_for_check = 300;
	size_t answer = 0;
	// get time
	clock_t start = clock();
	answer = countInArr(arr, MAX_ARR_SIZE, number_for_check);
	clock_t f = clock();
	double time = (double) (f - start)/CLOCKS_PER_SEC;

	size_t threadCount = 4;
	size_t answerD = 0;

	start = clock();
	answerD = countInArrThread(arr, MAX_ARR_SIZE, number_for_check, threadCount);
	f = clock();
	double timeD = (double) (f - start)/CLOCKS_PER_SEC/threadCount;

	if (answer != answerD)
		assert(false);


	std::cout<<"99999995 STATIC time:"<<time<<"\n";
	std::cout<<"99999995 DYNAMIC time:"<<timeD<<"\n";

	free(arr);
}


void test_random() {

	int * arr = (int *)calloc(MAX_ARR_SIZE, sizeof(int));

	for (size_t i = 0; i < MAX_ARR_SIZE; i++){
		arr[i] = rand()%1000 ; 
	}

	int number_for_check = 500;
	size_t answer = 0;
	
	clock_t start = clock();
	answer = countInArr(arr, MAX_ARR_SIZE, number_for_check);
	clock_t f = clock();
	double time = (double) (f - start)/CLOCKS_PER_SEC;

	size_t threadCount = 4;
	size_t answerD = 0;

	start = clock();
	answerD = countInArrThread(arr, MAX_ARR_SIZE, number_for_check, threadCount);
	f = clock();
	double timeD = (double) (f - start)/CLOCKS_PER_SEC/threadCount;

	if (answer != answerD)
		assert(false);


	std::cout<<"rand STATIC time:"<<time<<"\n";
	std::cout<<"rand DYNAMIC time:"<<timeD<<"\n";

	free(arr);
}


int main() {	
	
	printf("START tests!\n");
	test_5();
	test_99999995();
	test_random();
	
	printf("END tests!\n");
	return 0;
}
