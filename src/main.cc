#include <stdlib.h>
#include <stdio.h>
#include "mysql_wrapper.h"

int main(int argc, char *argv[])
{
	using namespace cobaya;

	MysqlWrapper *con;

	con = new MysqlWrapper;
	con->Connect("127.0.0.1", "root", "123456");
	con->SelectQuery("select * from holy.student");

	while (char** r = con->FetchRow())
		printf("%s\t%s\t%s\n", r[0], r[1], r[2]);

	return 0;
}
