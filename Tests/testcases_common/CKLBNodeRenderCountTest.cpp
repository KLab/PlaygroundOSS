#include "gtest/gtest.h"

#define private public
#define protected public
#include <PlaygroundOSS/CKLBNode.h>
#undef protected
#undef private

/**
 * Regression test for https://github.com/KLab/PlaygroundOSS/pull/51
 */
TEST(CKLBNodeRenderCountTest, Increment)
{
	CKLBNode *node = new CKLBNode();
	node->setRenderSlotCount(2);
	EXPECT_EQ(2, node->m_renderCount);
	node->setRenderSlotCount(3);
	EXPECT_EQ(3, node->m_renderCount);
}

TEST(CKLBNodeRenderCountTest, NoChange)
{
	CKLBNode *node = new CKLBNode();
	node->setRenderSlotCount(2);
	EXPECT_EQ(2, node->m_renderCount);
	node->setRenderSlotCount(2);
	EXPECT_EQ(2, node->m_renderCount);
}

TEST(CKLBNodeRenderCountTest, Decrement)
{
	CKLBNode *node = new CKLBNode();
	node->setRenderSlotCount(2);
	EXPECT_EQ(2, node->m_renderCount);
	node->setRenderSlotCount(1);
	EXPECT_EQ(1, node->m_renderCount);
}
