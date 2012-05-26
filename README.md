# node-fibonacci-native

So, you want to benchmark Node.js with fibonacci once again? - Here's the library for that. Thanks.

     npm install fibonacci-async

Example:
	var fibonacci = require('fibonacci-async').fibonacci;
	
	fibonacci(10, function(res) {
		process.stdout.write(res+"\n");
	});
