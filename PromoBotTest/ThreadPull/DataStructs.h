#pragma once
#include <thread>

using namespace std;
//+-----------------------------------------------------
//!структура потока задачи
//+-----------------------------------------------------
struct TaskThread {
	bool IsDone = false;//маркер завершения выполнения задачи
	thread* taskThread; //указатель на поток выполнения задачи
	TaskThread() {}
	TaskThread(bool isDn, thread* tThd) {
		IsDone = isDn;
		taskThread = tThd;
	}
};
//+-----------------------------------------------------
//!структура задачи
//+-----------------------------------------------------
struct Task
{
	long result = 0;//результат задачи
	int argument = 6;//аргумент по-умолчанию
	long(*function)(int arg) = nullptr;//указатель на функциональное действие

	Task() {}
	~Task() {}
	Task(int arg, long(*func)(int arg)) {
		argument = arg;
		function = *func;
	}
};
//+-----------------------------------------------------