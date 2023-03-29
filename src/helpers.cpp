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

int max_of_vector(const std::vector<int> &v)
{
    int max = v[0];
    for (int i = 1; i < v.size(); ++i)
        if (v[i] > max)
            max = v[i];

    return max;
}