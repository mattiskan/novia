
function AuthentificationMessage(username, password) {
    this.msg_type = 'authenticate';
    this.username = username;
    this.password = password;
}

function RequestMapMessage() {
    this.msg_type = 'request_map';
}

