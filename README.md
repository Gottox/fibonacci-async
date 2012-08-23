[![build status](https://secure.travis-ci.org/Gottox/fibonacci-async.png)](http://travis-ci.org/Gottox/fibonacci-async)
# fibonacci-async for node

So, you want to benchmark Node.js with fibonacci once again? - Here's the library for that. You're welcome.

     npm install fibonacci-async

Example:

	var fibonacci = require('fibonacci-async').fibonacci;
	
	fibonacci(10, function(res) {
		process.stdout.write(res+"\n");
	});
