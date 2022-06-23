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
	/**
	 * @class Single Single.h RxCW/Single.h
	 * @brief Represents an asynchronous object that can fail or complete with a value.
	 * 
	 * @tparam The value type a Single can complete with.
	 */
	template	<typename T>
	class	Single
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

			/**
			 * @brief Function that can be called when a Single has a value.
			 */
			typedef std::function<void(T)>									SuccessFunction;

			/**
			 * @brief Function that can be called when a Single fails.
			 */
			typedef std::function<void(std::exception_ptr)>					ErrorFunction;

			/**
			 * @brief Function that can be called when a Single completes.
			 */
			typedef std::function<void()>									CompleteFunction;

			/**
			 * @brief Function that can be used to construct a new Single. It takes two other functions to complete the Single with a value or make it fail.
			 */
			typedef std::function<void(SuccessFunction, ErrorFunction)>		Handler;

			/*
			*************
			** methods **
			*************
			*/

			/**
			 * @brief Destroy the Single object.
			 */
			~Single(void);

			/**
			 * @brief Create a new Single using the given handler.
			 * 
			 * @param handler The handler.
			 * @return Single The resulting Single.
			 */
			static Single<T>	create(const Handler& handler);

			/**
			 * @brief Defer Single creation to the given function.
			 * 
			 * @param function The function.
			 * @return Single The resulting Single.
			 */
			static Single<T>	defer(const std::function<Single<T>()>& function);

			/**
			 * @brief Create a Single with the given value.
			 * 
			 * @param value The value.
			 * @return Single The resulting Single.
			 */
			static Single<T>	just(const T& value);

			/**
			 * @brief Create a Single instance failing instantly with the given error when subscribed to.
			 * 
			 * @param error The error as an exception pointer.
			 * @return Single The resulting Single.
			 */
			static Single<T>	error(std::exception_ptr e);

			/**
			 * @brief Create a Single that never completes nor fails.
			 * 
			 * @return Single The resulting Single.
			 */
			static Single<T>	never();

			/**
			 * @brief Calls the given function on this Single success with the Single value.
			 * 
			 * @param onError The function to call.
			 * @return Single The resulting Single.
			 */
			Single<T>		doOnSuccess(const SuccessFunction& onSuccess);

			/**
			 * @brief Calls the given function on this Single error.
			 * 
			 * @param onError The function to call.
			 * @return Single The resulting Single.
			 */
			Single<T>		doOnError(const ErrorFunction& onError);

			/**
			 * @brief Calls the given function on this Single completion.
			 * 
			 * @param onComplete The function to call.
			 * @return Single The resulting Single.
			 */
			Single<T>		doOnComplete(const CompleteFunction& onComplete);

			/**
			 * @brief Calls the given function on this Single end.
			 * 
			 * @param onTerminate The function to call.
			 * @return Single The resulting Single.
			 */
			Single<T>		doOnTerminate(const CompleteFunction& onTerminate);

			/**
			 * @brief Convert this Single to a Maybe.
			 * 
			 * @return Maybe The resulting Maybe.
			 */
			Maybe<T>		toMaybe();

			/**
			 * @brief Convert this Single to a Completable.
			 * 
			 * @return Completable The resulting Completable.
			 */
			Completable		ignoreElement();

			/**
			 * @brief All values are queued and delivered using the given rxcpp coordination.
			 * 
			 * @param coordination The rxcpp coordination.
			 * @return Single The resulting Single.
			 */
			Single<T>		observeOn(rxcpp::observe_on_one_worker coordination);

			/**
			 * @brief Subscription and unsubscription are queued and delivered using the given rxcpp coordination.
			 * 
			 * @param coordination The rxcpp coordination.
			 * @return Single The resulting Single.
			 */
			Single<T>		subscribeOn(rxcpp::synchronize_in_one_worker coordination);

			/**
			 * @brief Subscribe to this Single.
			 */
			void			subscribe();

			/**
			 * @brief Subscribe to this Single.
			 * 
			 * @param onSuccess Function called on Single success with the Single value.
			 */
			void			subscribe(const SuccessFunction& onSuccess);

			/**
			 * @brief Subscribe to this Single.
			 * 
			 * @param onError Function called on Single error.
			 */
			void			subscribe(const ErrorFunction& onError);

			/**
			 * @brief Subscribe to this Single.
			 * 
			 * @param onComplete Function called on Single completion.
			 */
			void			subscribe(const CompleteFunction& onComplete);

			/**
			 * @brief Subscribe to this Single.
			 * 
			 * @param onSuccess Function called on Single success with the Single value.
			 * @param onError Function called on Single error.
			 */
			void			subscribe(const SuccessFunction& onSuccess, const ErrorFunction& onError);

			/**
			 * @brief Subscribe to this Single.
			 * 
			 * @param onSuccess Function called on Single success with the Single value.
			 * @param onError Function called on Single success with the Single value.
			 * @param onComplete Function called on Single completion.
			 */
			void			subscribe(const SuccessFunction& onSuccess, const ErrorFunction& onError, const CompleteFunction& onComplete);

			/**
			 * @brief Apply the given function to the Single value.
			 * 
			 * @param function The function to apply to the Single value.
			 * @tparam The type of the value returned by the function.
			 * @return Single The resulting Single.
			 */
			template	<typename R>
			Single<R>		map(const std::function<R(T)>& function);

			/**
			 * @brief Apply a function returning a Single to the value.
			 * 
			 * @param function The function to apply to the Single value.
			 * @tparam The type of the Single value returned by the function.
			 * @return Single The resulting Single.
			 */
			template	<typename R>
			Single<R>		flatMap(const std::function<Single<R>(T)>& function);

			/**
			 * @brief Apply a function returning a Maybe to the value.
			 * 
			 * @param function The function to apply to the Single value.
			 * @tparam The type of the Maybe value returned by the function.
			 * @return Maybe The resulting Maybe.
			 */
			template	<typename R>
			Maybe<R>		flatMapMaybe(const std::function<Maybe<R>(T)>& function);

			/**
			 * @brief Apply a function returning a Completable to the value.
			 * 
			 * @param function The function to apply to the Single value.
			 * @return Completable The resulting Completable.
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
			 * @brief Construct a new Single object.
			 * 
			 * @param observable The underlying rxcpp observable.
			 */
			Single(const rxcpp::observable<T>& observable);

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
			 * @brief Construct a new Single object.
			 */
			Single(void);

	};
}

#include <RxCW/Single.inl>
