#pragma once

#include <functional>
#include <vector>

namespace Logic {
class HistoryIndex {
public:
	HistoryIndex();

	auto next(std::function<int()> &&get_index) noexcept -> int;
	auto prev() noexcept -> int;

private:
	std::vector<int> m_indexes;
	int m_delta{};
};
} // namespace Logic
