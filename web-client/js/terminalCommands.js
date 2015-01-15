var NOT_CONNECTED_ERROR = 'Error: Requires active connection to server. See "help connect" for more information';

function interpret(input) {
    tokens = input.split(" ");
    
    cmd = tokens[0];
    args = tokens.slice(1); // rest of tokens

    switch(cmd) {
    case "help": return new HelpCommand(args); break;
    case "connect": return new ConnectCommand(args); break;
    case "login": return new LoginCommand(args); break;
    case "move": return new MoveCommand(args); break;
    case "examine": return new ExamineCommand(args); break;
    case "take": return new TakeCommand(args); break;
    case "use": return new UseCommand(args); break;
    case "attack": return new AttackCommand(args); break;

    default: return new UnknownCommand(cmd);
    }
}

function UnknownCommand(cmd) {
    this.invoke = function(print, socket) {
	if(cmd != "")
	    print('Unknown command: "' + cmd + '"');
    }
}

function HelpCommand(args) {
    this.args = args;

    this.invoke = function(print, socket) {
	if (args == "") {
	    print("Commands:");
	    print("- connect");
	    print("- help");
	    print("- login");
	    print("- move");
	    print("- use");
	    print("- take");
	    print("- attack");
	    print("See help <command> for help about specific commands.");
	} else {
	    console.log("lf help", args[0]);
	    topic = interpret(args[0]);
	    topic.help(print);
	}
    }

    this.help = function(print) {
	print("help [command]");
	print("prints available commands or information about a specified command");
    }
}

function ConnectCommand(args) {
    this.ipstr = (args.length >= 1)? args[0]: "127.0.0.1:9002";

    this.invoke = function(print, socket, $scope) {
	print("connecting to " + this.ipstr);

	socket.connect(this.ipstr, function() {
	    if (socket.isConnected())
		print("connection successful");
	    else
		print("connection failed");
	});

	socket.onMessage(function(msg) {
	    print(formatResponse(msg.data));
	    //print("From server: " + msg.data);
	});
    }

    this.help = function(print) {
	print('connect [ipstring]');
	print('default ip="127.0.0.1:9002"');
    }
}

function LoginCommand(args) {
    this.username = args[0];
    this.password = args[1];
    
    this.invoke = function(print, socket) {
	if (!socket.isConnected()){
	    print(NOT_CONNECTED_ERROR);
	    return;
	}
	socket.send(new AuthentificationMessage(this.username, this.password));
    };

    this.help = function(print) {
	print("login <username> <password>");
    }
}

function MoveCommand(args) {
    this.dest = args[0];

    this.invoke = function (print, socket) {
	if (!socket.isConnected()){
	    print(NOT_CONNECTED_ERROR);
	    return;
	}
	
	socket.send(new MoveMessage(this.dest));
    };

    this.help = function(print) {
	print('move <destination>');
    };

}

function ExamineCommand(args) {
    this.type = args[0];
    this.target = args[1];


    this.invoke = function (print, socket) {
	if (!socket.isConnected()){
	    print(NOT_CONNECTED_ERROR);
	    return;
	}
	if (args.length == 1 && this.type != "backpack") {
	    print("You must have a target!\n");
	    this.help(print);
	    return;
	}
	
	socket.send(new ExamineMessage(this.type, this.target));
    };

    this.help = function(print) {
	print('examine [<item/character/backpack> <target name>]');
    };

}

function TakeCommand(args) {
    this.item = args[0];

    this.invoke = function (print, socket) {
	if (!socket.isConnected()){
	    print(NOT_CONNECTED_ERROR);
	    return;
	}
	
	socket.send(new TakeMessage(this.item));
    };

    this.help = function(print) {
	print('take <item>');
    };
}

function UseCommand(args) {
    this.item = args[0];
    this.type = args[1];
    this.target = args[2];

    this.invoke = function (print, socket) {
	if (!socket.isConnected()){
	    print(NOT_CONNECTED_ERROR);
	    return;
	}
	if (this.type !== undefined && ["character", "backpack", "item", "exit"].indexOf(this.type) == -1) {
	    print("Unknown or missing type: "+this.type);
	    this.help(print);
	    return;
	}
	socket.send(new UseMessage(this.item, this.type, this.target));
    };

    this.help = function(print) {
	print('use [<character|item|backpack|exit> <target>]');
    };
}

function AttackCommand(args) {
    this.target = args[0];

    this.invoke = function (print, socket) {
	if (!socket.isConnected()){
	    print(NOT_CONNECTED_ERROR);
	    return;
	}
	if (target === undefined) {
	    print("You must attack something.");
	    this.help(print);
	    return;
	}
	socket.send(new AttackMessage(this.target));
    };

    this.help = function(print) {
	print('attack <character>');
    };

}
