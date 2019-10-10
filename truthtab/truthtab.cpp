#include "truthtab.h"
/*****************************************************************
 *                         CONSTANTS                             *
 *****************************************************************/ 
constexpr wchar_t g_lparen   {L'('};
constexpr wchar_t g_rparen   {L')'};
constexpr wchar_t g_invr     {L'¬'}; // INVERSION == NOT
constexpr wchar_t g_conj     {L'∧'}; // CONJUNCTION == AND
constexpr wchar_t g_disj     {L'∨'}; // DISJUNCTION == OR
constexpr wchar_t g_impl     {L'→'}; // IMPLICATION
constexpr wchar_t g_eqvl[]   {L'≡', L'∼', L'↔'}; // EQUIVALENCE

const std::map<wchar_t, std::string> g_tokenTable = {
    {g_lparen, "LPAREN"},
    {g_rparen, "RPAREN"},
    {g_invr,   "NOT"}, // INVR
    {g_conj,   "AND"}, // CONJ
    {g_disj,   "OR"}, // DISJ
    {g_impl,   "IMPL"},
    {g_eqvl[0], "EQVL"},
    {g_eqvl[1], "EQVL"},
    {g_eqvl[2], "EQVL"},
};
/*****************************************************************
 *                         EXCEPTIONS                            *
 *****************************************************************/ 
class UnknownTokenType {};


std::string tokentype(wchar_t lex);
std::wstring rm_spaces(const std::wstring &input);
/*****************************************************************
 *                    USER-DEFINED TYPES                         *
 *****************************************************************/
class Token
{
    public:
        wchar_t m_lex; // lexeme
        std::string m_type;

    public:
        Token(wchar_t lex): m_lex{lex}
        {
            m_type = tokentype(m_lex); 
        } 
};
/*****************************************************************
 *          FORWARD DECLARATIONS OF HELPER FUNCTIONS             *
 *****************************************************************/
std::vector<Token> tokenize(std::wstring &input);
std::string stringify(std::vector<Token> &tokens);
/*****************************************************************
 *                  SYNTAX ANALYZING PART                        *
 *****************************************************************/ 
std::vector<Token> tokenize(std::wstring &input)
{
    std::vector<Token> tokens;
    input = rm_spaces(input);
    tokens.reserve(input.length());

    for (const auto &ch : input)
        tokens.push_back(Token(ch));

    return tokens;
}
std::string parenthesize(std::vector<Token> &tokens)
{
    
}
std::string stringify(std::vector<Token> &tokens)
{
    std::string res;
    res.reserve(tokens.size());

    for (const auto &token : tokens)
        res.append(token.m_type + " ");
    return res;
}
std::string tokentype(wchar_t lex)
{
    try
    {
        return g_tokenTable.at(lex);
    }
    catch(const std::out_of_range& e)
    {
        if (isalpha(lex)) return "IDEN";
        throw UnknownTokenType();
    }
}
/*****************************************************************
 *        DEFINITIONS OF THE MAIN PUBLIC FUNCTIONS               *
 *****************************************************************/
std::string parse(std::wstring input)
{
    std::vector<Token> tokens = tokenize(input);
    return stringify(tokens);
} 
// std::string tokenize(std::wstring input) // throws UnknownTokenType
// {   
//     input = rm_spaces(input);
//     std::string res;
//     for (const auto &token : input)
//     {
//         try
//         {
//             std::string stoken {g_tokenTable.at(token)};
//             res.append(stoken + " ");
//         }
//         catch(const std::out_of_range& e)
//         {
//             // At this moment only identifiers are left, which are
//             // single alphabet letters, so if it something else we throw an exception.
//             char ctoken = static_cast<char>(token);
//             if (isalpha(ctoken) || ')' || '(') // TODO
//                 res.append(std::string(1, ctoken) + " ");
//             else 
//                 throw UnknownTokenType(); 
//         }
//     }
//     return res;
// }
/*****************************************************************
 *               DEFINITIONS OF HELPER FUNCTIONS                 *
 *****************************************************************/ 
std::wstring rm_spaces(const std::wstring &input)
{
    std::wstring res;
    for (const auto &ch : input)
    {
        if (!isblank(ch)) 
            res.push_back(ch);
    }
    return res;
}

