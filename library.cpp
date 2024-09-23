#include <iostream>
#include <string>
#include <ctime>

using namespace std;

const int maxbooks = 100;
const int maxborrowers = 50;

struct Book {
    string title;
    string author;
    string ISBN;
    bool isAvailable;
    time_t dueDate;
};

struct Borrower {
    string name;
    string borrowerID;
    string borrowedISBN;
};

Book books[maxbooks];
Borrower borrowers[maxborrowers];
int bookCount = 0;
int borrowerCount = 0;

void addBook() {
    if (bookCount >= maxbooks) {
        cout << "Library is full. Cannot add more books!" << endl;
        return;
    }
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, books[bookCount].title);
    cout << "Enter book author: ";
    getline(cin, books[bookCount].author);
    cout << "Enter book ISBN: ";
    getline(cin, books[bookCount].ISBN);
    books[bookCount].isAvailable = true;
    bookCount++;
    cout << "Book added successfully!" << endl;
}

void searchBook() {
    string query;
    cout << "Enter book title, author, or ISBN to search: ";
    cin.ignore();
    getline(cin, query);
    
    bool found = false;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].title == query || books[i].author == query || books[i].ISBN == query) {
            cout << "Book found: " << books[i].title << " by " << books[i].author << " (ISBN: " << books[i].ISBN << ")";
            cout << (books[i].isAvailable ? " - Available" : " - Checked out") << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No matching book found!" << endl;
    }
}

// Function to check out a book
void checkoutBook() {
    if (borrowerCount >= maxborrowers) {
        cout << "Too many borrowers. Cannot check out more books!" << endl;
        return;
    }
    string isbn;
    cout << "Enter ISBN of the book to check out: ";
    cin >> isbn;
    
    // Find the book
    int bookIndex = -1;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].ISBN == isbn) {
            bookIndex = i;
            break;
        }
    }
    
    if (bookIndex == -1 || !books[bookIndex].isAvailable) {
        cout << "Book not available for checkout!" << endl;
        return;
    }

    cout << "Enter borrower name: ";
    cin.ignore();
    getline(cin, borrowers[borrowerCount].name);
    cout << "Enter borrower ID: ";
    getline(cin, borrowers[borrowerCount].borrowerID);
    
    borrowers[borrowerCount].borrowedISBN = isbn;
    books[bookIndex].isAvailable = false;

    time_t now = time(0);
    books[bookIndex].dueDate = now + (14 * 24 * 60 * 60);  

    borrowerCount++;
    cout << "Book checked out successfully!" << endl;
}


void returnBook() {
    string borrowerID;
    cout << "Enter borrower ID: ";
    cin.ignore();
    getline(cin, borrowerID);
    
    int borrowerIndex = -1;
    for (int i = 0; i < borrowerCount; i++) {
        if (borrowers[i].borrowerID == borrowerID) {
            borrowerIndex = i;
            break;
        }
    }

    if (borrowerIndex == -1) {
        cout << "Borrower not found!" << endl;
        return;
    }

    string isbn = borrowers[borrowerIndex].borrowedISBN;
    int bookIndex = -1;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].ISBN == isbn) {
            bookIndex = i;
            break;
        }
    }
    
    if (bookIndex == -1) {
        cout << "Book record not found!" << endl;
        return;
    }

    time_t now = time(0);
    double fine = 0.0;
    if (now > books[bookIndex].dueDate) {
        int overdueDays = (now - books[bookIndex].dueDate) / (24 * 60 * 60); 
        fine = overdueDays * 0.5;  
    }

    books[bookIndex].isAvailable = true;

    cout << "Book returned successfully!" << endl;
    if (fine > 0) {
        cout << "Overdue fine: $" << fine << endl;
    }
}

void libraryMenu() {
    int choice;
    do {
        cout << "\nLibrary Management System" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Search Book" << endl;
        cout << "3. Checkout Book" << endl;
        cout << "4. Return Book" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                searchBook();
                break;
            case 3:
                checkoutBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                cout << "Exiting the system!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }

    } while (choice != 5);
}

int main() {
    libraryMenu();
    return 0;
}
