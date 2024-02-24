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
// Define the CheckBook class
class CheckBook
{
private:
    float balance;
    Check *chkPtr;
    float lastDeposit;
    int numOfChecks;
    int checkBookSize;

public:
    // Default constructor
    CheckBook() : balance(0), lastDeposit(0), numOfChecks(0), checkBookSize(4)
    {
        chkPtr = new Check[checkBookSize];
    }

    // Second constructor
    CheckBook(float initialBalance) : balance(initialBalance), lastDeposit(0), numOfChecks(0), checkBookSize(2)
    {
        chkPtr = new Check[checkBookSize];
    }

    // Destructor
    ~CheckBook()
    {
        delete[] chkPtr;
    }

    // Copy constructor
    CheckBook(const CheckBook &other) : balance(other.balance), lastDeposit(other.lastDeposit),
                                        numOfChecks(other.numOfChecks), checkBookSize(other.checkBookSize)
    {
        chkPtr = new Check[checkBookSize];
        for (int i = 0; i < numOfChecks; ++i)
        {
            chkPtr[i] = other.chkPtr[i];
        }
    }

    // Overloaded assignment operator
    CheckBook &operator=(const CheckBook &other)
    {
        if (this != &other)
        {
            delete[] chkPtr;
            balance = other.balance;
            lastDeposit = other.lastDeposit;
            numOfChecks = other.numOfChecks;
            checkBookSize = other.checkBookSize;
            chkPtr = new Check[checkBookSize];
            for (int i = 0; i < numOfChecks; ++i)
            {
                chkPtr[i] = other.chkPtr[i];
            }
        }
        return *this;
    }
    // Getter and setter functions
    float getBalance() const
    {
        return balance;
    }

    void setBalance(float newBalance)
    {
        balance = newBalance;
    }

    // Other getter and setter functions...

    // Deposit function
    void deposit(float amount)
    {
        balance += amount;
        lastDeposit = amount;
    }

    // WriteCheck function
    bool writeCheck(float c_amount)
    {
        if (c_amount > balance)
        {
            return false;
        }

        // checking array expansion logic 
        if (numOfChecks >= checkBookSize)
        {
            // doubling the Check array
            doubleCheckArray();
        }

        // gather tge check details,and update balance
        Check newCheck;
        newCheck.CheckAmount = c_amount;
        newCheck.CheckNum = numOfChecks + 1;
        balance -= c_amount; 

        // select a memo from the list
        string memos[] = {"wedding", "baby shower", "pizza", "coffee shop", "Salon", "furniture", "car dealership"};
        newCheck.CheckMemo = memos[rand() % (sizeof(memos) / sizeof(memos[0]))];

        // Save the check to the array
        chkPtr[numOfChecks] = newCheck;
        numOfChecks++;

        cout << "Check written: " << newCheck << endl;

        return true;
    }