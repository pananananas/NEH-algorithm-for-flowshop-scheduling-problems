#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "../inc/job.hh"
#include "../inc/helpers.hh"

int main(int argc, char const *argv[])
{
    const std::string filename = "./../data/neh.data.txt";
    try
    {
        bool end_program = false;

        while (!end_program)
        {
            std::cout << "Enter the number of the dataset you want to use (1-10) or k to exit: ";
            char dataset_number;
            std::cin >> dataset_number;
            if (dataset_number == 'k')
            {
                end_program = true;
                continue;
            }
            int dataset_number_int = dataset_number - '0';

            std::vector<Job> jobs = getJobsFromFile(filename, dataset_number_int);
            
            // std::vector<int> best_sequence = bruteForceBestSequence(jobs);
            // std::cout << "Best sequence using brute force: ";
            // for (int i = 0; i < best_sequence.size(); ++i)
            // {
            //     std::cout << best_sequence[i] << " ";
            // }
            // std::cout << "Cmax: " << Cmax(jobs, best_sequence) << std::endl;

            // get best sequence using NEH algorithm
            std::vector<int> neh_sequence = nehAlgorithmBestSequence(jobs);
            std::cout << "Best sequence using NEH algorithm: ";
            for (int i = 0; i < neh_sequence.size(); ++i)
            {
                std::cout << neh_sequence[i] << " ";
            }
            std::cout << "Cmax: " << Cmax(jobs, neh_sequence) << std::endl;
        }
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
}