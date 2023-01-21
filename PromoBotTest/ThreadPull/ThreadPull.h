#pragma once

#include "DataStructs.h"

#include <vector>
#include <atomic>

using namespace std;
//+-----------------------------------------------------
//!объявим и здесь счетчик потоков задач, его надо здесь видеть
//+-----------------------------------------------------
extern atomic<int> NumberOfThread;
//+-----------------------------------------------------
//!пространство имен для класса
//+-----------------------------------------------------
namespace ns_ThreadPull {
//+-----------------------------------------------------
//!класс потокового пулла
//+-----------------------------------------------------
	class ThreadPull {
		public:
			ThreadPull();
			~ThreadPull();

			void SetThreadsNumber(int num);
			void StopPull();
			void StartPull();
			bool GetStartStatus();
			int GetTasksSize();
			int GetThreadsSize();
			void AddTask(Task task);
			void RemoveTask(int index);
			Task* GetTask(int index);

			void Run();
		private:
			bool IsStartPull = false;//флаг старта пулла: по-умолчанию пулл остановлен
			vector<TaskThread> Threads;//пулл потоков( структура определена в DataStructs.h)
			vector<Task> Tasks;//пулл задач( структура определена в DataStructs.h)

			void RunTask(long(*function)(int arg), int arg, long& res, bool& threadDone);
			void CreateTaskThread(int threadIndex, int taskIndex);
	};
//------------------------------------------------------------
}
//+-----------------------------------------------------------
