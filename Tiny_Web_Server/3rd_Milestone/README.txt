=====================================
===========Tiny web server===========
=====================================

+++++++++++1st mile stone++++++++++++
* the given script tiny.c is compiled with csapp.c and csapp.h with -pthread library in gcc command (see Makefile)
* cgi-bin folder was created and adder binary is created (see Makefile)
* run tiny server binary
  ./tinyserver 1025
where 1025 is port number
* go to browser and type
  127.0.0.1:1025/image.jpg
to see pillars of creation (image.jpg)
  127.0.0.1:1025/cgi-bin/adder?10&27
to see addition result

++++++++++++2nd mile stone++++++++++++
* run 
	make all
on  terminal
* run 
	./tinyserver 1025
* open browser and type
	127.0.0.1:1025/cgi-bin/delay?10
 this runs a thread whos sole purpose is to delay itself for 10 seconds
* during this time you can open another tab and type
	127.0.0.1:1025/image.jpg
which will display image while the previous thread was running
hence threaded version of the tiny server was created.

++++++++++++++3rd milestone+++++++++++++
*threaded and queue version of the server has been created
*run 
	make all
	./tinyserver 1025
*in new terminal run
	./clients.sh
*ull see messages posted by producers and consumers indicating status of execution

+++++++++++++final milestone+++++++++++++
*prioritized version of server is created with main thead with highest priority
*a shell script for creating clients is written which opens dillo web browser and opens several tabs. the problem found with sillo is that it doesnt request server for new urls when it is waiting for 6 responses. so the same shell script can be made to run from two different terminals while the server is running.
*this will requst many requests at same time and server prints the queue is full.

	
