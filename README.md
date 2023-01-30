to compile server : gcc server.c -o server 

to compile cli.c : gcc cli.c -o cli

to compile cliudp.c : gcc cliudp.c -o cliudp

to run every thing :
./server 5000 (for server)
./cli 127.0.0.1 5000 (for tcp client)
./cliudp 127.0.0.1 5000 (for udp client)
