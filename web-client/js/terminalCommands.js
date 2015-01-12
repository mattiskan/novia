

function interpret(input) {
    tokens = input.split(" ");
    
    cmd = tokens[0];
    args = tokens.slice(1); // rest of tokens

    switch(cmd) {
    case "help": return new HelpCommand(args); break;
    case "connect": return new ConnectCommand(args); break;
    case "move": return new MoveCommand(args); break;

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
	    print("connect");
	    print("help");

	    print("see help <command> for further help about specific commands");
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
    }

    this.help = function(print) {
	print('connect [ipstring]');
	print('default ip="127.0.0.1:9002"');
    }
}

function MoveCommand(args) {
    this.dest = args[0];

    this.invoke = function (print, socket) {
	if (!socket.isConnected()){
	    print("Requires active conneciton to server");
	    return;
	}
	
	socket.send(new MoveMessage(this.dest));
    };

    this.help = function(print) {
	print('move <destination>');
    };

}
