#include "GroupNonOverlappingRectangles.h"


std::ostream& operator<<(std::ostream& os, Rect& rect) {
	os <<  rect.x1 << " " << rect.y1 << " " << rect.x2 << " " << rect.y2 ;
	return os;
}




std::vector<std::vector<Rect>> GroupNonOverlappingRectangles::runAlgorithm()
{
    // Sort by X1
    std::sort(rectangles.begin(), rectangles.end(), 
        [](const Rect& lhs, const Rect& rhs)
        {
            return lhs.x1 < rhs.x1;
        });

	for (int i = 0; i < rectangles.size(); i++) // N
	{
		int j;
		bool rectangle_pushed = false;
		for (j = 0; j < groups.size(); j++) // G where G is the group size
		{
			// Remove non-active elements which has (X2) <= X1 of current element
			// Notice: '>=' if touching is not overlapping and make it '>' if touching is overlapping
			while(!groupsMinHeap[j].empty() && rectangles[i].x1 > std::get<0>(groupsMinHeap[j].top()) ) { 
				std::tuple<long, long, long> top = groupsMinHeap[j].top();
				long x2 = std::get<0>(top);
				long y1 = std::get<1>(top);
				long y2 = std::get<2>(top);
				groupstree[j].erase(groupstree[j].find({y1, y2}));
				groupsMinHeap[j].pop();
			}

			// If current rectangle does not overlap with any of the rectangles in the current group
			// Notice: true if touching is not overlapping and false if touching is overlapping
			if (groupstree[j].overlap_find({ rectangles[i].y1,rectangles[i].y2 },false) == std::end(groupstree[j])) { 
				groups[j].push_back(rectangles[i]);

				groupstree[j].insert({ rectangles[i].y1,rectangles[i].y2 });
				groupsMinHeap[j].push({ rectangles[i].x2 , rectangles[i].y1 ,rectangles[i].y2 });

				rectangle_pushed = true;
				break;
			}
		}

		// If not already pushed into a group then create a new group
		if (!rectangle_pushed) {
			groups.push_back(std::vector<Rect> {rectangles[i]});

			lib_interval_tree::interval_tree_t<long> t;
			t.insert({ rectangles[i].y1, rectangles[i].y2 });
			groupstree.push_back(t);
			std::priority_queue<
				std::tuple<long, long, long>,
				std::vector<std::tuple<long, long, long>>,
				std::greater<std::tuple<long, long, long>>> minHeap;
			minHeap.push({ rectangles[i].x2,rectangles[i].y1, rectangles[i].y2 });
			groupsMinHeap.push_back(minHeap);

		}
	}

	std::cout << "Groups size = " << groups.size()<< std::endl;


	return groups;
}


GroupNonOverlappingRectangles::GroupNonOverlappingRectangles(std::vector<Rect> rects)
{
    rectangles = rects;
}

void GroupNonOverlappingRectangles::printRectangles()
{
	std::cout << "Size = " << rectangles.size() << std::endl;
	for (int i = 0; i < rectangles.size(); i++)
	{
		std::cout << rectangles[i] << std::endl;
	}
}
