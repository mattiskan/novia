
var formating = {
    response_new_player_status: function(data) {
	var string = "";
	string += data.player +" has";
	if (data.status == "CONNECTED") {
	    string += " connected to the server";
	} else if (data.status=="DISCONNECTED") {
	    string += " disconnected from the server";
	} else if (data.status=="NEW_PLAYER") {
	    string += " has created and connected to the server";
	}
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
    },
    examine: function(data) {
	var string = "You examine ";
	if (data.type=="CHARACTER") {
	    string += "the character '" +data.character+"' and finds out: \n"+data.description;
	} else if (data.type == "ITEM") {
	    string += "the item '" +data.item+"' and finds out: \n"+data.description;
	} else if (data.type == "DOOR") {
	    string += "the exit '" +data.door+"' and finds out: \n"+data.description;	    
	} else if (data.type == "BACKPACK") {
	    string += "your backpack and finds the following items:\n";
	    for (var i=0; i<data.items.length; i++) {
		string += " ["+i+"] "+data.items[i]+"\n";
	    }
	}
	return string;
    },

    event: function(data) {
	return {
	    'ITEM_GAINED': 'You gained the item: '+data.item,
	    'ITEM_DROPPED': 'You dropped the item: '+data.item,
	    'PLAYER_DIED': data.player + " died.",
	}[data.type];
    },

    attack: function(data) {
	var response = "Your attack strikes for "+data.damage+".";

	if (data.killed == true)
	    response += " It is fatal.";
	
	return response;
    }

};


formatResponse = function(data) {
    var msg_obj = JSON.parse(data);
    console.log("data", msg_obj);
    if (formating[msg_obj.msg_type] === undefined)
	return "Unknown message type: " + data;
    return formating[msg_obj.msg_type](msg_obj);
}
