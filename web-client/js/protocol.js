
function AuthentificationMessage(username, password) {
    this.msg_type = 'authenticate';
    this.username = username;
    this.password = password;
}

function MoveMessage(dest) {
    this.msg_type = 'move';

    this.destination = dest;
}

