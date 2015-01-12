var controller = function($scope, socket) {

    $scope.commands = [];

    var print = function(str) {	
	$scope.commands.push({
	    'str': str,
	    'prompt': false,
	    'class' : 'white'
	}) ;
    }
       
    $scope.parseCommand = function(keyEvent) {
	if (keyEvent.which !== 13)
	    return; // not enterkey

	$scope.commands.push({ str: $scope.cmd, prompt:true });
	
	command = interpret($scope.cmd);

	command.invoke(print, socket);
	
	$scope.cmd = "";
    };

};

app.controller('LoginController', controller);
