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
 * File: Observable.inl
 * Created: Tuesday, 12th April 2022 9:24:42 am
 * Author: Paul Ribault (pribault.dev@gmail.com)
 * 
 * Last Modified: Friday, 15th April 2022 4:06:09 pm
 * Modified By: Paul Ribault (pribault.dev@gmail.com)
 */

/*
**************
** includes **
**************
*/

// RxCW
#include <RxCW/Completable.h>
#include <RxCW/Single.h>
#include <RxCW/Maybe.h>

/*
********************************************************************************
************************************ METHODS ***********************************
********************************************************************************
*/

template	<typename T>
RxCW::Observable<T>::Observable(const rxcpp::observable<T>& observable) :
	_observable(new rxcpp::observable<T>(observable))
{
}

template	<typename T>
RxCW::Observable<T>::Observable(void)
{
}

template	<typename T>
RxCW::Observable<T>::~Observable(void)
{
}

template	<typename T>
RxCW::Observable<T>	RxCW::Observable<T>::create(const Handler& handler)
{
	return Observable<T>(rxcpp::observable<>::create<T>(
		[handler](rxcpp::subscriber<T> subscriber)
	{
		handler(
			[subscriber](T value)
		{
			subscriber.on_next(value);
		},
			[subscriber]()
		{
			subscriber.on_completed();
		},
			[subscriber](std::exception_ptr error)
		{
			subscriber.on_error(error);
		}
		);
	}
	));
}

template	<typename T>
RxCW::Observable<T>	RxCW::Observable<T>::defer(const std::function<RxCW::Observable<T>()>& function)
{
	return Observable<T>(rxcpp::observable<>::defer(
		[function]()
	{
		return *function()._observable;
	}
	));
}

template	<typename T>
RxCW::Observable<T>	RxCW::Observable<T>::empty()
{
	return Observable<T>(rxcpp::observable<>::empty<T>());
}

template	<typename T>
RxCW::Observable<T>	RxCW::Observable<T>::never()
{
	return Observable<T>(rxcpp::observable<>::never<T>());
}

template	<typename T>
RxCW::Observable<T>	RxCW::Observable<T>::just(const T& value)
{
	return Observable<T>(rxcpp::observable<>::just<T>(value));
}

template	<typename T>
RxCW::Observable<T>	RxCW::Observable<T>::error(std::exception_ptr error)
{
	return Observable<T>(rxcpp::observable<>::error<T>(error));
}

template	<typename T>
RxCW::Observable<T>	RxCW::Observable<T>::range(T start, T end, std::ptrdiff_t step)
{
	return Observable<T>(rxcpp::observable<>::range<T>(start, end, step));
}

template	<typename T>
RxCW::Observable<T>		RxCW::Observable<T>::interval(std::chrono::steady_clock::duration period)
{
	return Observable<T>(rxcpp::observable<>::interval(period));
}

template	<typename T>
RxCW::Observable<T>		RxCW::Observable<T>::interval(std::chrono::steady_clock::time_point when, std::chrono::steady_clock::duration period)
{
	return Observable<T>(rxcpp::observable<>::interval(when, period));
}

template	<typename T>
RxCW::Observable<T>		RxCW::Observable<T>::take(size_t count)
{
	return Observable<T>(_observable->take(count));
}

template	<typename T>
RxCW::Observable<T>		RxCW::Observable<T>::take_last(size_t count)
{
	return Observable<T>(_observable->take_last(count));
}

template	<typename T>
RxCW::Completable		RxCW::Observable<T>::ignoreElements()
{
	return Completable(_observable->ignore_elements()
		// use map to change observable type
		.map(
			[](T)
			{
				return 1;
			})
		.switch_if_empty(rxcpp::observable<>::just<int>(1)));
}

template	<typename T>
RxCW::Maybe<T>			RxCW::Observable<T>::elementAt(size_t index)
{
	return RxCW::Maybe<T>(_observable->element_at(index));
}

template	<typename T>
RxCW::Single<T>			RxCW::Observable<T>::elementAtOrError(size_t index)
{
	return RxCW::Single<T>(_observable->element_at(index)
		.switch_if_empty(rxcpp::observable<>::error<T>(make_exception_ptr(std::out_of_range("index " + std::to_string(index) + " out of range")))));
}

template	<typename T>
RxCW::Maybe<T>			RxCW::Observable<T>::first()
{
	return RxCW::Maybe<T>(_observable->take(1));
}

template	<typename T>
RxCW::Single<T>			RxCW::Observable<T>::firstOrError()
{
	return RxCW::Single<T>(_observable->take(1)
		.switch_if_empty(rxcpp::observable<>::error<T>(make_exception_ptr(std::out_of_range("first element out of range (empty Observable)")))));
}

template	<typename T>
RxCW::Maybe<T>			RxCW::Observable<T>::last()
{
	return RxCW::Maybe<T>(_observable->take_last(1));
}

template	<typename T>
RxCW::Single<T>			RxCW::Observable<T>::lastOrError()
{
	return RxCW::Single<T>(_observable->take_last(1)
		.switch_if_empty(rxcpp::observable<>::error<T>(make_exception_ptr(std::out_of_range("last element out of range (empty Observable)")))));
}

template	<typename T>
RxCW::Observable<T>		RxCW::Observable<T>::doOnSuccess(const SuccessFunction& onSuccess)
{
	return Observable<T>(_observable->tap(
		[onSuccess](T value){
			onSuccess(value);
		}
	));
}

template	<typename T>
RxCW::Observable<T>		RxCW::Observable<T>::doOnError(const ErrorFunction& onError)
{
	return Observable<T>(_observable->tap(
		[onError](std::exception_ptr e)
		{
			onError(e);
		}
	));
}

template	<typename T>
RxCW::Observable<T>		RxCW::Observable<T>::doOnComplete(const CompleteFunction& onComplete)
{
	return Observable<T>(_observable->tap(
		[onComplete]()
		{
			onComplete();
		}
	));
}

template	<typename T>
RxCW::Observable<T>		RxCW::Observable<T>::doOnTerminate(const CompleteFunction& onTerminate)
{
	return Observable<T>(_observable->tap(
		[](T)
		{
		},
		[onTerminate](std::exception_ptr e)
		{
			onTerminate();
		},
		[onTerminate]()
		{
			onTerminate();
		}
	));
}

template	<typename T>
RxCW::Observable<T>		RxCW::Observable<T>::observeOn(rxcpp::observe_on_one_worker coordination)
{
	return Observable<T>(_observable->observe_on(coordination));
}

template	<typename T>
RxCW::Observable<T>		RxCW::Observable<T>::subscribeOn(rxcpp::synchronize_in_one_worker coordination)
{
	return Observable<T>(_observable->subscribe_on(coordination));
}

template	<typename T>
void				RxCW::Observable<T>::subscribe()
{
	subscribe(
		[](T) {},
		[](const std::exception_ptr&) {},
		[]() {}
	);
}

template	<typename T>
void				RxCW::Observable<T>::subscribe(const SuccessFunction& onSuccess)
{
	subscribe(
		onSuccess,
		[](const std::exception_ptr&) {},
		[]() {}
	);
}

template	<typename T>
void				RxCW::Observable<T>::subscribe(const ErrorFunction& onError)
{
	subscribe(
		[](T) {},
		onError,
		[]() {}
	);
}

template	<typename T>
void				RxCW::Observable<T>::subscribe(const CompleteFunction& onComplete)
{
	subscribe(
		[](T) {},
		[](const std::exception_ptr&) {},
		onComplete
	);
}

template	<typename T>
void				RxCW::Observable<T>::subscribe(const SuccessFunction& onSuccess, const ErrorFunction& onError)
{
	subscribe(
		onSuccess,
		onError,
		[]() {}
	);
}

template	<typename T>
void				RxCW::Observable<T>::subscribe(const SuccessFunction& onSuccess, const ErrorFunction& onError, const CompleteFunction& onComplete)
{
	_observable->subscribe(
		[onSuccess](T value)
		{
			onSuccess(value);
		},
		[onError](std::exception_ptr e)
		{
			onError(e);
		},
		[onComplete]()
		{
			onComplete();
		}
	);
}

template	<typename T>
template	<typename R>
RxCW::Observable<R>		RxCW::Observable<T>::map(const std::function<R(T)>& function)
{
	return Observable<R>(_observable->map(function));
}

template	<typename T>
template	<typename R>
RxCW::Observable<R>		RxCW::Observable<T>::flatMap(const std::function<Observable<R>(T)>& function)
{
	return RxCW::Observable<R>(_observable->flat_map([function](T v) {
		return *function(v)._observable;
	}));
}
