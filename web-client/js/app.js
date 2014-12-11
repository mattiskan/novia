var app = angular.module('novia', ['ngRoute']);

app.config(['$routeProvider', function($routeProvider) {
    $routeProvider.when('/login',
			{
			    templateUrl: 'login/login.html',
			    controller: 'LoginController'
			})
	.otherwise({
	    redirectTo: '/login'
	});
}
	   ]);

app.factory('socketFactory', ['$rootScope', function($rootScope) {

    var ws;
    
    return {
	connect: function(ip) {
	    ws = new WebSocket("ws://"+ ip +":9002");
	   
 	    var has_connected = false;
	    
	    ws.onopen = function() {
		has_connected = true;
		console.log("Connection successful");
	    }

	    ws.onclose = function() {
		if(has_connected)
		    console.log("Socket closed");
	    }
	},

	onMessage : function(callback) {
	    ws.onmessage = function(msg) {
		$rootScope.$apply(function() {
		    callback(msg);
		});
	    };
	}
    };

}]);
