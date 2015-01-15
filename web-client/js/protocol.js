
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
	    if (type == "backpack") {
		this.target = parseInt(target);
	    } else {
		this.target = target;
	    }
	}
    }
}

function TakeMessage(item) {
    this.msg_type = "take";
    this.item = item;
}

function UseMessage(item, type, target) {
    this.msg_type = "use";
    this.item = parseInt(item);
    this.type = type;
    if (type !== undefined && type == "backpack") {
	this.target = parseInt(target);
    } else {
	this.target = target;
    }

}

function AttackMessage(target) {
    this.msg_type = "attack";
    this.target = target;
}
