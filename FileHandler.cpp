#include "FileHandler.h"


FileHandler::FileHandler(std::string file_path){
	filePath = file_path;
	infile.open(filePath);
}

std::vector<Rect> FileHandler::getRectanglesFromFile()
{
	std::vector<Rect> rectangles;

	if (!infile) {
		std::cout << "Error opening file!" << std::endl;
		return std::vector<Rect>();
	}
	std::string line;

	int id = 0;
	while (getline(infile, line)) {
		std::stringstream ss(line);
		std::vector<long> lineValues;
		std::string s;

		while (ss >> s) {
			long x;
			if (!isValidLong(s, x)) {
				std::cout << "Invalid input: " << s<<std::endl;
				return std::vector<Rect>();
			}
			lineValues.push_back(x);
		}
		if (lineValues.size() != 4) {
			std::cout << "Invalid input: expected 4 numbers per line and got: " << lineValues.size() << std::endl;
			return std::vector<Rect>();
		}
		Rect r;
		r.id = id;
		r.x1 = lineValues[0];
		r.y1 = lineValues[1];
		r.x2 = lineValues[2];
		r.y2 = lineValues[3];
		rectangles.push_back(r);
		id++;

	}
	std::cout << "Read file Successfully!" << std::endl;
	infile.close();
	return rectangles;
}

void FileHandler::outputFilesFromGroups(std::vector<std::vector<Rect>> groups)
{
	size_t lastSlash = filePath.find_last_of("\\");
	std::string filename = filePath.substr(lastSlash + 1);

	size_t lastDot = filename.find_last_of(".");
	std::string folderOutputName = "output/" + filename.substr(0, lastDot);


	if (!std::filesystem::exists("output")) {
		std::filesystem::create_directory("output");
	}
	

	if (!std::filesystem::exists(folderOutputName)) {
		std::filesystem::create_directory(folderOutputName);
	}

	
	for (int i = 0; i < groups.size(); i++)
	{
		std::string fullPath = folderOutputName + "/" + "group_" + std::to_string(i + 1) + ".txt";
		std::ofstream outFile(fullPath);

		if (!outFile) {
			std::cerr << "Failed to open file: " << fullPath << std::endl;
			return ;
		}

		for (int j = 0; j < groups[i].size() ; j++)
		{
			outFile << 
				groups[i][j].x1 << " " <<
				groups[i][j].y1 << " " <<
				groups[i][j].x2 << " " << 
				groups[i][j].y2 << " " <<
				std::endl;
		}
		outFile.close();

	}
	std::cout << "Rectangles written to /" << folderOutputName << std::endl;

}

bool FileHandler::isValidLong(const std::string& str, long& result)
{
	try {
		size_t pos;
		result = std::stol(str, &pos, 10);
		return pos == str.size();
	}
	catch (const std::invalid_argument&) {
		return false; // Not a number
	}
	catch (const std::out_of_range&) {
		return false; // Number out of long range
	}
}




