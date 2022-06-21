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
 * File: FileSystem.h
 * Created: 29th May 2022 11:19:18 pm
 * Author: Paul Ribault (pribault.dev@gmail.com)
 * 
 * Last Modified: 29th May 2022 11:19:20 pm
 * Modified By: Paul Ribault (pribault.dev@gmail.com)
 */

#pragma once

/*
**************
** includes **
**************
*/

// RxCW
#include "RxCW/Completable.h"
#include "RxCW/Single.h"

// stl
#include <string>

/*
****************
** class used **
****************
*/
namespace	RxCW
{
	class	AsyncFile;
}

/*
**********************
** class definition **
**********************
*/

namespace	RxCW
{
	/**
	 * @class FileSystem FileSystem.h RxCW/FileSystem.h
	 * @brief Utility class to asynchronously manipulate the file system.
	 */
	class	FileSystem
	{

		/*
		************************************************************************
		******************************** PUBLIC ********************************
		************************************************************************
		*/

		public:

			/*
			*************
			** methods **
			*************
			*/

			/**
			 * @brief Destroy the File System object
			 */
			virtual ~FileSystem(void);

			/**
			 * @brief Open the given file with the specified modes.
			 * 
			 * @param path The file to open.
			 * @param mode The mode to open the file with.
			 * @return AsyncFile* The resulting object to manipulate the file with. Can be:\n
			 *  - @b r: Open the file for reading, does not create the file if it does not already exists.\n
			 *  - @b w: Create a file for writing, truncate the file if it already exists, create it otherwise.\n
			 *  - @b a: Append to a file, create it if it does not already exists.\n
			 *  - @b r+: Open a file for read/write, does not create the file if it does not already exists.\n
			 *  - @b w+: Create a file for read/write, truncate the file if it already exists, create it otherwise.\n
			 *  - @b a+: Open a file for read/write, writings will be appended to the file. Create the file if it does not already exists.\n
			 */
			static AsyncFile*			open(const std::string& path, const std::string& mode);

			/**
			 * @brief The reactive version of the @ref open method.
			 * 
			 * @param path The file to open.
			 * @param mode The mode to open the file with.
			 * @return Single<AsyncFile*> The resulting Single.
			 */
			static Single<AsyncFile*>	rxOpen(const std::string& path, const std::string& mode);

			/**
			 * @brief Check if a file or directory exists
			 * 
			 * @param path The path to check.
			 * @return \b true: if file or directory exists.
			 * @return \b false: if file or directory does not exists.
			 */
			static bool				exists(const std::string& path);

			/**
			 * @brief The reactive version of the @ref exists method.
			 * 
			 * @param path The file to check.
			 * @return Single<bool> The resulting Single.
			 */
			static Single<bool>		rxExists(const std::string& path);

			/**
			 * @brief Remove a file or directory.
			 * 
			 * @param path The file or directory to remove.
			 */
			static void				remove(const std::string& path);

			/**
			 * @brief The reactive version of the @ref remove method.
			 * 
			 * @param path The file or directory to remove.
			 * @return Completable The resulting Completable.
			 */
			static Completable		rxRemove(const std::string& path);

			/**
			 * @brief Remove a file or directory with all its content.
			 * 
			 * @param path The file or directory to remove recursively.
			 */
			static void				removeRecursive(const std::string& path);

			/**
			 * @brief The reactive version of the @ref removeRecursive method.
			 * 
			 * @param path The file or directory to remove recursively.
			 * @return Completable The resulting Completable.
			 */
			static Completable		rxRemoveRecursive(const std::string& path);

			/**
			 * @brief Move/rename a file or a directory.
			 * 
			 * @param oldPath The current path.
			 * @param newPath The destination path.
			 */
			static void				move(const std::string& oldPath, const std::string& newPath);

			/**
			 * @brief The reactive version of the @ref move method.
			 * 
			 * @param oldPath The current path.
			 * @param newPath The destination path.
			 * @return Completable The resulting Completable.
			 */
			static Completable		rxMove(const std::string& oldPath, const std::string& newPath);

			/**
			 * @brief Create a directory.
			 * 
			 * @param path The directory path.
			 */
			static void				mkdir(const std::string& path);

			/**
			 * @brief The reactive version of the @ref mkdir method.
			 * 
			 * @param path The directory path.
			 * @return Completable The resulting Completable.
			 */
			static Completable		rxMkdir(const std::string& path);

			/**
			 * @brief Create a directory and all its parents if they don't exists.
			 * 
			 * @param path The directory path.
			 */
			static void				mkdirs(const std::string& path);

			/**
			 * @brief The reactive version of the @ref mkdirs method.
			 * 
			 * @param path The directory path.
			 * @return Completable The resulting Completable.
			 */
			static Completable		rxMkdirs(const std::string& path);

			/**
			 * @brief Get a file size.
			 * 
			 * @param path The file path.
			 * @return size_t The file size.
			 */
			static size_t			fileSize(const std::string& path);

			/**
			 * @brief The reactive version of the @ref fileSize method.
			 * 
			 * @param path The file path.
			 * @return Completable The resulting Completable.
			 */
			static Single<size_t>	rxFileSize(const std::string& path);

		/*
		************************************************************************
		******************************** PRIVATE *******************************
		************************************************************************
		*/

		private:

			/*
			*************
			** methods **
			*************
			*/

			/**
			 * @brief Construct a new File System object
			 */
			FileSystem(void);

	};
}
