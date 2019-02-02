/*
*  C#-like list implementation - wrapper around std::vector container.
*  By Kuba Maruszczyk (2016-2019).
*
*  This file is a part of RA_FRAMEWORK.
*/

#ifndef _KLM_LIST_H
#define _KLM_LIST_H

#include <vector>
#include <algorithm>
#include <random>
#include "RATypes.h";

namespace RA_FRAMEWORK
{

	template<class T>
	class KLMList
	{

	private:
		std::vector<T> m_Data;

	public:
		KLMList() {}
		KLMList(const KLMList& list)
		{
			KLMList<T>& data = const_cast<KLMList<T>&>(list);
			m_Data = data.GetStdVectorRef();
		}

		KLMList operator=(const KLMList& list)
		{
			KLMList<T>& data = const_cast<KLMList<T>&>(list);
			m_Data = data.GetStdVectorRef();
		}

		virtual ~KLMList() {}

		void Add(const T& element) { m_Data.push_back(element); }

		void Remove(const T& element) noexcept
		{
			m_Data.erase(std::remove(m_Data.begin(), m_Data.end(), element), m_Data.end());
		}

		void RemoveByIndex(unsigned index)
		{
			if (index >= m_Data.size())
			{
				throw std::out_of_range("Index is out of range");
				return;
			}
			m_Data.erase(m_Data.begin() + index);
		}

		void RemoveRange(unsigned fromIndex, unsigned toIndex)
		{
			if ((fromIndex >= m_Data.size()) || (toIndex >= m_Data.size()))
			{
				throw std::out_of_range("Index is out of range");
				return;
			}
			m_Data.erase(m_Data.begin() + fromIndex, m_Data.begin() + toIndex);
		}

		bool Contains(const T& element) noexcept
		{
			if (std::find(m_Data.begin(), m_Data.end(), element) != m_Data.end())
				return true;
			return false;
		}

		template<typename UnaryPredicate>
		T* Find(UnaryPredicate Predicate) noexcept
		{
			auto p = std::find_if(m_Data.begin(), m_Data.end(), Predicate);
			if(p != m_Data.end()) return &(*p);
			else return nullptr;
		}

		template<typename UnaryPredicate>
		void Sort(UnaryPredicate Predicate) noexcept
		{
			std::sort(m_Data.begin(), m_Data.end(), Predicate);
		}

		//Requires < operator
		void SortAscending() noexcept
		{
			this->Sort([](T const& a, T const& b) { return a < b; });
		}

		//Requires > operator
		void SortDescending() noexcept
		{
			this->Sort([](T const& a, T const& b) { return a > b; });
		}

		void Reverse() noexcept
		{
			std::reverse(m_Data.begin(), m_Data.end());
		}

		void GetReversed(KLMList& reversedList) noexcept
		{
			reversedList = KLMList();
			reversedList.GetStdVectorRef() = std::reverse(std::vector(m_Data));
		}

		void RandomShuffle() noexcept
		{
			/*static auto rng = std::default_random_engine{};
			std::shuffle(std::begin(m_Data), std::end(m_Data), rng);*/

			std::random_shuffle(m_Data.begin(), m_Data.end());
		}

		std::vector<T>& GetStdVectorRef() { return m_Data; }

		T& operator[](unsigned index)
		{
			return m_Data[index];
		}

		void Clear() noexcept { m_Data.clear(); }

		//Only to be used for pointer types
		/*static void KLMList::DeallocateAll(KLMList<T>& list)
		{
			for (auto it = list.GetStdVectorRef().begin(); it != list.GetStdVectorRef().end(); ++it)
			{
				delete (*it);
			}
			list.Clear();
		}*/

		unsigned Count()const noexcept { return m_Data.size(); }

		//Requires << operator to be overriden
		void ConsoleDump_DEBUG() noexcept
		{
			for (auto it = m_Data.begin(); it != m_Data.end(); ++it)
			{
				std::cout << (*it) << std::endl;
			}
		}

	};

	//AUXILARY OPERATORS - DEBUG ONLY
	template<class T>
	std::ostream& operator<<(std::ostream& os, const KLMList<T>& list)
	{
		KLMList<T>& data = const_cast<KLMList<T>&>(list);
		for (auto it = data.GetStdVectorRef().begin(); it != data.GetStdVectorRef().end(); ++it)
		{
			//os << (*it) << std::endl;
		}
		return os;
	}

}

#endif // !_KLM_LIST_H