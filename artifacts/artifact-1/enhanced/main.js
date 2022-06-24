const fs = require('fs');
const prompt = require('prompt-sync')({sigint: true});

// Use a constant for the customer data file path since it should never change
const CUSTOMER_DATA_FILE_PATH = './customer_data.json';

const VALID_SERVICES = [1, 2];

// Usernames and passwords should never be hardcoded, but changing that is not
// part of the intended enhancement for this assignment
const USERNAME = 'admin';
const PASSWORD = 'CS410IsAGreatC1a$$';

let customerData;

try {
  // Try to read the contents of the file at the specified file path
  customerData = fs.readFileSync(CUSTOMER_DATA_FILE_PATH);
  customerData = JSON.parse(customerData);
} catch (error) {
  console.error('Failed to read file at: ' + CUSTOMER_DATA_FILE_PATH);
  console.error('Full error:');
  console.error(error);
}

function checkUserPermissionAccess() {
  let inputUsername;
  let inputPassword;

  inputUsername = prompt('Enter your username: ');
  inputPassword = prompt('Enter your password: ');

  if (inputUsername === USERNAME && inputPassword === PASSWORD) {
    return true;
  } else {
    console.error('Invalid username or password! Please try again');
    return false;
  }
}

function displayInfo() {
  console.log('ID Number | Client\'s Name | Service Selected (1 = Brokerage, 2 = Retirement)');

  customerData.forEach((customer, index) => {
    // Increment the index by 1 when printing to avoid the 0 index from showing up in the menu
    console.log(`${index + 1} | ${customer.name} | ${customer.serviceChoice}`)
  });
}

function readInteger(message) {
  let integer;

  while (true) {
    try {
      integer = parseInt(prompt(message));
      return integer;
    } catch (err) {
      console.error('Error: Input not supported. Please enter an integer');
      continue;
    }
  }
}

function validateClientIDNumber(number) {
  if (number > customerData.length || number < 0) {
    return false;
  }

  return true;
}

function validateServiceChoice(choice) {
  return VALID_SERVICES.includes(choice);
}

function changeCustomerServiceChoice() {
  let clientIDNumber;
  let newService;

  clientIDNumber = readInteger('Enter the ID number of the client that you wish to change: ');
  clientIDNumber = clientIDNumber - 1; // Subtract by one to get the index since the menu prints numbers incremented by 1
  if (!validateClientIDNumber(clientIDNumber)) {
    console.log('Not a valid client ID number! Please try again');
    return;
  }

  newService = readInteger('Please enter the client\'s new service choice (1 = Brokerage, 2 = Retirement): ');
  if (!validateServiceChoice(newService)) {
    console.log('Not a valid service number! Please try again');
    return;
  }

  customerData[clientIDNumber].serviceChoice = newService;
  fs.writeFileSync(CUSTOMER_DATA_FILE_PATH, JSON.stringify(customerData, null, 2));
}

function main() {
  console.log('Created by: Mark Schnabel');
  console.log('Hello! Welcome to our investment company');

  let authenticated = false;

  while (!authenticated) {
    authenticated = checkUserPermissionAccess();
  }

  let shouldExit = false;
  let choice;

  while (!shouldExit) {
    console.log('What would you like to do?');
    console.log('DISPLAY the client list (enter 1)');
    console.log('CHANGE a client\'s choice (enter 2)');
    console.log('Exit the program.. (enter 3)');

    choice = readInteger();

    console.log(`You chose: ${choice}`);

    switch (choice) {
      case 1:
        displayInfo();
        break;
      case 2:
        changeCustomerServiceChoice();
        break;
      case 3:
        shouldExit = true;
        break;
      default:
        console.log('Invalid choice! Please try again');
    }
  }

  return 0;
}

main();
