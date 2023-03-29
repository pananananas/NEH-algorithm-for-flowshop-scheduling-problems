#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <queue>
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

std::vector<Job> getJobsFromFile(std::string filename, int dataset_number)
{
    // std::ifstream file(filename);
    // if (!file.is_open())
    // {
    //     throw std::runtime_error("Cannot open file " + filename);
    // }

    // std::string line;
    // std::vector<Job> jobs;
    // int p, w, d;
    // bool found_dataset = false;
    // int id = 0;

    // while (std::getline(file, line))
    // {
    //     // check if line starts with "data.x:"
    //     if (line.find("data." + std::to_string(dataset_number) + ":") == 0)
    //     {
    //         // read number of jobs
    //         std::getline(file, line);
    //         int n = std::stoi(line);
    //         // read jobs
    //         for (int i = 0; i < n; ++i)
    //         {
    //             if (!std::getline(file, line))
    //             {
    //                 throw std::runtime_error("Unexpected end of file while reading jobs");
    //             }
    //             std::stringstream ss(line);
    //             if (!(ss >> p >> w >> d))
    //             {
    //                 throw std::runtime_error("Error reading job data from file");
    //             }
    //             jobs.push_back(Job(id, p, w, d));
    //             id++;
    //         }
    //         found_dataset = true;
    //         break;
    //     }
    // }

    // if (!found_dataset)
    // {
    //     throw std::runtime_error("Cannot find dataset " + std::to_string(dataset_number) + " in file " + filename);
    // }

    // return jobs;
}