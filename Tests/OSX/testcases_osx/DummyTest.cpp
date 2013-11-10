#include "gtest/gtest.h"

#define private public
#define protected public
#include <PlaygroundOSS/CKLBNode.h>
#undef protected
#undef private

/**
 * Dummy test case for checking test runner is running properly or not.
 */
TEST(OSXDummyTest, AlwaysPass)
{
    EXPECT_TRUE(1);
}
