'use strict';
module.exports = function(app) {
  var controller = require('../controllers/led.controller');

  // todoList Routes
  app.route('/lightconfig')
    .get(controller.getCurrentConfig)
    .post(controller.pushConfig);

};
