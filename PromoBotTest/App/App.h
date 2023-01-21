#pragma once

#include <iostream>

#include "../ThreadPull/ThreadPull.h"

using namespace std;
using namespace ns_ThreadPull;
//+-----------------------------------------------------
//!класс для тестирования пула потоков
//+-----------------------------------------------------
class TestPullApp {

	public:
		TestPullApp();
		~TestPullApp();

		void StartPull();
		void StopPull();
		void RunPull();
		void SetNumberOfThreads(int number);
		void SetTaskArgument(int taskNum, int argument);
		long GetTaskResult(int taskNum);
		void CreateTasks();
		int  GetNumberOfTasks();
		void RemoveTask(int index);
	private:
		ThreadPull TPull;//пулл потоков

};
//+-----------------------------------------------
