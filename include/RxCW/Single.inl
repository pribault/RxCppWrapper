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
 * File: Single.inl
 * Created: 8th February 2022 2:29:00 pm
 * Author: Paul Ribault (pribault.dev@gmail.com)
 * 
 * Last Modified: 8th February 2022 2:29:08 pm
 * Modified By: Paul Ribault (pribault.dev@gmail.com)
 */

/*
**************
** includes **
**************
*/

#include <RxCW/Completable.h>
#include <RxCW/Maybe.h>

/*
********************************************************************************
************************************ METHODS ***********************************
********************************************************************************
*/

template	<typename T>
RxCW::Single<T>::Single(const rxcpp::observable<T>& observable) :
	_observable(new rxcpp::observable<T>(observable))
{
}

template	<typename T>
RxCW::Single<T>::Single(void)
{
}

template	<typename T>
RxCW::Single<T>::~Single(void)
{
}

template	<typename T>
RxCW::Single<T>	RxCW::Single<T>::create(const Handler& handler)
{
	return Single<T>(rxcpp::observable<>::create<T>(
		[handler](rxcpp::subscriber<T> subscriber)
	{
		handler(
			[subscriber](T value)
		{
			subscriber.on_next(value);
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
RxCW::Single<T>	RxCW::Single<T>::defer(const std::function<RxCW::Single<T>()>& function)
{
	return Single<T>(rxcpp::observable<>::defer(
		[function]()
	{
		return *function()._observable;
	}
	));
}

template	<typename T>
RxCW::Single<T>	RxCW::Single<T>::just(const T& value)
{
	return Single<T>(rxcpp::observable<>::just<T>(value));
}

template	<typename T>
RxCW::Single<T>	RxCW::Single<T>::error(std::exception_ptr e)
{
	return Single<T>(rxcpp::observable<>::error<T>(e));
}

template	<typename T>
RxCW::Single<T>	RxCW::Single<T>::never()
{
	return Single<T>(rxcpp::observable<>::never<T>());
}

template	<typename T>
RxCW::Single<T>		RxCW::Single<T>::doOnSuccess(const SuccessFunction& onSuccess)
{
	return Single<T>(_observable->tap(
		[onSuccess](T value){
			onSuccess(value);
		}
	));
}

template	<typename T>
RxCW::Single<T>		RxCW::Single<T>::doOnError(const ErrorFunction& onError)
{
	return Single<T>(_observable->tap(
		[onError](std::exception_ptr e)
		{
			onError(e);
		}
	));
}

template	<typename T>
RxCW::Single<T>		RxCW::Single<T>::doOnComplete(const CompleteFunction& onComplete)
{
	return Single<T>(_observable->tap(
		[onComplete]()
		{
			onComplete();
		}
	));
}

template	<typename T>
RxCW::Single<T>		RxCW::Single<T>::doOnTerminate(const CompleteFunction& onTerminate)
{
	return Single<T>(_observable->tap(
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
RxCW::Maybe<T>		RxCW::Single<T>::toMaybe()
{
	return Maybe<T>(*_observable);
}

template	<typename T>
RxCW::Completable	RxCW::Single<T>::ignoreElement()
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
RxCW::Single<T>		RxCW::Single<T>::observeOn(rxcpp::observe_on_one_worker coordination)
{
	return Single<T>(_observable->observe_on(coordination));
}

template	<typename T>
RxCW::Single<T>		RxCW::Single<T>::subscribeOn(rxcpp::synchronize_in_one_worker coordination)
{
	return Single<T>(_observable->subscribe_on(coordination));
}

template	<typename T>
void				RxCW::Single<T>::subscribe()
{
	subscribe(
		[](T) {},
		[](const std::exception_ptr&) {},
		[]() {}
	);
}

template	<typename T>
void				RxCW::Single<T>::subscribe(const SuccessFunction& onSuccess)
{
	subscribe(
		onSuccess,
		[](const std::exception_ptr&) {},
		[]() {}
	);
}

template	<typename T>
void				RxCW::Single<T>::subscribe(const ErrorFunction& onError)
{
	subscribe(
		[](T) {},
		onError,
		[]() {}
	);
}

template	<typename T>
void				RxCW::Single<T>::subscribe(const CompleteFunction& onComplete)
{
	subscribe(
		[](T) {},
		[](const std::exception_ptr&) {},
		onComplete
	);
}

template	<typename T>
void				RxCW::Single<T>::subscribe(const SuccessFunction& onSuccess, const ErrorFunction& onError)
{
	subscribe(
		onSuccess,
		onError,
		[]() {}
	);
}

template	<typename T>
void				RxCW::Single<T>::subscribe(const SuccessFunction& onSuccess, const ErrorFunction& onError, const CompleteFunction& onComplete)
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
RxCW::Single<R>		RxCW::Single<T>::map(const std::function<R(T)>& function)
{
	return Single<R>(_observable->map(function));
}

template	<typename T>
template	<typename R>
RxCW::Single<R>		RxCW::Single<T>::flatMap(const std::function<Single<R>(T)>& function)
{
	return RxCW::Single<R>(_observable->flat_map([function](T v) {
		return *function(v)._observable;
	}));
}

template	<typename T>
template	<typename R>
RxCW::Maybe<R>		RxCW::Single<T>::flatMapMaybe(const std::function<RxCW::Maybe<R>(T)>& function)
{
	return RxCW::Maybe<R>(_observable->flat_map([function](T v) {
		return *function(v)._observable;
	}));
}

template	<typename T>
RxCW::Completable	RxCW::Single<T>::flatMapCompletable(const std::function<RxCW::Completable(T)>& function)
{
	return RxCW::Completable(_observable->flat_map([function](T v) {
		return *function(v)._observable;
	}));
}
