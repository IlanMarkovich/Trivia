#include "Server.h"
#include <stdlib.h>

int main()
{
	srand(time(NULL));

	Server server;
	server.run();

	return 0;
}
