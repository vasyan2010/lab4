//
// Created by admin on 19.05.2019.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "floyd.h"

using testing::Eq;
namespace {
    class ClassDeclaration:public testing::Test{
    public:
        cities pulkovo;
        ClassDeclaration(){
            pulkovo;
        }
    };
}

TEST_F(ClassDeclaration, nameOfTheTest1){
    char str1[]="New York;Los Angeles;10;20";
    char str2[]="Los Angeles;Chicago;40;35";
    char str3[]="New York;Chicago;14;N/A";
    char str4[]="San Diego;Chicago;13;8";
    char str5[]="San Diego;New York;N/A;20";
    pulkovo.parser(str1);
    pulkovo.parser(str2);
    pulkovo.parser(str3);
    pulkovo.parser(str4);
    pulkovo.parser(str5);
    pulkovo.floudAlgoritm();
    if (pulkovo.way(1,2)==34)
        SUCCEED();
    else
        FAIL();
}

TEST_F(ClassDeclaration, nameOfTheTest2){
    char str1[]="New York;Los Angeles;10;20";
    char str2[]="Los Angeles;Chicago;40;35";
    char str3[]="New York;Chicago;14;N/A";
    char str4[]="San Diego;Chicago;13;8";
    char str5[]="San Diego;New York;N/A;20";
    pulkovo.parser(str1);
    pulkovo.parser(str2);
    pulkovo.parser(str3);
    pulkovo.parser(str4);
    pulkovo.parser(str5);
    pulkovo.floudAlgoritm();
    if (pulkovo.way(2,2)==-1)
        SUCCEED();
    else
        FAIL();
}
TEST_F(ClassDeclaration, nameOfTheTest3){
    char str1[]="New York;Los Angeles;10;20";
    char str2[]="Los Angeles;Chicago;40;35";
    char str3[]="New York;Chicago;14;N/A";
    char str4[]="San Diego;Chicago;13;8";
    char str5[]="San Diego;New York;N/A;20";
    pulkovo.parser(str1);
    pulkovo.parser(str2);
    pulkovo.parser(str3);
    pulkovo.parser(str4);
    pulkovo.parser(str5);
    pulkovo.floudAlgoritm();
    if (pulkovo.way(2,22)==-1)
        SUCCEED();
    else
        FAIL();
}