#pragma once

#include "DataStructs.h"

#include <vector>
#include <atomic>

using namespace std;
//+-----------------------------------------------------
//!������� � ����� ������� ������� �����, ��� ���� ����� ������
//+-----------------------------------------------------
extern atomic<int> NumberOfThread;
//+-----------------------------------------------------
//!������������ ���� ��� ������
//+-----------------------------------------------------
namespace ns_ThreadPull {
//+-----------------------------------------------------
//!����� ���������� �����
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
			bool IsStartPull = false;//���� ������ �����: ��-��������� ���� ����������
			vector<TaskThread> Threads;//���� �������( ��������� ���������� � DataStructs.h)
			vector<Task> Tasks;//���� �����( ��������� ���������� � DataStructs.h)

			void RunTask(long(*function)(int arg), int arg, long& res, bool& threadDone);
			void CreateTaskThread(int threadIndex, int taskIndex);
	};
//------------------------------------------------------------
}
//+-----------------------------------------------------------
