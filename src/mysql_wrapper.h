#ifndef _MYSQL_WRAPPER_H
#define _MYSQL_WRAPPER_H

#include <iostream>
#include <cassert>
#include <set>
#include <sys/shm.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <time.h>
#include <stdlib.h>
#include <memory>
#include <iconv.h>
#include <dlfcn.h>
#include <mysql/mysql.h>

namespace cobaya {

using namespace std;

#define ERRMSG1(fmt,...) \
	sprintf(m_szErrMsg, fmt, __VA_ARGS__)
#define ERRMSG2(fmt, args...) \
	sprintf(m_szErrMsg, "[%s 第 %d 行 ]; "fmt"\r\n" , __FILE__, __LINE__, ##args)

class MysqlWrapper {
	typedef map<string, int> MapFieldNameIndex;
public:
	MysqlWrapper();
	~MysqlWrapper();
public:

	int Connect(const char *ip, const char *user, const char *passwd);

	void CloseConnect();

	int SelectQuery(const char* szSQL);

	int ModifyQuery(const char* szSQL);

	const char* GetErrMsg();

	char** FetchRow();

	char* GetField(const char* szFieldName);

////////连接池那个类需要用到这3个函数。  2011-01-20
public:
	void SetUsed();
	void SetIdle();
	bool IsIdle(); //返回 true 标识 Idle
private:
	bool m_bUseIdle;    // true: use;   false:idle

private:

	bool IsConnected();

	void SetConnected(bool bTrueFalse);

	char* GetField(unsigned int iFieldIndex);

	void FreePreResult();

	int ReConnect();

	void SaveParam(const char* szDbIp, const char* szUser,
			const char* szPassword);

public:
	/* 数据库连接了吗?   true--已经连接;  false--还没有连接 */
	bool m_bConnected;

	/* 函数出错后, 错误信息放在此处 */
	char m_szErrMsg[1024];

	/* 字段个数 */
	int m_iFields;

	/* 是一个map,  key是字段名,  value是字段索引 */
	MapFieldNameIndex m_mapFieldNameIndex;

public:
	MYSQL m_connection;	//连接
	MYSQL_RES* m_result;	//结果集指针
	MYSQL_ROW m_row;	//一行,  typedef char **MYSQL_ROW;

private:
	string m_sDbIp;		//数据库服务器IP
	string m_sUser;		//用户名
	string m_sPassword;	//口令
};

} // namespace cobaya

#endif /* _MYSQL_WRAPPER_H */
