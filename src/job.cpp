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

void printJobs(const std::vector<Job> &jobs)
{
    std::cout << "id, p, w, d" << std::endl;
    for (int i = 0; i < jobs.size(); i++)
    {
        std::cout << jobs[i].getId() << " " << jobs[i].getLength() << " " << jobs[i].getWeight() << " " << jobs[i].getDeadline() << " " << std::endl;
    }
}

/**
 * @brief Get the Weighted Delays Sum number, known as WiTi.
 * This is our score, this value should be minimized.
 *
 * @param jobs
 * @return int
 */
int getWeightedDelaysSum(const std::vector<Job> &jobs)
{
    int c = 0;
    int delays = 0;
    for (auto job : jobs)
    {
        c += job.getLength();
        delays += job.getDelay(c) * job.getWeight();
    }
    return delays;
}

/**
 * @brief Get length of all jobs - or time needed to complete all jobs.
 *
 * @param jobs
 * @return int total length of all jobs
 */
int getTotalJobLength(const std::vector<Job> &jobs)
{
    int total_length = 0;
    for (auto job : jobs)
    {
        total_length += job.getLength();
    }
    return total_length;
}

std::vector<Job> getJobsFromFile(std::string filename, int dataset_number)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file " + filename);
    }

    std::string line;
    std::vector<Job> jobs;
    int p, w, d;
    bool found_dataset = false;
    int id = 0;

    while (std::getline(file, line))
    {
        // check if line starts with "data.x:"
        if (line.find("data." + std::to_string(dataset_number) + ":") == 0)
        {
            // read number of jobs
            std::getline(file, line);
            int n = std::stoi(line);
            // read jobs
            for (int i = 0; i < n; ++i)
            {
                if (!std::getline(file, line))
                {
                    throw std::runtime_error("Unexpected end of file while reading jobs");
                }
                std::stringstream ss(line);
                if (!(ss >> p >> w >> d))
                {
                    throw std::runtime_error("Error reading job data from file");
                }
                jobs.push_back(Job(id, p, w, d));
                id++;
            }
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