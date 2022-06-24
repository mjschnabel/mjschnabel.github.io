# Artifact #2 Original

## Getting started

To run this application on your system you will need the following installed:
- The G++ compiler

## How to run the program

After installing the G++ compiler, you can run the program with the following set of commands:

```
// Compile the program
g++ LinkedList.cpp CSVparser.cpp -o main.out

// Run the compiled program
./main.out
```

## Directory structure

There are numerous files that make up this application. This is what each of them does:

- LinkedList.cpp - contains the main LinkedList class implementation
- eBid_Monthly_Sales.csv and eBid_Monthly_Sales_Dec_2016.csv - Files containing the Bid data to load into the LinkedList
- CSVparser.cpp and CSVparser.hpp - Utility class and header file to load the data from the CSV files
