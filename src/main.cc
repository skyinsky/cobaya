#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "mysql_wrapper.h"
#include "rpc.h"

int main(int argc, char *argv[])
{
	using namespace cobaya;

	int res;

	RpcServer server;
	
	res = server.Init();
	res = server.AddEndpoint("127.0.0.1", 44333);
	res = server.CreateThreadPool(4);
	res = server.StartServer();
	
	// Wait for clients.
	std::cout << "Press Enter to exit." << std::endl;
	std::cin.get();

	server.StopServer();

	return 0;
}
