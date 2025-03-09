#pragma once

#include <filesystem>
#include <fstream>
#include <vector>

using namespace std::filesystem;
using namespace std;

string fileName(path filePath)
{
	return filePath.filename().string();
}
path connectPaths(path path1, path path2)
{
	return path1.string() + path2.string();
}