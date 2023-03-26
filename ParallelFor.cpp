#include <iostream>
#include <vector>
#include <set>
#include "ParallelFor.h"

#if defined WIN32 || defined _WIN64
#include "windows.h"
#else
#include <unistd.h>
#endif

void Delay(int milliseconds)
{
	#if defined WIN32 || defined _WIN64
	Sleep(milliseconds);
	#else
	usleep(milliseconds * 1000);
	#endif
}
	
int main()
{
    // To compile on linux use -lpthread key
    ParallelFor p;

    std::vector<int> TestVector = { 10, 1, 1, 1, 1 };

    p(0, (int)TestVector.size(), 2, [TestVector](int n)
        {
            Delay(TestVector[n] * 1000);
            std::cout << "Lambda thread: " << std::this_thread::get_id() << " Iteration: " << n << std::endl;
        });
    
    p(TestVector.begin(), TestVector.end(), 2, [](std::vector<int>::iterator n)
        {
            Delay(*n * 1000);
            std::cout << "Lambda iterator thread: " << std::this_thread::get_id() << " Element: " << *n << std::endl;
        });

    std::set<int> TestSet = { 10, 3, 1, 2, 7 };
    p(TestSet.begin(), TestSet.end(), 2, [](std::set<int>::iterator n)
        {
            Delay(*n * 1000);
            std::cout << "Lambda iterator set thread: " << std::this_thread::get_id() << " Element: " << *n << std::endl;
        });

    std::vector<int> TestVec = { 10, 3, 1, 
    2, 7, 9,
    5, 5, 67,
    1, 4, 66};

    p((std::uint64_t)0, (std::uint64_t)(TestVec.size() / 3), 2, [TestVec](std::uint64_t n)
        {
            Delay(TestVec[n * 3] * 1000);
            
            int summ = TestVec[n * 3] + TestVec[n * 3 + 1] + TestVec[n * 3 + 2];

            std::cout << "Lambda iterator set thread: " << std::this_thread::get_id() << " Summ: " << summ << std::endl;
        });
}
