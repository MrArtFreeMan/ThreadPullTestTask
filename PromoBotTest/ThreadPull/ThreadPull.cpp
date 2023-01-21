#include "ThreadPull.h"

#include <iostream>
#include <assert.h>

using namespace std;
//+---------------------------------------------------
//!������������ ���� ��� ������
//+---------------------------------------------------
namespace ns_ThreadPull {
//----------------------------------------------------
	ThreadPull::ThreadPull() {
	}
//----------------------------------------------------
	ThreadPull::~ThreadPull() {
	}
//----------------------------------------------------
	void ThreadPull::SetThreadsNumber(int num) {
		Threads.resize(num);
	}
//----------------------------------------------------
	void ThreadPull::StopPull() {
		IsStartPull = false;
	}
//----------------------------------------------------
	void ThreadPull::StartPull() {
		IsStartPull = true;
	}
//----------------------------------------------------
	bool ThreadPull::GetStartStatus() {
		return IsStartPull;
	}
//----------------------------------------------------
	int ThreadPull::GetTasksSize() {
		return (int)Tasks.size();
	}
//----------------------------------------------------
	int ThreadPull::GetThreadsSize() {
		return (int)Threads.size();
	}
//----------------------------------------------------
	void ThreadPull::AddTask(Task task) {
		Tasks.push_back(task);
	}
//----------------------------------------------------
	void ThreadPull::RemoveTask(int index) {
		if (index < Tasks.size())
			Tasks.erase(Tasks.begin() + index);
		else
			cout << "Error: size of tasks vector less then index of removing item" << endl;
	}
//----------------------------------------------------
	Task* ThreadPull::GetTask(int index) {
		if (index < Tasks.size())
			return &(Tasks.at(index));
		else {
			cout << "Error: size of tasks vector less then index of finding item" << endl;
			return nullptr;
		}
	}
//+---------------------------------------------------
//!����� �������� ������
//+---------------------------------------------------
	void ThreadPull::RunTask(long(*function)(int arg), int arg, long& res, bool& threadDone) {
		res = function(arg);
		NumberOfThread--;//������ ��������� - ������� ������� ���������
		threadDone = true;// ���� ���������
	}
//+---------------------------------------------------
//!�������� ����� ��� ������
//+---------------------------------------------------
	void ThreadPull::CreateTaskThread(int threadIndex, int taskIndex) {
		thread threadTask(&ThreadPull::RunTask, this, Tasks[taskIndex].function, Tasks[taskIndex].argument, ref(Tasks[taskIndex].result), ref(Threads.at(threadIndex).IsDone));
		Threads.at(threadIndex).taskThread = &threadTask;//�������� ����� � ����
		Threads.at(threadIndex).taskThread->join();
		NumberOfThread++;//����� ������� - �������������� �������
	}
//+---------------------------------------------------
//!�������� ����
//+---------------------------------------------------
	void ThreadPull::Run() {
		int Nth = (int)Threads.size();//���������� �������
		int Nts = (int)Tasks.size();//���������� �����
		//��������� �������������: ������� ���, ����� �������
		for (auto item : Threads) {
			item.IsDone = false;
			item.taskThread = nullptr;
		}

		if (Nth >= Nts) {//������� ������ ��� ����� �������
			int taskIndex = 0;
			int threadIndex = 0;
			while (taskIndex < Nts) {
				if (IsStartPull) {
					CreateTaskThread(threadIndex, taskIndex);
					taskIndex++;
					threadIndex++;
				}
				else{
					break;
				}
			}
		}
		else  if (Nth < Nts) {//����� ������ �������
			int taskIndex = 0;
			while (taskIndex < Nts) {
				if (IsStartPull) {
					for (int threadIndex = 0; threadIndex < Nth; threadIndex++) {
						if(taskIndex < Nts){
							if (IsStartPull) {
								if (!Threads[threadIndex].IsDone && (Threads[threadIndex].taskThread == nullptr)) {
									CreateTaskThread(threadIndex, taskIndex);
									taskIndex++;
								}
								if (Threads[threadIndex].IsDone) {//����� �������� ������
									Threads[threadIndex].taskThread = nullptr;//��������� ����� � ����
									Threads[threadIndex].IsDone = false;//������� ����
								}
							}
							else
								break;
						}
						else
							break;
					}
				}
				else 
					break;
			}
		}
		else {
			assert(false);//���� ������� ������ �����
		}
	}
//----------------------------------------------------

}