/**
 * This file contains implementations for methods in the PageTable class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page_table/page_table.h"
#include <limits>

using namespace std;


size_t PageTable::get_present_page_count() const {
  // DONE
	size_t presentPageCount = 0;
	for (size_t i = 0; i < rows.size(); ++i) {
		if (rows[i].present) {
			presentPageCount++;
		}
	}
	return presentPageCount;
}


size_t PageTable::get_oldest_page() const {
  // DONE
	size_t oldest= 0;
	size_t lowestLoadedAt = numeric_limits<size_t>::max();
	for (size_t i = 0; i < rows.size(); ++i) {
		if (rows[i].loaded_at < lowestLoadedAt && rows[i].present) {
			oldest = i;
			lowestLoadedAt = rows[i].loaded_at;
		}
	}
	return oldest;
}


size_t PageTable::get_least_recently_used_page() const {
  // DONE
	size_t leastRecent= 0;
	size_t lowestLast = numeric_limits<size_t>::max();
	for (size_t i = 0; i < rows.size(); ++i) {
		if (rows[i].last_accessed_at < lowestLast && rows[i].present) {
			leastRecent = i;
			lowestLast = rows[i].last_accessed_at;
		}
	}
	return leastRecent;
}
}
