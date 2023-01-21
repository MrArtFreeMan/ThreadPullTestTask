// PromoBotTest.cpp : точка входа приложения и допфункции исполнения

#include "PromoBotTest.h"
#include "App/App.h"

#include <array>
#include <thread>
#include <iostream> 
#include <string>
#include <regex>
#include <assert.h>

using namespace std;
//+-----------------------------------------------------
//!глобальные объекты:
//+-----------------------------------------------------
atomic<int> NumberOfThread=0;// определим счетчик потоков задач
TestPullApp app;//экземпляр класса-тестера потокового пулла
//+-----------------------------------------------------
//!энум доступных действий
//+-----------------------------------------------------
enum Commands {
	cmPausePull = 0,
	cmStartPull,
	cmShowHelp,
	cmSetThreadNumber,
	cmSetTaskArgument,
	cmShowTasksNumber,
	cmStopProgram,
	cmRemoveTask,
	cmGetTaskResult,
	Count
};
//+-----------------------------------------------------
//!массив описаний доступных действий
//+-----------------------------------------------------
const array<string, Commands::Count> AvailableCommands = {
	"0 - pause the thread pull",
	"1 - start the thread pull;",
	"2 - print available commands;",
	"3 - set number of threads;",
	"4 - set task argument using task index",
	"5 - show number of tasks",
	"6 - stop program",
	"7 - remove task",
	"8 - get task result"
};
//+-----------------------------------------------------
//!проверка на ввод команды
//+-----------------------------------------------------
bool CheckCommand(int command) {
	if ((command >= 0) && (command < AvailableCommands.size()))
		return true;
	return false;
}
//+-----------------------------------------------------
//!проверка: введенное является числом?
//+-----------------------------------------------------
bool IsDigit(string strDigit) {
	return regex_match(strDigit, regex("[0-9]+"));
}
//+-----------------------------------------------------
//!создадим пулл задач
//+-----------------------------------------------------
void Prepairing() {
	app.CreateTasks();
}
//+-----------------------------------------------------
//!запросим ввод команды
//+-----------------------------------------------------
int InputCommand(string prompt) {
	string stringCommand = "2";//default: print help
	int intCommand = 2;
	cout << prompt.c_str() << endl;
	cin >> stringCommand;
	if (IsDigit(stringCommand)) {
		intCommand = stoi(stringCommand);
		if (CheckCommand(intCommand)) {
			return intCommand;
		}
	}
	cout << "error command input" << endl;
	return 2;
}
//+-----------------------------------------------------
//!печать справки 
//+-----------------------------------------------------
void PrintAvailableCommands() {
	cout << "Available commands:"                << endl;
	cout << AvailableCommands[cmPausePull      ] << endl;
	cout << AvailableCommands[cmStartPull      ] << endl;
	cout << AvailableCommands[cmShowHelp       ] << endl;
	cout << AvailableCommands[cmShowTasksNumber] << endl;
	cout << AvailableCommands[cmStopProgram    ] << endl;
	cout << AvailableCommands[cmRemoveTask     ] << endl;
	cout << AvailableCommands[cmGetTaskResult  ] << endl;
}
//+-----------------------------------------------------
//!функция запуска пулла
//+-----------------------------------------------------
void Run() {
	app.RunPull();
}
//+-----------------------------------------------------
//!запустим пулл
//+-----------------------------------------------------
void StartPull() {
	app.StartPull();
	if (!IsRunThreadPull) {
		thread runThread(Run);
		runThread.detach();
		IsRunThreadPull = true;//
	}
}
//+-----------------------------------------------------
//!остановим пулл
//+-----------------------------------------------------
void StopPull() {
	app.StopPull();
	IsRunThreadPull = false;//
}
//+-----------------------------------------------------
//!указать число потоков
//+-----------------------------------------------------
void SetThreadNumber() {
	if (!IsRunThreadPull) {
		cout << "Input number of threads: " << endl;
		string strNum;
		cin >> strNum;
		if (IsDigit(strNum)) {
			int number = stoi(strNum);
			app.SetNumberOfThreads(number);
		}
		else
			cout << "Error input" << endl;
	}
}
//+-----------------------------------------------------
//!изменим аргумент выбранной по индексу задачи
//+-----------------------------------------------------
void SetTaskArgument() {
	if (!IsRunThreadPull) {
		string strInp;
		cout << "Input task index: " << endl;
		cin >> strInp;
		int number = 0;
		int argument = 0;
		if (IsDigit(strInp)) {
			number = stoi(strInp);
		}
		else {
			cout << "Error input" << endl;
			return;
		}
		cout << "Input argument of task: " << endl;
		cin >> strInp;
		if (IsDigit(strInp)) {
			argument = stoi(strInp);
		}
		else {
			cout << "Error input" << endl;
			return;
		}
		app.SetTaskArgument(number, argument);
	}
}
//+-----------------------------------------------------
//!показать число задач в пулле задач
//+-----------------------------------------------------
void ShowNumberOfTasks() {
	cout << "Number of tasks: " << to_string(app.GetNumberOfTasks()) << endl;
}
//+-----------------------------------------------------
//!удалить задачу
//+-----------------------------------------------------
void RemoveTask() {
	string strInp;
	cout << "Input task index: " << endl;
	cin >> strInp;
	int number = 0;
	if (IsDigit(strInp)) {
		number = stoi(strInp);
	}
	else {
		cout << "Error input" << endl;
		return;
	}
	app.RemoveTask(number);
}
//+-----------------------------------------------------
//!получить результат задачи по индексу
//+-----------------------------------------------------
void GetTaskResult() {
	string strInp;
	cout << "Input task index: " << endl;
	cin >> strInp;
	if (IsDigit(strInp)) {
		int number = stoi(strInp);
		long res = app.GetTaskResult(number);
		cout << "Task["<< strInp<<"] = "<< to_string(res) << endl;
	}
	else {
		cout << "Error input" << endl;
		return;
	}
}
//+-----------------------------------------------------
//!точка входа
//+-----------------------------------------------------
int main()
{
	bool isStopProgram = false;
	int command = 2;
	Prepairing();
	cout << "Thread pull test:" << endl;
	cout << endl;
	SetThreadNumber();
	SetTaskArgument();
	PrintAvailableCommands();
	string inputPrompt = "Enter command: ";
	while ((!isStopProgram) && (NumberOfThread==0)) {
		command = InputCommand(inputPrompt);
		if (command == cmStartPull) {
			StartPull();
		}
		if (command == cmPausePull) {
			StopPull();
		}
		if (command == cmShowHelp) {
			PrintAvailableCommands();
		}
		if (command == cmShowTasksNumber) {
			ShowNumberOfTasks();
		}
		if (command == cmStopProgram) {
			StopPull();
			isStopProgram = true;
		}
		if (command == cmRemoveTask) {
			RemoveTask();
		}
		if (command == cmGetTaskResult) {
			GetTaskResult();
		}
	}
	return 0;
}
//+---------------------------------------------------
