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

	    ws.onopen = function() {
		console.log("Connection successful");
	    }

	    ws.onclose = function() {
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
