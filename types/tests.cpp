#include "string.h"
#include <gtest/gtest.h>

TEST(test_strlen_function, _)
{
    char surname[] = "Danilov";
    ASSERT_EQ(7, dtf::strlen(surname));
    ASSERT_EQ(0, dtf::strlen(""));
    ASSERT_EQ(1, dtf::strlen("A"));
    ASSERT_EQ(6, dtf::strlen("Artyom"));
}

TEST(test_strcpy_function, char_array)
{
    char dest[20];
    char src[15] = "Harry Potter!";
    dtf::strcpy(dest, src, dtf::strlen(src));
    ASSERT_STREQ(dest, src);
}

TEST(test_strcat_function, _)
{
    char dest[20] = "Hermione";
    const char *surname = " Granger";
    dtf::strcat(dest, surname);
    ASSERT_STREQ(dest, "Hermione Granger");
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}