#include "pch.h"
#include <queue>
#include <algorithm>
#include "deque\deque.h"
#include <fstream>
#include <iostream>
#include <time.h>
#include <cmath>
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

template <typename T>
bool eqDeque(const Deque <T>& d1, const std::deque <T>& d2) {
	if (d1.size() != d2.size())
		return false;
	for (size_t i = 0; i < d1.size(); i++)
		if (d1[i] != d2[i])
			return false;
	return true;
}
enum InteractiveTestCase {
	ITpush_front,
	ITpush_back,
	ITpop_back,
	ITpop_front,
	ITsize
};
const int MAX_SIZE = 10000000;
void InteractiveTest(long long temps, bool eqflag) {
	Deque <int> q1;
	std::deque <int> q2;
	for (long long i = 0; i < temps; i++) {
		int k;
		int Case = rand() % ITsize;
		switch (Case) {
		case ITpush_front:
			if (q2.size() > MAX_SIZE)
				break;
			k = rand();
			q1.push_front(k);
			q2.push_front(k);
			break;
		case ITpush_back:
			k = rand();
			if (q2.size() > MAX_SIZE)
				break;
			q1.push_back(k);
			q2.push_back(k);
			break;
		case ITpop_back:
			if (q2.empty())
				break;
			q2.pop_back();
			q1.pop_back();
			break;
		case ITpop_front:
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
void somePush(Deque <double>& d) {
	if (d.size() == MAX_SIZE)
		return;
	if (rand() % 2)
		d.push_back(rand() * 1.0 / (rand() + 1));
	else
		d.push_front(rand() * 1.0 / (rand() + 1));
}
void somePop(Deque <double>& d) {
	if (d.empty())
		return;
	if (rand() % 2)
		d.pop_back();
	else
		d.pop_front();
}

void InteractiveTest2(int numOfTemps) {
	int tbegin = clock();
	long long numOfOper = 2, sumOfOper = 0;
	Deque <double> d;
	for (long long i = 1; i <= numOfTemps; i++) {
		for (int j = 0; j < numOfOper; j++) {
			if (rand() % 10)
				somePop(d);
			else
				somePush(d);
		}
		for (int j = 0; j < numOfOper; j++) {
			if (rand() % 10)
				somePush(d);
			else
				somePop(d);
		}
		sumOfOper += 2 * numOfOper;
		numOfOper *= 2;
		std::ofstream out("C:/myFavoriteUniversity/myFavoriteSubject/GtestOut.txt", std::ios::in);
		out.seekp(0, std::ios::end);
		out << "Test number " << i << ". " << numOfOper <<
		" operations done. It took " << (clock() - tbegin) / CLOCKS_PER_SEC << " seconds.\n";
		out.close();
	}
}
TEST(TestTime, MainTest) {
	InteractiveTest2(30);
}