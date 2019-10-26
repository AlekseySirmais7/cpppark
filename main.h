﻿// IZ_2.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.
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

#pragma once
#include <iostream>
#include <time.h>
#include "static.h"
#include "dynamic.h"


size_t MAX_ARR_SIZE = 100000000;
int NUMBER_FOR_CHECK = 10;


// [start, ... , end)
//size_t funT(const ARR_TYPE *arr, const size_t &start, const size_t &end, const  ARR_TYPE &numberForCheck);