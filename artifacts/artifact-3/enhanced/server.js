const express = require('express');
const app = express();
const mongoose = require('mongoose');

mongoose.connect('mongodb://localhost/tasks', { useNewUrlParser: true });
const db = mongoose.connection;

db.on('once', () => {
  console.log('Connected to MongoDB');
});

db.on('error', error => {
  console.log(error);
});

app.use(express.json());

const apiV1TasksRouter = require('./routes/api/v1/tasks');

app.use('/api/v1/tasks', apiV1TasksRouter);

const PORT = 4000;

app.listen(PORT, () => {
  console.log(`Tasks API server running on: ${PORT}`);
});
