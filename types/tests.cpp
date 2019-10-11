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

TEST(test_strcpy_function, _)
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

TEST(test_strequal_function, _)
{
    const char *name = "Malfoy";
    const char *other_name = "Malfoy";
    ASSERT_TRUE(dtf::strequal(name, other_name));
}

TEST(test_dtf_string_class, equal_operator)
{
    ASSERT_TRUE(dtf::string("Ron") == "Ron");
    ASSERT_TRUE("Ron" == dtf::string("Ron"));
    ASSERT_TRUE(dtf::string("Ron") == dtf::string("Ron"));
}

TEST(test_dtf_string_class, notequal_operator)
{
    ASSERT_TRUE(dtf::string("Weasley") != "Granger");
    ASSERT_TRUE("Weasley" != dtf::string("Malfoy"));
    ASSERT_TRUE(dtf::string("Ron") != dtf::string("Draco"));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}