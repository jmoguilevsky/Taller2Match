//
// Created by mvbattan on 27/04/16.
//

#ifndef APPLICATIONSERVER_HTTPREQUESTTEST_H
#define APPLICATIONSERVER_HTTPREQUESTTEST_H
#include "../../src/HTTP/HTTPRequest.h"
#include <gtest/gtest.h>

class HttpRequestTest : public ::testing::Test {
protected:
    HttpRequestTest() {}
    virtual ~HttpRequestTest() {}
    virtual void SetUp() {}
    virtual void TearDown() {}
};

TEST_F(HttpRequestTest, otroTest) {
    EXPECT_EQ(true, true);
}

#endif //APPLICATIONSERVER_HTTPREQUESTTEST_H
