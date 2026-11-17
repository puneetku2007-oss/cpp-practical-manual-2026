// Library Management System - Practical 12 (individual mini project)
// Concepts: encapsulation, constructors, inheritance + polymorphism (Item -> Book),
//           STL map, custom exceptions, CSV file I/O, RAII (unique_ptr, fstream).
//
// Usage:  ./library [path-to-csv]        (default: data/books.csv)
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;

// ======================= Exceptions =======================
// Every library-specific problem derives from LibraryError, so main() can catch them together.
class LibraryError : public runtime_error {
public:
    explicit LibraryError(const string& message) : runtime_error(message) {}
};
class BookNotFound : public LibraryError {
public:
    explicit BookNotFound(int id) : LibraryError("Book ID " + to_string(id) + " not found") {}
};
class DuplicateBook : public LibraryError {
public:
    explicit DuplicateBook(int id) : LibraryError("Book ID " + to_string(id) + " already exists") {}
};
class BookUnavailable : public LibraryError {
public:
    explicit BookUnavailable(const string& title)
        : LibraryError("'" + title + "' is already issued") {}
};
class FileError : public LibraryError {
public:
    explicit FileError(const string& message) : LibraryError(message) {}
};

// ======================= Item (abstract) and Book =======================
// Item is an abstract base class: it only declares what every library item must be able to do.
class Item {
public:
    virtual string describe() const = 0;   // text shown to the user
    virtual string toCsv() const = 0;      // one line for the CSV file
    virtual ~Item() = default;             // virtual destructor: safe deletion via Item*
};

class Book : public Item {
private:                                   // encapsulation: data can only change via methods
    int id;
    string title;
    string author;
    bool available;
public:
    Book(int bookId, const string& bookTitle, const string& bookAuthor, bool isAvailable = true)
        : id(bookId), title(bookTitle), author(bookAuthor), available(isAvailable) {}

    int getId() const { return id; }
    const string& getTitle() const { return title; }
    const string& getAuthor() const { return author; }
    bool isAvailable() const { return available; }
    void issue() { available = false; }
    void giveBack() { available = true; }

    string describe() const override {
        ostringstream out;
        out << "[" << id << "] " << title << " by " << author << " - "
            << (available ? "Available" : "Issued");
        return out.str();
    }
    string toCsv() const override {
        return to_string(id) + "," + title + "," + author + "," + (available ? "1" : "0");
    }
};

// ======================= Library =======================
class Library {
private:
    map<int, unique_ptr<Book>> books;      // STL map: sorted by ID, owns the Book objects
    string filePath;

    static string lower(string s) {
        transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return tolower(c); });
        return s;
    }
public:
    explicit Library(const string& csvPath) : filePath(csvPath) {}

    void addBook(int id, const string& title, const string& author) {
        if (books.count(id)) throw DuplicateBook(id);
        books[id] = make_unique<Book>(id, title, author);
    }
    Book& findById(int id) {
        auto it = books.find(id);
        if (it == books.end()) throw BookNotFound(id);
        return *it->second;
    }
    void issueBook(int id) {
        Book& book = findById(id);
        if (!book.isAvailable()) throw BookUnavailable(book.getTitle());
        book.issue();
    }
    void returnBook(int id) {
        Book& book = findById(id);
        if (book.isAvailable()) throw LibraryError("'" + book.getTitle() + "' was not issued");
        book.giveBack();
    }
    void displayAll() const {
        if (books.empty()) { cout << "No books in the library." << endl; return; }
        for (const auto& entry : books) cout << entry.second->describe() << endl;
        cout << books.size() << " book(s) in total." << endl;
    }
    // Case-insensitive partial match on the title.
    int searchByTitle(const string& keyword) const {
        int found = 0;
        string key = lower(keyword);
        for (const auto& entry : books) {
            if (lower(entry.second->getTitle()).find(key) != string::npos) {
                cout << entry.second->describe() << endl;
                ++found;
            }
        }
        return found;
    }

    // ---------- File handling ----------
    void save() const {
        error_code ec;
        filesystem::path parent = filesystem::path(filePath).parent_path();
        if (!parent.empty()) filesystem::create_directories(parent, ec);
        ofstream out(filePath);                       // closed automatically (RAII)
        if (!out) throw FileError("Cannot open '" + filePath + "' for writing");
        out << "id,title,author,available\n";
        for (const auto& entry : books) out << entry.second->toCsv() << "\n";
        out.flush();
        if (!out) throw FileError("Failed while writing '" + filePath + "'");
    }
    // Loads records; bad lines are reported and skipped. A missing file simply means "no data yet".
    void load() {
        ifstream in(filePath);
        if (!in) {
            if (filesystem::exists(filePath))
                cout << "Warning: cannot read '" << filePath << "'. Starting with an empty library." << endl;
            else
                cout << "No data file '" << filePath << "' found. Starting with an empty library." << endl;
            return;
        }
        string line;
        getline(in, line);                            // header
        int lineNo = 1, loaded = 0;
        while (getline(in, line)) {
            ++lineNo;
            if (line.empty()) continue;
            stringstream ss(line);
            string id, title, author, flag;
            if (!getline(ss, id, ',') || !getline(ss, title, ',') ||
                !getline(ss, author, ',') || !getline(ss, flag, ',')) {
                cout << "Skipping malformed line " << lineNo << endl;
                continue;
            }
            try {
                int bookId = stoi(id);
                if (bookId <= 0 || title.empty() || author.empty() || (flag != "0" && flag != "1"))
                    throw invalid_argument("bad value");
                if (books.count(bookId)) throw DuplicateBook(bookId);
                books[bookId] = make_unique<Book>(bookId, title, author, flag == "1");
                ++loaded;
            } catch (const exception&) {
                cout << "Skipping invalid record on line " << lineNo << endl;
            }
        }
        cout << "Loaded " << loaded << " book(s) from " << filePath << endl;
    }
};

// ======================= Input helpers =======================
string readLine(const string& prompt) {
    cout << prompt;
    string text;
    getline(cin, text);
    if (cin.eof() && text.empty()) throw runtime_error("EOF");
    cout << text << endl;                       // echo, so scripted runs read like a console session
    return text;
}
// Whole positive number only (rejects letters, signs, empty input and very large values).
int readPositiveInt(const string& prompt) {
    string text = readLine(prompt);
    if (text.empty() || text.size() > 9 || !all_of(text.begin(), text.end(), ::isdigit))
        throw LibraryError("Invalid number: '" + text + "'. Enter a positive whole number.");
    int value = stoi(text);
    if (value <= 0) throw LibraryError("ID must be greater than zero");
    return value;
}
string readText(const string& prompt, const string& fieldName) {
    string text = readLine(prompt);
    if (text.find_first_not_of(' ') == string::npos) throw LibraryError(fieldName + " cannot be empty");
    if (text.find(',') != string::npos) throw LibraryError(fieldName + " cannot contain a comma (CSV format)");
    return text;
}
void trySave(const Library& library) {
    try { library.save(); }
    catch (const FileError& e) { cout << "WARNING: " << e.what() << " (changes are not saved)" << endl; }
}

// ======================= main =======================
int main(int argc, char* argv[]) {
    cout << "Name: Puneet Kumar" << endl;
    Library library(argc > 1 ? argv[1] : "data/books.csv");
    library.load();

    while (true) {
        cout << "\n===== LIBRARY MENU =====\n"
             << "1. Add book\n2. Display all books\n3. Search by ID\n4. Search by title\n"
             << "5. Issue book\n6. Return book\n7. Exit\n";
        try {
            string choice = readLine("Choice: ");
            if (choice == "1") {
                int id = readPositiveInt("Book ID: ");
                string title = readText("Title: ", "Title");
                string author = readText("Author: ", "Author");
                library.addBook(id, title, author);
                cout << "Book added." << endl;
                trySave(library);
            } else if (choice == "2") {
                library.displayAll();
            } else if (choice == "3") {
                int id = readPositiveInt("Book ID to search: ");
                cout << library.findById(id).describe() << endl;
            } else if (choice == "4") {
                string keyword = readText("Title keyword: ", "Keyword");
                if (library.searchByTitle(keyword) == 0) cout << "No book found with '" << keyword << "' in the title." << endl;
            } else if (choice == "5") {
                library.issueBook(readPositiveInt("Book ID to issue: "));
                cout << "Book issued." << endl;
                trySave(library);
            } else if (choice == "6") {
                library.returnBook(readPositiveInt("Book ID to return: "));
                cout << "Book returned." << endl;
                trySave(library);
            } else if (choice == "7") {
                cout << "Goodbye!" << endl;
                break;
            } else {
                cout << "Invalid menu choice. Enter a number from 1 to 7." << endl;
            }
        } catch (const LibraryError& e) {
            cout << "ERROR: " << e.what() << endl;
        } catch (const runtime_error&) {      // end of input (EOF)
            cout << "\nInput ended. Exiting." << endl;
            break;
        }
    }
    return 0;
}
