#include "../inc/helpers.hh"

std::vector<int> decimalToBinaryVector(int number)
{
    std::vector<int> binary;
    while (number > 0)
    {
        binary.push_back(number % 2);
        number /= 2;
    }
    return binary;
}