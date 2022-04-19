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
 * File: Observable.h
 * Created: Tuesday, 12th April 2022 9:24:34 am
 * Author: Paul Ribault (pribault.dev@gmail.com)
 * 
 * Last Modified: Tuesday, 12th April 2022 9:43:11 am
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
****************
** class used **
****************
*/

namespace	RxCW
{
	class		Completable;
	template	<typename T>
	class		Maybe;
}

/*
**********************
** class definition **
**********************
*/

namespace	RxCW
{
	template	<typename T>
	class	Observable
	{

		/*
		************************************************************************
		******************************** PUBLIC ********************************
		************************************************************************
		*/

		public:

			template<typename> friend class	Observable;

			/*
			***********
			** types **
			***********
			*/

			typedef std::function<void(T)>													SuccessFunction;
			typedef std::function<void(std::exception_ptr)>									ErrorFunction;
			typedef std::function<void()>													CompleteFunction;
			typedef std::function<void(SuccessFunction, CompleteFunction, ErrorFunction)>	Handler;

			/*
			*************
			** methods **
			*************
			*/

			/**
			 * Destructor
			 */
			~Observable(void);

			static Observable<T>	create(const Handler& handler);
			static Observable<T>	defer(const std::function<Observable<T>()>& function);
			static Observable<T>	empty();
			static Observable<T>	never();
			static Observable<T>	just(const T& value);
			static Observable<T>	error(std::exception_ptr e);
			static Observable<T>	range(T start, T end, std::ptrdiff_t step = 1);
			static Observable<T>	interval(std::chrono::steady_clock::duration period);
			static Observable<T>	interval(std::chrono::steady_clock::time_point when, std::chrono::steady_clock::duration period);

			Observable<T>		take(size_t count);
			Observable<T>		take_last(size_t count);
			Observable<T>		doOnSuccess(const SuccessFunction& onSuccess);
			Observable<T>		doOnError(const ErrorFunction& onError);
			Observable<T>		doOnComplete(const CompleteFunction& onComplete);
			Observable<T>		observeOn(rxcpp::observe_on_one_worker coordination);
			Observable<T>		subscribeOn(rxcpp::synchronize_in_one_worker coordination);
			void				subscribe(const SuccessFunction& onSuccess, const ErrorFunction& onError, const CompleteFunction& onComplete);

			template	<typename R>
			Observable<R>		map(const std::function<R(T)>& function);
			template	<typename R>
			Observable<R>		flatMap(const std::function<Observable<R>(T)>& function);

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
			Observable(const rxcpp::observable<T>& observable);

			/*
			****************
			** attributes **
			****************
			*/

			std::shared_ptr<rxcpp::observable<T>>	_observable;

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
			Observable(void);

	};
}

#include <Observable.inl>
