#pragma once

namespace POG::Util
{
	template <typename T, T capacity, T maxValue>
	class SparseSet
	{
	public:
		SparseSet()
			: dense(nullptr)
			, sparse(nullptr)
			, count(0)
		{
			dense = new T[capacity];
			sparse = new T[maxValue + 1];

			for (T i = 0; i < capacity; i++)
			{
				dense[i] = 0;
			}

			for (T i = 0; i <= maxValue; i++)
			{
				sparse[i] = 0;
			}
		}

		~SparseSet()
		{
			delete[] sparse;
			delete[] dense;
		}

		bool Find(T element, T& index) const
		{
			// Get the index of the element
			index = sparse[element];

			// If the element in the dense array at the index matches, return true
			return index < count&& dense[index] == element;
		}

		bool Contains(T element) const
		{
			T index;
			return Find(element, index);
		}

		T Insert(T element)
		{
			// Insert the element into the dense array at position count
			dense[count] = element;

			// Store the position of that element in the sparse array
			sparse[element] = count;

			// Finally increment count to match the current number of elements now stored in the dense array
			return count++;
		}

		void Remove(T element)
		{
			// Make sure the element actually exists
			T indexOfElementToDelete;
			if (!Find(element, indexOfElementToDelete))
			{
				return;
			}

			// Replace the deleted element with the last element in the dense array
			T lastElement = dense[count - 1];
			dense[indexOfElementToDelete] = lastElement;

			// Update the index of the last element to its new location
			sparse[lastElement] = indexOfElementToDelete;

			// Finally decreae the count
			count--;
		}

		constexpr T Capacity() const
		{
			return capacity;
		}

		constexpr T MaxValue() const
		{
			return maxValue;
		}

		T Count() const
		{
			return count;
		}

	private:
		// The tightly packed array containing the actual elements
		T* dense;

		// The sparse array containing the indexes of the elements in the dense array
		T* sparse;

		// The current number of elements in the dense array
		T count;
	};
}