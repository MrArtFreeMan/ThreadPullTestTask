#pragma once
#include <thread>

using namespace std;
//+-----------------------------------------------------
//!��������� ������ ������
//+-----------------------------------------------------
struct TaskThread {
	bool IsDone = false;//������ ���������� ���������� ������
	thread* taskThread; //��������� �� ����� ���������� ������
	TaskThread() {}
	TaskThread(bool isDn, thread* tThd) {
		IsDone = isDn;
		taskThread = tThd;
	}
};
//+-----------------------------------------------------
//!��������� ������
//+-----------------------------------------------------
struct Task
{
	long result = 0;//��������� ������
	int argument = 6;//�������� ��-���������
	long(*function)(int arg) = nullptr;//��������� �� �������������� ��������

	Task() {}
	~Task() {}
	Task(int arg, long(*func)(int arg)) {
		argument = arg;
		function = *func;
	}
};
//+-----------------------------------------------------