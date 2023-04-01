#pragma once
#include <vector>
#include <string>
#include <algorithm>

class Task
{
private:
    int _duration;

public:
    Task(int duration) : _duration(duration) {}
    int getDuration() const { return _duration; }
};

class Job
{
private:
    std::vector<Task> _tasks;

public:
    Job(std::vector<Task> tasks) : _tasks(tasks) {}
    Job(std::vector<int> tasks)
    {
        for (int i = 0; i < tasks.size(); i++)
        {
            _tasks.push_back(Task(tasks[i]));
        }
    }
    std::vector<Task> getTasks() const { return _tasks; }

    int getSumOfTasksDurations() const
    {
        int sum = 0;
        for (auto task : _tasks)
        {
            sum += task.getDuration();
        }
        return sum;
    }
};

int Cmax(const std::vector<Job> &jobs, const std::vector<int> &sequence = {});
std::vector<Job> getJobsFromFile(std::string filename, int dataset_number);
std::vector<int> bruteForceBestSequence(const std::vector<Job> &jobs);
std::vector<Job> reorderJobs(const std::vector<Job> &jobs, const std::vector<int> &sequence);
std::vector<int> nehAlgorithmBestSequence(const std::vector<Job> &jobs);
void printJobs(const std::vector<Job> &jobs);