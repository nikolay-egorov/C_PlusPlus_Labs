#include "Thread_pool.h"
#include  "EXCPN_NO_FILE.h"


Thread_pool::Thread_pool(string input, string output, unsigned int thread_count)
{
	this->input = input;
	this->output = output;
 
	if (thread_count <= thread::hardware_concurrency())this->thread_count = thread_count;
	else this->thread_count = thread::hardware_concurrency();
	 
	this->absolution = this->life_Ebb= false;
	this->_act = true;
	fin.open(this->input);
	if (!fin.good())
		throw EXCPN_NO_FILE();

	else {
		workers.resize(this->thread_count);

		for (std::unique_ptr<std::thread>& worker : workers)
		{
			worker.reset(new std::thread(&Thread_pool::enternity, this));
		}


		Proceed();
	}
}

Thread_pool::~Thread_pool()
{
	fin.close();
	fout.close();
	pool[0].detach();
 	pool[1].join();

	{
		std::unique_lock<std::mutex> lockQueue(m_lockJobsList);
		life_Ebb = true;
		m_notifyJob.notify_all();
	}
	for (std::unique_ptr<std::thread>& worker  : workers)
	{
		worker ->join();
	}
 
}

void Thread_pool::enternity()
{
	try {
		for (;;)
		{

			std::pair<std::function<void()>, std::function<string()> > job = getNextTask();
			job.first();

			{std::unique_lock<std::mutex> lock(wback);
			fout << job.second() << endl;
			}
		}

	}
	catch (Breach&a)
	{
	 
	}

}




 
void Thread_pool::Farewell()
{
	while (true) {


		string answer;
		cin >> answer;
		cin.clear();
		if (answer == "exit") {
			absolution = true;
			life_Ebb = true;

		}
		if (answer == "pause") {
			_act = false;
		//	cout << "pausing\n";
			if (fout.is_open())
				fout.close();
		}
		if (answer == "resume") {
			_act = true;
			cout << "resuming??????\n";
			if (!fout.is_open())
				fout.open(output, ios::app);
				cv.notify_all();

		}
	    
	}
}

void Thread_pool::Proceed()
{
	 
	fout.open(output );
	pool.push_back(thread(&Thread_pool::Farewell, this));
	pool.push_back(thread(&Thread_pool::ReadFile, this));

	
}



void Thread_pool::enqueueJob(std::function<void()> task, std::function<string()> taskInfo)
{
	std::unique_lock<std::mutex> lockQueue(m_lockJobsList);
	tasks.emplace_back(move(task), move(taskInfo));
	m_notifyJob.notify_one();
}



 pair<std::function<void()>, std::function<string()>> Thread_pool::getNextTask()
{
	std::unique_lock<std::mutex> lockList(m_lockJobsList);

 
		while (!life_Ebb)
		{
			if (!tasks.empty())
			{
				std::pair<std::function<void()>, std::function<string()> > job = tasks.front();
				tasks.pop_front();
				return job;
			}

			m_notifyJob.wait(lockList);
		}
		throw Breach("As life ebbs, terrible vistas of emptyness reveal themself\n");

	 
}

void Thread_pool::ReadFile()
{
	uint64_t n;

		while (!absolution) {

			unique_lock<mutex> ulm(mtx);
			while (!this->_act)  cv.wait(ulm);

			if (fin >> n  ) {
				Factor *t = new Factor(n);
				enqueueJob( bind(&Factor::Blend, t), bind(&Factor::Get, t));
				if (absolution)
					break;
				_sleep(500);

			}

		}
		fin.close();
		fout.close();


	
}