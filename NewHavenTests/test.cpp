#include "pch.h"
#include "../Resources.h"

TEST(ResourcePool, ResourcePoolToString) {
    ResourcePool pool = ResourcePool(0, 1, 2, 3);
    ASSERT_STREQ(pool.toString().c_str(), "ResourcePool(meadow: 0, forest: 1, quarry: 2, wheat: 3)");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}