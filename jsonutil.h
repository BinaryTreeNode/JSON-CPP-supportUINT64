//
// Created by liyang77 on 2019/12/20.
//

#ifndef ESEARCH_ALL_JSONUTIL_H
#define ESEARCH_ALL_JSONUTIL_H

#include "reader.h"
#include "writer.h"
#include "value.h"
#include "json.h"
//#include "json_value.cpp"
//#include "json_writer.cpp"
//#include "json_reader.cpp"
#include <sharelib/dll/properties.h>
#include <indexlib/common.h>
#include <indexlib/util/log.h>

using namespace sharelib;
using namespace std;

INDEXLIB_BEGIN_NS(index);

class JsonUtil {
public:
    JsonUtil();
    ~JsonUtil() {}

public:
    bool Init();
    static size_t GetFieldCnt(char *src,  std::map<std::string, std::string> &values, std::string id1, std::string id2);
    static size_t GetFullBuildFieldCnt(char *src,  int fieldCnt,std::map<std::string, std::string> &values, std::string id1, std::string id2);
    static std::string GetDocId(const char *src);
    static uint64_t GetDocTime(const char *src);
    static int GetScore(const char *src);
    static void WriteJson(std::string &result, int code, std::string msg);
private:

    LOG_DECLARE();
};

TYPEDEF_SHARED_PTR(JsonUtil);

INDEXLIB_END_NS(index);

#endif //ESEARCH_ALL_JSONUTIL_H
