#pragma once

#include <list>
#include <stack>

namespace POG::Editor
{
	class WidgetManager
	{
	public:
		WidgetManager(int idPoolSize)
			: availableIds()
			, usedIds()
		{
			for (int i = head; i < head + idPoolSize; i++)
			{
				availableIds.push(i);
			}

			head += idPoolSize;
		}

		int PopId()
		{
			int id = availableIds.top();
			availableIds.pop();
			usedIds.push_back(id);
			return id;
		}

		void PushId(int id)
		{
			availableIds.push(id);
		}

		void Reset()
		{
			usedIds.reverse();
			for (int id : usedIds)
			{
				PushId(id);
			}

			usedIds.clear();
		}

	private:
		static int head;

		std::stack<int> availableIds;
		std::list<int> usedIds;
	};
}