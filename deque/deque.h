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
	static const double Exp_;
	static const size_t MinSize_;
	size_t size_, realSize_;
	T* elements_;
	void renew_();
	void setNewSize_(size_t newSize);
public:
	Vector();
	Vector(const Vector & v);
	~Vector();
	Vector& operator=(Vector v);
	void push_back(const T& key);
	void pop_back();
	void resize(const size_t &newSize);
	const T& at(const size_t& index) const;
	T& get(const size_t& index) const;
	T& operator [](const size_t& index);
	const T& operator [](const size_t& index) const;
	void leftShift(const size_t &num);
	T& back();
	const T& back() const;
	size_t size() const;
	size_t realSize();
	bool empty() const;
	void clear();
};
template <typename T>
Vector <T>::Vector() {
	realSize_ = MinSize_;
	elements_ = new T[MinSize_];
	size_ = 0;
}
template <typename T>
Vector <T>::Vector(const Vector & v) {
	realSize_ = v.realSize_;
	size_ = v.size_;
	elements_ = new T[realSize_];
	std::copy(v.elements_, v.elements_ + size_, elements_);
}
template <typename T>
Vector <T>::~Vector() {
	delete[] elements_;
}
template <typename T>
Vector<T>& Vector <T>::operator=(Vector <T> v) {
	delete[] elements_;
	realSize_ = v.realSize_;
	size_ = v.size_;
	elements_ = new T[realSize_];
	std::copy(v.elements_, v.elements_ + size_, elements_);
	return *this;
}
template <typename T>
size_t Vector <T>::size() const {
	return size_;
}
template <typename T>
size_t Vector <T>::realSize() {
	return realSize_;
}
template <typename T>
bool Vector <T>::empty() const {
	return !size_;
}
template <typename T>
void Vector <T>::clear() {
	resize(0);
}
template <typename T>
const double Vector <T>::Exp_ = 2;
template <typename T>
const size_t Vector <T>::MinSize_ = 4; 
template <typename T>
void Vector <T>::renew_() {
	if (size_ == realSize_)
		setNewSize_(size_t(size_ * Exp_));
	if (size_ * (Exp_ * 2 + 1) <= realSize_)
		setNewSize_(size_t(size_ * Exp_));
}

template <typename T>
void Vector <T>::setNewSize_(size_t newSize) {
	if (newSize < MinSize_)
		newSize = MinSize_;
	if (realSize_ == newSize)
		return;
	T* newElements = new T[newSize];
	std::copy (elements_, elements_ + size_, newElements);
	delete[] elements_;
	elements_ = newElements;
	realSize_ = newSize;
}

template <typename T>
void Vector <T>::push_back(const T& key) {
	elements_[size_] = key;
	size_++;
	renew_();
}
template <typename T>
void Vector <T>::pop_back() {
	assert(size_ > 0);
	size_--;
	renew_();
}
template <typename T>
const T& Vector <T>::back() const {
	assert(!empty());
	return at(size_ - 1);
}
template <typename T>
T& Vector <T>::back(){
	assert(!empty());
	return elements_[size_ - 1];
}
template <typename T>
const T& Vector <T>::at(const size_t &index) const{
	assert(index >= 0 && index < size_);
	return elements_[index];
}
template <typename T>
T& Vector <T>::get(const size_t &index) const{
	assert(index >= 0 && index < size_);
	return elements_[index];
}
template <typename T>
T& Vector <T>::operator [](const size_t &index) {
	return get(index);
}
template <typename T>
const T& Vector <T>::operator [](const size_t &index) const{
	return get(index);
}
template <typename T>
void Vector <T>::resize(const size_t &newSize) {
	if (newSize < size_) {
		size_ = newSize;
		renew_();
	}
	else {
		for (; size_ < newSize;)
			push_back(T());
	}
}
template <typename T>
void Vector <T>::leftShift(const size_t &num) {
	assert(num <= size_);
	std::copy(elements_ + num, elements_ + size_, elements_);
	resize(size_ - num);
}
template <typename T>
class Deque {
private:
	Vector <T> vBegin_, vEnd_;
	void align_();
	T& get_(const size_t& index) const;
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
	Deque& operator =(const Deque& q);
	void push_front(const T& key);
	void push_back(const T& key);
	size_t size() const;
	bool empty() const;
	void pop_back();
	void pop_front();
	T& back();
	const T& back() const;
	T& front();
	const T& front() const;
	const T& operator [](const size_t& index) const;
	T& operator [](const size_t& index);
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
Deque<T>& Deque<T>::operator =(const Deque<T>& q) {
	if (this == &q)
		return *this;
	vBegin_ = q.vBegin_;
	vEnd_ = q.vEnd_;
	return *this;
}
template <typename T>
void Deque<T>::push_front(const T& key) {
	vEnd_.push_back(key);
}
template <typename T>
void Deque<T>::push_back(const T& key) {
	vBegin_.push_back(key);
}
template <typename T>
size_t Deque<T>::size() const {
	return vBegin_.size() + vEnd_.size();
}
template <typename T>
bool Deque<T>::empty() const {
	return vBegin_.empty() && vEnd_.empty();
}
template <typename T>
void moveElements(Vector <T>& from, Vector <T>& to, int numOfElements) {
	for (int i = numOfElements - 1; i >= 0; i--)
		to.push_back(from.at(i));
	from.leftShift(numOfElements);

}
template <typename T>
void Deque <T>::align_() {
	if (vEnd_.empty()) {
		if (vBegin_.empty())
			return;
		moveElements(vBegin_, vEnd_, vBegin_.size() / 2);
	}
	if (vBegin_.empty())
		moveElements(vEnd_, vBegin_, (vEnd_.size() + 1) / 2);
}
template <typename T>
void Deque <T>::pop_front() {
	assert(!empty());
	align_();
	if (vEnd_.empty())
		vBegin_.pop_back();
	else
		vEnd_.pop_back();
}
template <typename T>
void Deque <T>::pop_back() {
	assert(!empty());
	align_();
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
const T& Deque <T>::front() const{
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
const T& Deque <T>::back() const{
	assert(!empty());
	if (vBegin_.empty())
		return vEnd_[0];
	return vBegin_.back();
}
template <typename T>
T& Deque <T>::get_(const size_t& index) const {
	assert(index < size());
	if (index < vEnd_.size())
		return vEnd_.get(vEnd_.size() - index - 1);
	return vBegin_.get(index - vEnd_.size());
}

template <typename T>
T& Deque <T>::operator[](const size_t& index){
	return get_(index);
}
template <typename T>
const T& Deque <T>::operator[](const size_t& index) const {
	return get_(index);
}

#endif