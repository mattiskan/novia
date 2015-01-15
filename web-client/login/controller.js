var controller = function($scope, $timeout, socket) {
    $scope.commands = [];
    $scope.cmd = "";
    
    var index = -1;
    var lastCmd = "";
    
    var print = function(str) {
	$scope.$broadcast("new_message");
	$scope.commands.push({
	    'str': str,
	    'prompt': false,
	    'class' : 'white'
	}) ;
    }
       
    $scope.parseCommand = function(keyEvent) {
	var userCommands = [];
	$scope.commands.forEach(function (cmd) {
	    if (cmd.prompt)
		userCommands.push(cmd);
	});
	
	var num_cmd = userCommands.length;

	// key up is forwards in history
	if (keyEvent.keyCode === 38 &&  num_cmd > 0) {
	    if (index == -1) {
		lastCmd = $scope.cmd;
	    }
	    
	    index++;
	    index %= num_cmd+1;
	    
	    if (index == num_cmd) {
		$scope.cmd = lastCmd;
		index = -1;
	    } else {
		$scope.cmd = userCommands[num_cmd - index-1].str;
	    }
	}

	// key down is backwards in history
	if (keyEvent.keyCode === 40 && $scope.commands.length > 0) {
	    if (index == -1) {
		lastCmd = $scope.cmd;
	    }
	    
	    index--;
	    if (index == -2)
		index = num_cmd-1;
	    
	    if (index == -1) {
		$scope.cmd = lastCmd;
	    } else {
		$scope.cmd = userCommands[num_cmd - index-1].str;
	    }
	}
	
	if (keyEvent.keyCode !== 13) // not enter
	    return;

	$scope.commands.push({ str: $scope.cmd, prompt:true });
	
	command = interpret($scope.cmd);

	command.invoke(print, socket, $scope);
	
	$scope.cmd = "";
    };

    
    print('Welcome to the crappy shit game. Type "help" or "connect" to get started.');

    $timeout(function() {
	print("Or don't, I don't care.");
    }, 2000);
};

app.controller('LoginController', controller);
