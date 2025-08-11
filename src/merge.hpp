#pragma once
#include <iostream>

template <typename T>
class List;

template <typename T>
List<T> mergeSort(const List<T>& coll) {
    if (coll.size() == 1) {
        return coll;
    }
    List<T> left(coll.begin(), coll.begin() + coll.size() / 2);
    List<T> right(coll.begin() + coll.size() / 2 , coll.end());

    left = mergeSort(left);
    right = mergeSort(right);
    return merge(left, right);;
}

template <typename T>
List<T> merge(List<T>& leftColl, List<T>& rightColl) {
    List<T> res;

    while (!leftColl.empty() && !rightColl.empty() ) {
        if (leftColl.front() < rightColl.front()) {
            res.push_back(leftColl.front());
            leftColl.pop_front();
        }
        else {
            res.push_back(rightColl.front());
            rightColl.pop_front();
        }        
    }

    if (leftColl.empty()) {
        res.merge(rightColl);
    }    
    else if (rightColl.empty()) {
        res.merge(leftColl);
    }
    return res;
}