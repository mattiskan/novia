

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

    default: return new UnknownCommand(cmd);
    }
}

function UnknownCommand(cmd) {
    this.invoke = function(print, socket) {
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

    this.invoke = function(print, socket) {
	print("connecting to " + this.ipstr);

	socket.connect(this.ipstr, function() {
	    if (socket.isConnected())
		print("connection successful");
	    else
		print("connection failed");
	});

	socket.onMessage(function(msg) {
	    print("From server: " + msg.data);
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
	    print("Requires active connection to server");
	    return;
	}
	
	socket.send(new MoveMessage(this.dest));
    };

    this.help = function(print) {
	print('move <destination>');
    };

}

function ExamineCommand(args) {
    this.target = args[1];
    this.type = args[0];

    this.invoke = function (print, socket) {
	if (!socket.isConnected()){
	    print("Requires active connection to server");
	    return;
	}
	if (args.length == 1) {
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
