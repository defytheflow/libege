#include "task1.h"
#include "common.h"


int wh_nums_btwn(int begin, const char *beg_op, const char *end_op, int end)
{
    int count{};
    if (beg_op == "<" && end_op == "<")
    {
        for (++begin; begin < end; ++begin) ++count;
        return count;
    }
    else if (beg_op == "<=" && end_op == "<=")
    {
        for (; begin <= end; ++begin) ++count;
        return count;
    }
    else if (beg_op == "<" && end_op == "<=")
    {
        for(++begin; begin <= end; ++begin) ++count;
        return count;           
    }
    else if (beg_op == "<=" && end_op == "<")
    {
        for (; begin < end; ++begin) ++count;
        return count;
    }
    else 
        error("Unknown operators inside wh_numb_btwn()");
}
