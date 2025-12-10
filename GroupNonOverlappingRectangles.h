#ifndef GROUP_NON_OVERLAPPING_RECTANGLES
#define GROUP_NON_OVERLAPPING_RECTANGLES


#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>

#include "interval-tree/interval_tree.hpp"

struct Rect
{
	int id;
	long x1,y1,x2,y2;

	// For Testing
	bool operator==(const Rect& b) const {
		return x1 == b.x1 &&
			y1 == b.y1 &&
			x2 == b.x2 &&
			y2 == b.y2;
	}
};



class GroupNonOverlappingRectangles
{
public:
	std::vector<std::vector<Rect>> runAlgorithm();
	GroupNonOverlappingRectangles(std::vector<Rect> rects);
	void printRectangles();

private:
	std::vector<Rect> rectangles;

	// groups, groupstree, groupsMinHeap should be local variables in runAlgorithm function
	// but just for testing memory consumption, they are class attributes
	std::vector<std::vector<Rect>> groups;
	std::vector<lib_interval_tree::interval_tree_t<long>> groupstree;
	std::vector<std::priority_queue<std::tuple<long, long, long>, std::vector<std::tuple<long, long, long>>, std::greater<std::tuple<long, long, long>>>> groupsMinHeap;

	

};
#endif // !GROUP_NON_OVERLAPPING_RECTANGLES

