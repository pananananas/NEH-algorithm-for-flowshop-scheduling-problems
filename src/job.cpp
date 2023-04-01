#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <queue>
#include <numeric>
#include <cmath>
#include <chrono>
#include <ctime>
#include "../inc/job.hh"
#include "../inc/helpers.hh"

std::vector<Job> reorderJobs(const std::vector<Job> &jobs, const std::vector<int> &sequence)
{
    std::vector<Job> reordered_jobs;
    for (int i = 0; i < sequence.size(); ++i)
    {
        reordered_jobs.push_back(jobs[sequence[i]]);
    }
    return reordered_jobs;
}

int Cmax(const std::vector<Job> &jobs, const std::vector<int> &sequence)
{
    std::vector<Job> reordered_jobs = sequence.empty() ? jobs : reorderJobs(jobs, sequence);
    std::vector<int> machine_times(jobs[0].getTasks().size() + 1);

    for (auto job : reordered_jobs)
    {
        std::vector<Task> tasks = job.getTasks();
        for (int j = 1; j < machine_times.size(); ++j)
        {
            machine_times[j] = tasks[j - 1].getDuration() + std::max(machine_times[j - 1], machine_times[j]);
        }
    }

    return max_of_vector(machine_times);
}

std::vector<int> bruteForceBestSequence(const std::vector<Job> &jobs)
{
    std::vector<int> sequence;
    for (int i = 0; i < jobs.size(); ++i)
    {
        sequence.push_back(i);
    }

    std::vector<int> best_sequence = sequence;
    int best_cmax = Cmax(jobs, sequence);

    while (std::next_permutation(sequence.begin(), sequence.end()))
    {
        int cmax = Cmax(jobs, sequence);
        if (cmax < best_cmax)
        {
            best_cmax = cmax;
            best_sequence = sequence;
        }
    }

    return best_sequence;
}

std::vector<int> nehAlgorithmBestSequence(const std::vector<Job> &jobs)
{
    std::vector<Job> sorted_jobs = jobs;
    std::sort(sorted_jobs.begin(), sorted_jobs.end(), [](Job a, Job b)
              { return a.getSumOfTasksDurations() > b.getSumOfTasksDurations(); });

    std::vector<int> sequence = {0};

    for (int i = 1; i < jobs.size(); ++i)
    {
        int best_cmax = std::numeric_limits<int>::max();
        int best_position = 0;

        for (int j = 0; j <= sequence.size(); ++j)
        {
            std::vector<int> new_sequence = sequence;
            new_sequence.insert(new_sequence.begin() + j, i);
            int cmax = Cmax(jobs, new_sequence);
            if (cmax < best_cmax)
            {
                best_cmax = cmax;
                best_position = j;
            }
        }

        sequence.insert(sequence.begin() + best_position, i);
    }
    return sequence;
}

std::vector<Job> getJobsFromFile(std::string filename, int dataset_number)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file " + filename);
    }

    std::string dataset_number_string = std::to_string(dataset_number);
    while (dataset_number_string.size() < 3)
    {
        dataset_number_string = "0" + dataset_number_string;
    }
    std::string line;
    bool found_dataset = false;
    std::vector<Job> jobs;

    while (std::getline(file, line))
    {
        if (line.find("data." + dataset_number_string) != std::string::npos)
        {
            std::cout << "Found dataset " << dataset_number << std::endl;
            // read number of jobs and number of machines
            std::getline(file, line);
            std::stringstream ss(line);
            int n, m;
            if (!(ss >> n >> m))
            {
                throw std::runtime_error("Error reading number of jobs and machines from file");
            }
            std::cout << "Reading " << n << " jobs with " << m << " machines each ..." << std::endl;

            for (int i = 0; i < n; ++i)
            {
                if (!std::getline(file, line))
                {
                    throw std::runtime_error("Unexpected end of file while reading jobs");
                }
                std::stringstream tasks_ss(line);
                std::vector<int> tasks;
                int task;
                for (int j = 0; j < m; ++j)
                {
                    if (!(tasks_ss >> task))
                    {
                        throw std::runtime_error("Error reading task " + std::to_string(j) + " from job " + std::to_string(i));
                    }
                    tasks.push_back(task);
                }

                jobs.push_back(Job(tasks));

                if (tasks.size() != m)
                {
                    throw std::runtime_error("Number of tasks in job " + std::to_string(i) + " is not equal to number of machines");
                }
            }

            std::cout << "Read " << jobs.size() << " jobs" << std::endl;
            found_dataset = true;
            break;
        }
    }

    if (!found_dataset)
    {
        throw std::runtime_error("Cannot find dataset " + std::to_string(dataset_number) + " in file " + filename);
    }

    return jobs;
}

void printJobs(const std::vector<Job> &jobs)
{
    for (auto job : jobs)
    {
        auto tasks = job.getTasks();
        for (auto task : tasks)
        {
            std::cout << task.getDuration() << " ";
        }
        std::cout << std::endl;
    }
}