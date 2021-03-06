# Artifact 1 - Software Engineering and Design

## Links to artifacts
- [Artifact #1 - Enhanced](https://github.com/mjschnabel/mjschnabel.github.io/tree/main/artifacts/artifact-1/enhanced)
- [Artifact #1 - Original](https://github.com/mjschnabel/mjschnabel.github.io/tree/main/artifacts/artifact-1/original)

## Narrative

The artifact that I’ve chosen to enhance for the category of Software Engineering and Design is the code from the final project of the class CS-410 Software Reverse Engineering. This was one of the last projects I did in my Computer Science degree program here at SNHU. The original project tasked us students with reverse engineering a binary software application that the original code had been lost for. We were given the binary file and had to decompile it into assembly and then use reverse engineering skills to reconstruct the program in C++. After reconstructing the program we were tasked with suggesting improvements that could be made to the program and its security. While doing this, I saw numerous design flaws and poor practices in the way the program was written. Because of this I felt this project was the perfect project for me to enhance and showcase my skills in Software Design and Engineering.

I had a number of different ideas for what I could enhance about the code of this project, however I settled on tackling two specific issues. The first was that the program was written in such a way that all of its state was stored entirely in memory (i.e. in variables that were set directly in the program) and none of it was persisted to the hard disk. For some context, the program was a simple CLI that would be used by some sort of fictional investment firm to track customer’s investment choices. There were numerous variables in the code that hardcoded the starting state of the application. This meant that all the customer data was hardcoded. The code for this can be seen here:
  
```
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
```

The way the program worked is num1 would be the investment choice for the customer stored under name1, num2 would be the choice for the customer under name2 and so on. This is a bad design for a number of reasons.

The first is that you need to declare two variables for every single customer in the system. You also need to manually update each of the variables whenever updating a customer. Instead, a data structure like a hash table could be used to more efficiently manage the data. The data structure would also allow you to scale the program to having as many customers as you want. The second issue is that since all of the customer data is hard coded and stored only in variables you would need to make a code change to add a new customer, and you would also lose any of the updates that were made if the program ever crashed or was terminated because it was only stored in memory and not persisted to disk.

So for my enhancement I chose to do away with this method of tracking the state in the application and instead manage all state with a JSON file. Basically, in my enhanced version of the program, customer data is read from and written to a JSON file called “customer_data.json” The way the data is structured is it is an array of objects, where each object contains a name and a choice property. The program prints out a list of all the customers to the user of the program and then when a user wants to update a customer’s choice they will enter in their ID number, which basically is reference to the customer’s object index in the array, and the program will use that index and the user’s input to update the customer’s choice. This solution is much better because it allows data to be persisted to disk and because it is using appropriate data structures it allows the program to scale to having as many customers in the system as is required. This solution could even be further improved by moving off of JSON files and onto using a relational database like Postgres or a non-relational database like MongoDB. However, that would require a more complicated development environment and did not seem necessary for this project at this time. 

For my second enhancement to the program, and to enable the changes I detailed above, I ported the entire application from C++ to JavaScript/Node.js. The reason I chose to do this was that C++ is quite an old and difficult language to work with. Typically, you want to use C++ or similar languages when you need the performance benefits they bring or need to be close to the hardware. For this project, neither of those things were relevant and it made sense to move to a more modern and readable language for the sake of maintenance. In C++ even reading and writing to a JSON file can be a large challenge because it won’t necessarily be supported by the standard library. In JavaScript, this is greatly simplified because JavaScript has built in support for working with JSON and has libraries in the standard library for reading and writing to the filesystem.
I do believe that by making these enhancements I achieved what I set out to do in my initial plan and more. In my initial plan, I had only mentioned my intentions of improving the way the state of the application is managed, and moving over to the JSON system I detailed above. During implementation was when I made the call to switch to using JavaScript instead of C++ as I realized JavaScript provided benefits C++ did not and the benefits C++ provided were not necessary for the application. 

The main lesson I learned from this exercise was that everything in Software Engineering is truly a tradeoff. On one hand, I had the option of keeping everything in C++. That would mean I would not have to do a full rewrite of the application and could benefit from C++’s performance benefits if ever needed in the future. However, porting to JavaScript allowed me to simplify the code as a whole, move to a language with a fantastic ecosystem and standard library that let me do what I needed to do with ease and hopefully make the code more readable and maintainable overall. C++ also had some serious drawbacks like if I wanted to have JSON support I would need to use turbo C++ or other variants which adds complexity to the build process and getting other developers to work on the project since they would have additional dependencies to install on their systems. With my JavaScript version of the program, all one needs to do is install Node.js which works on pretty much any of the main operating systems and developer’s could get started with ease. These trade-offs made the choice extremely easy, but it did really highlight to me that everything has its pros and cons and as an engineer you will need to evaluate those pros and cons and choose the best solution based on your needs. 
