/**
 * \file nonhashmap.hpp
 * \brief Mapping type that doesn't use hashes.
 */

#ifndef NONHASH_MAP_HPP
#define NONHASH_MAP_HPP 1

#include "map.hpp"
#include "deque.hpp"


template <typename K, typename V>
class NonHashMap : public Map<K, V> {
private:
	/**
	 * \brief Forward iterator.
	 */
	class Iterator;

	/**
	 * \brief Constant forward iterator.
	 */
	class ConstIterator;

	/**
	 * \brief Reverse iterator.
	 */
	class ReverseIterator;

	/**
	 * \brief Constant reverse iterator.
	 */
	class ConstReverseIterator;

	/**
	 * \brief Key data member of the map.
	 */
	struct Key;

public:
	/**
	 * \brief Default constructor.
	 */
	NonHashMap();

	/**
	 * \brief Copy constructor.
	 */
	NonHashMap(NonHashMap<K, V> const& orig);

	/**
	 * \brief Move constructor.
	 */
	NonHashMap(NonHashMap<K, V>&& other);

	/**
	 * \brief Assignment operator.
	 */
	NonHashMap<K, V>& operator=(NonHashMap<K, V> rhs);

	/**
	 * \brief Idiomatic swap function.
	 */
	template <typename KEY, typename VALUE>
	friend void swap(NonHashMap<KEY, VALUE>& lhs, NonHashMap<KEY, VALUE>& rhs);

	/**
	 * \brief We can use a default destructor because Deque has its own
	 *        destructor.
	 */
	~NonHashMap() = default;

	/**
	 * \brief Adds a key-value pair to the map.
	 */
	void addValue(K key, V value);

	/**
	 * \brief Removes the value associated with a given key
	 */
	void removeValue(K key);

	/**
	 * \brief Gets the value associated with a key.
	 */
	V& getValue(K key) const;

	/**
	 * \brief Gets the number of elements in the map.
	 */
	std::size_t size() const;

	/**
	 * \brief Determines whether or not the map is empty.
	 */
	bool isEmpty() const;

	/**
	 * \brief Determines whether or not the key is present.
	 */
	bool contains(K key) const;

	/**
	 * \brief Gets a list of all keys in the map.
	 */
	Deque<K>* getKeys() const;

	/**
	 * \brief Gets a list of all values in the map.
	 */
	Deque<V>* getValues() const;

	typedef Iterator iterator;
  	typedef ConstIterator const_iterator;
  	typedef ReverseIterator reverse_iterator;
  	typedef ConstReverseIterator const_reverse_iterator;

    /**
     * \brief Start of the deque.
     */
	iterator begin();

	/**
	 * \brief Termination of the deque.
	 */
    iterator end();

    /** 
     * \brief Start of the deque.
     */
    const_iterator begin() const;

    /**
     * \brief Termination of the deque.
     */
    const_iterator end() const;

    /**
     * \brief End of the deque.
     */
	reverse_iterator rbegin();

	/**
	 * \brief Termination of the reversed deque.
	 */
    reverse_iterator rend();

    /** 
     * \brief End of the deque.
     */
    const_reverse_iterator rbegin() const;

    /**
     * \brief Terminatin of the reversed deque.
     */
    const_reverse_iterator rend() const;

private:
	class Iterator : public std::iterator<std::forward_iterator_tag, K>
	{
	public:
		    /**
			 * \brief Prefix increment operator overloading.
			 */
			Iterator& operator++();

			/**
			 * \brief Postfix increment operator overloading.
			 */
			Iterator operator++(int) const;

			/**
			 * \brief Dereferencing operator overloading.
			 */
			const K& operator*() const;

			/**
			 * \brief Member access operator overriding.
			 */
			const K* operator->() const;

			/**
			 * \brief Equality operator overriding.
			 */
			bool operator==(const Iterator& rhs) const;

			/**
			 * \brief Inequality operator overriding.
			 */
			bool operator!=(const Iterator& rhs) const;

		private:
			friend class NonHashMap;
			/**
		     * \brief The default constructor.
		     */
		    Iterator() = delete;
		    /**
		     * \brief All iterators should have a current node.
		     */
		    Iterator(Key* key) : current_{key}
		    {
		    }
			
			Key* current_;
	};

	class ConstIterator : public std::iterator<std::forward_iterator_tag, K>
	{
	public:
		    /**
			 * \brief Prefix increment operator overloading.
			 */
			ConstIterator& operator++();

			/**
			 * \brief Postfix increment operator overloading.
			 */
			ConstIterator operator++(int) const;

			/**
			 * \brief Dereferencing operator overloading.
			 */
			const K& operator*() const;

			/**
			 * \brief Member access operator overriding.
			 */
			const K* operator->() const;

			/**
			 * \brief Equality operator overriding.
			 */
			bool operator==(const ConstIterator& rhs) const;

			/**
			 * \brief Inequality operator overriding.
			 */
			bool operator!=(const ConstIterator& rhs) const;

		private:
			friend class NonHashMap;
			/**
		     * \brief The default constructor.
		     */
		    ConstIterator() = delete;
		    /**
		     * \brief All iterators should have a current node.
		     */
		    ConstIterator(Key* key) : current_{key}
		    {
		    }
			
			Key* current_;
	};

	class ReverseIterator : public std::iterator<std::forward_iterator_tag, K>
	{
	public:
		    /**
			 * \brief Prefix increment operator overloading.
			 */
			ReverseIterator& operator++();

			/**
			 * \brief Postfix increment operator overloading.
			 */
			ReverseIterator operator++(int) const;

			/**
			 * \brief Dereferencing operator overloading.
			 */
			const K& operator*() const;

			/**
			 * \brief Member access operator overriding.
			 */
			const K* operator->() const;

			/**
			 * \brief Equality operator overriding.
			 */
			bool operator==(const ReverseIterator& rhs) const;

			/**
			 * \brief Inequality operator overriding.
			 */
			bool operator!=(const ReverseIterator& rhs) const;

		private:
			friend class NonHashMap;
			/**
		     * \brief The default constructor.
		     */
		    ReverseIterator() = delete;
		    /**
		     * \brief All iterators should have a current node.
		     */
		    ReverseIterator(Key* key) : current_{key}
		    {
		    }
			
			Key* current_;
	};

	class ConstReverseIterator : 
		public std::iterator<std::forward_iterator_tag, K>
	{
	public:
	    /**
		 * \brief Prefix increment operator overloading.
		 */
		ConstReverseIterator& operator++();

		/**
		 * \brief Postfix increment operator overloading.
		 */
		ConstReverseIterator operator++(int) const;

		/**
		 * \brief Dereferencing operator overloading.
		 */
		const K& operator*() const;

		/**
		 * \brief Member access operator overriding.
		 */
		const K* operator->() const;

		/**
		 * \brief Equality operator overriding.
		 */
		bool operator==(const ConstReverseIterator& rhs) const;

		/**
		 * \brief Inequality operator overriding.
		 */
		bool operator!=(const ConstReverseIterator& rhs) const;

	private:
		friend class NonHashMap;
		/**
	     * \brief The default constructor.
	     */
	    ConstReverseIterator() = delete;
	    /**
	     * \brief All iterators should have a current node.
	     */
	    ConstReverseIterator(Key* key) : current_{key}
	    {
	    }
		
		Key* current_;
	};

	struct Key
	{
		K key_;
		V value_;
		bool operator==(Key const& k) const;
	};

	Deque<Key> keys_;
};

#include "_nonhashmap.hpp"

#endif
