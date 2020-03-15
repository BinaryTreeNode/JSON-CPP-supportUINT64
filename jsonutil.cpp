//
// Created by liyang77 on 2019/12/19.
//

#include "jsonutil.h"

using namespace sharelib;

INDEXLIB_BEGIN_NS(index);

LOG_SETUP(index, JsonUtil);

JsonUtil::JsonUtil(){}
//用于获取实时创建时的索引
size_t JsonUtil::GetFieldCnt(char *src, std::map<std::string, std::string> &values, std::string id1_key, std::string id2_key) {
    std::string strValue(src);

    Json::Reader reader;
    Json::Value value;
    Json::FastWriter fast_writer;


    std::string keyword,op,id;
    int score,id1,id2;
    uint64_t wtabletime;
    if (reader.parse(strValue, value))
    {
        if (value["op"].empty() || value["doc"].empty())
            return 0;
        op = value["op"].asString();
        if (0 == strcmp("del",op.c_str())){
            //del
            values["op"] = op;
            wtabletime = value["time"].asUInt64();
            values["time"] = std::to_string(wtabletime);
            if (value["doc"].isMember("id")){
                id = value["doc"]["id"].asString();
                values["id"] =id;
            }
        }else if (0 == strcmp("add",op.c_str())){
            //add
            if (!value["doc"].isMember("keyword"))
                return 0;
            if (!value["doc"].isMember("keyword") || !value["doc"].isMember("score") ||value["doc"]["keyword"].empty() || value["doc"]["score"].empty()){
                return 1;
            }
            keyword = value["doc"]["keyword"].asString();
            score = value["doc"]["score"].asInt();
            wtabletime = value["doc"]["wtabletime"].asUInt64();
            std::string doc (fast_writer.write(value["doc"]), 0, fast_writer.write(value["doc"]).size()-1);
            values["score"] = std::to_string(score);
            values["keyword"] = keyword;
            values["op"] = op;
            values["doc"] = doc;
            values["time"] = std::to_string(wtabletime);

            if (value["doc"].isMember("id")){
                id = value["doc"]["id"].asString();
                values["id"] =id;
            }
            if (("" != id1_key)&& value["doc"].isMember(id1_key)){
                id1 = value["doc"][id1_key].asInt();
                values["id1"] = std::to_string(id1);
            }

            if (("" != id2_key) && value["doc"].isMember(id2_key)){
                id2 = value["doc"][id2_key].asInt();
                values["id2"] = std::to_string(id2);
            }
        }
    }
    return values.size();
}
//用于获取全量创建时的索引
size_t JsonUtil::GetFullBuildFieldCnt(char *src, int fieldCnt, std::map<std::string, std::string> &values, std::string id1_key, std::string id2_key) {
    std::string strValue(src);

    Json::Reader reader;
    Json::Value value;

    std::string keyword,id;
    int score,id1,id2;

    if (reader.parse(strValue, value))
    {
        keyword = value["keyword"].asString();
        score = value["score"].asInt();
        id = value["id"].asString();
        values["keyword"] = keyword;
        values["score"] = std::to_string(score);
        values["id"] =id;

        if (fieldCnt == 0 ){
            return values.size();
        }else if (fieldCnt == 1 ){
            id1 = value[id1_key].asInt();
            values["id1"] = std::to_string(id1);
        }
        else{
            id1 = value[id1_key].asInt();
            id2 = value[id2_key].asInt();
            //C++中map的insert方法会被直接放弃。不会被覆盖
            values["id2"] = std::to_string(id2);
            values["id1"] = std::to_string(id1);
        }

    }
    return values.size();
}
// 用于获取文档的id
std::string JsonUtil::GetDocId(const char *src) {
    std::string strValue(src);

    Json::Reader reader;
    Json::Value value;

    std::string id;

    if (reader.parse(strValue, value))
    {
        id = value["id"].asString();
    }
    return id;
}
// 用于获取文档的time
uint64_t JsonUtil::GetDocTime(const char *src) {
    std::string strValue(src);

    Json::Reader reader;
    Json::Value value;

    uint64_t time;

    if (reader.parse(strValue, value))
    {
        time = value["wtabletime"].asUInt64();
    }
    return time;
}
int JsonUtil::GetScore(const char *src) {
    std::string strValue(src);
    Json::Reader reader;
    Json::Value value;

    uint64_t score;

    if (reader.parse(strValue, value))
    {
        score = value["score"].asInt();
    }
    return score;
}
void JsonUtil::WriteJson(std::string &result, int code, std::string msg){
    Json::Value root;
    Json::Value arrayObj;
    Json::Value item;

    root["code"] = code;
    root["msg"] = msg;

    result = root.toStyledString();
//    std::string out = root.toStyledString();
//    std::cout << out << std::endl;
}
INDEXLIB_END_NS(index);
