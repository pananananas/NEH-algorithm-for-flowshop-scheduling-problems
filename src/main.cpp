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
    const std::string filename = "./../neh.data.txt";
    try
    {
        bool end_program = false;

        while (!end_program)
        {
            int dataset_number;
            int algorithm_number;
            std::cout << "Enter the number of the dataset you want to use (1-10) or -1 to exit: ";
            std::cin >> dataset_number;

            //  check if equal to 'k' to exit program
            if (dataset_number == -1)
            {
                end_program = true;
                break;
            }

            if (dataset_number < 0 || dataset_number > 100)
            {
                std::cout << "Invalid dataset number. Try again." << std::endl;
                continue;
            }

            std::cout << "Choose algorithm: 1 - Brute force, 2 - NEH algorithm: ";
            std::cin >> algorithm_number;

            if (algorithm_number != 1 && algorithm_number != 2)
            {
                std::cout << "Invalid algorithm number. Try again." << std::endl;
                continue;
            }

            std::vector<Job> jobs = getJobsFromFile(filename, dataset_number);

            if (jobs.size() > 10 && algorithm_number == 1)
            {
                std::cout << "\n\t Too many jobs to calculate Cmax using brute force. Using NEH algorithm instead.\n"
                          << std::endl;
                continue;
            }

            if (algorithm_number == 1)
            {
                // get best sequence using brute force
                std::vector<int> best_sequence = bruteForceBestSequence(jobs);
                std::cout << "\n\t Best sequence using brute force: \n\t";
                for (int i = 0; i < best_sequence.size(); ++i)
                {
                    std::cout << best_sequence[i]+1 << " ";
                }
                std::cout << "\t Cmax: " << Cmax(jobs, best_sequence) << std::endl;
            }
            else
            {
                // get best sequence using NEH algorithm
                std::vector<int> neh_sequence = nehAlgorithmBestSequence(jobs);
                std::cout << "\n\t Best sequence using NEH algorithm: \n\t";
                for (int i = 0; i < neh_sequence.size(); ++i)
                {
                    std::cout << neh_sequence[i]+1 << " ";
                }
                std::cout << "\t Cmax: " << Cmax(jobs, neh_sequence) << std::endl;
            }
        }
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
}