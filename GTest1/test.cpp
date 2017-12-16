#include "pch.h"
#include <queue>
#include <algorithm>
#include "deque\deque.h"
#include <fstream>
#include <iostream>
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

template <typename T>
bool eqDeque(const Deque <T>& d1, const std::deque <T>& d2) {
	if (d1.size() != d2.size())
		return false;
	for (int i = 0; i < (int)d1.size(); i++)
		if (d1[i] != d2[i])
			return false;
	return true;
}

const int MAX_SIZE = 1000000;
void InteractiveTest(long long temps, bool eqflag) {
	Deque <int> q1;
	std::deque <int> q2;
	for (long long i = 0; i < temps; i++) {
		int j = rand() % 4, k;
		switch (j) {
		case 0:
			if (q2.size() > MAX_SIZE)
				break;
			k = rand();
			q1.push_front(k);
			q2.push_front(k);
			break;
		case 1:
			k = rand();
			if (q2.size() > MAX_SIZE)
				break;
			q1.push_back(k);
			q2.push_back(k);
			break;
		case 2:
			if (q2.empty())
				break;
			q2.pop_back();
			q1.pop_back();
			break;
		case 3:
			if (q2.empty())
				break;
			q2.pop_front();
			q1.pop_front();
			break;
		default:
			break;
		}
		ASSERT_EQ(q1.size(), q2.size()) << "ERROR___size___ERROR";
		ASSERT_EQ(q1.empty(), q2.empty()) << "ERROR___empty___ERROR";
		if (!q2.empty()) {
			ASSERT_EQ(q1.back(), q2.back()) << "ERROR___back___ERROR";
			ASSERT_EQ(q1.front(), q2.front()) << "ERROR___front___ERROR";
			if (eqflag)
				ASSERT_TRUE(eqDeque(q1, q2)) << "ERROR____EqDeque____ERROR";
			else {
				int k = rand() % q1.size();
				ASSERT_EQ(q1[k], q2[k]) << "ERROR___operator[]___ERROR";
			}
		}
	}
}
TEST(DequeTest, Test1) {
	InteractiveTest(100, true);
}
TEST(DequeTest, Test2) {
	InteractiveTest(1000, true);
}
TEST(DequeTest, Test3) {
	InteractiveTest(10000, true);
}
TEST(DequeTest, Test4) {
	InteractiveTest(100000, false);
}
TEST(DequeTest, Test5) {
	InteractiveTest(1000000, false);
}
TEST(DequeTest, Test6) {
	InteractiveTest(10000000, false);
}
TEST(DequeTest, Test7) {
	InteractiveTest(100000000, false);
}
void IteratorTest(int temps) {
	Deque <int> d1;
	std::deque <int> d2;
	for (int i = 0; i < temps; i++) {
		int k = rand();
		d1.push_back(k);
		d2.push_back(k);
	}
	std::sort(d1.begin(), d1.end());
	std::sort(d2.begin(), d2.end());
	for (int i = 0; i < temps; i++)
		ASSERT_EQ(d1[i], d2[i]) << "ERROR___sort___ERROR";
	for (int i = 1; i < temps; i++)
		ASSERT_TRUE(d1[i - 1] <= d1[i]) << "ERROR___sort_order___ERROR";
}
TEST(IteratorTest, Test1) {
	IteratorTest(10);
}
TEST(IteratorTest, Test2) {
	IteratorTest(100);
}
TEST(IteratorTest, Test3) {
	IteratorTest(1000);
}
TEST(IteratorTest, Test4) {
	IteratorTest(10000);
}
TEST(IteratorTest, Test5) {
	IteratorTest(100000);
}
TEST(IteratorTest, Test6) {
	IteratorTest(1000000);
}
void ReverseIteratorTest(int temps) {
	Deque <int> d1;
	std::deque <int> d2;
	for (int i = 0; i < temps; i++) {
		int k = rand();
		d1.push_back(k);
		d2.push_back(k);
	}
	std::sort(d1.rbegin(), d1.rend());
	std::sort(d2.rbegin(), d2.rend());
	std::reverse(d1.rbegin(), d1.rend());
	std::reverse(d2.rbegin(), d2.rend());
	ASSERT_TRUE(eqDeque(d1, d2)) <<  "ERROR___reverse_sort___ERROR";
	for (int i = 1; i < temps; i++)
		ASSERT_TRUE(d1[i - 1] <= d1[i]) << "ERROR___reverse_sort_order___ERROR";
}
TEST(ReverseIteratorTest, Test1) {
	ReverseIteratorTest(1000);
}
TEST(ReverseIteratorTest, Test2) {
	ReverseIteratorTest(100000);
}
std::string randstr() {
	int len = rand() % 10;
	std::string ans = "";
	for (int i = 0; i < len; i++)
		ans += char('a' + rand() % 26);
	return  ans;
}
TEST(CONSTRUCTOR, Test1) {
	Deque <std::string> d1, d11;
	std::deque <std::string> d2, d22;
	for (int i = 0; i < 20000; i++) {
		std::string s = randstr();
		d1.push_back(s);
		d2.push_back(s);
	}
	d11 = d1;
	d22 = d2;
	Deque <std::string> d111(d11);
	std::deque <std::string> d222(d22);
	ASSERT_EQ((d1.begin())->size(), (d2.begin())->size());
	ASSERT_TRUE(eqDeque(d111, d222)) << "ERROR___operator=___ERROR";
}