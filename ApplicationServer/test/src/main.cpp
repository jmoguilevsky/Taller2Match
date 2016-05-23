//
// Created by chris on 28/04/16.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "../testsClasses/HttpRequestTest.h"
#include "../testsClasses/utilsTests.h"

TEST(TestCase, MyTest1) {
	ASSERT_EQ(util::sum(1, 2), 5);
}

TEST(TestCase, MyTest2) {
	ASSERT_EQ(2, 2);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
