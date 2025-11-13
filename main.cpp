#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

class Question {
    string text;
    vector<string> options;
    char correct;
public:
    Question(string t, vector<string> opts, char corr)
        : text(t), options(opts), correct(tolower(corr)) {
    }

    void show() const {
        cout << text << endl;
        char letter = 'a';
        for (auto& opt : options) {
            cout << "  " << letter++ << ") " << opt << endl;
        }
    }

    bool checkAnswer(char ans) const {
        return tolower(ans) == correct;
    }
};

class Test {
    string title;
    vector<Question> questions;
public:
    Test(string t) : title(t) {}

    string getTitle() const { return title; }

    void addQuestion(const Question& q) {
        questions.push_back(q);
    }

    void showQuestions() const {
        for (size_t i = 0; i < questions.size(); i++) {
            cout << i + 1 << ". ";
            questions[i].show();
        }
    }

    void passTest() const {
        int correctAnswers = 0;
        for (size_t i = 0; i < questions.size(); i++) {
            cout << "\nQuestion " << i + 1 << ":\n";
            questions[i].show();
            cout << "Your answer (a, b, c, d): ";
            char ans;
            cin >> ans;
            if (questions[i].checkAnswer(ans))
                correctAnswers++;
        }
        cout << "\nYou answered " << correctAnswers << " out of "
            << questions.size() << " questions correctly.\n";
    }
};

class TestSystem {
    vector<Test> tests;
    const string adminPassword = "arthurmarkarianmihailovich4yearsukraineandrussia28iula1914";
public:
    void start() {
        while (true) {
            cout << "\n=== MAIN MENU ===\n";
            cout << "1. Admin\n";
            cout << "2. Guest\n";
            cout << "3. Exit\n";
            cout << "Choose option: ";

            int choice;
            cin >> choice;

            if (choice == 1)
                adminLogin();
            else if (choice == 2)
                guestMenu();
            else if (choice == 3) {
                cout << "Exiting program...\n";
                break;
            }
            else
                cout << "Invalid choice. Try again.\n";
        }
    }

private:
    void adminLogin() {
        cout << "Enter admin password: ";
        string pass;
        cin >> pass;
        if (pass == adminPassword) {
            adminMenu();
        }
        else {
            cout << "Wrong password.\n";
        }
    }

    void adminMenu() {
        while (true) {
            cout << "\n=== ADMIN MENU ===\n";
            cout << "1. Create test\n";
            cout << "2. Show tests\n";
            cout << "3. Delete test\n";
            cout << "4. Back to main menu\n";
            cout << "Choose option: ";

            int choice;
            cin >> choice;

            if (choice == 1)
                createTest();
            else if (choice == 2)
                showTests();
            else if (choice == 3)
                deleteTest();
            else if (choice == 4)
                break;
            else
                cout << "Invalid choice.\n";
        }
    }

    void createTest() {
        cout << "Enter test title: ";
        string title;
        cin.ignore();
        getline(cin, title);

        Test newTest(title);

        cout << "How many questions? ";
        int num;
        cin >> num;
        cin.ignore();

        for (int i = 0; i < num; i++) {
            cout << "\nEnter question " << i + 1 << ": ";
            string text;
            getline(cin, text);

            vector<string> opts(4);
            for (int j = 0; j < 4; j++) {
                cout << "Option " << char('a' + j) << ": ";
                getline(cin, opts[j]);
            }

            cout << "Enter correct option (a, b, c, d): ";
            char correct;
            cin >> correct;
            cin.ignore();

            newTest.addQuestion(Question(text, opts, correct));
        }

        tests.push_back(newTest);
        cout << "Test created successfully.\n";
    }

    void showTests() const {
        if (tests.empty()) {
            cout << "No tests available.\n";
            return;
        }
        cout << "\nAvailable tests:\n";
        for (size_t i = 0; i < tests.size(); i++) {
            cout << i + 1 << ". " << tests[i].getTitle() << endl;
        }
    }

    void deleteTest() {
        showTests();
        if (tests.empty()) return;

        cout << "Enter test number to delete: ";
        int num;
        cin >> num;

        if (num > 0 && num <= (int)tests.size()) {
            tests.erase(tests.begin() + num - 1);
            cout << "Test deleted.\n";
        }
        else {
            cout << "Invalid number.\n";
        }
    }

    void guestMenu() {
        while (true) {
            cout << "\n=== GUEST MENU ===\n";
            cout << "1. Take test\n";
            cout << "2. Show test list\n";
            cout << "3. Back to main menu\n";
            cout << "Choose option: ";

            int choice;
            cin >> choice;

            if (choice == 1)
                takeTest();
            else if (choice == 2)
                showTests();
            else if (choice == 3)
                break;
            else
                cout << "Invalid choice.\n";
        }
    }

    void takeTest() {
        showTests();
        if (tests.empty()) return;

        cout << "Choose test number: ";
        int num;
        cin >> num;

        if (num > 0 && num <= (int)tests.size()) {
            tests[num - 1].passTest();
        }
        else {
            cout << "Invalid number.\n";
        }
    }
};
int main() {
    TestSystem system;
    system.start();
    return 0;
}
