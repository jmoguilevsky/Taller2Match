//
// Created by chris on 28/04/16.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "../testsClasses/HttpRequestTest.h"
#include "../testsClasses/utilsTests.h"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
