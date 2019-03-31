/**********************************************
 * 算法：经典快速排序
 * 
 * *******************************************/
#include <vector>

template <typename Comparable>
void sort(std::vector<Comparable> & items)
{
    if(items.size() > 1)
    {
        std::vector<Comparable> smaller;
        std::vector<Comparable> same;
        std::vector<Comparable> larger;

        auto chosenItem = items[items.size() / 2];

        for(auto & i : items)
        {
            if(i < chosenItem)
                smaller.push_back(std::move(i));
            else if(i > chosenItem)
                larger.push_back(std::move(i));
            else
                same.push_back(std::move(i));
        }

        sort(smaller);
        sort(larger);

        std::move(begin(smaller), end(smaller), begin(items));
        std::move(begin(same), end(same), begin(items) + smaller.size());
        std::move(begin(larger), end(larger), end(items) - larger.size());
    }
}