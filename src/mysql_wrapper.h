#ifndef _MYSQL_WRAPPER_H
#define _MYSQL_WRAPPER_H

#include <stdint.h>
#include <mysql/mysql.h>

namespace cobaya {

class MysqlWrapper {
public:
	MysqlWrapper();
	~MysqlWrapper();

	int Connect();

	int SelectQuery(const char *sql);
	int ModifyQuery(const char *sql);

	char** FetchRow();
	uint64_t GetNumRows();
	uint32_t GetNumFields();

private:
	MYSQL mysql_con;
	MYSQL_RES *mysql_res;
	MYSQL_ROW mysql_row;
};

inline char** MysqlWrapper::FetchRow()
{
	if (!mysql_res)
		return NULL;
	return mysql_fetch_row(mysql_res);
}

inline uint64_t MysqlWrapper::GetNumRows()
{
	if (!mysql_res)
		return 0;
	return mysql_num_rows(mysql_res);
}

inline uint32_t MysqlWrapper::GetNumFields()
{
	if (!mysql_res)
		return 0;
	return mysql_num_fields(mysql_res);
}

} // namespace cobaya

#endif /* _MYSQL_WRAPPER_H */
