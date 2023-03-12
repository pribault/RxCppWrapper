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
****************
** class used **
****************
*/

namespace	RxCW
{
	template	<typename T>
	class		Observable;
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
	 * @class Completable Completable.h RxCW/Completable.h
	 * @brief Represents an asynchronous object that can either complete or fail.
	 */
	class	Completable
	{

		/*
		************************************************************************
		******************************** PUBLIC ********************************
		************************************************************************
		*/

		public:

			template<typename> friend class	Maybe;
			template<typename> friend class	Single;
			template<typename> friend class	Observable;

			/*
			***********
			** types **
			***********
			*/

			/**
			 * @brief Function that can be called when a Completable fails.
			 */
			typedef std::function<void(std::exception_ptr)>					ErrorFunction;

			/**
			 * @brief Function that can be called when a Completable completes.
			 */
			typedef std::function<void()>									CompleteFunction;

			/**
			 * @brief Function that can be used to construct a new Completable. It takes two other functions to either make the Completable fail, or complete.
			 */
			typedef std::function<void(CompleteFunction, ErrorFunction)>	Handler;

			/**
			 * @brief Function supplying a boolean.
			 */
			typedef std::function<bool()>									BooleanSupplier;

			/*
			*************
			** methods **
			*************
			*/

			/**
			 * @brief Destroy the Completable object.
			 */
			~Completable(void);

			/**
			 * @brief Create a new Completable using the given handler.
			 * 
			 * @param handler The handler.
			 * @return Completable The resulting Completable.
			 */
			static Completable	create(const Handler& handler);

			/**
			 * @brief Defer Completable creation to the given function.
			 * 
			 * @param function The function.
			 * @return Completable The resulting Completable.
			 */
			static Completable	defer(const std::function<Completable()>& function);

			/**
			 * @brief Create a Completable instance completing instantly when subscribed to.
			 * 
			 * @return Completable The resulting Completable.
			 */
			static Completable	complete();

			/**
			 * @brief Create a Completable that never completes nor fails.
			 * 
			 * @return Completable The resulting Completable.
			 */
			static Completable	never();

			/**
			 * @brief Create a Completable instance failing instantly with the given error when subscribed to.
			 * 
			 * @param error The error as an exception pointer.
			 * @return Completable The resulting Completable.
			 */
			static Completable	error(std::exception_ptr error);

			/**
			 * @brief Returns a Completable that will run this Completable first, and then the given Completable.
			 * 
			 * @param other The Completable to run after this one.
			 * @return Completable The resulting Completable.
			 */
			Completable		andThen(const Completable& other);

			/**
			 * @brief Returns a Single that will run this Completable first, and then the given Single.
			 * 
			 * @param other The Single to run after this one.
			 * @return Single The resulting Single.
			 */
			template	<typename T>
			Single<T>	andThen(const Single<T>& other);

			/**
			 * @brief Returns a Maybe that will run this Completable first, and then the given Maybe.
			 * 
			 * @param other The Maybe to run after this one.
			 * @return Maybe The resulting Maybe.
			 */
			template	<typename T>
			Maybe<T>	andThen(const Maybe<T>& other);

			/**
			 * @brief Returns a Observable that will run this Completable first, and then the given Observable.
			 * 
			 * @param other The Observable to run after this one.
			 * @return Observable The resulting Observable.
			 */
			template	<typename T>
			Observable<T>	andThen(const Observable<T>& other);

			/**
			 * @brief Merge all Completables into one, those Completables will be subscribed at the same time and the resulting Completable will only complete after all the merged Completables.
			 * 
			 * @param completables The completables to merge into one.
			 * @return Completable The resulting Completable.
			 */
			template	<typename ... Args>
			Completable	merge(Args ... completables);

			/**
			 * @brief Concatenate all Completables, all of them will be subscribed one after another. The resulting Completable will complete only after all of them.
			 * 
			 * @param completables The completables to concatenate.
			 * @return Completable The resulting Completable.
			 */
			template	<typename ... Args>
			Completable	concat(Args ... completables);

			/**
			 * @brief Repeat this Completable infinitely.
			 * 
			 * @return Completable The resulting Completable.
			 */
			Completable		repeat();

			/**
			 * @brief Repeat this Completable the given number of times.
			 * 
			 * @param times The number of times to repeat this Completable.
			 * @return Completable The resulting Completable.
			 */
			Completable		repeat(size_t times);

			/**
			 * @brief Repeat this Completable until the given BooleanSupplier returns true.
			 * 
			 * @param supplier The BooleanSupplier.
			 * @return Completable The resulting Completable.
			 */
			Completable		repeatUntil(const BooleanSupplier& supplier);

			/**
			 * @brief Calls the given function on this Completable completion.
			 * 
			 * @param onComplete The function to call.
			 * @return Completable The resulting Completable.
			 */
			Completable		doOnComplete(const CompleteFunction& onComplete);

			/**
			 * @brief Calls the given function on this Completable error.
			 * 
			 * @param onError The function to call.
			 * @return Completable The resulting Completable.
			 */
			Completable		doOnError(const ErrorFunction& onError);

			/**
			 * @brief Calls the given function on this Completable end.
			 * 
			 * @param onTerminate The function to call.
			 * @return Completable The resulting Completable.
			 */
			Completable		doOnTerminate(const CompleteFunction& onTerminate);

			/**
			 * @brief All values are queued and delivered using the given rxcpp coordination.
			 * 
			 * @param coordination The rxcpp coordination.
			 * @return Completable The resulting Completable.
			 */
			Completable		observeOn(rxcpp::observe_on_one_worker coordination);

			/**
			 * @brief Subscription and unsubscription are queued and delivered using the given rxcpp coordination.
			 * 
			 * @param coordination The rxcpp coordination.
			 * @return Completable The resulting Completable.
			 */
			Completable		subscribeOn(rxcpp::synchronize_in_one_worker coordination);

			/**
			 * @brief Subscribe to this Completable.
			 */
			void			subscribe();

			/**
			 * @brief Subscribe to this Completable.
			 * 
			 * @param onComplete Function called on Completable completion.
			 */
			void			subscribe(const CompleteFunction& onComplete);

			/**
			 * @brief Subscribe to this Completable.
			 * 
			 * @param onError Function called on Completable error.
			 */
			void			subscribe(const ErrorFunction& onError);

			/**
			 * @brief Subscribe to this Completable.
			 * 
			 * @param onComplete Function called on Completable completion.
			 * @param onError Function called on Completable error.
			 */
			void			subscribe(const CompleteFunction& onComplete, const ErrorFunction& onError);

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

			/**
			 * @brief The underlying rxcpp observable.
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
			 * @brief Construct a new Completable object.
			 * 
			 * @param observable The underlying rxcpp observable.
			 */
			Completable(const rxcpp::observable<int>& observable);

			/**
			 * @brief Construct a new Completable object.
			 */
			Completable(void);

	};
}

#include <RxCW/Completable.inl>
