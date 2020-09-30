#pragma once

#include <functional>
#include <iostream>
#include <utility>


template<typename Iterator>
class Sorter{
public:
    explicit Sorter(Iterator){}
    Sorter() = default;

    using value_type = typename std::iterator_traits<Iterator>::value_type;
    using Comparator = std::function<bool(value_type&, value_type&)>;

    virtual void sort(Iterator begin, Iterator end, Comparator comp = std::less<value_type>{}) = 0;

    virtual void sort_starting_from_percentage(Iterator begin, Iterator end, int percents, Comparator comp = std::less<value_type>{}){
        if (percents < 0){
            sort(begin, end, comp);
            return;
        } else if (percents > 100){
            return;
        }

        Iterator first = begin + ((end - begin) * percents)/100;
        sort(first, end, comp);
    }

    virtual void sort_starting_from_position(Iterator begin, Iterator end, int position, Comparator comp = std::less<value_type>{}){
        if (position < 0){
            sort(begin, end, comp);
            return;
        } else if (position > end - begin){
            return;
        }

        Iterator first = begin + position;
        sort(first, end, comp);
    }
};


template<typename Iterator>
class QuickSorter : public Sorter<Iterator>{
public:
    using value_type = typename Sorter<Iterator>::value_type;
    using Comparator = std::function<bool(value_type&, value_type&)>;

    void sort(Iterator begin, Iterator end, Comparator comp = std::less<value_type>{}) override{
        /* pi is partitioning index, arr[p] is now
           at right place */
        if (begin == end){
            return;
        }

        Iterator pi = partition(begin, end, comp);


        // Separately sort elements before
        // partition and after partition

        if (pi != begin){
            sort(begin, std::prev(pi), comp);
        }
        if (std::next(pi) != end){
           sort(std::next(pi), end, comp);
        }
    }

private:
    Iterator partition (Iterator begin, Iterator end, Comparator comp)
    {
        value_type pivot = *std::prev(end);
        Iterator i = std::prev(begin);
        for (Iterator j = begin; j != std::prev(end); j++)
        {
            // If current element is smaller than or
            // equal to pivot
            if (comp(*j, pivot))
            {
                i++;    // increment index of smaller element
                std::iter_swap(i, j);
            }
        }
        std::iter_swap(std::next(i), std::prev(end));
        return (i + 1);
    }
};
