#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <set>
#include <map>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include "mysql_wrapper.h"

namespace cobaya {

MysqlWrapper::MysqlWrapper() {
	SetConnected(false);
	//把结果集置为空
	m_result = NULL;
	//初始化连接
	mysql_init(&m_connection);
}
MysqlWrapper::~MysqlWrapper() {
	//释放上一次的结果集
	FreePreResult();
	//关闭数据库连接
	CloseConnect();
}

int MysqlWrapper::Connect(const char* szDbIp, const char* szUser,
		const char* szPassword) {
	SaveParam(szDbIp, szUser, szPassword);
	//先判断是否已经连接了, 防止重复连接
	if (IsConnected())
		return 0;
	//连接数据库
	if (mysql_real_connect(&m_connection, szDbIp, szUser, szPassword, NULL, 0,
			NULL, 0) == NULL) {
		ERRMSG2("%s", mysql_error(&m_connection));
		return -1;
	}
	printf("[mysql] conn to %s [user:%s] success!\r\n", szDbIp, szUser);
	//设置连接标志为 true
	SetConnected(true);
	return 0;
}

void MysqlWrapper::CloseConnect() {
	//不论m_connection曾经是否连接过， 这样关闭都不会有问题
	mysql_close(&m_connection);
	SetConnected(false);
}

int MysqlWrapper::SelectQuery(const char* szSQL) {
	//如果查询串是空指针,则返回
	if (szSQL == NULL) {
		ERRMSG2("%s", "szSQL==NULL");
		return -1;
	}
	//如果还没有连接,则返回
	if (!IsConnected()) {
		ERRMSG2("%s", "还没有建立连接");
		return -2;
	}
	try //这些语句与连接有关，出异常时就重连
	{
		//查询
		if (mysql_real_query(&m_connection, szSQL, strlen(szSQL)) != 0) {
			ERRMSG2("%s", mysql_error(&m_connection));
			printf("%s", mysql_error(&m_connection));
			printf("ReConnect()  is called, select111  !!!***\r\n");
			int nRet = ReConnect();
			if (nRet != 0)
				return -3;
			//
			if (mysql_real_query(&m_connection, szSQL, strlen(szSQL)) != 0)
				return -33;
			//
		}
		//释放上一次的结果集
		FreePreResult();
		//取结果集
		m_result = mysql_store_result(&m_connection);
		if (m_result == NULL) {
			ERRMSG2("%s", mysql_error(&m_connection));
			return -4;
		}
	} catch (...) {
		printf("ReConnect()  is called, select  !!!***\r\n");
		ReConnect();
		return -5;
	}
	//取字段的个数
	m_iFields = mysql_num_fields(m_result);
	m_mapFieldNameIndex.clear();
	//取各个字段的属性信息
	MYSQL_FIELD *fields;
	fields = mysql_fetch_fields(m_result);
	//把字段名字和索引保存到一个map中
	for (unsigned int i = 0; i < m_iFields; i++) {
		m_mapFieldNameIndex[fields[i].name] = i;
	}
	return 0;
}

int MysqlWrapper::ModifyQuery(const char* szSQL) {
	//如果查询串是空指针,则返回
	if (szSQL == NULL) {
		ERRMSG2("%s", "szSQL==NULL");
		return -1;
	}
	//如果还没有连接,则返回
	if (!IsConnected()) {
		ERRMSG2("%s", "还没有建立连接");
		return -2;
	}
	try //这些语句与连接有关，出异常时就重连
	{
		//查询, 实际上开始真正地修改数据库
		if (mysql_real_query(&m_connection, szSQL, strlen(szSQL)) != 0) {
			ERRMSG2("%s", mysql_error(&m_connection));
			return -3;
		}
	} catch (...) {
		printf("ReConnect()  is called  ,modify!!!***\r\n");
		ReConnect();
		return -5;
	}
	return 0;
}

char** MysqlWrapper::FetchRow() {
	//如果结果集为空,则直接返回空; 调用FetchRow之前, 必须先调用 SelectQuery(...)
	if (m_result == NULL)
		return NULL;
	//从结果集中取出一行
	m_row = mysql_fetch_row(m_result);
	return m_row;
}

char* MysqlWrapper::GetField(const char* szFieldName) {
	return GetField(m_mapFieldNameIndex[szFieldName]);
}

char* MysqlWrapper::GetField(unsigned int iFieldIndex) {
	//防止索引超出范围
	if (iFieldIndex >= m_iFields)
		return NULL;
	return m_row[iFieldIndex];
}

void MysqlWrapper::FreePreResult() {

	if (m_result != NULL) {
		mysql_free_result(m_result);
		m_result = NULL;
	}
}

const char* MysqlWrapper::GetErrMsg() {
	return m_szErrMsg;
}

bool MysqlWrapper::IsConnected() {
	return m_bConnected;
}

void MysqlWrapper::SetConnected(bool bTrueFalse) {
	m_bConnected = bTrueFalse;
}

void MysqlWrapper::SaveParam(const char* szDbIp, const char* szUser,
		const char* szPassword) {
	m_sDbIp = szDbIp; //数据库服务器IP
	m_sUser = szUser; //用户名
	m_sPassword = szPassword; //口令
}

int MysqlWrapper::ReConnect() {
	CloseConnect();
	//连接数据库
	if (mysql_real_connect(&m_connection, m_sDbIp.c_str(), m_sUser.c_str(),
			m_sPassword.c_str(), NULL, 0, NULL, 0) == NULL) {
		ERRMSG2("%s", mysql_error(&m_connection));
		return -1;
	}
	//设置连接标志为 true
	SetConnected(true);
	return 0;
}
/////////////////////////  连接池那个类需要用到这3个函数。
void MysqlWrapper::SetUsed() {
	m_bUseIdle = true;
}
void MysqlWrapper::SetIdle() {
	m_bUseIdle = false;
}

//如果空闲，返回true
bool MysqlWrapper::IsIdle() {
	return !m_bUseIdle;
}

} // namespace cobaya
