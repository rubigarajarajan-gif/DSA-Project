
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

class Book
{
public:
    int id;
    string title;
    string author;
    int totalCopies;
    int availableCopies;
};

vector<Book> books;
unordered_map<int,int> bookIndex;
list<int> issuedBooks;

void buildHashTable()
{
    bookIndex.clear();

    for(int i=0;i<books.size();i++)
    {
        bookIndex[books[i].id]=i;
    }
}

// Load books from file
void loadBooks()
{
    ifstream fin("books.txt");

    if (!fin)
        return;

    Book b;

    while (fin >> b.id)
    {
        fin.ignore();

        getline(fin, b.title);
        getline(fin, b.author);

        fin >> b.totalCopies;
        fin >> b.availableCopies;

        fin.ignore();

        books.push_back(b);
    }

    fin.close();

    buildHashTable();
}
// Save books to file
void saveBooks()
{
    ofstream fout("books.txt");

    for(Book b : books)
    {
        fout << b.id << endl;
        fout << b.title << endl;
        fout << b.author << endl;
        fout << b.totalCopies << endl;
        fout << b.availableCopies << endl;
    }

    fout.close();
}

// Add Book
void addBook()
{
    Book b;

    cout << "\nEnter Book ID : ";
    cin >> b.id;
    cin.ignore();

    cout << "Enter Book Title : ";
    getline(cin, b.title);

    cout << "Enter Author Name : ";
    getline(cin, b.author);

    cout<<"Enter Number of Copies : ";
    cin>>b.totalCopies;

    b.availableCopies=b.totalCopies;

    books.push_back(b);
    bookIndex[b.id]=books.size()-1;

    saveBooks();

    cout << "\nBook Added Successfully.\n";
}

// Display Books
void displayBooks()
{
    if (books.empty())
    {
        cout << "\nNo Books Available.\n";
        return;
    }

    cout << "\n========== BOOK LIST ==========\n";

    for (Book b : books)
    {
        cout << "Book ID : " << b.id << endl;
        cout << "Title   : " << b.title << endl;
        cout << "Author  : " << b.author << endl;
        cout<<"Total Copies     : "<<b.totalCopies<<endl;
        cout<<"Available Copies : "<<b.availableCopies<<endl;

        cout << "-----------------------------\n";
    }
}

void searchBook()
{
    int id;

    cout << "\nEnter Book ID : ";
    cin >> id;

    if(bookIndex.find(id) == bookIndex.end())
    {
        cout << "\nBook Not Found.\n";
        return;
    }

    Book b = books[bookIndex[id]];

    cout << "\nBook Found\n";
    cout << "Book ID          : " << b.id << endl;
    cout << "Title            : " << b.title << endl;
    cout << "Author           : " << b.author << endl;
    cout << "Total Copies     : " << b.totalCopies << endl;
    cout << "Available Copies : " << b.availableCopies << endl;

    if(b.availableCopies > 0)
        cout << "Status           : Available" << endl;
    else
        cout << "Status           : Out of Stock" << endl;
}
void updateBook()
{
    int id;

    cout << "\nEnter Book ID to Update : ";
    cin >> id;
    cin.ignore();

    for(int i=0;i<books.size();i++)
    {
        if(books[i].id==id)
        {
            cout << "Enter New Title : ";
            getline(cin,books[i].title);

            cout << "Enter New Author : ";
            getline(cin,books[i].author);

            saveBooks();

            cout << "\nBook Updated Successfully.\n";
            return;
        }
    }

    cout << "\nBook Not Found.\n";
}

void deleteBook()
{
    int id;

    cout << "\nEnter Book ID to Delete : ";
    cin >> id;

    for(int i=0;i<books.size();i++)
    {
        if(books[i].id==id)
        {
            books.erase(books.begin()+i);

            buildHashTable();

            saveBooks();

            cout << "\nBook Deleted Successfully.\n";
            return;
        }
    }

    cout << "\nBook Not Found.\n";
}

void issueBook()
{
    int id;

    cout << "\nEnter Book ID to Issue : ";
    cin >> id;

    for(int i=0;i<books.size();i++)
    {
        if(books[i].id==id)
        {
     if(books[i].availableCopies==0)
        {
            cout<<"\nNo Copies Available.\n";
        }
        else
        {
            books[i].availableCopies--;

            issuedBooks.push_back(id);

            saveBooks();

            cout<<"\nBook Issued Successfully.\n";
        }
            return;
        }
    }

    cout << "\nBook Not Found.\n";
}

void returnBook()
{
    int id;

    cout << "\nEnter Book ID to Return : ";
    cin >> id;

    for(int i=0;i<books.size();i++)
    {
        if(books[i].id==id)
        {
            if(books[i].availableCopies==books[i].totalCopies)
                {
                    cout<<"\nAll Copies Already Returned.\n";
                }
                else
                {
                    books[i].availableCopies++;

                    issuedBooks.remove(id);

                    saveBooks();

                    cout<<"\nBook Returned Successfully.\n";
                }

            return;
        }
    }

    cout << "\nBook Not Found.\n";
}

void displayIssuedBooks()
{
    bool found = false;

    cout << "\n========== ISSUED BOOKS ==========\n";

    for(Book b : books)
    {
        int issuedCopies = b.totalCopies - b.availableCopies;

        if(issuedCopies > 0)
        {
            found = true;

            cout << "Book ID          : " << b.id << endl;
            cout << "Title            : " << b.title << endl;
            cout << "Author           : " << b.author << endl;
            cout << "Issued Copies    : " << issuedCopies << endl;
            cout << "Available Copies : " << b.availableCopies << endl;
            cout << "----------------------------------" << endl;
        }
    }

    if(!found)
    {
        cout << "No Issued Books.\n";
    }
}

void showIssuedHistory()
{
    cout<<"\nIssued Book IDs\n";

    if(issuedBooks.empty())
    {
        cout<<"No Books Issued\n";
        return;
    }

    for(int id:issuedBooks)
    {
        cout<<id<<endl;
    }
}

int main()
{
    loadBooks();

    int choice;

    do
    {
        cout<<"\n========== LIBRARY MANAGEMENT SYSTEM ==========\n";

        cout<<"1. Add Book"<<endl;
        cout<<"2. Display Books"<<endl;
        cout<<"3. Search Book"<<endl;
        cout<<"4. Update Book"<<endl;
        cout<<"5. Delete Book"<<endl;
        cout<<"6. Issue Book"<<endl;
        cout<<"7. Return Book"<<endl;
        cout<<"8. View Issued Books"<<endl;
        cout<< "9. Issued History"<<endl;
        cout<<"10. Exit"<<endl;

        cout<<"\nEnter Choice : ";
        cin>>choice;

       switch(choice)
        {
        case 1:
            addBook();
            break;

        case 2:
            displayBooks();
            break;

        case 3:
            searchBook();
            break;

        case 4:
            updateBook();
            break;

        case 5:
            deleteBook();
            break;

        case 6:
            issueBook();
            break;

        case 7:
            returnBook();
            break;

        case 8:
            displayIssuedBooks();
            break;

        case 9:
           showIssuedHistory();
            break;

        case 10:
           cout << "\nThank You!\n";
           break;

        default:
            cout<<"\nInvalid Choice.\n";
        }

    } while (choice != 10);

    return 0;
}
