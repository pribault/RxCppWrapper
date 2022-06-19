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
#include "ReadStream.h"
#include "WriteStream.h"

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

			static const size_t	defaultReadBufferSize = 4;
			static const size_t	defaultWriteQueueSize = 1;

			/*
			*************
			** methods **
			*************
			*/

			/**
			 * Destructor
			 */
			virtual ~AsyncFile(void);

			// Stream base
			virtual void		exceptionHandler(const StreamBase<std::string>::ErrorFunction& handler);

			// Read stream
			virtual void		endHandler(const ReadStream<std::string>::EndFunction& handler);
			virtual void		handler(const ReadStream<std::string>::DataFunction& handler);

			virtual void		pause();
			virtual void		resume();

			// Write stream
			virtual void		drainHandler(const WriteStream<std::string>::DrainFunction& handler);
			virtual void		end();
			virtual void		write(const std::string& data);
			virtual void		setWriteQueueMaxSize(size_t size);
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
			 * Constructor
			 */
			AsyncFile(void);

			/**
			 * Constructor
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
