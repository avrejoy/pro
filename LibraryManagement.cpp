/*-------------------------------------------
Library Management System
System: Visual Studio Code on Windows
Author: Joy Avre
------------------------------------------- */


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>

using namespace std;

// Function prototypes for all the glorious function decomposition
void printMenu();
void addItemToLibrary(vector <string> &bookTitle, vector <string> &isbn, vector <int> &checkoutState);
void clearLibraryEntries(vector <string> &bookTitle, vector <string> &isbn, vector <int> &checkoutState);
void displayLibraryEntries(vector <string> &bookTitle, vector <string> &isbn, vector <int> &checkoutState);
void listInvalidLibraryEntries(vector <string> &bookTitle, vector <string> &isbn, vector <int> &checkoutState);
void loadLibraryFromFile(vector<string> &bookTitle, vector<string> &isbn, vector<int> &checkoutState);
void outputLibraryToFile(vector<string> &bookTitle, vector<string> &isbn, vector<int> &checkoutState);
void printCheckoutStats(vector<int>& checkoutState);
void removeLibraryEntry(vector<string> &bookTitle, vector<string> &isbn, vector<int> &checkoutState);
void searchLibraryEntry(vector<string> &bookTitle, vector<string> &isbn, vector<int> &checkoutState);


int main()
{
    string command;

    vector <string> bookTitle;
    vector <string> isbn;
    vector <int> checkoutState;


    cout << "Welcome to the Library Management System" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

    do 
    {
        // Output the menu and acquire a user selection
        printMenu();
        cout << endl << "Enter a command (case does not matter): ";


        getline(cin, command);
        cout << endl;

        if (command == "a" || command == "A") {

            addItemToLibrary(bookTitle, isbn, checkoutState);

        }
        else if (command == "c" || command == "C") {

            clearLibraryEntries(bookTitle, isbn, checkoutState);

        }
        else if (command == "d" || command == "D") {

            displayLibraryEntries(bookTitle, isbn, checkoutState);
        }
        else if (command == "i" || command == "I") {

            listInvalidLibraryEntries(bookTitle, isbn, checkoutState);

        }
        else if (command == "l" || command == "L") {

            loadLibraryFromFile(bookTitle, isbn, checkoutState);

        }
        else if (command == "o" || command == "O") {

            outputLibraryToFile(bookTitle, isbn, checkoutState);

        }
        else if (command == "p" || command == "P") {

            printCheckoutStats(checkoutState);

        }
        else if (command == "r" || command == "R") {

            removeLibraryEntry(bookTitle, isbn, checkoutState);

        }
        else if (command == "s" || command == "S") {

            searchLibraryEntry(bookTitle, isbn, checkoutState);

        }

        cout << endl;

    } while (!(command == "x" || command == "X"));

    return 0;
}


void printMenu()
{
    cout << "Library Management Menu" << endl;
    cout << "-----------------------" << endl;
    cout << "A - Add Item To Library" << endl;
    cout << "C - Clear The Library Of All Entries" << endl;
    cout << "D - Display Library Entries" << endl;    
    cout << "I - List Invalid Library Entries" << endl;
    cout << "L - Load Library From File" << endl;    
    cout << "O - Output Library To File" << endl;
    cout << "P - Print Out Checkout Stats" << endl;
    cout << "R - Remove A Library Entry" << endl;      
    cout << "S - Search For A Library Entry" << endl;    
    cout << "X - Exit Program" << endl;
}

// function to add new item to library
void addItemToLibrary(vector <string> &bookTitle, vector <string> &isbn, vector <int> &checkoutState) {

    string title;
    string isbnNum;

    cout << "What is the book title? " << endl;
    getline(cin, title);

    // check if book title contains commas
    for (size_t i = 0; i < title.length(); i++) {
        if (title.at(i) == ',') {
            cout << "The book title cannot contain commas." << endl;
            return;
        }
    }

    cout << "What is the 13-digit ISBN (with hyphens)? " << endl;
    getline(cin, isbnNum);

    // add the information to its respective vectors
    bookTitle.push_back(title);
    isbn.push_back(isbnNum);
    checkoutState.push_back(0);

    cout << "The Following Entry Was Added" << endl;
    cout << "-----------------------------" << endl;
    cout << title << " --- " <<  isbnNum << " --- In Library" << endl;

}

// function to clear all library entries
void clearLibraryEntries(vector <string> &bookTitle, vector <string> &isbn, vector <int> &checkoutState) {

    bookTitle.clear();
    isbn.clear();
    checkoutState.clear();
    cout << "Your library is now empty." << endl;

}

// function to display library entries
void displayLibraryEntries(vector <string> &bookTitle, vector <string> &isbn, vector <int> &checkoutState) {

    cout << "Your Current Library" << endl;
    cout << "--------------------" << endl;

    // error handling
    if (bookTitle.empty()) {
        cout << "The library has no books" << endl;
        return;
    }

    // loop through vectors and display information
    for (size_t i = 0; i < bookTitle.size(); ++i) {
        cout << bookTitle.at(i) << " --- " << isbn.at(i) << " --- ";

        // check the check out state and display accordingly
        if (checkoutState.at(i) == 0) {
            cout << "In Library";
        }
        else if (checkoutState.at(i) == 1) {
        cout << "Checked Out";
        }
        else if (checkoutState.at(i) == 2) {
        cout << "On Loan";
        }
        else if (checkoutState.at(i) == 3) {
        cout << "Unknown State";
        }
        else {
        cout << "Invalid State";
        }
        cout << endl;

    }

}

// function to list invalid library entries
void listInvalidLibraryEntries(vector<string>& bookTitles, vector<string>& ISBNs, vector<int>& checkoutStatus) {

    cout << "The Following Library Entries Have Invalid Data" << endl;
    cout << "-----------------------------------------------" << endl;

    int total = 0;
    int numInvalid = 0;
    int weightMultiplier = 0; //alternate weight of isbn digits
    int checkDigit = 0;

    // check if library has no books
    if (bookTitles.empty()) {
        cout << "The library has no books." << endl;
    }

    // loop through isbn vector to check for invalid entries (conditions given)
    for (int i = 0; i < ISBNs.size(); i++) {
        for (int j = 0; j < ISBNs[i].length(); j++) {
            char currentChar = ISBNs[i][j];

            if (isdigit(currentChar)) { // check if the character is a digit
                if (weightMultiplier % 2 == 0 && currentChar != '-' && currentChar != ' ' && j != ISBNs[i].size() - 1) { //calculate total based on isbn and weight
                    string numStr(1, currentChar);
                    total += stoi(numStr) * 1; // even positions have weight of 1
                    weightMultiplier = 1;
                } else if (weightMultiplier % 2 == 1 && currentChar != '-' && currentChar != ' ' && j != ISBNs[i].size() - 1) {
                    string numStr(1, currentChar);
                    total += stoi(numStr) * 3; // odd positions have weight of 3
                    weightMultiplier = 0;
                }

                // store it if its the last digit
                if (j == ISBNs[i].size() - 1) {
                    string numStr(1, currentChar);
                    checkDigit = stoi(numStr);
                    weightMultiplier = 0; //reset for next digit
                }
            }
        }

        string status;

        if (checkoutStatus[i] == 0) { //deterine check out status based on value
            status = "In Library";
        } else if (checkoutStatus[i] == 1) {
            status = "Checked Out";
        } else if (checkoutStatus[i] == 2) {
            status = "On Loan";
        } else if (checkoutStatus[i] == 3) {
            status = "Unknown State";
        } else {
            status = "Invalid State";
        }

        total = total % 10;

        if (total != 0) {
            total = 10 - total;
        }

        // check for invalid entries and display them
        if (total != checkDigit) {
            cout << bookTitles[i] << " --- " << ISBNs[i] << " --- " << status << endl;
            numInvalid++;
        } else if (status == "Invalid State") {
            cout << bookTitles[i] << " --- " << ISBNs[i] << " --- " << status << endl;
            numInvalid++;
        }

        checkDigit = 0;
        total = 0;
    }

    // check if there are no invalid entries
    if (numInvalid == 0 && !bookTitles.empty()) {
        cout << "The library has no invalid entries." << endl;
    }

}

// function to load library entries from file
void loadLibraryFromFile(vector<string>& bookTitle, vector<string>& isbn, vector<int>& checkoutState) {

    string fileName;
    string bookName, isbnNum, status;

    int count = 0;

    cout << "What database to read from? " << endl;
    getline(cin, fileName);

    ifstream inputFile;
    inputFile.open(fileName);

    // check if file is open
    if (!inputFile.is_open()) {
        cout << "Could not find the database file." << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) { // read lines from file
        count++;

        // if a line does not contain a comma, treat it as a book title and assign it default isbn and checkout state
        if (line.find(',') == string::npos) {
            bookTitle.push_back(line);
            isbn.push_back("000-0-00-000000-0");
            checkoutState.push_back(0);
            continue;
        } else { // extract book name
            bookName = line.substr(0, line.find(','));
            bookTitle.push_back(bookName);
            line = line.substr(line.find(',') + 2);

            // if no more comma is found, treat as isbn 
            if (line.find(',') == string::npos) {
                isbnNum = line;
                isbn.push_back(isbnNum);
                checkoutState.push_back(0);
            } else { // extract isbn and checkout state
                isbnNum = line.substr(0, line.find(','));
                isbn.push_back(isbnNum);
                checkoutState.push_back(stoi(line.substr(line.find(',') + 2)));
            }
        }
    }

    inputFile.close();

    cout << "Read in " << count << " lines from the file." << endl;

}



// functon to save library entries to a file
void outputLibraryToFile(vector<string> &bookTitle, vector<string> &isbn, vector<int> &checkoutState) {

    string filename;
    getline(cin, filename);
    cout << endl;

    // open file for writing
    ofstream outFile(filename);

    if (!outFile.is_open()){ // check if successfully opened
        cout << "Could not open database file for writing." << endl;
        return;
    }

    // oterate through vectors and write data to output file
    for (size_t i = 0; i < bookTitle.size(); ++i) {
        outFile << bookTitle.at(i) << ", " << isbn.at(i) << ", " << checkoutState.at(i) << endl;
    }

    outFile.close();

    // display how many lines of data written to
    if(bookTitle.size() == 1) {
        cout << "1 line of data written to " << filename << endl;
    } else {
        cout << bookTitle.size() << " lines of data written to " << filename << endl;
    }

}

// function to display the checkout states
void printCheckoutStats(vector<int>& checkoutState) {

    cout << "Your Current Library's Stats" << endl;
    cout << "----------------------------" << endl;

    // initialize counters for different states
    int inLibrary = 0;
    int checkedOut = 0;
    int onLoan = 0;
    int unknown = 0;
    int other = 0;

    // iterate through check out states and increment count
    for (int status : checkoutState) {

        switch(status) {
            case 0:
                inLibrary++;
                break;
            case 1:
                checkedOut++;
                break;;
            case 2:
                onLoan++;
                break;
            case 3:
                unknown++;
                break;
            default:
                other++;
                break;

        }

    }

    // display statistics
    cout << "Total Books: " << checkoutState.size() << endl;
    cout << "   In Library: " <<inLibrary << endl;
    cout << "   Checked Out: " << checkedOut << endl;
    cout << "   On Loan: " << onLoan << endl;
    cout << "   Unknown: " << unknown << endl;
    cout << "   Other: " << other << endl;

}


// function to remove library entry by book name or isbn
void removeLibraryEntry(vector<string> &bookTitle, vector<string> &ISBN, vector<int> &checkOut) {

    string choice;
    cout << "Would you like remove by (1) name or (2) ISBN." << endl;
    cout << "Enter the numeric choice: ";
    getline(cin, choice);
    cout << endl;

    if (choice == "1") { 
        string bookName;
        cout << "Enter the book name: ";
        getline(cin, bookName);
        cout << endl;
        cout << "The Following Entry Was Removed From The Library" << endl;
        cout << "------------------------------------------------" << endl;

        bool removed = false;

        // iterate in reverse order
        for (int i = bookTitle.size() - 1; i >= 0; --i) {
            if (bookName == bookTitle.at(i)) { 
                string name1 = bookTitle.at(i);
                string name2 = ISBN.at(i);
                string name3 = ""; 
                int num = checkOut.at(i); 

                // determine status based on checkout state
                if (num == 0) {
                    name3 = "In Library";
                } else if (num == 1) {
                    name3 = "Checked Out";
                } else if (num == 2) {
                    name3 = "On Loan";
                } else if (num == 3) {
                    name3 = "Unknown State";
                } else {
                    name3 = "Invalid State";
                }

                // erase entry from all three vectors
                bookTitle.erase(bookTitle.begin() + i);
                ISBN.erase(ISBN.begin() + i);
                checkOut.erase(checkOut.begin() + i);

                // print removed entry
                cout << name1 << " --- " << name2 << " --- " << name3 << endl;
                removed = true;
                break;
            }
        }

        if (!removed) {
            cout << "No matching entry found in the library." << endl;
        }
    }
    else if (choice == "2") { 
        string bookNum;
        cout << "Enter the book 13-digit ISBN (with dashes): ";
        getline(cin, bookNum);
        cout << endl;
        cout << "The Following Entry Was Removed From The Library" << endl;
        cout << "------------------------------------------------" << endl;

        bool removed = false;

        for (int i = ISBN.size() - 1; i >= 0; --i) { 
            if (bookNum == ISBN.at(i)) { 
                string name1 = bookTitle.at(i);
                string name2 = ISBN.at(i);
                string name3 = ""; 
                int num = checkOut.at(i); 

                if (num == 0) {
                    name3 = "In Library";
                } else if (num == 1) {
                    name3 = "Checked Out";
                } else if (num == 2) {
                    name3 = "On Loan";
                } else if (num == 3) {
                    name3 = "Unknown State";
                } else {
                    name3 = "Invalid State";
                }

                bookTitle.erase(bookTitle.begin() + i);
                ISBN.erase(ISBN.begin() + i);
                checkOut.erase(checkOut.begin() + i);
                cout << name1 << " --- " << name2 << " --- " << name3 << endl;
                removed = true;
                break;
            }
        }

        if (!removed) {
            cout << "No matching entry found in the library." << endl;
        }
    }
    else { 
        cout << "Invalid remove by choice option." << endl;
    }

}


// function to search for library entry
void searchLibraryEntry(vector<string> &bookTitle, vector<string> &isbn, vector<int> &checkoutState) {

    string searchChoice;

    // prompt user to search by name or isbn
    cout << "Would you like to search by (1) name or (2) ISBN. " << endl;
    cout << "Enter the numeric choice: ";

    getline(cin, searchChoice);
    cout << endl;

    if (searchChoice == "1") {
        string bookTitleInput;
        cout << "Enter the book name: ";
        getline(cin, bookTitleInput);
        cout << endl;

        cout << "The Following Are Your Search Results" << endl;
        cout << "-------------------------------------" << endl;

        bool found = false;

        // iterate through library entries to find match by book name
        // iterate from behind to search for most recent entry
        for (int i = bookTitle.size() - 1; i >= 0; i--) {
            if (bookTitleInput == bookTitle[i]) { 
                string status;
                if (checkoutState[i] == 0) { // determine checkout state and assign string
                    status = "In Library";
                } else if (checkoutState[i] == 1) {
                    status = "Checked Out";
                } else if (checkoutState[i] == 2) {
                    status = "On Loan";
                } else if (checkoutState[i] == 3) {
                    status = "Unknown State";
                } else {
                    status = "Other";
                }
                cout << bookTitle[i] << " --- " << isbn[i] << " --- " << status << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "No matching entry found in the library." << endl;
        }
    } else if (searchChoice == "2") { 
        string isbnInput;
        cout << "Enter the book 13-digit ISBN (with dashes): ";
        getline(cin, isbnInput);
        cout << endl;

        cout << "The Following Are Your Search Results" << endl;
        cout << "-------------------------------------" << endl;

        bool found = false;

        // iterate through library entries to find match by isbn
        for (int i = isbn.size() - 1; i >= 0; i--) {
            if (isbnInput == isbn[i]) { 
                string status;
                if (checkoutState[i] == 0) {
                    status = "In Library";
                } else if (checkoutState[i] == 1) {
                    status = "Checked Out";
                } else if (checkoutState[i] == 2) {
                    status = "On Loan";
                } else if (checkoutState[i] == 3) {
                    status = "Unknown State";
                } else {
                    status = "Other";
                }
                // print search result
                cout << bookTitle[i] << " --- " << isbn[i] << " --- " << status << endl;
                found = true;
                break;
            }
        }

        // inform user if no matching entry is found
        if (!found) {
            cout << "No matching entry found in the library." << endl;
        }
    } else { 
        cout << "Invalid search by choice option." << endl;
    }
}


