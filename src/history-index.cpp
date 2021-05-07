#include "history-index.hpp"

using namespace Logic;

HistoryIndex::HistoryIndex() {
	m_indexes.reserve(4096);
}

auto HistoryIndex::next(std::function<int()> &&get_index) noexcept -> int {
	if (m_delta == 0) {
		m_indexes.emplace_back(get_index());
	} else {
		m_delta--;
	}
	return m_indexes[m_indexes.size() - m_delta - 1];
}

auto HistoryIndex::prev() noexcept -> int {
	if ((m_delta + 1) >= m_indexes.size())
		return m_indexes[0];

	m_delta++;
	return m_indexes[m_indexes.size() - m_delta - 1];
}
