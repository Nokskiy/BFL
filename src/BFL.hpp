#pragma once

#include <filesystem>
#include <vector>
#include <fstream>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#include <cstring>
#include <cstring>
#endif
using namespace std;
using namespace std::filesystem;

namespace BFL
{
	inline bool isHidden(const directory_entry& entry)
	{
	#ifdef _WIN32
		// На Windows используем атрибуты файлов
		DWORD attributes = GetFileAttributesW(entry.path().c_str()); // Используем GetFileAttributesW
		if (attributes == INVALID_FILE_ATTRIBUTES)
		{
			std::cerr << "Error getting attributes for: " << entry.path() << std::endl;
			return false;
		}
		return (attributes & FILE_ATTRIBUTE_HIDDEN);
	#else
		// На Linux/Unix скрытые файлы начинаются с точки (.)
		std::string filename = entry.path().filename().string();
		return !filename.empty() && filename[0] == '.';
	#endif
	}

	inline string pathToString(const path& filePath)
	{
		return filePath.string();
	}

	inline path normalPath(path filePath)
	{
		return filePath.make_preferred();
	}

	inline bool isFile(const path& filePath)
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

	inline string fileName(const path& filePath)
	{
		return filePath.filename().string();
	}

	inline path connectPaths(const path& path1,const path& path2)
	{
		return path1.string() + path2.string();
	}

	inline std::vector<std::filesystem::path> everythingInDirectory(const path& directory,const bool& throwError = true)
	{
		vector<path> files;
		if (exists(directory))
		{
			if (!isFile(directory))
			{
				try
				{
					for (const auto& entry : directory_iterator(directory,directory_options::skip_permission_denied))
					{
						if(!isHidden(entry))
						{
							files.push_back(entry);
						}
					}
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << '\n';
				}
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

	inline std::vector<std::filesystem::path> everythingInDirectoryRecursive(const path& directory,const bool& throwError = true)
	{
		vector<path> files;
		if (exists(directory))
		{
			if (!isFile(directory))
			{
				try
				{
					for (const auto& entry : recursive_directory_iterator(directory,directory_options::skip_permission_denied))
					{
						if(!isHidden(entry))
						{
							files.push_back(entry);
						}
					}
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << '\n';
				}
				
				
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

	inline unsigned long long itemSize(const path& directory,const bool& throwError = true)
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

	inline void create(const path& dirPath,const path& name)
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

	inline void rem(const path& dirPath,const bool& printDelFile = false,const bool& throwError = true)
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
				for (const auto& i : everythingInDirectoryRecursive(dirPath))
				{
					if (printDelFile)
						cout << i << endl;
					dirs.push_back(i);
				}
				reverse(dirs.begin(), dirs.end());
				for (const auto& i : dirs)
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
	
	inline void ren(const path& dirPath,const path& name,const bool& throwError = true)
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

	inline auto GetDrives()
	{
		#ifdef _WIN32
		std::vector<std::string> drives;
		char buffer[256];
		DWORD result = GetLogicalDriveStringsA(sizeof(buffer), buffer);

		if (result == 0)
		{
			throw "error";
		}

		char* drive = buffer;
		while (*drive) 
		{
			drives.push_back(drive);
			drive += strlen(drive) + 1;
		}

		return drives;
		#else
		std::vector<std::string> drives;
		DIR* dir;
		struct dirent* entry;

		dir = opendir("/dev");
		if (!dir) 
		{
			throw "error";
		}

		while ((entry = readdir(dir)) != nullptr) 
		{
			if (strncmp(entry->d_name, "sd", 2) == 0 || strncmp(entry->d_name, "hd", 2) == 0) 
			{
				drives.push_back("/dev/" + std::string(entry->d_name));
			}
		}

		closedir(dir);
		return drives;
		#endif
	}

	inline path curPath()
	{
		return current_path();
	}

	inline void clearFile(const path& filePath)
	{
		ofstream op;
		op.open(filePath);
		op.close();
	}

	inline void writeToFile(const path& filePath,const string& text,const bool& nLine = true)
	{
		ofstream op;
		op.open(filePath,ofstream::app);
		if(nLine)
			op << string("\n" + text);
		else
			op << text;
		op.close();
	}

	inline string readFile(const path& filePath)
	{
		ifstream fout;
		fout.open(filePath,ofstream::binary);
		char ch;
		string result;
		while(fout.get(ch))
		{
			result.push_back(ch);
		}
		return result;
	}

	inline auto find(const path& root,const path& target)
	{
		if(root.root_path() == root)
		{
			for(const auto& dirInRoot : everythingInDirectory(root))
			{
				if(!isFile(dirInRoot))
				{
					for(const auto& dir : everythingInDirectoryRecursive(dirInRoot))
					{
						if(pathToString(dir).find(pathToString(target)) != std::string::npos)
						{
							return dir;
						}
					}
				}
				else
				{
					if(pathToString(dirInRoot).find(pathToString(target)) != std::string::npos)
					{
						return dirInRoot;
					}
				}
			}
		}
	}
}