#include <gtest/gtest.h>
#include "list.hpp"
#include <vector>

class ListFixture : public ::testing::Test {
protected:
    List<int> empty_List{};
    List<int> ininList_List{1, 2, 3, 4};

    void SetUp() override {
    }

    void TearDown() override {

    }
};

