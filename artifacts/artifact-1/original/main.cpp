#include <iostream>
#include <string>

using namespace std;

int num1 = 1;
int num2 = 2;
int num3 = 1;
int num4 = 1;
int num5 = 1;

string name1 = "Bob Jones";
string name2 = "Sarah Davis";
string name3 = "Amy Friendly";
string name4 = "Johnny Smith";
string name5 = "Carol Spears";

string username = "admin";
string password = "CS410IsAGreatC1a$$";

int validServices[] = {1, 2};

bool CheckUserPermissionAccess() {
  string inputUsername;
  string inputPassword;

  cout << "Enter your username: " << endl;
  cin >> inputUsername;

  cout << "Enter password: " << endl;
  cin >> inputPassword;

  if (inputUsername == username && inputPassword == password) {
    return true;
  } else {
    cout << "Invalid Username or Password. Please try again" << endl;
    return false;
  }
}

void DisplayInfo() {
  cout << "  Client's Name    Service Selected (1 = Brokerage, 2 = Retirement)" << endl;

  cout << "1. " << name1 << " selected option " << num1 << endl;
  cout << "2. " << name2 << " selected option " << num2 << endl;
  cout << "3. " << name3 << " selected option " << num3 << endl;
  cout << "4. " << name4 << " selected option " << num4 << endl;
  cout << "5. " << name5 << " selected option " << num5 << endl;
}

// Fixed vulnerability: Previously, anywhere that the program needed to read in an integer did not protect against
// if a user entered a non-integer value. This would cause an exception to be thrown and the program to crash,
// giving attackers a very easy way to take down the system. This function was added and used in all places that
// the program reads in integers and catches the error for if a non integer value was entered.
int ReadInteger() {
  int integer;

  while (true) {
    try {
      cin >> integer;
      return integer;
    } catch (int e) {
      cout << "Error: Input not supported. Please enter an integer." << endl;
      continue;
    }
  }
}

bool ValidateServiceChoice(int choice) {
  for(int i = 0; i < sizeof(validServices); i++) {
    if (choice == validServices[i]) {
      return true;
    }
  }

  return false;
}

void ChangeCustomerChoice() {
  int clientNumber;
  int newService;

  cout << "Enter the number of the client that you wish to change" << endl;
  clientNumber = ReadInteger();

  cout << "Please enter the client's new service choice (1 = Brokerage, 2 = Retirement)" << endl;
  newService = ReadInteger();

  if (!ValidateServiceChoice(newService)) {
    cout << "Service choice is not valid! Please try again" << endl;
    return;
  }

  switch (clientNumber) {
    case 1:
      num1 = newService;
      break;
    case 2:
      num2 = newService;
      break;
    case 3:
      num3 = newService;
      break;
    case 4:
      num4 = newService;
      break;
    case 5:
      num5 = newService;
      break;
  }
}

int main() {
  cout << "Created by: Mark Schnabel" << endl;
  cout << "Hello! Welcome to our Investment Company" << endl;

  bool authenticated = false;

  while (authenticated != true) {
    authenticated = CheckUserPermissionAccess();
  }

  bool shouldExit = false;
  int choice;

  while (!shouldExit) {
    cout << "What would you like to do?" << endl;
    cout << "DISPLAY the client list (enter 1)" << endl;
    cout << "CHANGE a client's choice (enter 2)" << endl;
    cout << "Exit the program.. (enter 3)" << endl;

    choice = ReadInteger();

    cout << "You chose " << choice << endl;

    switch (choice) {
      case 1:
        DisplayInfo();
        break;
      case 2:
        ChangeCustomerChoice();
        break;
      case 3:
        shouldExit = true;
        break;
    }
  }

  return 0;
}
