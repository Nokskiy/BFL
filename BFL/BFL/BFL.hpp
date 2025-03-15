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
		if (exists(filePath))
		{
			return filesystem::is_regular_file(filePath);
		}
		else
		{
			return filePath.string().back() != '/';
		}
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

	void rem(path dirPath,bool printDelFile = false, bool throwError = true)
	{
		if (exists(dirPath))
		{
			if (isFile(dirPath))
			{
				filesystem::remove(dirPath);
			}
			else
			{
				vector<path> dirs;
				for (const auto i : everythingInDirectoryRecursive(dirPath))
				{
					if (printDelFile)
						cout << i << endl;
					dirs.push_back(i);
				}
				reverse(dirs.begin(), dirs.end());
				for (const auto i : dirs)
				{
					filesystem::remove(i);
				}
				if (printDelFile)
					cout << dirPath << endl;
				filesystem::remove(dirPath);
			}
		}
		else
		{
			if(throwError)
				throw "directory/file not exist";
		}
	}
	void ren(path dirPath, path name, bool throwError = true)
	{
		if (exists(dirPath))
		{
			string newName = dirPath.string();

			for (int i = 0; i < fileName(dirPath).length(); i++)
				newName.pop_back();
			for (int i = 0; i < name.string().length(); i++)
				newName.push_back(name.string()[i]);

			rename(dirPath, newName);
		}
		else
		{
			if (throwError)
			{
				throw "directory/file not exist";
			}
		}
	}
}