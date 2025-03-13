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

// Function to clear the screen
void clearScreen() {
    system(CLEAR);
}

// Function to display the file manager menu
void Display_FileManager_Menu() {
    cout << "\n========= File Manager =========\n";
    cout << "01. VIEW ACCOUNTS (without PINs)\n";
    cout << "02. VIEW PINs (mapped to account numbers)\n";
    cout << "03. EXIT\n";
    cout << "\nSELECT OPTION: ";
}

// Function to view account details (excluding PINs)
void viewAccounts() {
    clearScreen();
    ifstream inFile("accounts.dat");
    if (!inFile) {
        cout << "\n ERROR: Unable to open accounts.dat file!\n";
        return;
    }

    cout << "\n========= ACCOUNT DETAILS =========\n";
    string accountNumber, pin, name;
    double balance;
    bool found = false;

    while (inFile >> accountNumber >> pin >> ws) {
        getline(inFile, name, ' ');
        inFile >> balance;

        cout << "\n Account Number: " << accountNumber;
        cout << "\n Holder: " << name;
        cout << "\n Balance: Rs. " << fixed << setprecision(2) << balance;
        cout << "\n-----------------------------------\n";
        found = true;
    }
    
    inFile.close();
    if (!found) cout << "\n No accounts found in the database!\n";
}

// Function to view PINs mapped to account numbers
void viewPins() {
    clearScreen();
    ifstream inFile("accounts.dat");
    if (!inFile) {
        cout << "\n ERROR: Unable to open accounts.dat file!\n";
        return;
    }

    cout << "\n========= PIN DETAILS =========\n";
    string accountNumber, pin, name;
    double balance;
    bool found = false;

    while (inFile >> accountNumber >> pin >> ws) {
        getline(inFile, name, ' ');
        inFile >> balance;

        cout << " Account: " << accountNumber << " | PIN: " << pin << "\n";
        found = true;
    }

    inFile.close();
    if (!found) cout << "\n No PINs found in the database!\n";
}

int main() {
    char choice;
    do {
        clearScreen();
        Display_FileManager_Menu();
        cin >> choice;

        switch (choice) {
            case '1': viewAccounts(); break;
            case '2': viewPins(); break;
            case '3': cout << "\n Exiting File Manager. Thank you!\n"; break;
            default: cout << "\n Invalid Option! Try Again.\n";
        }
        
        cin.ignore();
        cin.get(); // Pause before clearing the screen again
    } while (choice != '3');

    return 0;
}
