#include "list_test.hpp"

TEST_F(ListFixture, empty_list_test) {
    EXPECT_TRUE(empty_List.empty());
    
    EXPECT_EQ(empty_List.begin(), nullptr);
    EXPECT_EQ(empty_List.end(), nullptr);
    
    EXPECT_DEATH(empty_List.front(), "");
    EXPECT_DEATH(empty_List.back(), "");
    
    EXPECT_DEATH(empty_List.pop_front(), "");
    EXPECT_DEATH(empty_List.pop_back(), "");

    empty_List.push_back(10);
    EXPECT_EQ(empty_List.front(), 10);
    EXPECT_EQ(empty_List.back(), 10);

    empty_List.push_front(3);
    EXPECT_EQ(empty_List.front(), 3);
    EXPECT_EQ(empty_List.back(), 10);

    empty_List.pop_front();
    EXPECT_EQ(empty_List.front(), 10);
    EXPECT_EQ(empty_List.back(), 10);
}

TEST_F(ListFixture, init_list_test) {
    EXPECT_EQ(ininList_List.size(), 4);
    EXPECT_EQ(ininList_List.size(), 4);
}

TEST_F(ListFixture, copy_cons_test) {
    List<int> copy_List{ininList_List};

    EXPECT_TRUE(copy_List == ininList_List);
    EXPECT_EQ(copy_List.size(), 4);
    EXPECT_EQ(copy_List.front(), 1);
    EXPECT_EQ(copy_List.back(), 4);
}

TEST_F(ListFixture, copy_asg_test) {
    List<int> copyAsg_List{};
    copyAsg_List = ininList_List;

    EXPECT_TRUE(copyAsg_List == ininList_List);
    EXPECT_EQ(copyAsg_List.size(), 4);
    EXPECT_EQ(copyAsg_List.front(), 1);
    EXPECT_EQ(copyAsg_List.back(), 4);
}

TEST_F(ListFixture, move_cons_test) {
    List<int> move_List{List<int>{-1, -4, 7}};

    EXPECT_EQ(move_List.size(), 3);
    EXPECT_EQ(move_List.front(), -1);
    EXPECT_EQ(move_List.back(), 7);
}

TEST_F(ListFixture, move_asg_test) {

    List<int> moveAsg_List{};
    moveAsg_List = List<int>{0, -5, 10, 1000};

    
    EXPECT_EQ(moveAsg_List.size(), 4);
    EXPECT_EQ(moveAsg_List.front(), 0);
    EXPECT_EQ(moveAsg_List.back(), 1000);
}

TEST_F(ListFixture, alloc_cons_test) {
    List<int> alloc_list(5, 1);

    EXPECT_EQ(alloc_list.size(), 5);
    EXPECT_EQ(alloc_list.front(), 1);
    EXPECT_EQ(alloc_list.back(), 1);
}



TEST_F(ListFixture, modifying_test) {
    /// insert, erase, merge, clear
    List<int> list = {1, 2, 3, 4};

    /// insert
    list.insert(list.begin(), -1);
    EXPECT_EQ(list.front(), -1);
    list.insert(list.begin() + 2, 5);
    auto insert_it = list.begin() + 2;
    EXPECT_EQ(insert_it, 5);
    
    
    /// erase
    list = {1, 2, 3, 4};
    list.erase(list.begin() + 1);
    auto erase_it = list.begin() + 1;
    EXPECT_EQ(*erase_it, 3);

    list = {1, 2, 3, 4};
    list.erase(list.begin(), list.begin() + 3);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 4);
}

TEST_F(ListFixture, iterators_test) {
    std::vector<int> expected{1, 2, 3, 4};
    size_t i = 0;

    /// pre-increment
    for (List<int>::Iterator it = ininList_List.begin(); it != ininList_List.end(); ++it, ++i) {
        EXPECT_EQ(*it, expected[i]);
    }

    /// post-increment
    i = 0;    
    for (List<int>::Iterator it = ininList_List.begin(); it != ininList_List.end(); it++, ++i) {
        EXPECT_EQ(*it, expected[i]);
    }

    List<int>::Iterator it = ininList_List.begin() + 3;
    EXPECT_EQ(*it, 4);
    --it;
    EXPECT_EQ(*it, 3);
    it--;
    EXPECT_EQ(*it, 2);


}