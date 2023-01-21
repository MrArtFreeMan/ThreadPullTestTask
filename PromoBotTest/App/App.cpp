#include "App.h"

using namespace std;
using namespace ns_ThreadPull;
//+-------------------------------------------------------------
//! Tasks:
//+-------------------------------------------------------------
//факториал числа N
static long Factorial(int N) {
	long ret = 1;
	for (long i = 1; i <= N; ++i)
		ret *= i;
	return ret;
}
//двойной факториал числа N
static long TwinFactorial(int N) {
    long res = 1;
    if (N % 2 == 0)
    {
        for (int i = 2; i <= N; i += 2)
            res *= i;
    }
    else
    {
        for (int i = 1; i <= N; i += 2)
            res *= i;
    }
    return res;
}
//N-ое число Фиббоначи
static long NFibbonachiNumber(int N) {
    if (N <= 1) {
        return 0;
    }
    else if (N == 2) {
        return 1;
    }
    else {
        long numFirst = 1;
        long numSecond = 1;
        long numNext = 1;
        for (int i = 0; i < N - 2; i++) {
            numNext = numFirst + numSecond;
            numFirst = numSecond;
            numSecond = numNext;
        }
        return numNext;
    }
}
//-------------------------------------------------------------
TestPullApp::TestPullApp() {
}
//-------------------------------------------------------------
TestPullApp::~TestPullApp() {
}
//-------------------------------------------------------------
void TestPullApp::StartPull() {
	TPull.StartPull();
}
//-------------------------------------------------------------
void TestPullApp::StopPull() {
	TPull.StopPull();
}
//-------------------------------------------------------------
long TestPullApp::GetTaskResult(int taskNum) {
    Task* task = TPull.GetTask(taskNum);
    if (task != nullptr)
        return TPull.GetTask(taskNum)->result;
    else
        return 0;
}
//-------------------------------------------------------------
void TestPullApp::SetNumberOfThreads(int number) {
	TPull.SetThreadsNumber(number);
}
//-------------------------------------------------------------
void TestPullApp::RunPull() {
	TPull.Run();
}
//+------------------------------------------------------------
//!создание пулла задач
//+------------------------------------------------------------
void TestPullApp::CreateTasks() {
    Task task1, task2, task3;
    task1.function = Factorial;
    TPull.AddTask(task1);
    task2.function = TwinFactorial;
    TPull.AddTask(task2);
    task3.function = NFibbonachiNumber;
    TPull.AddTask(task3);
}
//-------------------------------------------------------------
void TestPullApp::SetTaskArgument(int taskNum, int argument) {
    if (taskNum < TPull.GetTasksSize()) {
        TPull.GetTask(taskNum)->argument = argument;
    }
}
//-------------------------------------------------------------
int TestPullApp::GetNumberOfTasks() {
    return TPull.GetTasksSize();
}
//-------------------------------------------------------------
void TestPullApp::RemoveTask(int index) {
    TPull.RemoveTask(index);
}
//-------------------------------------------------------------