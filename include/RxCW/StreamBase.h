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
 * File: StreamBase.h
 * Created: 28th May 2022 9:35:05 am
 * Author: Paul Ribault (pribault.dev@gmail.com)
 * 
 * Last Modified: 28th May 2022 9:35:36 am
 * Modified By: Paul Ribault (pribault.dev@gmail.com)
 */

#pragma once

/*
**********************
** class definition **
**********************
*/

namespace	RxCW
{
	/**
	 * @class StreamBase StreamBase.h RxCW/StreamBase.h
	 * @brief the base class for reactive streams.
	 * 
	 * @tparam T the type handled by the stream
	 */
	template	<typename T>
	class	StreamBase
	{

		/*
		************************************************************************
		******************************** PUBLIC ********************************
		************************************************************************
		*/

		public:

			/*
			*************
			** friends **
			*************
			*/

			template<typename> friend class	StreamBase;

			/*
			***********
			** types **
			***********
			*/

			/**
			 * @brief Function that can be called when the stream encounters an exception.
			 */
			typedef std::function<void(std::exception_ptr)>		ErrorFunction;

			/*
			*************
			** methods **
			*************
			*/

			/**
			 * @brief Destroy the Stream Base object.
			 */
			virtual ~StreamBase(void);

			/**
			 * @brief set the exception handler. Will be called when an exception occurs.
			 * 
			 * @param handler the handler to call
			 */
			virtual void	exceptionHandler(const ErrorFunction& handler) = 0;

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
			 * @brief Construct the Stream Base object.
			 */
			StreamBase(void);

	};
}

#include <RxCW/StreamBase.inl>
