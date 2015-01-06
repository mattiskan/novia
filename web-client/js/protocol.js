
function AuthentificationMessage(username, password) {
    return {
	'msg_type': 'authenticate',
	'message' : {
	    'username': username,
	    'password': password
	}
    };
}

function RequestMapMessage() {
    return {
	'msg_type': 'request_map'
    };
}

