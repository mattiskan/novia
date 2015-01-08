var controller = function($scope, socketFactory) {

    $scope.messages = [];
    $scope.ip = "127.0.0.1";
    $scope.username = "";
    $scope.password = "";
    $scope.is_connected = false;

    $scope.connect = function() {
	var msg = new AuthentificationMessage($scope.username, $scope.password);

	socketFactory.connect($scope.ip, msg, function() {
	    $scope.is_connected = true;
	});

	socketFactory.onMessage(function (msg) {
	    console.log("recieved message");
	    $scope.messages.push(msg.data);
	});
	
	$scope.messages = [];
    };

    $scope.request_map = function() {
	socketFactory.send(new RequestMapMessage());
    }
};

app.controller('LoginController', controller);
