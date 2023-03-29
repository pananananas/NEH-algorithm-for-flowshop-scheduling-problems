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
        std::string filename = "./../data/witi.data.txt";

        for (int dataset_number = 10; dataset_number <= 20; dataset_number++)
        {
            std::vector<Job> jobs = getJobsFromFile(filename, dataset_number);
            std::cout << "Wynik dla zbioru " << dataset_number << std::endl;
            std::cout << "Wynik nieposortowany: " << getWeightedDelaysSum(jobs) << " --- ";
            std::cout << "Wynik optymalny: " << getPDAlgorithmWitiSum(jobs) << std::endl << std::endl;
        }
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
}