#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "../inc/job.hh"
#include "../inc/helpers.hh"
#include "../inc/job_algorithms.hh"

int main(int argc, char const *argv[])
{
    try
    {
        std::string filename = "./../data/neh.data.txt";

        std::vector<std::vector<int>> jobs_data = {
            {1, 1, 3},
            {4, 1, 2},
            {3, 4, 3},
            {2, 4, 1}};
        std::vector<Job> jobs;
        std::vector<int> sequence = {0, 2, 1, 3};

        for (int i = 0; i < jobs_data.size(); i++)
        {
            jobs.push_back(Job(jobs_data[i]));
        }

        std::cout << "Cmax:" << Cmax(jobs, sequence) << std::endl;

        // for (int dataset_number = 10; dataset_number <= 20; dataset_number++)
        // {
        //     std::vector<Job> jobs = getJobsFromFile(filename, dataset_number);
        //     std::cout << "Wynik dla zbioru " << dataset_number << std::endl;
        //     std::cout << "Wynik nieposortowany: " << getWeightedDelaysSum(jobs) << " --- ";
        //     std::cout << "Wynik optymalny: " << getPDAlgorithmWitiSum(jobs) << std::endl << std::endl;
        // }
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
}