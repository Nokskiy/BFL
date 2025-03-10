#pragma once

#include <filesystem>
#include <vector>

namespace BFL
{
	using namespace std;
	using namespace std::filesystem;

	string fileName(path filePath)
	{
		return filePath.filename().string();
	}

	path connectPaths(path path1, path path2)
	{
		return path1.string() + path2.string();
	}

	std::vector<std::filesystem::path> everythingInDirectory(path directory)
	{
		vector<path> files;
		if (exists(directory))
		{
			for (const auto entry : directory_iterator(directory))
				files.push_back(entry);
		}
		else
		{
			throw "directory not exist";
		}

		return files;
	}
	std::vector<std::filesystem::path> everythingInDirectory(path directory, bool throwError)
	{
		vector<path> files;
		if (exists(directory))
		{
			for (const auto entry : directory_iterator(directory))
				files.push_back(entry);
		}
		else
		{
			if (throwError)
			{
				throw "directory not exist";
			}
		}
		return files;
	}

	std::vector<std::filesystem::path> everythingInDirectoryRecursive(path directory)
	{
		vector<path> files;
		if (exists(directory))
		{
			for (const auto entry : recursive_directory_iterator(directory))
				files.push_back(entry);
		}
		else
		{
			throw "directory not exist";
		}
		return files;
	}
	std::vector<std::filesystem::path> everythingInDirectoryRecursive(path directory,bool throwError)
	{
		vector<path> files;
		if (exists(directory))
		{
			for (const auto entry : recursive_directory_iterator(directory))
				files.push_back(entry);
		}
		else
		{
			if(throwError)
				throw "directory not exist";
		}
		return files;
	}

	unsigned long long directorySize(path directory)
	{
		unsigned long long result = 0;
		if (exists(directory))
		{
			for (const auto i : everythingInDirectoryRecursive(directory))
				result += file_size(i);
		}
		else
		{
			throw "directory not exist";
		}

		return(result);
	}
	unsigned long long directorySize(path directory, bool throwError)
	{
		unsigned long long result = 0;
		if (exists(directory))
		{
			for (const auto i : everythingInDirectoryRecursive(directory))
				result += file_size(i);
		}
		else
		{
			if(throwError)
				throw "directory not exist";
		}

		return(result);
	}
}