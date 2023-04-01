#pragma once

#include <utility>

template <typename... Ts>
class Action
{
	std::unordered_map<int, std::function<void(Ts...)>> callbacks{};
	int nextAvailableId = 0;

public:
	int subscribe(const std::function<void(Ts...)>& func)
	{
		callbacks[nextAvailableId] = func;
		return nextAvailableId++;
	}
	void unsubscribe(int id)
	{
		callbacks.erase(id);
	}

	void operator+=(const std::function<void(Ts...)>& func)
	{
		subscribe(func);
	}

	void operator()(Ts... args) const {
		for (auto& [id, func] : callbacks)
			func(args...);
	}
};
