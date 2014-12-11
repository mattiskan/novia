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








app.factory('socket', ['$rootScope', function($rootScope) {

    var ws = new WebSocket("ws://127.0.0.1:9002");

    ws.onopen = function() {
	console.log("Connection successful");
    }

    ws.onclose = function() {
	console.log("Socket closed");
    }
    
    return {
	onMessage : function(callback) {
	    ws.onmessage = function(msg) {
		$rootScope.$apply(function() {
		    callback(msg);
		});
	    };
	}
    };

}]); 


