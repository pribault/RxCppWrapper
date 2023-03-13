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
	class		Observable;
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
	 * @class Maybe Maybe.h RxCW/Maybe.h
	 * @brief Represents an asynchronous object that can, fail, complete with a value or complete with no value at all.
	 * 
	 * @tparam The value type a Maybe can complete with.
	 */
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
			template<typename> friend class	Observable;
			template<typename> friend class	Single;

			/*
			***********
			** types **
			***********
			*/

			/**
			 * @brief Function that can be called when a Maybe completes with a value.
			 */
			typedef std::function<void(T)>									SuccessFunction;

			/**
			 * @brief Function that can be called when a Maybe fails.
			 */
			typedef std::function<void(std::exception_ptr)>					ErrorFunction;

			/**
			 * @brief Function that can be called when a Maybe completes.
			 */
			typedef std::function<void()>									CompleteFunction;

			/**
			 * @brief Function that can be used to construct a new Maybe. It takes three other functions to give the Maybe a value, complete it or make it fail.
			 */
			typedef std::function<void(SuccessFunction, ErrorFunction)>		Handler;

			/*
			*************
			** methods **
			*************
			*/

			/**
			 * @brief Destroy the Maybe object.
			 */
			~Maybe(void);

			/**
			 * @brief Create a new Maybe using the given handler.
			 * 
			 * @param handler The handler.
			 * @return Maybe The resulting Maybe.
			 */
			static Maybe<T>	create(const Handler& handler);

			/**
			 * @brief Defer Maybe creation to the given function.
			 * 
			 * @param function The function.
			 * @return Maybe The resulting Maybe.
			 */
			static Maybe<T>	defer(const std::function<Maybe<T>()>& function);

			/**
			 * @brief Create a Maybe with the given value.
			 * 
			 * @param value The value.
			 * @return Maybe The resulting Maybe.
			 */
			static Maybe<T>	just(const T& value);

			/**
			 * @brief Create a Maybe instance failing instantly with the given error when subscribed to.
			 * 
			 * @param error The error as an exception pointer.
			 * @return Maybe The resulting Maybe.
			 */
			static Maybe<T>	error(std::exception_ptr e);

			/**
			 * @brief Create a Maybe with no value.
			 * 
			 * @return Maybe The resulting Maybe.
			 */
			static Maybe<T>	empty();

			/**
			 * @brief Create a Maybe that never completes nor fails.
			 * 
			 * @return Maybe The resulting Maybe.
			 */
			static Maybe<T>	never();

			/**
			 * @brief Calls the given function on this Maybe success with the Maybe value.
			 * 
			 * @param onError The function to call.
			 * @return Maybe The resulting Maybe.
			 */
			Maybe<T>		doOnSuccess(const SuccessFunction& onSuccess);

			/**
			 * @brief Calls the given function on this Maybe error.
			 * 
			 * @param onError The function to call.
			 * @return Maybe The resulting Maybe.
			 */
			Maybe<T>		doOnError(const ErrorFunction& onError);

			/**
			 * @brief Calls the given function on this Maybe completion.
			 * 
			 * @param onComplete The function to call.
			 * @return Maybe The resulting Maybe.
			 */
			Maybe<T>		doOnComplete(const CompleteFunction& onComplete);

			/**
			 * @brief Calls the given function on this Maybe end.
			 * 
			 * @param onTerminate The function to call.
			 * @return Maybe The resulting Maybe.
			 */
			Maybe<T>		doOnTerminate(const CompleteFunction& onTerminate);

			/**
			 * @brief Asynchronously check if a Maybe is empty.
			 * 
			 * @return \b true: if the Maybe is empty.
			 * @return \b false: if the Maybe contains a value.
			 */
			Single<bool>	isEmpty();

			/**
			 * @brief If empty, switch this Maybe with the given one.
			 * 
			 * @param other The Maybe to switch this one with.
			 * @return Maybe The resulting Maybe.
			 */
			Maybe<T>		switchIfEmpty(Maybe<T>& other);

			/**
			 * @brief Convert this Maybe to a Single. If empty an error will be returned.
			 * 
			 * @return Single The resulting Single.
			 */
			Single<T>		toSingle();

			/**
			 * @brief Convert this Maybe to a Completable.
			 * 
			 * @return Completable The resulting Completable.
			 */
			Completable		ignoreElement();

			/**
			 * @brief All values are queued and delivered using the given rxcpp coordination.
			 * 
			 * @param coordination The rxcpp coordination.
			 * @return Maybe The resulting Maybe.
			 */
			Maybe<T>		observeOn(rxcpp::observe_on_one_worker coordination);

			/**
			 * @brief Subscription and unsubscription are queued and delivered using the given rxcpp coordination.
			 * 
			 * @param coordination The rxcpp coordination.
			 * @return Maybe The resulting Maybe.
			 */
			Maybe<T>		subscribeOn(rxcpp::synchronize_in_one_worker coordination);

			/**
			 * @brief Subscribe to this Maybe.
			 */
			void			subscribe();

			/**
			 * @brief Subscribe to this Maybe.
			 * 
			 * @param onSuccess Function called on Maybe success with the Maybe value.
			 */
			void			subscribe(const SuccessFunction& onSuccess);

			/**
			 * @brief Subscribe to this Maybe.
			 * 
			 * @param onError Function called on Maybe error.
			 */
			void			subscribe(const ErrorFunction& onError);

			/**
			 * @brief Subscribe to this Maybe.
			 * 
			 * @param onComplete Function called on Maybe completion.
			 */
			void			subscribe(const CompleteFunction& onComplete);

			/**
			 * @brief Subscribe to this Maybe.
			 * 
			 * @param onSuccess Function called on Maybe success with the Maybe value.
			 * @param onError Function called on Maybe error.
			 */
			void			subscribe(const SuccessFunction& onSuccess, const ErrorFunction& onError);

			/**
			 * @brief Subscribe to this Maybe.
			 * 
			 * @param onSuccess Function called on Maybe success with the Maybe value.
			 * @param onError Function called on Maybe success with the Maybe value.
			 * @param onComplete Function called on Maybe completion.
			 */
			void			subscribe(const SuccessFunction& onSuccess, const ErrorFunction& onError, const CompleteFunction& onComplete);

			/**
			 * @brief Apply the given function to the Maybe value.
			 * 
			 * @param function The function to apply to the Maybe value.
			 * @tparam The type of the value returned by the function.
			 * @return Maybe The resulting Maybe.
			 */
			template	<typename R>
			Maybe<R>		map(const std::function<R(T)>& function);

			/**
			 * @brief Apply a function returning a Maybe to the value.
			 * 
			 * @param function The function to apply to the Maybe value.
			 * @tparam The type of the Maybe value returned by the function.
			 * @return Maybe The resulting Maybe.
			 */
			template	<typename R>
			Maybe<R>		flatMap(const std::function<Maybe<R>(T)>& function);

			/**
			 * @brief Apply a function returning a Completable to the value.
			 * 
			 * @param function The function to apply to the Single value.
			 * @return Single The resulting Single.
			 */
			Completable		flatMapCompletable(const std::function<Completable(T)>& function);

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
			 * @brief Construct a new Maybe object.
			 * 
			 * @param observable The underlying rxcpp observable.
			 */
			Maybe(const rxcpp::observable<T>& observable);

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
			 * @brief Construct a new Maybe object.
			 */
			Maybe(void);

	};
}

#include <RxCW/Maybe.inl>
