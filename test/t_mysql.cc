#include <stdlib.h>
#include <stdio.h>

#include "mysql_wapper.h"

using namespace cobaya;

int main(int argc, char *argv[]) {
	MysqlWrapper *con;
	con = new MysqlWrapper;
	con->Connect("127.0.0.1", "root", "123456");
	con->SelectQuery("select * from 用户");
	while (char** r = con->FetchRow())
		printf("%s\t%s\t%s\n", r[0], r[1], r[2]);
	return 0;
}
