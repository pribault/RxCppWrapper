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
#include "Completable.h"
#include "StreamBase.h"

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
	template	<typename T>
	class	ReadStream : public StreamBase<T>
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

			typedef std::function<void()>			EndFunction;
			typedef std::function<void(const T&)>	DataFunction;

			/*
			*************
			** methods **
			*************
			*/

			/**
			 * Destructor
			 */
			virtual ~ReadStream(void);

			virtual void	endHandler(const EndFunction& handler) = 0;
			virtual void	handler(const DataFunction& handler) = 0;

			virtual void		pause() = 0;
			virtual void		resume() = 0;
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
			 * Constructor
			 */
			ReadStream(void);

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

#include <ReadStream.inl>
