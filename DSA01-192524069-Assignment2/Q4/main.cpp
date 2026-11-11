#include <iostream>
#include <iomanip>

class SavingsAccount {
    long long accountNumber;
    long long balancePaise;
    static const int MAX_TX = 10;
    long long transactions[MAX_TX];
    int count;

public:
    SavingsAccount(long long accNum, long long initialBalance)
        : accountNumber(accNum), balancePaise(initialBalance), count(0) {}

    bool deposit(long long amountPaise) {
        if (amountPaise <= 0) return false;
        balancePaise += amountPaise;
        recordTransaction(amountPaise);
        return true;
    }

    bool withdraw(long long amountPaise);
    void miniStatement() const;

private:
    void recordTransaction(long long amountPaise);
};

bool SavingsAccount::withdraw(long long amountPaise) {
    if (amountPaise <= 0 || amountPaise > balancePaise) {
        return false;
    }
    balancePaise -= amountPaise;
    recordTransaction(-amountPaise);
    return true;
}

void SavingsAccount::recordTransaction(long long amountPaise) {
    if (count < MAX_TX) {
        transactions[count++] = amountPaise;
    } else {
        for (int i = 0; i < MAX_TX - 1; ++i) {
            transactions[i] = transactions[i + 1];
        }
        transactions[MAX_TX - 1] = amountPaise;
    }
}

void SavingsAccount::miniStatement() const {
    std::cout << "========================================\n";
    std::cout << "           ATM MINI-STATEMENT           \n";
    std::cout << "Account Number: " << accountNumber << "\n";
    std::cout << "Current Balance: Rs " << balancePaise / 100 << "."
              << std::setfill('0') << std::setw(2) << (balancePaise % 100) << "\n";
    std::cout << "Last " << count << " Transactions:\n";
    std::cout << "----------------------------------------\n";
    for (int i = 0; i < count; ++i) {
        long long tx = transactions[i];
        if (tx >= 0) {
            std::cout << std::setw(2) << (i + 1) << ". CREDIT : +Rs " << tx / 100 << "." 
                      << std::setfill('0') << std::setw(2) << (tx % 100) << "\n";
        } else {
            long long absTx = -tx;
            std::cout << std::setw(2) << (i + 1) << ". DEBIT  : -Rs " << absTx / 100 << "."
                      << std::setfill('0') << std::setw(2) << (absTx % 100) << "\n";
        }
    }
    std::cout << "========================================\n\n";
}

int main() {
    SavingsAccount acc(90124589, 500000);

    acc.deposit(100000);
    acc.withdraw(50000);
    acc.deposit(20000);
    acc.withdraw(15000);
    acc.deposit(30000);
    acc.deposit(40000);
    acc.withdraw(25000);
    acc.deposit(12000);
    acc.withdraw(8000);
    acc.deposit(5000);

    std::cout << "Statement after 10 transactions:\n";
    acc.miniStatement();

    std::cout << "Executing 11th and 12th transactions (discarding oldest):\n";
    acc.deposit(99000);
    acc.withdraw(11000);

    acc.miniStatement();

    return 0;
}
