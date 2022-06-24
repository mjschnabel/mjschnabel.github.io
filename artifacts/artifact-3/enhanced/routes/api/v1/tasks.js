const express = require('express');
const router = express.Router();
const Task = require('../../../models/task');

// Re-usable middleware function for finding a task based on the tasks ID
async function findTask(req, res, next) {
  try {
    const task = await Task.findById(req.params.id);

    if (!task) {
      res.status(404).json({ message: `No task with ID: ${req.params.id}`});
    }

    res.task = task;
  } catch (err) {
    res.status(500).json({ message: err.message });
  }

  next();
}

// Get all tasks
router.get('/', async (req, res) => {
  try {
    const tasks = await Task.find();
    res.json(tasks);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
});

// Get a single task
router.get('/:id', findTask, (_req, res) => {
  res.json(res.task);
});

// Create a new task
router.post('/', async (req, res) => {
  try {
    const task = await new Task({
      name: req.body.name,
      description: req.body.description,
      status: req.body.status
    }).save();

    res.status(201).json(task);
  } catch (err) {
    res.status(400).json({ message: err.message })
  }
});

// Update a single task
router.patch('/:id', findTask, async (req, res) => {
  try {
    ['name', 'status', 'description'].forEach(param => {
      if (req.body[param]) {
        res.task[param] = req.body[param];
      }
    });

    const task = await res.task.save()
    res.json(task)
  } catch (err) {
    res.status(400).json({ message: err.message })
  }
});

// Delete a single task
router.delete('/:id', findTask, async (_req, res) => {
  try {
    await res.task.remove()
    res.json({ message: 'Succesfully deleted Task' })
  } catch (err) {
    res.status(500).json({ message: err.message })
  }
});

module.exports = router;
