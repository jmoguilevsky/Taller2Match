#include <gtest/gtest.h>

namespace {

class Foo {
public:
	int factorial(int n) {
		if (n < 2) return 1;
		return n * factorial(n-1);
	}
	
	int factorial_mock(int n) {
		return 4;
	}

	Foo() {}
	~Foo() {}
};

// The fixture for testing class Foo.
class FooTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  FooTest() {
    // You can do set-up work for each test here.
  }

  virtual ~FooTest() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Objects declared here can be used by all tests in the test case for Foo.
};

TEST_F(FooTest, MethodHandlesZero) {
  Foo f;
  EXPECT_EQ(1, f.factorial(0));
}

TEST_F(FooTest, MethodHandlesPositiveIntegers) {
  Foo f;
  EXPECT_EQ(2, f.factorial(2));
  EXPECT_EQ(6, f.factorial(3));
  EXPECT_EQ(720, f.factorial(6));

}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
