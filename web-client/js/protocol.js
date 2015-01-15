
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

function TakeMessage(item) {
    this.msg_type = "take";
    this.target = item;
}

function UseMessage(item, type, target) {
    this.msg_type = "use";
    this.item = item;
    this.type = type;
    this.target = target;
}
