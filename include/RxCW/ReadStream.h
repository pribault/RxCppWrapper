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
 * File: ReadStream.h
 * Created: 28th May 2022 9:35:11 am
 * Author: Paul Ribault (pribault.dev@gmail.com)
 * 
 * Last Modified: 28th May 2022 9:35:26 am
 * Modified By: Paul Ribault (pribault.dev@gmail.com)
 */

#pragma once

/*
**************
** includes **
**************
*/

// RxCW
#include <RxCW/Completable.h>
#include <RxCW/StreamBase.h>

// stl
#include <functional>

/*
****************
** class used **
****************
*/

namespace	RxCW
{
	class	Completable;
	template	<typename T>
	class	WriteStream;
}

/*
**********************
** class definition **
**********************
*/

namespace	RxCW
{
	/**
	 * @class ReadStream ReadStream.h RxCW/ReadStream.h
	 * @brief the base class for reactive read streams.
	 * 
	 * @tparam T the type handled by the stream
	 */
	template	<typename T>
	class	ReadStream : public virtual StreamBase<T>
	{

		/*
		************************************************************************
		******************************** PUBLIC ********************************
		************************************************************************
		*/

		public:

			template<typename> friend class	ReadStream;

			/*
			***********
			** types **
			***********
			*/

			/**
			 * @brief Function that will be called when the stream ends.
			 */
			typedef std::function<void()>			EndFunction;

			/**
			 * @brief Function that will be called for each block of data read.
			 */
			typedef std::function<void(const T&)>	DataFunction;

			/*
			*************
			** methods **
			*************
			*/

			/**
			 * @brief Destroy the Read Stream object.
			 */
			virtual ~ReadStream(void);

			/**
			 * @brief Set the handler to call when the file end is reached while reading.
			 * 
			 * @param handler The handler.
			 */
			virtual void		endHandler(const EndFunction& handler) = 0;

			/**
			 * @brief Set the handler to call for each block of data read.
			 * 
			 * @param handler The handler.
			 */
			virtual void		handler(const DataFunction& handler) = 0;

			/**
			 * @brief Pause the stream.
			 */
			virtual void		pause() = 0;

			/**
			 * @brief Resume the stream.
			 */
			virtual void		resume() = 0;

			/**
			 * @brief Asynchronously pipe this stream to the given WriteStream.
			 * 
			 * @param writeStream The WriteStream to pipe this ReadStream to.
			 * @return The resulting Completable.
			 */
			virtual Completable	rxPipeTo(WriteStream<T>& writeStream);

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
			 * @brief Construct the Read Stream object.
			 */
			ReadStream(void);

	};
}

#include <RxCW/ReadStream.inl>
