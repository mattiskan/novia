
var formating = {
    response_new_player_status: function(data) {
	var string = "";
	string += data.player +" has";
	string += (data.status=="CONNECTED")? " connected to the server" : " disconnected from the server";
	return string;
    },
    confirmation: function(data) {
	var string = "";
	if (data.status == "accepted")
	    string += "Authentication accepted.";
	else
	    string += "Authentication failed.";
	return string;
    },
    info: function(data) {
	var string = "";
	string += data.description + "\n";

	string += "In the room there are "+data.characters.length+" character(s): \n";
	for (var i=0; i<data.characters.length; i++) {
	    string += " - "+data.characters[i] + "\n"
	}

	string += data.items.length + " item(s):\n";
	for (var i=0; i<data.items.length; i++) {
	    string += " - "+data.items[i] + "\n"
	}

	string += data.exits.length + " exit(s):\n";
	for (var i=0; i<data.exits.length; i++) {
	    string += " - "+data.exits[i] + "\n"
	}

	
	
	return string;
    },
    invalid_command: function(data) {
	var string = "";
	string += data.message;
	return string;
    }

};


formatResponse = function(data) {
    var msg_obj = JSON.parse(data);
    console.log("data", msg_obj);
    if (formating[msg_obj.msg_type] === undefined)
	return "Unknown message type: " + data;
    return formating[msg_obj.msg_type](msg_obj);
}
