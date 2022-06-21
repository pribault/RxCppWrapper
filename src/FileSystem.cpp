/*
 * MIT License
 * 
 * Copyright (c) 2022 paul ribault
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * File: FileSystem.cpp
 * Created: 29th May 2022 11:19:40 pm
 * Author: Paul Ribault (pribault.dev@gmail.com)
 * 
 * Last Modified: 29th May 2022 11:19:42 pm
 * Modified By: Paul Ribault (pribault.dev@gmail.com)
 */

#include "RxCW/FileSystem.h"

/*
**************
** includes **
**************
*/

// RxCW
#include "RxCW/AsyncFile.h"
#include "RxCW/Single.h"

// stl
#include <filesystem>

/*
****************
** namespaces **
****************
*/

using namespace RxCW;

/*
********************************************************************************
************************************ METHODS ***********************************
********************************************************************************
*/

FileSystem::FileSystem(void)
{
}

FileSystem::~FileSystem(void)
{
}

AsyncFile*			FileSystem::open(const std::string& fileName, const std::string& mode)
{
	return new AsyncFile(fileName, mode);
}

Single<AsyncFile*>	FileSystem::rxOpen(const std::string& fileName, const std::string& mode)
{
	return Single<AsyncFile*>::defer([fileName, mode]()
	{
		return Single<AsyncFile*>::just(FileSystem::open(fileName, mode));
	});
}

bool			FileSystem::exists(const std::string& path)
{
	return std::filesystem::exists(path);
}

Single<bool>	FileSystem::rxExists(const std::string& path)
{
	return Single<bool>::defer([path]()
	{
		return Single<bool>::just(FileSystem::exists(path));
	});
}

void			FileSystem::remove(const std::string& path)
{
	std::filesystem::remove(path);
}

Completable		FileSystem::rxRemove(const std::string& path)
{
	return Completable::defer([path]()
	{
		FileSystem::remove(path);
		return Completable::complete();
	});
}

void			FileSystem::removeRecursive(const std::string& path)
{
	std::filesystem::remove_all(path);
}

Completable		FileSystem::rxRemoveRecursive(const std::string& path)
{
	return Completable::defer([path]()
	{
		FileSystem::removeRecursive(path);
		return Completable::complete();
	});
}

void			FileSystem::move(const std::string& oldPath, const std::string& newPath)
{
	std::filesystem::rename(oldPath, newPath);
}

Completable		FileSystem::rxMove(const std::string& oldPath, const std::string& newPath)
{
	return Completable::defer([oldPath, newPath]()
	{
		FileSystem::move(oldPath, newPath);
		return Completable::complete();
	});
}

void			FileSystem::mkdir(const std::string& path)
{
	std::filesystem::create_directory(path);
}

Completable		FileSystem::rxMkdir(const std::string& path)
{
	return Completable::defer([path]()
	{
		FileSystem::mkdir(path);
		return Completable::complete();
	});
}

void			FileSystem::mkdirs(const std::string& path)
{
	std::filesystem::create_directories(path);
}

Completable		FileSystem::rxMkdirs(const std::string& path)
{
	return Completable::defer([path]()
	{
		FileSystem::mkdirs(path);
		return Completable::complete();
	});
}

size_t			FileSystem::fileSize(const std::string& path)
{
	return std::filesystem::file_size(path);
}

Single<size_t>	FileSystem::rxFileSize(const std::string& path)
{
	return Single<size_t>::defer([path]()
	{
		return Single<size_t>::just(FileSystem::fileSize(path));
	});
}
