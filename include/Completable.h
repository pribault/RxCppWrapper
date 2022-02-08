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
 * File: Completable.h
 * Created: 8th February 2022 12:11:45 pm
 * Author: Paul Ribault (pribault.dev@gmail.com)
 * 
 * Last Modified: 8th February 2022 12:15:22 pm
 * Modified By: Paul Ribault (pribault.dev@gmail.com)
 */

#pragma once

/*
**************
** includes **
**************
*/

// RxCpp
#include <rx-observable.hpp>

/*
**********************
** class definition **
**********************
*/

namespace	RxCW
{
	class	Completable
	{

		/*
		************************************************************************
		******************************** PUBLIC ********************************
		************************************************************************
		*/

		public:

			/*
			***********
			** types **
			***********
			*/

			typedef std::function<void()>								SuccessFunction;
			typedef std::function<void(std::exception_ptr)>				ErrorFunction;
			typedef std::function<void()>								CompleteFunction;
			typedef std::function<void(SuccessFunction, ErrorFunction)>	Handler;

			/*
			*************
			** methods **
			*************
			*/

			/**
			 * Destructor
			 */
			~Completable(void);

			static Completable	create(const Handler& handler);
			static Completable	defer(const std::function<Completable()>& function);
			static Completable	complete();
			static Completable	error(std::exception_ptr e);

			Completable		andThen(Completable& other);
			Completable		doOnSuccess(const SuccessFunction& onSuccess);
			Completable		doOnError(const ErrorFunction& onError);
			Completable		doOnComplete(const CompleteFunction& onComplete);
			void			subscribe(const SuccessFunction& onSuccess, const ErrorFunction& onError, const CompleteFunction& onComplete);

		/*
		************************************************************************
		******************************* PROTECTED ******************************
		************************************************************************
		*/

		protected:

			/*
			****************
			** attributes **
			****************
			*/

			std::shared_ptr<rxcpp::observable<int>>	_observable;

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
			 * Constructor
			 */
			Completable(const rxcpp::observable<int>& observable);

			/**
			 * Constructor
			 */
			Completable(void);

	};
}
