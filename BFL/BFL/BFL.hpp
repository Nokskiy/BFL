#pragma once

#include <filesystem>
#include <vector>
#include <fstream>

namespace BFL
{
	using namespace std;
	using namespace std::filesystem;

	bool isFile(path filePath)
	{
		return filePath.string().back() != '/';
	}

	string fileName(path filePath)
	{
		return filePath.filename().string();
	}

	path connectPaths(path path1, path path2)
	{
		return path1.string() + path2.string();
	}

	std::vector<std::filesystem::path> everythingInDirectory(path directory, bool throwError = true)
	{
		vector<path> files;
		if (exists(directory))
		{
			if (!isFile(directory))
			{
				for (const auto entry : directory_iterator(directory))
					files.push_back(entry);
			}
			else
			{
				if (throwError)
					throw "not a directory";
			}
		}
		else
		{
			if (throwError)
				throw "directory not exist";
		}
		return files;
	}

	std::vector<std::filesystem::path> everythingInDirectoryRecursive(path directory,bool throwError = true)
	{
		vector<path> files;
		if (exists(directory))
		{
			if (!isFile(directory))
			{
				for (const auto entry : recursive_directory_iterator(directory))
					files.push_back(entry);
			}
			else
			{
				if (throwError)
					throw "not a directory";
			}
		}
		else
		{
			if (throwError)
				throw "directory not exist";
		}
		return files;
	}

	unsigned long long itemSize(path directory, bool throwError = true)
	{
		unsigned long long result = 0;
		if (exists(directory))
		{
			if (!isFile(directory))
			{
				for (const auto i : everythingInDirectoryRecursive(directory))
					result += file_size(i);
			}
			else
			{
				result = file_size(directory);
			}
		}
		else
		{
			if(throwError)
				throw "directory not exist";
		}

		return(result);
	}

	void create(path dirPath,path name)
	{
		if (isFile(connectPaths(dirPath, name)))
		{
			ofstream out;
			out.open(connectPaths(dirPath, name));
			out.close();
		}
		else
		{
			create_directory(connectPaths(dirPath, name));
		}
	}
}