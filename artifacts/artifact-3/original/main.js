const fs = require('fs');
const { program } = require('commander');

const TASKS_FILE_PATH = './tasks.json';
const taskList = JSON.parse(fs.readFileSync(TASKS_FILE_PATH));

const taskStatuses = Object.freeze({
  TODO: 'Todo',
  DONE: 'Done',
})

function save() {
  fs.writeFileSync(TASKS_FILE_PATH, JSON.stringify(taskList, null, 2));
}

program
  .name('task-cli')
  .description('CLI that lets you keep track of your tasks in your terminal')
  .version('1.0.0');

program.command('create')
  .description('Create a new task')
  .argument('<name>', 'Name for the task')
  .action((name) => {
    if (taskList[name]) {
      console.error(`A task with a name of: "${name}" already exists!`);
      console.error('Please try again with a new task name');
      return;
    }

    taskList[name] = taskStatuses.TODO;
    save(taskList);
  });

program.command('update')
  .description('Update the status of a task')
  .argument('<name>', 'Name for the task you want to update')
  .argument('<status>', 'Update the status of the task')
  .action((name, status) => {
    if (!taskList[name]) {
      console.error(`A task with a name of: "${name}" does not exist!`);
      console.error('Please try again with a new task name');
      return;
    }

    // If the status the user passed is not one of the available statuses throw an error
    if (!Object.keys(taskStatuses).includes(status.toUpperCase())) {
      console.error(`The status: ${status} is not valid! Please try again`);
      return;
    }

    taskList[name] = taskStatuses[status.toUpperCase()];
    save(taskList);
  });

program.command('delete')
  .description('Delete a task from the list')
  .argument('<name>', 'Name for the task you want to delete')
  .action((name) => {
    if (!taskList[name]) {
      console.error(`A task with a name of: "${name}" does not exist!`);
      console.error('Please try again with a new task name');
      return;
    }

    delete taskList[name];
    save(taskList);
  });

program.command('list')
  .description('Print all the tasks in the list')
  .action(() => {
    console.log('|  Name   |   Status   |');

    Object.keys(taskList).forEach(name => {
      console.log(`|   ${name}   |   ${taskList[name]}   |`);
    });
  });

program.parse();
