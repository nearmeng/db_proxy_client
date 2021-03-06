#ifndef _DB_PROXY_CLIENT_H_
#define _DB_PROXY_CLIENT_H_

#include "redis_def.h"
#include "hiredis.h"

typedef void(*DB_PROXY_CLIENT_MSG_CALLBACK)(uint64_t qwCoroID, const char* pBuffer, size_t dwSize);

class IInitInterface 
{
public:
	virtual BOOL send_to_dbproxy(int32_t nMsgID, char* pData, int32_t nSize, uint64_t qwCoroID) = 0;
	virtual BOOL register_msg(int32_t nMsgID, DB_PROXY_CLIENT_MSG_CALLBACK callback) = 0;
};

class CDBProxyClient
{
public:
	CDBProxyClient() {};
	~CDBProxyClient() {};

	BOOL init(IInitInterface* pInit, BOOL bResume);
	BOOL uninit(void);
	BOOL mainloop(void);
	inline static CDBProxyClient& instance();

    BOOL redis_command(int32_t nCmdID, const char* pUserData, size_t dwUserDataLen, const char* format, ...);
    BOOL redis_eval(int32_t nCmdID, const char* pUserData, size_t dwUserDataLen, const char* pszScript, const char* format, ...);

    BOOL redis_command_coro(const char* format, ...);
    BOOL redis_eval_coro(uint64_t qwCoroID, const char* pszScript, const char* format, ...);

    inline BOOL reg_redis_callback(int32_t nCmdID, REDIS_CMD_CALLBACK pCallBack);
    inline REDIS_CMD_CALLBACK get_redis_callback(int32_t nCmdID);

private:
    BOOL _pack_redis_command(char* pPackedBuffer, int32_t &nPackedSize, const char* format, va_list valist);
    BOOL _pack_redis_eval_script(char*& pPackedBuffer, int32_t &nPackedSize, const char* pcszScript);

    BOOL _command(uint64_t qwCoroID, int32_t nCmdID, const char* pUserData, size_t dwUserDataLen, const char* pcszScript, const char* format, va_list args);

private:
    static CDBProxyClient ms_Instance;
    
	IInitInterface* m_pInit;
    REDIS_CMD_CALLBACK m_RedisHandler[MAX_CMD_HANDLER_COUNT];
};

inline CDBProxyClient& CDBProxyClient::instance()
{
	return ms_Instance;
}

inline BOOL CDBProxyClient::reg_redis_callback(int32_t nCmdID, REDIS_CMD_CALLBACK pCallBack)
{
    int32_t nRetCode = 0;

    LOG_PROCESS_ERROR(pCallBack);
    LOG_PROCESS_ERROR(nCmdID > 0 && nCmdID < MAX_CMD_HANDLER_COUNT);
    LOG_PROCESS_ERROR(m_RedisHandler[nCmdID] == NULL);

    m_RedisHandler[nCmdID] = pCallBack;

    return TRUE;
Exit0:
    return FALSE;
}

inline REDIS_CMD_CALLBACK CDBProxyClient::get_redis_callback(int32_t nCmdID)
{
    LOG_PROCESS_ERROR(nCmdID > 0 && nCmdID < MAX_CMD_HANDLER_COUNT);

    return m_RedisHandler[nCmdID];
Exit0:
    return NULL;
}

#endif