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
 * File: AsyncFile.h
 * Created: 6th June 2022 1:44:47 pm
 * Author: Paul Ribault (pribault.dev@gmail.com)
 * 
 * Last Modified: 6th June 2022 1:44:52 pm
 * Modified By: Paul Ribault (pribault.dev@gmail.com)
 */

#pragma once

/*
**************
** includes **
**************
*/

// RxCW
#include "RxCW/ReadStream.h"
#include "RxCW/WriteStream.h"

// stl
#include <string>

/*
****************
** class used **
****************
*/

namespace	RxCW
{
	class	FileSystem;
}

/*
**********************
** class definition **
**********************
*/

namespace	RxCW
{
	/**
	 * @class AsyncFile AsyncFile.h RxCW/AsyncFile.h
	 * @brief Allows to asynchronously read from and write to a file.
	 */
	class	AsyncFile : public ReadStream<std::string>, public WriteStream<std::string>
	{

		/*
		************************************************************************
		******************************** PUBLIC ********************************
		************************************************************************
		*/

		public:

			friend class	FileSystem;

			/*
			***********
			** types **
			***********
			*/

			/**
			 * @brief The default read buffer size.
			 * 
			 */
			static const size_t	DEFAULT_READ_BUFFER_SIZE = 4096;
			/**
			 * @brief The default write queue size.
			 */
			static const size_t	DEFAULT_WRITE_QUEUE_SIZE = 16;

			/*
			*************
			** methods **
			*************
			*/

			/**
			 * @brief Destroy the Async File object
			 */
			virtual ~AsyncFile(void);

			/**
			 * @brief Set the handler to call when an exception occurs.
			 * 
			 * @param handler The handler.
			 */
			virtual void		exceptionHandler(const StreamBase<std::string>::ErrorFunction& handler);

			/**
			 * @brief Set the handler to call when the file end is reached while reading.
			 * 
			 * @param handler The handler.
			 */
			virtual void		endHandler(const ReadStream<std::string>::EndFunction& handler);

			/**
			 * @brief Set the handler to call for each block of data read.
			 * 
			 * @param handler The handler.
			 */
			virtual void		handler(const ReadStream<std::string>::DataFunction& handler);

			/**
			 * @brief Pause the stream for reading.
			 */
			virtual void		pause();

			/**
			 * @brief Resume the stream for reading.
			 */
			virtual void		resume();

			/**
			 * @brief Set the handler to call when data can be pushed to the write queue again.
			 * 
			 * @param handler The handler.
			 */
			virtual void		drainHandler(const WriteStream<std::string>::DrainFunction& handler);

			/**
			 * @brief End writing.
			 */
			virtual void		end();

			/**
			 * @brief Write the given data to the file.
			 * 
			 * @param data The data to write to the file.
			 */
			virtual void		write(const std::string& data);

			/**
			 * @brief Set the write queue max size.
			 * 
			 * @param size The write queue max size.
			 */
			virtual void		setWriteQueueMaxSize(size_t size);

			/**
			 * @brief Checks if the write queue is full.
			 * 
			 * @return \b true: no more data can be written to the file for now.
			 * @return \b false: data can be written to the file.
			 */
			virtual bool		writeQueueFull();

		/*
		************************************************************************
		******************************* PROTECTED ******************************
		************************************************************************
		*/

		protected:

			/*
			*************
			** methods **
			*************
			*/

			/**
			 * @brief Construct a new Async File object.
			 */
			AsyncFile(void);

			/**
			 * @brief Construct a new Async File object.
			 * 
			 * @param fileName The file to open.
			 * @param mode The mode to open the file with.
			 * 
			 * @see FileSystem::open
			 */
			AsyncFile(const std::string& fileName, const std::string& mode);

			/*
			****************
			** attributes **
			****************
			*/

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

			Completable	rxInternalRead();
			Completable	rxInternalWrite();

			/*
			****************
			** attributes **
			****************
			*/

			std::FILE*	_file;
			bool		_closed;

			size_t		_readBufferSize;
			bool		_paused;
			bool		_readEnded;

			bool					_writeEnded;
			size_t					_writeQueueSize;
			bool					_writeQueueFull;
			std::list<std::string>	_writeQueue;

			StreamBase<std::string>::ErrorFunction	_errorHandler;
			ReadStream<std::string>::EndFunction	_endHandler;
			WriteStream<std::string>::DrainFunction	_drainHandler;
			ReadStream<std::string>::DataFunction	_dataHandler;

	};
}
