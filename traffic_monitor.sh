#!/bin/sh
mv bin/socket bin/socket.original
socat -t100 -x -v UNIX-LISTEN:bin/socket,mode=777,reuseaddr,fork UNIX-CONNECT:bin/socket.original
