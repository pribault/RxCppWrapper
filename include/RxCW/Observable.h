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
#include <rx.hpp>

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
	/**
	 * @class Observable Observable.h RxCW/Observable.h
	 * @brief Represents an asynchronous object that can handle a flow of data, complete or fail.
	 * 
	 * @tparam The value type an Observable can handle.
	 */
	template	<typename T>
	class	Observable
	{

		/*
		************************************************************************
		******************************** PUBLIC ********************************
		************************************************************************
		*/

		public:

			friend class					Completable;
			template<typename> friend class	Observable;

			/*
			***********
			** types **
			***********
			*/

			/**
			 * @brief Function that can be called for each Observable value.
			 */
			typedef std::function<void(T)>													SuccessFunction;

			/**
			 * @brief Function that can be called when an Observable fails.
			 */
			typedef std::function<void(std::exception_ptr)>									ErrorFunction;

			/**
			 * @brief Function that can be called when an Observable completes.
			 */
			typedef std::function<void()>													CompleteFunction;

			/**
			 * @brief Function that can be used to construct a new Observable. It takes three other functions to provide values to the Observable, complete it or make it fail.
			 */
			typedef std::function<void(SuccessFunction, CompleteFunction, ErrorFunction)>	Handler;

			/*
			*************
			** methods **
			*************
			*/

			/**
			 * @brief Destroy the Observable object.
			 */
			~Observable(void);

			/**
			 * @brief Create a new Observable using the given handler.
			 * 
			 * @param handler The handler.
			 * @return Observable The resulting Observable.
			 */
			static Observable<T>	create(const Handler& handler);

			/**
			 * @brief Defer Observable creation to the given function.
			 * 
			 * @param function The function.
			 * @return Observable The resulting Observable.
			 */
			static Observable<T>	defer(const std::function<Observable<T>()>& function);

			/**
			 * @brief Create an Observable with no value.
			 * 
			 * @return Observable The resulting Observable.
			 */
			static Observable<T>	empty();

			/**
			 * @brief Create an Observable that never completes nor fails.
			 * 
			 * @return Observable The resulting Observable.
			 */
			static Observable<T>	never();

			/**
			 * @brief Create an Observable with the given value.
			 * 
			 * @param value The value.
			 * @return Observable The resulting Observable.
			 */
			static Observable<T>	just(const T& value);

			/**
			 * @brief Create an Observable instance failing instantly with the given error when subscribed to.
			 * 
			 * @param error The error as an exception pointer.
			 * @return Observable The resulting Observable.
			 */
			static Observable<T>	error(std::exception_ptr error);

			/**
			 * @brief Create an Observable with a range of values.
			 * 
			 * @param start The start value of the range.
			 * @param end The end value of the range.
			 * @param step The step between each value of the range.
			 * @return Observable The resulting Observable.
			 */
			static Observable<T>	range(T start, T end, std::ptrdiff_t step = 1);

			/**
			 * @brief Create an Observable emitting a value every specified time interval.
			 * 
			 * @param period The time interval between each value.
			 * @return Observable The resulting Observable.
			 */
			static Observable<T>	interval(std::chrono::steady_clock::duration period);

			/**
			 * @brief Create an Observable emitting a value every specified time interval starting from the given time point.
			 * 
			 * @param when The time point the Observable should start emitting from.
			 * @param period The time interval between each value.
			 * @return Observable The resulting Observable.
			 */
			static Observable<T>	interval(std::chrono::steady_clock::time_point when, std::chrono::steady_clock::duration period);

			/**
			 * @brief Take the first count values.
			 * 
			 * @param count The number of values to take.
			 * @return Observable The resulting Observable.
			 */
			Observable<T>		take(size_t count);

			/**
			 * @brief Take the last count values.
			 * 
			 * @param count The number of values to take.
			 * @return Observable The resulting Observable.
			 */
			Observable<T>		take_last(size_t count);

			/**
			 * @brief Convert this Observable to a Completable.
			 * 
			 * @return Completable The resulting Completable.
			 */
			Completable			ignoreElements();

			/**
			 * @brief Returns a Maybe containing the value at the specified index or nothing if that index is out of range.
			 * 
			 * @param index The item index.
			 * @return Maybe<T> The resulting Maybe.
			 */
			Maybe<T>			elementAt(size_t index);

			/**
			 * @brief Returns a Single containing the value at the specified index, or an error if that index is out of range.
			 * 
			 * @param index The item index.
			 * @return Single<T> The resulting Single.
			 */
			Single<T>			elementAtOrError(size_t index);

			/**
			 * @brief Returns a Maybe containing the value of the first item or nothing if that Observable is empty.
			 * 
			 * @return Maybe<T> The resulting Maybe.
			 */
			Maybe<T>			first();

			/**
			 * @brief Returns a Single containing the value of the first item or an error if that Observable is empty.
			 * 
			 * @return Single<T> The resulting Single.
			 */
			Single<T>			firstOrError();

			/**
			 * @brief Returns a Maybe containing the value of the last item or nothing if that Observable is empty.
			 * 
			 * @return Maybe<T> The resulting Maybe.
			 */
			Maybe<T>			last();

			/**
			 * @brief Returns a Single containing the value of the last item or an error if that Observable is empty.
			 * 
			 * @return Single<T> The resulting Single.
			 */
			Single<T>			lastOrError();

			/**
			 * @brief Calls the given function for each Observable value.
			 * 
			 * @param onSuccess The function to call.
			 * @return Observable The resulting Observable.
			 */
			Observable<T>		doOnSuccess(const SuccessFunction& onSuccess);

			/**
			 * @brief Calls the given function on this Observable error.
			 * 
			 * @param onError The function to call.
			 * @return Observable The resulting Observable.
			 */
			Observable<T>		doOnError(const ErrorFunction& onError);

			/**
			 * @brief Calls the given function on this Observable completion.
			 * 
			 * @param onComplete The function to call.
			 * @return Observable The resulting Observable.
			 */
			Observable<T>		doOnComplete(const CompleteFunction& onComplete);

			/**
			 * @brief Calls the given function on this Observable end.
			 * 
			 * @param onTerminate The function to call.
			 * @return Observable The resulting Observable.
			 */
			Observable<T>		doOnTerminate(const CompleteFunction& onTerminate);

			/**
			 * @brief All values are queued and delivered using the given rxcpp coordination.
			 * 
			 * @param coordination The rxcpp coordination.
			 * @return Observable The resulting Observable.
			 */
			Observable<T>		observeOn(rxcpp::observe_on_one_worker coordination);

			/**
			 * @brief Subscription and unsubscription are queued and delivered using the given rxcpp coordination.
			 * 
			 * @param coordination The rxcpp coordination.
			 * @return Observable The resulting Observable.
			 */
			Observable<T>		subscribeOn(rxcpp::synchronize_in_one_worker coordination);

			/**
			 * @brief Subscribe to this Observable.
			 */
			void				subscribe();

			/**
			 * @brief Subscribe to this Observable.
			 * 
			 * @param onSuccess Function called on Observable success for each value.
			 */
			void				subscribe(const SuccessFunction& onSuccess);

			/**
			 * @brief Subscribe to this Observable.
			 * 
			 * @param onError Function called on Observable error.
			 */
			void				subscribe(const ErrorFunction& onError);

			/**
			 * @brief Subscribe to this Observable.
			 * 
			 * @param onComplete Function called on Observable completion.
			 */
			void				subscribe(const CompleteFunction& onComplete);

			/**
			 * @brief Subscribe to this Observable.
			 * 
			 * @param onSuccess Function called on Observable success for each value.
			 * @param onError Function called on Observable error.
			 */
			void				subscribe(const SuccessFunction& onSuccess, const ErrorFunction& onError);

			/**
			 * @brief Subscribe to this Observable.
			 * 
			 * @param onSuccess Function called on Observable success for each value.
			 * @param onError Function called on Observable success with the Observable value.
			 * @param onComplete Function called on Observable completion.
			 */
			void				subscribe(const SuccessFunction& onSuccess, const ErrorFunction& onError, const CompleteFunction& onComplete);

			/**
			 * @brief Apply the given function to the Observable values.
			 * 
			 * @param function The function to apply to the Observable values.
			 * @tparam The type of the values returned by the function.
			 * @return Observable The resulting Observable.
			 */
			template	<typename R>
			Observable<R>		map(const std::function<R(T)>& function);

			/**
			 * @brief Apply a function returning an Observable to the values.
			 * 
			 * @param function The function to apply to the Observable values.
			 * @tparam The type of the Observable values returned by the function.
			 * @return Observable The resulting Observable.
			 */
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
			 * @brief Construct a new Observable object.
			 * 
			 * @param observable The underlying rxcpp observable.
			 */
			Observable(const rxcpp::observable<T>& observable);

			/*
			****************
			** attributes **
			****************
			*/

			/**
			 * @brief The underlying rxcpp observable.
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
			 * @brief Construct a new Observable object.
			 */
			Observable(void);

	};
}

#include <RxCW/Observable.inl>
