#ifndef __SSDB_CLIENT_H__
#define __SSDB_CLIENT_H__

#include <vector>
#include <string>
#include <unordered_map>
#include <stdint.h>

/*  同步ssdb client api   */

struct buffer_s;

namespace ssdb {

class SSDBProtocolResponse;
class SSDBProtocolRequest;

class Status
{
public:
    Status(){}
    Status(const std::string& code)
    {
        mCode = code;
    }

    int             not_found() const
    {
        return mCode == "not_found";
    }

    int             ok() const
    {
        return mCode == "ok";
    }

    int             error() const
    {
        return mCode != "ok";
    }

    std::string     code() const
    {
        return mCode;
    }

private:
    std::string     mCode;
};

class SSDBClient
{
public:
    SSDBClient();
    ~SSDBClient();

    void                    disConnect();
    void                    connect(const char* ip, int port);
    bool                    isConnect() const;
    Status                 auth(const std::string& key);

    void                       execute(const char* str, int len);
    Status                  info(std::vector<std::string> *ret);

    Status                  set(const std::string& key, const std::string& val);
    Status                  setx(const std::string &key, const std::string &val, int ttl);

    Status                  get(const std::string& key, std::string *val);

    Status                  del(const std::string& key);
    Status                  multiDel(const std::vector<std::string> &keys);

    Status                  incr(const std::string &key, int64_t incrby, int64_t *ret);

    Status                  hset(const std::string& name, const std::string& key, std::string val);
    Status                  hdel(const std::string& name, const std::string& key);
    Status                  multiHset(const std::string& name, const std::unordered_map<std::string, std::string> &kvs);
    Status                  hget(const std::string& name, const std::string& key, std::string *val);
    Status                  multiHget(const std::string& name, const std::vector<std::string> &keys, std::vector<std::string> *ret);
    Status                  multiHdel(const std::string &name, const std::vector<std::string> &keys);

    Status                  zset(const std::string& name, const std::string& key, int64_t score);

    Status                  zget(const std::string& name, const std::string& key, int64_t *score);

    Status                  zsize(const std::string& name, int64_t *size);

    Status                  zkeys(const std::string& name, const std::string& key_start,
                                  int64_t score_start, int64_t score_end,uint64_t limit, std::vector<std::string> *ret);

    Status                  zscan(const std::string& name, const std::string& key_start,
                                  int64_t score_start, int64_t score_end,uint64_t limit, std::vector<std::string> *ret);

    Status                  scan(const std::string &key_start, const std::string &key_end,
                                 uint64_t limit, std::vector<std::string> *ret);

    Status                  zclear(const std::string& name);
    Status                  hclear(const std::string& name);

    Status                  qpush(const std::string& name, const std::string& item);
    Status                  qpop(const std::string& name, std::string* item);
    Status                  qslice(const std::string& name, int64_t begin, int64_t end, std::vector<std::string> *ret);
    Status                  qclear(const std::string& name);

private:
    SSDBClient(const SSDBClient&);
    void operator=(const SSDBClient&);

private:
    void                    request(const char*, int len);
    int                     send(const char* buffer, int len);
    void                    recv();

private:
    buffer_s*               m_recvBuffer;
    SSDBProtocolResponse*   m_reponse;
    SSDBProtocolRequest*    m_request;

    int                     m_socket;

    std::string             m_ip;
    int                     m_port;
};

}//end namespace

#include <inttypes.h>
static inline std::string str(int64_t v)
{
    char buf[21] = {0};
    snprintf(buf, sizeof(buf), "%" PRId64 "", v);
    return std::string(buf);
}

#endif
