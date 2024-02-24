#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// defined the Check struct
struct Check
{
    int CheckNum;
    string CheckMemo;
    float CheckAmount;

    // Overloaded operator to compare CheckAmount
    bool operator>(float amount) const
    {
        return CheckAmount > amount;
    }

    // Overloaded operator to print Check details
    friend ostream &operator<<(ostream &os, const Check &check);
};
ostream &operator<<(ostream &os, const Check &check)
{
    os << "CheckNum: " << check.CheckNum << ", CheckMemo: " << check.CheckMemo << ", CheckAmount: $" << check.CheckAmount;
    return os;
}