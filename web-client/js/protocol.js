
function AuthentificationMessage(username, password) {
    this.msg_type = 'authenticate';
    this.username = username;
    this.password = password;
}

function MoveMessage(dest) {
    this.msg_type = 'move';

    this.destination = dest;
}

function ExamineMessage(type, target) {
    this.msg_type = "examine";
    if (type === undefined) {
	this.type = "room";
    } else {
	this.type = type;
	if (target !== undefined) {
	    this.target = target;
	}
    }
}

