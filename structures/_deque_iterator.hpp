template <>
template <typename T, bool const_it> inline
Deque<T>::Iterator<const_it>::Iterator(typename Deque<T>::ListNode* node) : current_{node} 
{

}

template <typename T, bool const_it> inline
Deque<T>::ReverseIterator<const_it>::ReverseIterator(
	ListNode* node) : current_{node} 
{

}

template <typename T, bool const_it> inline
typename Deque<T>::Iterator<const_it>&
Deque<T>::Iterator<const_it>::operator++()
{
	current_ = current_->next_;
	return *this;
}

template <typename T, bool const_it> inline
typename Deque<T>::ReverseIterator<const_it>&
Deque<T>::ReverseIterator<const_it>::operator++()
{
	current_ = current_->previous_;
	return *this;
}

template <typename T, bool const_it> inline
typename Deque<T>::Iterator<const_it>&
Deque<T>::Iterator<const_it>::operator++(int) const
{
    auto old = current_;
    current_ = current_->next_;
    return Iterator<const_it>{old};
}

template <typename T, bool const_it> inline
typename Deque<T>::ReverseIterator<const_it>&
Deque<T>::ReverseIterator<const_it>::operator++(int) const
{
    auto old = current_;
    current_ = current_->next_;
    return ReverseIterator<const_it>{old};
}

template <typename T, bool const_it> inline
const Deque<T>::Iterator<const_it>::reference
Deque<T>::Iterator<const_it>::operator*() const
{
	return current_->value_;
}

template <typename T, bool const_it> inline
const Deque<T>::ReverseIterator<const_it>::reference
Deque<T>::ReverseIterator<const_it>::operator*() const
{
	return current_->value_;
}

template <typename T, bool const_it> inline
const Deque<T>::Iterator<const_it>::pointer
Deque<T>::Iterator<const_it>::operator->() const
{
	return current_->value_;
}

template <typename T, bool const_it> inline
const Deque<T>::ReverseIterator<const_it>::pointer
Deque<T>::ReverseIterator<const_it>::operator->() const
{
	return current_->value_;
}

template <typename T, bool const_it> inline
bool Deque<T>::Iterator<const_it>::operator==(
	const Iterator<const_it>& rhs) const
{
	return current_ == rhs.current_;
} 

template <typename T, bool const_it> inline
bool Deque<T>::ReverseIterator<const_it>::operator==(
	const ReverseIterator<const_it>& rhs) const
{
	return current_ == rhs.current_;
} 

template <typename T, bool const_it> inline
bool Deque<T>::Iterator<const_it>::operator!=(
	const Iterator<const_it>& rhs) const
{
	return !(*this == rhs);
} 

template <typename T, bool const_it> inline
bool Deque<T>::ReverseIterator<const_it>::operator!=(
	const ReverseIterator<const_it>& rhs) const
{
	return !(*this == rhs);
}  