#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

ofstream outFile;
ifstream inFile;

class User
{
private:
    int  userID;
    char name[50];
    int  age;
    char password[20];
    char plan[30];
    int  balance;
    int  tripsUsed;

public:
    User();

    int   getUserID();
    char* getName();
    int   getAge();
    char* getPlan();
    int   getBalance();
    int   getTripsUsed();


    void setUserID(int id);
    void setName(char* n);
    void setAge(int a);
    void setPassword(char* p);
    void setPlan(int choice);
    void setBalance(int b);
    void setTripsUsed(int t);
    void setRegistrationInput(int id);


    void getPassDetails();
    void getPlans();


    void usePass(int fare);
    void recharge(int amount);
    int  getLoginCheck(int id, char* pwd);


    void setToFile();
    void getFromFile();
    void setPassToFile(char* filename);
};

User:: User()
{
    userID    = 0;
    age       = 0;
    balance   = 0;
    tripsUsed = 0;
    strcpy(name, "");
    strcpy(password, "");
    strcpy(plan, "");
}

int User::getUserID()
{
    return userID;
}

char* User::getName()
{
    return name;
}

int User::getAge()
{
    return age;
}

char* User::getPlan()
{
    return plan;
}

int User::getBalance()
{
    return balance;
}

int User::getTripsUsed()
{
    return tripsUsed;
}
void User::setUserID(int id)
{
    userID = id;
}
void User::setAge(int a)
{
    age = a;
}
void User::setBalance(int b)
{
    balance = b;
}
void User::setTripsUsed(int t)
{
    tripsUsed = t;
}
void User::setName(char* n)
{
    strcpy(name, n);
}
void User::setPassword(char* p)
{
    strcpy(password, p);
}

void User::setPlan(int choice)
{
    tripsUsed = 0;
    if (choice == 1)
    {
        strcpy(plan, "Super Saver");
        balance = 180;
    }
    else if (choice == 2)
    {
        strcpy(plan, "Senior Citizen");
        balance = 180;
    }
    else if (choice == 3)
    {
        strcpy(plan, "Unlimited");
        balance = 360;
    }
    else if (choice == 4)
    {
        strcpy(plan, "Student");
        balance = 180;
    }
    else
    {
        strcpy(plan, "Super Saver");
        balance = 180;
    }
}

void User::setRegistrationInput(int id)
{
    setUserID(id);

    cout << "Enter name    : ";
    cin.ignore();
    cin.getline(name, 50);

    cout << "Enter age     : ";
    cin >> age;

    cout << "Enter password: ";
    cin >> password;
}


void User::getPassDetails()
{
    cout << "\n--- Bus Pass Details ---\n";
    cout << "User ID    : " << userID << "\n";
    cout << "Name       : " << name << "\n";
    cout << "Age        : " << age << "\n";
    cout << "Plan       : " << plan << "\n";
    cout << "Balance    : Rs." << balance << "\n";
    cout << "Trips Used : " << tripsUsed << "\n";
    cout << "-------------------------\n";
}

void User::getPlans()
{
    cout << "\n--- Plans ---\n";
    cout << "1. Super Saver     - Rs.180\n";
    cout << "2. Senior Citizen  - Rs.180\n";
    cout << "3. Unlimited       - Rs.360\n";
    cout << "4. Student         - Rs.180\n";
    cout << "---------------\n";
}

void User::usePass(int fare)
{
    if (balance < fare)
    {
        cout << "Not enough balance\n";
        return;
    }
    balance = balance - fare;
    tripsUsed = tripsUsed + 1;
    cout << "Trip done. Balance: Rs." << balance << "\n";
}

void User::recharge(int amount)
{
    balance = balance + amount;
    cout << "Recharge done. Balance: Rs." << balance << "\n";
}

int User::getLoginCheck(int id, char* pwd)
{
    if (id == userID && strcmp(password, pwd) == 0)
        return 1;
    return 0;
}


void User::setToFile()
{
    outFile << userID << "\n";
    outFile << name << "\n";
    outFile << age << "\n";
    outFile << password << "\n";
    outFile << plan << "\n";
    outFile << balance << "\n";
    outFile << tripsUsed << "\n";
}

void User::getFromFile()
{
    inFile >> userID;
    inFile.ignore();
    inFile.getline(name, 50);
    inFile >> age;
    inFile >> password;
    inFile.ignore();
    inFile.getline(plan, 30);
    inFile >> balance;
    inFile >> tripsUsed;
}

void User::setPassToFile(char* filename)
{
    ofstream file(filename);
    file << "|==============================================|\n";
    file << "|             CHALO BUS PASS                   |\n";
    file << "|==============================================|\n";
    file << "| User ID    : " << userID << "                |\n";
    file << "| Name       : " << name << "                  |\n";
    file << "| Age        : " << age << "                   |\n";
    file << "| Plan       : " << plan << "                  |\n";
    file << "| Balance    : Rs." << balance << "            |\n";
    file << "| Trips Used : " << tripsUsed << "             |\n";
    file << "|==============================================|\n";
    file.close();
}


User users[100];
int  totalUsers = 0;

void setAllToFile()
{
    outFile.open("users.txt");
    outFile << totalUsers << "\n";
    for (int i = 0; i < totalUsers; i++)
        users[i].setToFile();
    outFile.close();
}

void getAllFromFile()
{
    inFile.open("users.txt");
    if (!inFile.is_open())
        return;
    inFile >> totalUsers;
    inFile.ignore();
    for (int i = 0; i < totalUsers; i++)
        users[i].getFromFile();
    inFile.close();
}

void setRegisterUser()
{
    if (totalUsers >= 100)
    {
        cout << "Max users reached\n";
        return;
    }

    int newID = 1001 + totalUsers;

    cout << "\n=== REGISTER ===\n";
    users[totalUsers].setRegistrationInput(newID);

    users[totalUsers].getPlans();
    cout << "Pick plan (1-4): ";
    int choice;
    cin >> choice;
    users[totalUsers].setPlan(choice);

    cout << "\nRegistration done!\n";
    cout << "User ID : " << users[totalUsers].getUserID() << "\n";
    cout << "Plan    : " << users[totalUsers].getPlan() << "\n";
    cout << "Balance : Rs." << users[totalUsers].getBalance() << "\n";

    totalUsers++;
    setAllToFile();
}

int getLoginUser()
{
    cout << "\n=== LOGIN ===\n";
    int  id;
    char pwd[20];

    cout << "Enter User ID : ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> pwd;

    for (int i = 0; i < totalUsers; i++)
    {
        if (users[i].getLoginCheck(id, pwd) == 1)
        {
            cout << "Welcome " << users[i].getName() << "\n";
            return i;
        }
    }

    cout << "Wrong ID or password\n";
    return -1;
}

void getAllUsers()
{
    if (totalUsers == 0)
    {
        cout << "No users registered\n";
        return;
    }

    cout << "\n--- All Users ---\n";
    for (int i = 0; i < totalUsers; i++)
    {
        cout << i + 1 << ". " << users[i].getName()
             << " | ID: " << users[i].getUserID()
             << " | Plan: " << users[i].getPlan()
             << " | Balance: Rs." << users[i].getBalance() << "\n";
    }
    cout << "------------------\n";
}

void setDisplayPass()
{
    cout << "Enter User ID: ";
    int searchID;
    cin >> searchID;

    for (int i = 0; i < totalUsers; i++)
    {
        if (users[i].getUserID() == searchID)
        {
            users[i].setPassToFile("your_pass.txt");
            cout << "Pass saved to 'your_pass.txt'\n";
            system("start your_pass.txt");
            return;
        }
    }

    cout << "User not found\n";
}

void getUserMenu(int idx)
{
    int choice;
    do
    {
        cout << "\n--- USER MENU ---\n";
        cout << "1. View Pass\n";
        cout << "2. Use Pass\n";
        cout << "3. Recharge\n";
        cout << "4. Logout\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            users[idx].getPassDetails();

        }
        else if (choice == 2)
        {
            cout << "Enter fare: ";
            int fare;
            cin >> fare;
            users[idx].usePass(fare);
            setAllToFile();

        }
        else if (choice == 3)
        {
            cout << "Enter amount: ";
            int amount;
            cin >> amount;
            users[idx].recharge(amount);
            setAllToFile();

        }
        else if (choice == 4)
        {
            cout << "Goodbye " << users[idx].getName() << "\n";

        }
        else
        {
            cout << "Wrong option\n";
        }

    }
    while (choice != 4);
}
int main()
{
    getAllFromFile();

    cout << "\n===== CHALO BUS PASS SYSTEM =====\n";

    int choice;
    do
    {
        cout << "\n--- MAIN MENU ---\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. See Plans\n";
        cout << "4. Show All Users\n";
        cout << "5. Display Pass\n";
        cout << "6. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            setRegisterUser();

        }
        else if (choice == 2)
        {
            int idx = getLoginUser();
            if (idx != -1)
                getUserMenu(idx);

        }
        else if (choice == 3)
        {
            User temp;
            temp.getPlans();

        }
        else if (choice == 4)
        {
            getAllUsers();

        }
        else if (choice == 5)
        {
            setDisplayPass();

        }
        else if (choice == 6)
        {
            cout << "Bye!\n";

        }
        else
        {
            cout << "Wrong option\n";
        }

    }
    while (choice != 6);

    return 0;
}
