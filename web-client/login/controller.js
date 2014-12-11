var controller = function($scope, socket) {

    $scope.categories = ['building', 'characters', 'din mamma'];

    $scope.messages = [];

    socket.onMessage(function (msg) {
	console.log("recieved message");
	$scope.messages.push(msg.data);
    });

    

};

app.controller('LoginController', controller);
