/*
 * main.cpp
 *
 *  Created on: 2013-3-26
 *      Author: holy
 */

#include "encapsulation_mysql.h"

using EncapMysql::CEncapMysql;

int main(int argc, char *argv[]) {
	CEncapMysql *con;
	con = new CEncapMysql;
	con->Connect("127.0.0.1", "root", "123456");
	con->SelectQuery("select * from holy.student");
	while (char** r = con->FetchRow())
		printf("%s\t%s\t%s\n", r[0], r[1], r[2]);
	return 0;
}
