#include "gmock/gmock.h"
#include <iostream>


class TestCaseFixture : public testing::Test {
public:

};

using namespace std;
TEST_F(TestCaseFixture, TestDescription) {
	cout << "DUPA";

}

