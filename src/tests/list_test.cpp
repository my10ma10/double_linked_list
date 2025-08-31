#include "list_test.hpp"

TEST_F(ListFixture, empty_list_test) {
    EXPECT_TRUE(empty_List.empty());
    EXPECT_TRUE(ininList_List != empty_List);
    
    // EXPECT_EQ(empty_List.begin().getNodePtr(), nullptr);
    // EXPECT_EQ(empty_List.end().getNodePtr(), nullptr);
    
    EXPECT_THROW(empty_List.front(), std::out_of_range);
    EXPECT_THROW(empty_List.back(), std::out_of_range);

    empty_List.push_back(10);
    EXPECT_EQ(empty_List.front(), 10);
    EXPECT_EQ(empty_List.back(), 10);

    empty_List.push_front(3);
    EXPECT_EQ(empty_List.front(), 3);
    EXPECT_EQ(empty_List.back(), 10);

    empty_List.pop_back();
    EXPECT_EQ(empty_List.front(), 3);
    EXPECT_EQ(empty_List.back(), 3);
    
    empty_List.pop_front();
    EXPECT_TRUE(empty_List.empty());
}

TEST_F(ListFixture, push_methods_test) {
    ininList_List.push_back(5);
    EXPECT_EQ(ininList_List.back(), 5);

    ininList_List.push_front(-5);
    EXPECT_EQ(ininList_List.front(), -5);
}

TEST_F(ListFixture, pop_methods_test) {
    ininList_List.pop_back();
    EXPECT_EQ(ininList_List.back(), 3);

    ininList_List.pop_front();
    EXPECT_EQ(ininList_List.front(), 2);

    EXPECT_THROW(empty_List.pop_front(), std::out_of_range);
    EXPECT_THROW(empty_List.pop_back(), std::out_of_range);
}

TEST_F(ListFixture, default_cons) {
    List<int> list;
    EXPECT_TRUE(list.empty());

    List<int> list2 = {};
    EXPECT_TRUE(list2.empty());

    EXPECT_TRUE(list == list2);
}

TEST_F(ListFixture, self_assignment) {
    List<int> list = {1, 2, 3, 4};
    list = list;

    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 4);
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

TEST_F(ListFixture, operators_test) {
    List<int> other = {1, 2, 3, 4};
    EXPECT_TRUE(other == ininList_List);
}

TEST_F(ListFixture, insert_test) {
    List<int> list = {1, 2, 3, 4};

    /// insert
    list.insert(list.begin(), -1);
    EXPECT_EQ(list.front(), -1);

    list.insert(list.end(), 5);
    EXPECT_EQ(list.back(), 5);

    list.insert(list.begin() + 2, 5);
    auto insert_it = list.begin() + 2;    
    EXPECT_EQ(*insert_it, 5);


    list = {1, 2, 3, 4};
    std::initializer_list<int> other = {5, 6, 7};
    List<int> res = {5, 6, 7, 1, 2, 3, 4};

    list.insert(list.begin(), other);

    EXPECT_EQ(list, res);
}

TEST_F(ListFixture, erase_test) {
    List<int> list = {1, 2, 3, 4};
    
    list.erase(list.begin() + 1);
    auto erase_it = list.begin() + 1;
    EXPECT_EQ(*erase_it, 3);

    list = {1, 2, 3, 4};
    list.erase(list.begin(), list.begin() + 3);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 4);


    ininList_List.erase(ininList_List.begin());
    EXPECT_EQ(ininList_List.front(), 2);
    
    ininList_List.erase(ininList_List.end());
    EXPECT_EQ(ininList_List.back(), 2);
}

TEST_F(ListFixture, merge_test) {
    List<int> list = {1, 2, 3};
    List<int> other = {4, 5, 6};
    list.merge(other);
    List<int> res = {1, 2, 3, 4, 5, 6};
    EXPECT_EQ(list, res);

    list = {};
    list.merge(other);
    res = {4, 5, 6};
    EXPECT_EQ(list, res);
}

TEST_F(ListFixture, clear_test) {
    List<int> list = {1, 2, 3, 4};
    list.clear();
    List<int> res {};
    
    EXPECT_EQ(list.size(), 0);
    EXPECT_EQ(list, res);
}

TEST_F(ListFixture, sort_test) {
    List<int> list = {-3, 2, 0, -5, 11};
    list.sort();
    List<int> res = {-5, -3, 0, 2, 11};
    EXPECT_EQ(list, res);
    
    list = {4, 3, 2, 0};
    list.sort();
    res = {0, 2, 3, 4};

    EXPECT_EQ(list, res);
}

TEST_F(ListFixture, reverse_test) {
    List<int> list = {1, 2, 3, 4};
    list.reverse();
    List<int> res = {4, 3, 2, 1};

    EXPECT_EQ(list, res);

    list = {};
    list.reverse();

    EXPECT_EQ(list, empty_List);
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