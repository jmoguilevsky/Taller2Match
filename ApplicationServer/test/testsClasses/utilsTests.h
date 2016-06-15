//
// Created by mvbattan on 27/04/16.
//

#ifndef APPLICATIONSERVER_UTILSTESTS_H
#define APPLICATIONSERVER_UTILSTESTS_H

#include "../../src/Utilities/util.h"
#include <gtest/gtest.h>

class UtilsTest : public ::testing::Test {
protected:
    UtilsTest() {}
    virtual ~UtilsTest() {}
    virtual void SetUp() {}
    virtual void TearDown() {}
};

TEST_F(UtilsTest, unTest) {
    EXPECT_EQ(true, true);
}

#endif //APPLICATIONSERVER_UTILSTESTS_H
