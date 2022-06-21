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
 * File: WriteStream.h
 * Created: 28th May 2022 9:35:17 am
 * Author: Paul Ribault (pribault.dev@gmail.com)
 * 
 * Last Modified: 28th May 2022 9:35:40 am
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
#include "RxCW/StreamBase.h"

// stl
#include <functional>

/*
****************
** class used **
****************
*/

/*
**********************
** class definition **
**********************
*/

namespace	RxCW
{
	/**
	 * @class WriteStream WriteStream.h RxCW/WriteStream.h
	 * @brief the base class for reactive write streams.
	 * 
	 * @tparam T the type handled by the stream
	 */
	template	<typename T>
	class	WriteStream : public virtual StreamBase<T>
	{

		/*
		************************************************************************
		******************************** PUBLIC ********************************
		************************************************************************
		*/

		public:

			template<typename> friend class	WriteStream;

			/*
			***********
			** types **
			***********
			*/

			/**
			 * @brief Function that will be called when the stream accepts writing again.
			 */
			typedef std::function<void()>			DrainFunction;

			/*
			*************
			** methods **
			*************
			*/

			/**
			 * @brief Destroy the Write Stream object.
			 */
			virtual ~WriteStream(void);

			/**
			 * @brief Set the handler to call when data can be pushed to the write queue again.
			 * 
			 * @param handler The handler.
			 */
			virtual void			drainHandler(const DrainFunction& handler) = 0;

			/**
			 * @brief End stream.
			 */
			virtual void			end() = 0;

			/**
			 * @brief Reactive version of the @ref end method.
			 * 
			 * @return The resulting Completable.
			 */
			virtual Completable		rxEnd();

			/**
			 * @brief Write the given data to the stream.
			 * 
			 * @param data The data to write to the stream.
			 */
			virtual void			write(const T& data) = 0;

			/**
			 * @brief Reactive version of the @ref write method.
			 * 
			 * @param data The data to write to the stream.
			 * @return The resulting Completable.
			 */
			virtual Completable		rxWrite(const T& data);

			/**
			 * @brief Set the write queue max size.
			 * 
			 * @param size The write queue max size.
			 */
			virtual void			setWriteQueueMaxSize(size_t size) = 0;

			/**
			 * @brief Checks if the write queue is full.
			 * 
			 * @return \b true: no more data can be written to the file for now.
			 * @return \b false: data can be written to the file.
			 */
			virtual bool			writeQueueFull() = 0;

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
			 * @brief Construct the Write Stream object.
			 */
			WriteStream(void);

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

	};
}

#include <RxCW/WriteStream.inl>
