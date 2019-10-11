#include "string.h"
#include <gtest/gtest.h>

TEST(test_strlen_function, cstring_literals)
{
    ASSERT_EQ(0, dtf::strlen(""));
    ASSERT_EQ(1, dtf::strlen("A"));
    ASSERT_EQ(6, dtf::strlen("Artyom"));
}

TEST(test_strlen_function, char_arrays)
{
    char surname[] = "Danilov";
    ASSERT_EQ(7, dtf::strlen(surname));
}

TEST(test_strcpy_function, cstring_literal)
{
    char buffer[10];
    const char *name = "Artyomka";
    dtf::strcpy(buffer, name, dtf::strlen(name));
    ASSERT_STREQ(name, buffer);
}

TEST(test_strcpy_function, char_array)
{
    char dest[20];
    char src[15] = "Harry Potter!";
    dtf::strcpy(dest, src, dtf::strlen(src));
    ASSERT_STREQ(src, dest);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}