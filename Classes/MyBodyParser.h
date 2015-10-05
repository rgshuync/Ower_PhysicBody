//
//  MyBodyParser.h
//  guny
//
//  Created by NguyenHuy on 7/29/15.
//
//

#ifndef __guny__MyBodyParser__
#define __guny__MyBodyParser__

#include <stdio.h>

#endif /* defined(__guny__MyBodyParser__) */

#pragma once

#include <string>
#include "cocos2d.h"
USING_NS_CC;
#include "json/document.h"

class MyBodyParser {
    MyBodyParser(){}
    rapidjson::Document doc;
public:
    static MyBodyParser* getInstance();
    bool parseJsonFile(const std::string& pFile);
    bool parse(unsigned char* buffer, long length);
    void clearCache();
    PhysicsBody* bodyFormJson(Node* pNode, const std::string& name);
};