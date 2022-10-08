#include <iostream>
#include <vector>
#include <string>
 
using namespace std;
 //bubble sort
void sort(vector<pair<int, string>>& vec) 
{
    bool sorted;
    int size = vec.size();
 
    for (int j = 0; j < size - 1; j++)
    {
        sorted = true;
 
        for (int i = 0; i < size - j - 1; i++)
        {
            //if true than change place
            if (vec[i].first > vec[i + 1].first)
            {
                pair<int, string> temp = vec[i];
                vec[i] = vec[i + 1];
                vec[i + 1] = temp;
 
                sorted = false;
            }
        }
 
        if (sorted)
        {
            break;
        }
    }
}
 //count of the same number
int count(vector<int>& v, int number)
{
    int result = 0;
 
    for (int i : v)
    {
        if (i == number)
        {
            result++;
        }
    }
 
    return result;
}
 //Result like 19=5+3+3+2+2+2+2 ---> (5 3^2 2^4)
int calcNumberValue(vector<int> v, vector<int> array)
{
    int result = 0;
 //array have only numbers of StartPrimes!
    for (int i : array)
    {
        result += count(v, i);
        result *= 10;
    }
 
    result /= 10;
 
    return result;
}
 //amount - index value
void prepareResult(vector<int>& result, int amount, vector<pair<int, string>>& line_result, vector<int> array)
{
    vector<int> v;
    string result_string;
    //accept, only rise sort
    for (int i = 1; i < amount; i++)
    {
        if (result[i] > result[i - 1])
        {
            return;
        }
    }
 //push too vecotor and convert to string
    for (int i = 0; i < amount; i++)
    {
        v.push_back(result[i]);
        result_string += to_string(result[i]) + "+";
    }
 //remov the last element in line because "+"
    result_string.erase(result_string.size() - 1);
    //make pair because "calc_number_value" count of given number, "result_string" that numbers with "+"
    line_result.push_back(make_pair(calcNumberValue(v, array), result_string));
}
 
bool isPrimeNumber(int n)
{
    if (n < 2)
    {
        return false;
    }
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}
 
vector<int> startPrime(int n)
{
    vector<int> v;
 
    for (int i = n; i > 0; i--)
    {
        if (isPrimeNumber(i))
        {
            v.push_back(i);
        }
    }
    return v;
}
 
void findPartitions(vector<int>& result, int index, int sum, vector<int> array, int new_number, vector<pair<int, string>>& line_result)
{
    if (sum == new_number)
    {
        prepareResult(result, index, line_result, array);
        return;
    } 
    if (sum > new_number || index >= new_number)
    {
        return;
    }
 
    for (int i : array)
    {
        if (index >= result.size())
        {
            result.push_back(i);
        }
        else
        {
            //next prime element index
            result[index] = i;
        }
        findPartitions(result, index + 1, sum + i, array, new_number, line_result);
    }
}
 
void partitions(int number, int max_number, vector<string>& result_all_lines)
{
    if (number <= 0 || isPrimeNumber(max_number) == false)
    {
        return;
    }
 
    // Collect result
    vector<int> result;
    vector<int> array;
    vector<pair<int, string>> line_result;
    //array of all prime numbers -- max_number
    array = startPrime(max_number);
    //push first element in arrary, it is the biggest or equal on next
    result.push_back(max_number);
 
    findPartitions(result, 1, max_number, array, number, line_result);
    sort(line_result);
 
    for (pair<int, string> res : line_result)
    {
        result_all_lines.push_back(res.second);
    }
}
 
int main()
{
    int lines, number, max_number;
    vector<string> result_all_lines;
 
    cin >> lines;
 
    for (int i = 0; i < lines; i++)
    {
        cin >> number;
        cin >> max_number;
        partitions(number, max_number, result_all_lines);
    }
    
    for (int i = 0; i < result_all_lines.size(); i++)
    {
        cout << result_all_lines[i] << endl;
    }
    return 0;
}