Bin Bin::operator+(Bin const &other) const
{
    throw NotImplementedYet();
    char carry {'0'};
    bool this_neg {isneg(m_sval)};
    bool other_neg {isneg(other.get_sval())};
    
    std::string res_sval;
    std::string this_sval {rm_prefix(this->m_sval)};
    std::string other_sval {rm_prefix(other.get_sval())};
    // ---------------------------------------------------------------------
    // Make them eqal in length by padding zeros in front of the lesser one.
    while (other_sval.length() < this_sval.length())
    {
        other_sval.insert(0, "0");
    }
    while (this_sval.length() < other_sval.length())
    {
        this_sval.insert(0, "0");
    }
    // ----------------------------------------------------------------------
    std::reverse(this_sval.begin(), this_sval.end());
    std::reverse(other_sval.begin(), other_sval.end());
    // ----------------------------------------------------------------------
    for (int i = 0, length = this_sval.length(); i < length; ++i)
    {
        if (this_sval[i] == '0' && other_sval[i] == '0')
        {
            switch (carry)
            {
                case '0':
                    res_sval.push_back('0');
                    break;
                case '1':
                    res_sval.push_back('1');
                    carry = '0';
                    break;
            }
        }
        else if (this_sval[i] == '0' && other_sval[i] == '1')
        {
            switch (carry)
            {
                case '0':
                    res_sval.push_back('1');
                    break;
                case '1':
                    res_sval.push_back('0');
                    carry = '1';
                    break;
            }
        }
        else if (this_sval[i] == '1' && other_sval[i] == '0')
        {
            switch (carry)
            {
                case '0':
                    res_sval.push_back('1');
                    break;
                case '1':
                    res_sval.push_back('0');
                    carry = '1';
                    break;
            }
        }
        else if (this_sval[i] == '1' && other_sval[i] == '1')
        {
            switch (carry)
            {
                case '0':
                    res_sval.push_back('0');
                    carry = '1';
                    break;
                case '1':
                    res_sval.push_back('1');
                    carry = '1';
                    break;
            }
        }
    }
    if (carry == '1')
    {
        res_sval.push_back('1');
    }
    // ----------------------------------------------------------------------
    std::reverse(res_sval.begin(), res_sval.end());
    
    if (this_neg && other_neg)
        return Bin{NEG_BIN_PREFIX  + res_sval};
    else if (!this_neg && !other_neg)
        return Bin{POS_BIN_PREFIX + res_sval};
}