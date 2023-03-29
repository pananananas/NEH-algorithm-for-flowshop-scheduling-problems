// #include "../inc/job.hh"
// #include "../inc/helpers.hh"
// #include "../inc/job_algorithms.hh"
// #include <map>
// #include <algorithm>
// #include <iostream>

// std::vector<Job> filterJobsByOperationNumber(const std::vector<Job> &jobs, int decimal_number)
// {
//     std::vector<Job> result_jobs;
//     result_jobs.reserve(jobs.size()); // pre-allocate memory for the result vector

//     for (int i = 0, b = 1; i < jobs.size(); i++, b <<= 1)
//     {
//         if (b & decimal_number)
//         {
//             result_jobs.push_back(jobs[i]);
//         }
//     }

//     return result_jobs;
// }

// // lecimy po wszystkich jobach majac kolejnego joba i robimy swap swap
// // po wszystkich jobach i dla kazdego liczymy cmax i pozycje na ktorej jest, 
// // po wszystkich jobach  wstawiamy tego nowego joba tam gdzie mial najmniejszy cmax  (zapisalismy ta pozycje)
// //  

// int getPDAlgorithmWitiSum(const std::vector<Job> &jobs)
// {
//     int jobs_size = jobs.size();
//     int memory_size = 1 << jobs_size;
//     int max_op_num = memory_size;
//     std::vector<int> weighted_delays(memory_size);
//     weighted_delays[0] = 0;

//     for (int op_num = 1; op_num < max_op_num; op_num++)
//     {
//         std::vector<Job> filtered_jobs = filterJobsByOperationNumber(jobs, op_num);
//         int length = getTotalJobLength(filtered_jobs);
//         weighted_delays[op_num] = INT_MAX;

//         for (int i = 0, b = 1; i < jobs_size; ++i, b <<= 1)
//         {
//             if (op_num & b)
//             {
//                 weighted_delays[op_num] = std::min(weighted_delays[op_num], weighted_delays[op_num - b] + jobs[i].getPenalty(length));
//             }
//         }
//     }

//     return weighted_delays[max_op_num - 1];
// }