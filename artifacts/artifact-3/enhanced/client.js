const axios = require('axios');

axios.defaults.baseURL = 'http://localhost:4000/';

(async () => {
  console.log('Starting client script');

  console.log('Creating the first Task for the DB');
  const createResponse = await axios.post('api/v1/tasks', {
    name: 'Task 1',
    description: 'First task',
    status: 'Todo'
  });
  console.log('Response:');
  console.log(createResponse.data);
  console.log();

  console.log('Testing the get one route using the new task');
  const getOneResponse = await axios.get(`api/v1/tasks/${createResponse.data._id}`);
  console.log('Response:');
  console.log(getOneResponse.data);
  console.log();

  console.log('Testing the get all route');
  let getAllResponse = await axios.get(`api/v1/tasks/${createResponse.data._id}`);
  console.log('Response:');
  console.log(getAllResponse.data);
  console.log();

  console.log('Testing the update route using the new task');
  const updateResponse = await axios.patch(`api/v1/tasks/${createResponse.data._id}`, {
    status: 'In Progress'
  });
  console.log('Response:');
  console.log(updateResponse.data);
  console.log();

  console.log('Testing the delete route using the new task');
  const deleteResponse = await axios.delete(`api/v1/tasks/${createResponse.data._id}`);
  console.log('Response:');
  console.log(deleteResponse.data);
  console.log();

  console.log('Checking if the task was deleted by hitting the get all route');
  getAllResponse = await axios.get('api/v1/tasks');
  console.log('Response:');
  console.log(getAllResponse.data);
  console.log();
})();
