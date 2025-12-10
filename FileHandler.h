#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <sys/stat.h>
#include <filesystem>

#include "GroupNonOverlappingRectangles.h"


class FileHandler
{

public:
	FileHandler(std::string file_path);
	std::vector<Rect> getRectanglesFromFile();
	void outputFilesFromGroups(std::vector<std::vector<Rect>> groups);



private:
	std::string filePath;
	std::ifstream infile;
	bool isValidLong(const std::string& str, long& result);
	



};
#endif

