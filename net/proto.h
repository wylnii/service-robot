/* P2P 程序传输协议*/
#ifndef P2P_PROTOL_H__
#define P2P_PROTOL_H__

// 默认服务器端口
const static int DEFAULT_SERVER_PORT = 6061;
const static int MAX_MESSAGE_SIZE = 512;
typedef unsigned short WORD;
typedef unsigned long DWORD;
enum MessageType
{
	MSGTYPE_LOGIN = 1,
	MSGTYPE_LOGOUT,
	MSGTYPE_GETALLUSER_REQ,
	MSGTYPE_GETALLUSER_ACK,

	MSGTYPE_P2PWANTCALLEETRASHTOME,
	MSGTYPE_P2PSOMEONEWANTCALLYOU,
	MSGTYPE_P2PTRASH,
	MSGTYPE_P2PMSG_REQ,
	MSGTYPE_P2PMSG_ACK,

	MSGTYPE_ONLINE_REQ,
	MSGTYPE_ONLINE_ACK
};

enum NATTypeEnum
{
	NAT_FULL_CONE = 1,
	NAT_RESTRICTED_CONE = 2,
	NAT_PORT_RESTRICTED_CONE =3,
	NAT_SYMMETRIC = 4
};

enum P2PErrCodeEnum
{
	P2PERR_SUCCESS = 0
};

// 客户节点信息
struct stUserNode
{
	char userName[10];
	char ip[16];
	WORD port;
	DWORD natType;
};

//消息头
struct stMessageHead
{
	DWORD	dwMessageType;
	DWORD	dwErrorCode;
};

// Client登录消息
struct stLoginMessage
{
	struct stMessageHead msgHead;
	char userName[10];
	char password[10];
	DWORD natType;
};

// Client注销消息
struct stLogoutMessage
{
	struct stMessageHead msgHead;
	char userName[10];
};

// Client在线用户列表请求[REQ]
struct stAllUserReqMessage
{
	struct stMessageHead msgHead;
	char userName[10];
};

// Server在线用户列表回应[ACK]
struct stAllUserAckMessage
{
	struct stMessageHead msgHead;
	DWORD dwUserCount;
	struct stUserNode userNodeArray[1];
};

struct stOnLineReqMessage
{
	struct stMessageHead msgHead;
	char userName[10];
};

struct stOnLineAckMessage
{
	struct stMessageHead msgHead;
};

// Client向服务器请求"被呼叫者(callee)向自己方向发送UDP打洞"消息
struct stP2PWantCalleeTrashToMeMessage
{
	struct stMessageHead msgHead;
	char calleeName[10];
	char calleeIp[16];
	WORD calleePort;
};

//Server向Client发送"有人(caller)想联系你，应向呼叫者发送UDP打洞"消息
struct stP2PSomeoneWantCallYouMessage
{
	struct stMessageHead msgHead;
	char callerName[10];
	char callerIp[16];
	WORD callerPort;
};

//客户端之间发送打洞消息
struct stP2PTrashMessage
{
	struct stMessageHead msgHead;
};

// 客户端之间发送消息请求[REQ]
struct stP2PMessageReqMessage
{
	struct stMessageHead msgHead;
    char message[128];
};

//客户端之间消息应答[ACK]
struct stP2PMessageAckMessage
{
	struct stMessageHead msgHead;
};

#endif //

