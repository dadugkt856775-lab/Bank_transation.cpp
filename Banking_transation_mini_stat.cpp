
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Transaction {
public:
    string type;
    double amount;
    double balanceAfter;

    Transaction(string t, double a, double b) {
        type = t;
        amount = a;
        balanceAfter = b;
    }

    void display() const {
        cout << left << setw(15) << type
             << right << setw(12) << fixed
             << setprecision(2) << amount
             << setw(18) << balanceAfter << endl;
    }
};

class BankAccount {
private:
    long long accountNumber;
    string holderName;
    double balance;
    vector<Transaction> history;

public:
    BankAccount(long long number, string name,
                double initialBalance) {
        accountNumber = number;
        holderName = name;
        balance = initialBalance;

        history.emplace_back(
            "Opening", initialBalance, balance
        );
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Enter a valid deposit amount!\n";
            return;
        }

        balance += amount;
        history.emplace_back("Deposit", amount, balance);

        cout << "Deposit successful!\n";
        cout << "Current balance: Rs. "
             << fixed << setprecision(2)
             << balance << endl;
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Enter a valid withdrawal amount!\n";
        } else if (amount > balance) {
            cout << "Insufficient balance!\n";
        } else {
            balance -= amount;
            history.emplace_back(
                "Withdrawal", amount, balance
            );

            cout << "Withdrawal successful!\n";
            cout << "Current balance: Rs. "
                 << fixed << setprecision(2)
                 << balance << endl;
        }
    }

    void showBalance() const {
        cout << "\nAccount Holder: " << holderName << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Available Balance: Rs. "
             << fixed << setprecision(2)
             << balance << endl;
    }

    void miniStatement() const {
        cout << "\n========== MINI STATEMENT ==========\n";
        cout << "Account Holder: " << holderName << endl;
        cout << "Account Number: " << accountNumber << endl;

        cout << left << setw(15) << "Transaction"
             << right << setw(12) << "Amount"
             << setw(18) << "Balance" << endl;

        cout << string(45, '-') << endl;

        for (const Transaction& t : history) {
            t.display();
        }

        cout << string(45, '-') << endl;
        cout << "Final Balance: Rs. "
             << fixed << setprecision(2)
             << balance << endl;
    }
};

int main() {
    long long accountNumber;
    string name;
    double initialBalance;
    int choice;

    cout << "===== CREATE BANK ACCOUNT =====\n";

    cout << "Enter account number: ";
    cin >> accountNumber;

    cout << "Enter account holder name: ";
    cin >> ws;
    getline(cin, name);

    cout << "Enter opening balance: Rs. ";
    cin >> initialBalance;

    if (initialBalance < 0) {
        cout << "Opening balance cannot be negative!\n";
        return 1;
    }

    BankAccount account(
        accountNumber, name, initialBalance
    );

    do {
        cout << "\n===== BANKING MENU =====\n";
        cout << "1. Deposit Money\n";
        cout << "2. Withdraw Money\n";
        cout << "3. Check Balance\n";
        cout << "4. View Mini Statement\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            double amount;
            cout << "Enter deposit amount: Rs. ";
            cin >> amount;
            account.deposit(amount);
            break;
        }

        case 2: {
            double amount;
            cout << "Enter withdrawal amount: Rs. ";
            cin >> amount;
            account.withdraw(amount);
            break;
        }

        case 3:
            account.showBalance();
            break;

        case 4:
            account.miniStatement();
            break;

        case 5:
            cout << "Thank you for using the banking system!\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
