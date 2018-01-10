#include <gtest/gtest.h>

#include <xbase64/xbase64.h>

#include <iostream>

using namespace std;

TEST(Locking, DISABLED_Test) {
#ifdef XB_LOCKING_ON
	// TODO: Implement test for locking
	ASSERT_TRUE(false);
#else
	// Locking is not compiled in
	ASSERT_TRUE(false);
#endif
}
