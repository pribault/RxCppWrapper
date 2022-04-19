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
 * File: Single.h
 * Created: 8th February 2022 2:24:10 pm
 * Author: Paul Ribault (pribault.dev@gmail.com)
 * 
 * Last Modified: 8th February 2022 2:24:38 pm
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
	class	Single
	{

		/*
		************************************************************************
		******************************** PUBLIC ********************************
		************************************************************************
		*/

		public:

			template<typename> friend class	Single;
			template<typename> friend class	Maybe;

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
			~Single(void);

			static Single<T>	create(const Handler& handler);
			static Single<T>	defer(const std::function<Single<T>()>& function);
			static Single<T>	just(const T& value);
			static Single<T>	error(std::exception_ptr e);
			static Single<T>	never();

			Single<T>		doOnSuccess(const SuccessFunction& onSuccess);
			Single<T>		doOnError(const ErrorFunction& onError);
			Single<T>		doOnComplete(const CompleteFunction& onComplete);
			Maybe<T>		toMaybe();
			Completable		ignoreElement();
			Single<T>		observeOn(rxcpp::observe_on_one_worker coordination);
			Single<T>		subscribeOn(rxcpp::synchronize_in_one_worker coordination);
			void			subscribe(const SuccessFunction& onSuccess, const ErrorFunction& onError, const CompleteFunction& onComplete);

			template	<typename R>
			Single<R>		map(const std::function<R(T)>& function);
			template	<typename R>
			Single<R>		flatMap(const std::function<Single<R>(T)>& function);

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
			Single(const rxcpp::observable<T>& observable);

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
			Single(void);

	};
}

#include <Single.inl>
