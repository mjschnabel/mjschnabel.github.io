# Artifact 3 - Databases

## Links to artifacts
- [Artifaxt #3 - Enhanced](https://github.com/mjschnabel/mjschnabel.github.io/tree/main/artifacts/artifact-3/enhanced)
- [Artifaxt #3 - Enhanced](https://github.com/mjschnabel/mjschnabel.github.io/tree/main/artifacts/artifact-3/original)

## Narrative

For this milestone, the artifact I decided to enhance was a personal project that I had made when I was first teaching myself JavaScript and programming in general. I originally wanted to enhance my final project from CS-340 Client Server development. That project was an API server which interacted with a MongoDB database. However, I took a long hiatus from school after starting my first professional job in the industry and could not find the original files for the project anywhere and it seemed as if they had been archived in Codio. So instead, I chose to make my enhancement in the spirit of that project by building an API which uses MongoDB on top of my old personal project.

My old personal project was a simple CLI (command line interface) which allowed a user to keep a todo list inside of their terminal. It was a Node.js program and the way it worked was that you would call the program from the terminal and it would print out a menu of options to you. You could then choose from this menu to do basic CRUD operations on all of your list of tasks that needed to be done, like creating new tasks, updating existing tasks and deleting tasks. You can see the menu for the application here:
```
➜  artifact-3 git:(master) ✗ node ./main.js
Usage: task-cli [options] [command]
 
CLI that lets you keep track of your tasks in your terminal
 
Options:
 -V, --version           output the version number
 -h, --help              display help for command
 
Commands:
 create <name>           Create a new task
 update <name> <status>  Update the status of a task
 delete <name>           Delete a task from the list
 list                    Print all the tasks in the list
 help [command]          display help for command
 ```

The tasks were stored inside of a JSON file on the user’s computer named “tasks.json”. All the CRUD operations performed by the program would update that JSON file by either creating, deleting or updating the tasks inside of it. 

For my enhancement, I moved this application away from being a CLI and towards being an API. The API no longer used a simple JSON file for the database, but it instead used a full database, MongoDB. MongoDB is a non-relational JSON based database which I thought would be perfect for this application because it is what we used in CS-340 so I was able to pay homage to that project and since it is JSON based it also matched what I had for the existing application, so it was a good fit on a technical level as well. The API was built using Node.js as the programming language and Express.js as the web framework. 

I believe that this enhancement shows my proficiency in the category of databases because I had to create an API server that could interact with a brand new database. The API can perform a full suite of CRUD actions on the Task model in the database. It can create, update, read and delete Tasks from the database, and it even uses an ODM to do this. An ODM or an Object Document Mapper is a tool that allows you to easily interact with a document based database (which is what mongodb is) from inside your code. Essentially, it allows you to interact with your database models as if they were just objects inside your code, which is phenomenal from a readability perspective (Tyler, What is the difference between ODM and Orm? 2018). The ODM that I used for this project was Mongoose, however there are a large number of open source ODMs available to work with. I chose Mongoose due to the fact that it is a very well maintained and respected project, so I could theoretically count on community support for a long time.

I do believe that I met the objectives I set out for myself. I intended to use what I learned in the class CS-340 about MongoDB and document based databases to create an API server that was capable of doing full CRUD on a given resource. I regrettably could not find my original work from CS-340, but I believe that I was able to make significant enhancements upon the original program and showcased that I am able to get a new database and application server up and running. This showcases that I know how to work with databases and can use them effectively.

I relied a lot on my existing knowledge from CS-340 as well as my professional and personal experiences to complete this milestone, however I did learn quite a bit about ODMs. I had been very familiar with ORMs (Object Relational Mappings) as I make use of an ORM at work and have used various ORMs for personal projects. Though since I had never worked with MongoDB or any other document based database in my professional career I had never used an ODM to interact with a database. It was not terribly different from working with an ORM, but it was interesting to see how you would set up a schema for a document database using an ORM and the differences in how other operations would be done like queries and data migrations. Overall, it was just nice to have an experience that allowed me to dig deeper into the world of document databases.

## References
Tyler, J. (2018, November 27). What is the difference between ODM and Orm? Medium. Retrieved June 24, 2022, from https://medium.com/@julianam.tyler/what-is-the-difference-between-odm-and-orm-267bbb7778b0 
