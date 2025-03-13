#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

using namespace std;

// Structure for Bank Account
struct BankAccount {
    string accountNumber;
    string name;
    double balance;
    string pin;
};

// Function to clear the screen
void clearScreen() {
    system(CLEAR);
}

// Function to create a new account
void createAccount() {
    clearScreen();
    BankAccount acc;
    ofstream outFile("accounts.dat", ios::app);

    cout << "\n========= CREATE BANK ACCOUNT =========\n";
    cout << "Enter Account Number (12 digits): ";
    cin >> acc.accountNumber;
    cout << "Enter Account Holder Name: ";
    cin.ignore();
    getline(cin, acc.name);
    cout << "Set a 4-digit PIN: ";
    cin >> acc.pin;
    cout << "Enter Initial Deposit Amount: ";
    cin >> acc.balance;

    outFile << acc.accountNumber << " " << acc.pin << " " << acc.name << " " << acc.balance << "\n";
    outFile.close();

    cout << "\n Account Created Successfully!\n";
}

// Function to modify account details
void modifyAccount() {
    clearScreen();
    string accNum, enteredPin;
    BankAccount acc;
    ifstream inFile("accounts.dat");
    ofstream outFile("temp.dat");
    bool found = false;

    cout << "\n========= MODIFY AN ACCOUNT =========\n";
    cout << "Enter Account Number: ";
    cin >> accNum;
    cout << "Enter PIN: ";
    cin >> enteredPin;

    while (inFile >> acc.accountNumber >> acc.pin >> ws) {
        getline(inFile, acc.name, ' ');
        inFile >> acc.balance;

        if (acc.accountNumber == accNum && acc.pin == enteredPin) {
            cout << "\nEnter New Account Holder Name: ";
            cin.ignore();
            getline(cin, acc.name);
            cout << "Enter New PIN: ";
            cin >> acc.pin;
            found = true;
            cout << "\n Account Modified Successfully!\n";
        }
        outFile << acc.accountNumber << " " << acc.pin << " " << acc.name << " " << acc.balance << "\n";
    }

    inFile.close();
    outFile.close();
    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");

    if (!found) cout << " Invalid Account Number or PIN!\n";
}

// Function to check balance
void balanceEnquiry() {
    clearScreen();
    string accNum, enteredPin;
    BankAccount acc;
    ifstream inFile("accounts.dat");

    cout << "\n========= BALANCE ENQUIRY =========\n";
    cout << "Enter Account Number: ";
    cin >> accNum;
    cout << "Enter PIN: ";
    cin >> enteredPin;

    bool found = false;
    while (inFile >> acc.accountNumber >> acc.pin >> ws) {
        getline(inFile, acc.name, ' ');
        inFile >> acc.balance;

        if (acc.accountNumber == accNum && acc.pin == enteredPin) {
            cout << "\n Account Holder: " << acc.name;
            cout << "\n Available Balance: Rs. " << fixed << setprecision(2) << acc.balance << "\n";
            found = true;
            break;
        }
    }
    inFile.close();

    if (!found) cout << " Invalid Account Number or PIN!\n";
}

// Function to deposit money
void depositAmount() {
    clearScreen();
    string accNum;
    double deposit;
    BankAccount acc;
    ifstream inFile("accounts.dat");
    ofstream outFile("temp.dat");
    bool found = false;

    cout << "\n========= DEPOSIT IN ACCOUNT =========\n";
    cout << "Enter Account Number: ";
    cin >> accNum;
    cout << "Enter Amount to Deposit: ";
    cin >> deposit;

    while (inFile >> acc.accountNumber >> acc.pin >> ws) {
        getline(inFile, acc.name, ' ');
        inFile >> acc.balance;

        if (acc.accountNumber == accNum) {
            acc.balance += deposit;
            found = true;
            cout << "\n Deposit Successful! New Balance: Rs. " << fixed << setprecision(2) << acc.balance << "\n";
        }
        outFile << acc.accountNumber << " " << acc.pin << " " << acc.name << " " << acc.balance << "\n";
    }

    inFile.close();
    outFile.close();
    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");

    if (!found) cout << " Account Not Found!\n";
}

// Function to withdraw money
void withdrawAmount() {
    clearScreen();
    string accNum, enteredPin;
    double withdraw;
    BankAccount acc;
    ifstream inFile("accounts.dat");
    ofstream outFile("temp.dat");
    bool found = false;

    cout << "\n========= WITHDRAW FROM ACCOUNT =========\n";
    cout << "Enter Account Number: ";
    cin >> accNum;
    cout << "Enter PIN: ";
    cin >> enteredPin;
    cout << "Enter Amount to Withdraw: ";
    cin >> withdraw;

    while (inFile >> acc.accountNumber >> acc.pin >> ws) {
        getline(inFile, acc.name, ' ');
        inFile >> acc.balance;

        if (acc.accountNumber == accNum && acc.pin == enteredPin) {
            if (acc.balance >= withdraw) {
                acc.balance -= withdraw;
                found = true;
                cout << "\n Withdrawal Successful! New Balance: Rs. " << fixed << setprecision(2) << acc.balance << "\n";
            } else {
                cout << " Insufficient Balance!\n";
            }
        }
        outFile << acc.accountNumber << " " << acc.pin << " " << acc.name << " " << acc.balance << "\n";
    }

    inFile.close();
    outFile.close();
    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");

    if (!found) cout << " Invalid Account Number or PIN!\n";
}

// Function to display all accounts
void allAccountList() {
    clearScreen();
    BankAccount acc;
    ifstream inFile("accounts.dat");

    cout << "\n========= ALL ACCOUNT HOLDER LIST =========\n";
    while (inFile >> acc.accountNumber >> acc.pin >> ws) {
        getline(inFile, acc.name, ' ');
        inFile >> acc.balance;

        cout << "\n Account Number: " << acc.accountNumber;
        cout << "\n Name: " << acc.name;
        cout << "\n Balance: Rs. " << fixed << setprecision(2) << acc.balance << "\n----------------------------\n";
    }
    inFile.close();
}

// Function to delete an account
void closeAccount() {
    clearScreen();
    string accNum, enteredPin;
    BankAccount acc;
    ifstream inFile("accounts.dat");
    ofstream outFile("temp.dat");
    bool found = false;

    cout << "\n========= CLOSE AN ACCOUNT =========\n";
    cout << "Enter Account Number: ";
    cin >> accNum;
    cout << "Enter PIN: ";
    cin >> enteredPin;

    while (inFile >> acc.accountNumber >> acc.pin >> ws) {
        getline(inFile, acc.name, ' ');
        inFile >> acc.balance;

        if (acc.accountNumber == accNum && acc.pin == enteredPin) {
            found = true;
        } else {
            outFile << acc.accountNumber << " " << acc.pin << " " << acc.name << " " << acc.balance << "\n";
        }
    }

    inFile.close();
    outFile.close();
    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");

    if (found) cout << "\n Account Deleted Successfully!\n";
    else cout << " Invalid Account Number or PIN!\n";
}

// Function to display the main menu
void Display_Menu() {
    cout << "\n================ SecurePay Bank ================\n";
    cout << "01. CREATE NEW ACCOUNT\n02. MODIFY AN ACCOUNT\n03. BALANCE ENQUIRY\n";
    cout << "04. DEPOSIT\n05. WITHDRAW\n06. ACCOUNT LIST\n07. CLOSE ACCOUNT\n08. EXIT\n";
    cout << "\nSELECT OPTION: ";
}

int main() {
    char choice;
    do {
        clearScreen();
        Display_Menu();
        cin >> choice;

        switch (choice) {
            case '1': createAccount(); break;
            case '2': modifyAccount(); break;
            case '3': balanceEnquiry(); break;
            case '4': depositAmount(); break;
            case '5': withdrawAmount(); break;
            case '6': allAccountList(); break;
            case '7': closeAccount(); break;
            case '8': cout << "\n Exiting. Thank you!\n"; break;
            default: cout << "\n Invalid Option! Try Again.\n";
        }
        cin.ignore();
        cin.get();
    } while (choice != '8');

    return 0;
}
