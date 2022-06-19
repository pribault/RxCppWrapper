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
 * File: Maybe.h
 * Created: 8th February 2022 2:24:15 pm
 * Author: Paul Ribault (pribault.dev@gmail.com)
 * 
 * Last Modified: 8th February 2022 2:24:35 pm
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
	template	<typename T>
	class		Single;
}

/*
**********************
** class definition **
**********************
*/

namespace	RxCW
{
	template	<typename T>
	class	Maybe
	{

		/*
		************************************************************************
		******************************** PUBLIC ********************************
		************************************************************************
		*/

		public:

			friend class					Completable;
			template<typename> friend class	Maybe;
			template<typename> friend class	Single;

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
			~Maybe(void);

			static Maybe<T>	create(const Handler& handler);
			static Maybe<T>	defer(const std::function<Maybe<T>()>& function);
			static Maybe<T>	just(const T& value);
			static Maybe<T>	error(std::exception_ptr e);
			static Maybe<T>	empty();
			static Maybe<T>	never();

			Maybe<T>		doOnSuccess(const SuccessFunction& onSuccess);
			Maybe<T>		doOnError(const ErrorFunction& onError);
			Maybe<T>		doOnComplete(const CompleteFunction& onComplete);
			Single<bool>	isEmpty();
			Maybe<T>		switchIfEmpty(Maybe<T>& other);
			Single<T>		toSingle();
			Maybe<T>		observeOn(rxcpp::observe_on_one_worker coordination);
			Maybe<T>		subscribeOn(rxcpp::synchronize_in_one_worker coordination);
			void			subscribe();
			void			subscribe(const SuccessFunction& onSuccess);
			void			subscribe(const ErrorFunction& onError);
			void			subscribe(const CompleteFunction& onComplete);
			void			subscribe(const SuccessFunction& onSuccess, const ErrorFunction& onError);
			void			subscribe(const SuccessFunction& onSuccess, const ErrorFunction& onError, const CompleteFunction& onComplete);

			template	<typename R>
			Maybe<R>		map(const std::function<R(T)>& function);
			template	<typename R>
			Maybe<R>		flatMap(const std::function<Maybe<R>(T)>& function);

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
			Maybe(const rxcpp::observable<T>& observable);

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
			Maybe(void);

	};
}

#include <Maybe.inl>
