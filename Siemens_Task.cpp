
#include <iostream>
#include "FileHandler.h"
#include "GroupNonOverlappingRectangles.h"
#include <chrono>


#include <windows.h>
#include <psapi.h>



std::string getMemoryUsage() {
	PROCESS_MEMORY_COUNTERS memInfo;
	GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));

	SIZE_T memoryUsedBytes = memInfo.WorkingSetSize;

	SIZE_T memoryMB = memoryUsedBytes / (1024 * 1024);
	SIZE_T memoryKB = (memoryUsedBytes % (1024 * 1024)) / 1024;

	return std::to_string(memoryMB) + "." + std::to_string(memoryKB) + " MB";
}


int main()
{
	// Can choose between data_set_1.txt , data_set_2.txt , data_set_3.txt, ... , data_set_16.txt
    FileHandler filehandler("assets\\data_set_5.txt");

    std::vector<Rect> rectangles = filehandler.getRectanglesFromFile();
	

	GroupNonOverlappingRectangles algo(rectangles);

	std::cout << "Rectangles N = " << rectangles.size() << std::endl;


	std::cout << "Memory before alogrithm: " << getMemoryUsage() << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

	std::vector<std::vector<Rect>> groups = algo.runAlgorithm();

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;

	std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;


	std::cout << "Memory after alogrithm: " << getMemoryUsage()  << std::endl;


	std::cout << "There are " << groups.size() << " groups: " << std::endl;

	filehandler.outputFilesFromGroups(groups);

	/*for (int i = 0; i < groups.size(); i++)
	{
		std::cout << "Group " << i + 1 << ":" << std::endl;
		for (int j = 0; j < groups[i].size(); j++)
		{
			std::cout<< "\t" << groups[i][j].id << std::endl;
		}
	}*/
}
