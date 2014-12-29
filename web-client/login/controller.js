var controller = function($scope, socketFactory) {

    $scope.messages = [];
    $scope.ip = "127.0.0.1";
    $scope.username = "";
    $scope.password = "";    


    $scope.connect = function() {
	var login = {
	    'msg_type': 'authenticate',
	    'username': $scope.username,
	    'password': $scope.password
	};
	
	socketFactory.connect($scope.ip, JSON.stringify(login));

	socketFactory.onMessage(function (msg) {
	    console.log("recieved message");3
	    $scope.messages.push(msg.data);
	});

	$scope.messages = [];
    };
    
};

app.controller('LoginController', controller);
