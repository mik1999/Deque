// https://github.com/mik1999/Deque.git
#ifndef DEQUE_H_INCLUDED
#define DEQUE_H_INCLUDED
#include <iostream>
#include <iterator>
#include <cassert>
#include <algorithm>

typedef size_t myPtrdiff_t;

template <typename T>
class Vector {
private:
	static const double Exp;
	static const size_t MinSize;
	size_t size_, realSize_;
	T* elements_;
	void renew();
	void setNewSize(size_t newSize);
public:
	Vector() {
		realSize_ = MinSize;
		elements_ = new T[MinSize];
		size_ = 0;
	}
	Vector(const Vector & v){
		realSize_ = v.realSize_;
		size_ = v.size_;
		elements_ = new T[realSize_];
		std::copy(v.elements_, v.elements_ + size_, elements_);
		//for (size_t i = 0; i < size_; i++)
		//	elements_[i] = v.elements_[i];
	}
	~Vector() {
		delete[] elements_;
	}
	Vector& operator=(Vector v) {
		delete[] elements_;
		realSize_ = v.realSize_;
		size_ = v.size_;
		elements_ = new T[realSize_];
		std::copy(v.elements_, v.elements_ + size_, elements_);
		return *this;
	}
	void push_back(const T& key);
	void pop_back();
	void resize(const size_t &newSize);
	T at(const size_t& index) const;
	T& operator [](const size_t& index);
	T operator [](const size_t& index) const;
	void leftShift(const size_t &num);
	T& back();
	T back() const;
	size_t size() const{
		return size_;
	}
	size_t realSize() {
		return realSize_;
	}
	bool empty() const{
		return !size_;
	}
	void clear() {
		resize(0);
	}
};
template <typename T>
const double Vector <T>::Exp = 2;
template <typename T>
const size_t Vector <T>::MinSize = 1; 
template <typename T>
void Vector <T>::renew() {
	if (size_ == realSize_)
		setNewSize(size_t(size_ * Exp));
	if (size_ * (Exp * 2 + 1) <= realSize_)
		setNewSize(size_t(size_ * Exp));
}

template <typename T>
void Vector <T>::setNewSize(size_t newSize) {
	if (newSize < MinSize)
		newSize = MinSize;
	if (realSize_ == newSize)
		return;
	T* newElements = new T[newSize];
	//std::copy (elements_, elements_ + size_, newElements);
	for (int i = 0; i < (int)size_; i++)
		newElements[i] = elements_[i];
	delete[] elements_;
	elements_ = newElements;
	realSize_ = newSize;
}

template <typename T>
void Vector <T>::push_back(const T& key) {
	elements_[size_] = key;
	size_++;
	renew();
}
template <typename T>
void Vector <T>::pop_back() {
	assert(size_ > 0);
	size_--;
	renew();
}
template <typename T>
T Vector <T>::back() const {
	assert(!empty());
	return at(size_ - 1);
}
template <typename T>
T& Vector <T>::back(){
	assert(!empty());
	return elements_[size_ - 1];
}
template <typename T>
T Vector <T>::at(const size_t &index) const{
	assert(index >= 0 && index < size_);
	return elements_[index];
}
template <typename T>
T& Vector <T>::operator [](const size_t &index) {
	assert(index >= 0 && index < size_);
	return elements_[index];
}
template <typename T>
T Vector <T>::operator [](const size_t &index) const{
	assert(index >= 0 && index < size_);
	return elements_[index];
}
template <typename T>
void Vector <T>::resize(const size_t &newSize) {
	if (newSize < size_) {
		size_ = newSize;
		renew();
	}
	else {
		for (; size_ < newSize;)
			push_back(T());
	}
}
template <typename T>
void Vector <T>::leftShift(const size_t &num) {
	assert(num <= size_);
	for (int i = 0; i < int(size_ - num); i++)
		elements_[i] = elements_[i + num];
	resize(size_ - num);
}
template <typename T>
class Deque {
private:
	Vector <T> vBegin_, vEnd_;
	void align();
	template <class ItDeque, class ItT, class ItRef>
	class OwnIterator : public std::iterator <std::random_access_iterator_tag, ItT, myPtrdiff_t, ItT*, ItRef> {
	private:
		ItDeque* parent_;
		int position_;
		friend class Deque;
	public:
		OwnIterator() {
			parent_ = nullptr;
			position_ = 0;
		}
		ItRef operator *() const {
			return parent_->operator [](position_);
		}
		ItRef operator [](const myPtrdiff_t& pos) const {
			return *(*this + pos);
		}
		ItT* operator ->() const{
			return &(operator *());
		}
		OwnIterator operator ++(int) {
			OwnIterator old = *this;
			position_++;
			return old;
		}
		OwnIterator& operator ++() {
			position_++;
			return *this;
		}
		OwnIterator operator --(int) {
			OwnIterator old = *this;
			position_--;
			return old;
		}
		OwnIterator& operator --() {
			position_--;
			return *this;
		}
		OwnIterator& operator +=(const myPtrdiff_t& diff) {
			position_ += diff;
			return *this;
		}
		OwnIterator operator +(const myPtrdiff_t& diff) const {
			OwnIterator it = *this;
			it += diff;
			return it;
		}
		OwnIterator operator +(const OwnIterator& it) const {
			OwnIterator ans = *this;
			ans.position_ += it.position_;
			return ans;
		}
		OwnIterator& operator -=(const myPtrdiff_t& diff) {
			position_ -= diff;
			return *this;
		}
		OwnIterator operator -(const myPtrdiff_t& diff) const {
			OwnIterator it = *this;
			it -= diff;
			return it;
		}
		myPtrdiff_t operator -(const OwnIterator& it) const {
			return position_ - it.position_;
		}
		bool operator ==(const OwnIterator& it) const {
			return position_ - it.position_ == 0;
		}
		bool operator !=(const OwnIterator& it) const {
			return !(*this == it);
		}
		bool operator <(const OwnIterator& it) const {
			return position_ - it.position_ < 0;
		}
		bool operator >(const OwnIterator& it) const {
			return it < *this;
		}
		bool operator <=(const OwnIterator& it) const {
			return !(it < *this);
		}
		bool operator >=(const OwnIterator& it) const {
			return !(*this < it);
		}
	};
public:
	Deque() {}
	~Deque() {}
	Deque(const Deque& q): vBegin_(q.vBegin_), vEnd_(q.vEnd_){}
	Deque& operator =(const Deque& q) {
		if (this == &q)
			return *this;
		vBegin_ = q.vBegin_;
		vEnd_ = q.vEnd_;
		return *this;
	}
	void push_front(const T& key) {
		vEnd_.push_back(key);
	}
	void push_back(const T& key) {
		vBegin_.push_back(key);
	}
	void pop_back();
	void pop_front();
	T& back();
	T back() const;
	T& front();
	T front() const;
	T operator [](const size_t& index) const;
	T& operator [](const size_t& index);
	size_t size() const{
		return vBegin_.size() + vEnd_.size();
	}
	bool empty() const{
		return vBegin_.empty() && vEnd_.empty();
	}
	typedef OwnIterator<Deque, T, T&> iterator;
	typedef OwnIterator<const Deque, T, T> const_iterator;
	typedef std::reverse_iterator <typename Deque::iterator> reverse_iterator;
	typedef std::reverse_iterator <typename Deque::const_iterator> const_reverse_iterator;
	iterator begin(){
		iterator b;
		b.parent_ = this;
		b.position_ = 0;
		return b;
	}
	iterator end() {
		iterator e;
		e.parent_ = this;
		e.position_ = size();
		return e;
	}
	const_iterator begin() const {
		const_iterator b;
		b.parent_ = this;
		b.position_ = 0;
		return b;
	}
	const_iterator end() const{
		const_iterator e;
		e.parent_ = this;
		e.position_ = size();
		return e;
	}
	const_iterator cbegin() const {
		const_iterator b;
		b.parent_ = this;
		b.position_ = 0;
		return b;
	}
	const_iterator cend() const{
		const_iterator e;
		e.parent_ = this;
		e.position_ = size();
		return e;
	}
	reverse_iterator rbegin() {
		return std::reverse_iterator <iterator>(end());
	}
	reverse_iterator rend() {
		return std::reverse_iterator <iterator>(begin());
	}
	const_reverse_iterator rbegin() const{
		return std::reverse_iterator <const_iterator>(cend());
	}
	const_reverse_iterator rend() const{
		return std::reverse_iterator <const_iterator>(cbegin());
	}
	const_reverse_iterator crbegin() const{
		return std::reverse_iterator <const_iterator>(cend());
	}
	const_reverse_iterator crend() const{
		return std::reverse_iterator <const_iterator>(cbegin());
	}
	/*void out() {
		for (int i = vEnd_.size() - 1; i >= 0; i--)
			cout << vEnd_[i] << ' ';
		cout << "| ";
		for (int i = 0; i < vBegin_.size(); i++)
			cout << vBegin_[i] << ' ';
		cout << endl;
	}*/
};
template <typename T>
void Deque <T>::align() {
	if (vEnd_.empty()) {
		if (vBegin_.empty())
			return;
		for (int i = vBegin_.size() / 2 - 1; i >= 0; i--)
			vEnd_.push_back(vBegin_.at(i));
		vBegin_.leftShift(vBegin_.size() / 2);
	}
	if (vBegin_.empty()) {
		for (int i = (vEnd_.size() + 1) / 2 - 1; i >= 0; i--)
			vBegin_.push_back(vEnd_.at(i));
		vEnd_.leftShift((vEnd_.size() + 1) / 2);
	}
}
template <typename T>
void Deque <T>::pop_front() {
	assert(!empty());
	align();
	if (vEnd_.empty())
		vBegin_.pop_back();
	else
		vEnd_.pop_back();
}
template <typename T>
void Deque <T>::pop_back() {
	assert(!empty());
	align();
	vBegin_.pop_back();
}
template <typename T>
T& Deque <T>::front() {
	assert(!empty());
	if (vEnd_.empty())
		return vBegin_[0];
	return vEnd_.back();
}
template <typename T>
T Deque <T>::front() const{
	assert(!empty());
	if (vEnd_.empty())
		return vBegin_[0];
	return vEnd_.back();
}
template <typename T>
T& Deque <T>::back() {
	assert(!empty());
	if (vBegin_.empty())
		return vEnd_[0];
	return vBegin_.back();
}
template <typename T>
T Deque <T>::back() const{
	assert(!empty());
	if (vBegin_.empty())
		return vEnd_[0];
	return vBegin_.back();
}
template <typename T>
T& Deque <T>::operator[](const size_t& index){
	assert(index < size());
	if (index < vEnd_.size())
		return vEnd_[vEnd_.size() - index - 1];
	return vBegin_[index - vEnd_.size()];
}
template <typename T>
T Deque <T>::operator[](const size_t& index) const {
	assert(index < size());
	if (index < vEnd_.size())
		return vEnd_[vEnd_.size() - index - 1];
	return vBegin_[index - vEnd_.size()];
}

#endif