#pragma once
#include <string>
#include <fstream>
#include <queue>
#include <thread>
#include <vector>
#include <mutex>
#include <list>
#include <atomic>
#include "Factor.h"
#include "Breach.h"
using namespace std;

class Thread_pool
{
public:
	Thread_pool(string input, string output, unsigned int thread_count);
	~Thread_pool();
	
	void ReadFile();
	void Farewell();
	void Proceed();
	void enqueueJob(std::function<void()> task, std::function<string()> taskInfo);
	void enternity();

private:
	string input;
	string output;
	ifstream fin;
	ofstream fout;
	condition_variable cv, m_notifyJob;
	mutex m_lockJobsList;


	bool _act, absolution;
	mutex mtx,wback;
	
	pair<std::function<void()>, std::function<string()> > getNextTask();
 	vector <unique_ptr<std::thread> > workers;
	unsigned int thread_count;
 
	list< std::pair<std::function<void()>, std::function<string()>>> tasks;
	vector<thread> pool; //2 main threads
	atomic<bool> life_Ebb;
};

