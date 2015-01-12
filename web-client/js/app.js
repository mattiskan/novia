var app = angular.module('novia', ['ngRoute']);

app.config(['$routeProvider', function($routeProvider) {
    $routeProvider.when('/login', {
        templateUrl: 'login/login.html',
	controller: 'LoginController'
    })
    .otherwise({
        redirectTo: '/login'
    });
}]);

app.factory('socket', ['$rootScope', function($rootScope) {
    var ws;
    var isConnected = false;
    
    return {
	connect: function(ipstr, callback) {
	    ws = new WebSocket("ws://"+ ipstr);
	    
	    ws.onopen = function() {
		isConnected = true;
		console.log("Connection successful");
		$rootScope.$apply(function() {
		    callback();
		});
	    };
	    
	    ws.onerror = function() {
		isConnected = false;
		$rootScope.$apply(function() {
		    callback();
		});
	    };
	    
	    ws.onclose = function() {
		is_connected = false;
	    };
	},
	onMessage : function(callback) {
	    ws.onmessage = function(msg) {
		$rootScope.$apply(function() {
		    callback(msg);
		});
	    };
	},
	isConnected : function() {
	    return isConnected;
	},
	send: function(message) {
	    ws.send(JSON.stringify(message));
	}
    };
}]);

app.directive('ngFocus', function($timeout) {
    return {
        link: function ( scope, element, attrs ) {
            scope.$watch( attrs.ngFocus, function ( val ) {
                if ( angular.isDefined( val ) && val ) {
                    $timeout( function () { element[0].focus(); } );
                }
            }, true);

            element.bind('blur', function () {
                if ( angular.isDefined( attrs.ngFocusLost ) ) {
                    scope.$apply( attrs.ngFocusLost );

                }
            });
        }
    };
});

app.directive('scroll', function($timeout) {
    return {
	restrict: 'A',
	link: function(scope, element, attr) {
	    scope.$watchCollection(attr.scroll, function(newVal) {
		$timeout(function() {
		    element[0].scrollTo = element[0].scrollHeight;
		});
	    });
	}
    }
});
