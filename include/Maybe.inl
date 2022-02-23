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
 * File: Maybe.inl
 * Created: 8th February 2022 2:29:04 pm
 * Author: Paul Ribault (pribault.dev@gmail.com)
 * 
 * Last Modified: 8th February 2022 2:29:10 pm
 * Modified By: Paul Ribault (pribault.dev@gmail.com)
 */

/*
**************
** includes **
**************
*/

// RxCW
#include <Single.h>

/*
********************************************************************************
************************************ METHODS ***********************************
********************************************************************************
*/

template	<typename T>
RxCW::Maybe<T>::Maybe(const rxcpp::observable<T>& observable) :
	_observable(new rxcpp::observable<T>(observable))
{
}

template	<typename T>
RxCW::Maybe<T>::Maybe(void)
{
}

template	<typename T>
RxCW::Maybe<T>::~Maybe(void)
{
}

template	<typename T>
RxCW::Maybe<T>	RxCW::Maybe<T>::create(const Handler& handler)
{
	return Maybe<T>(rxcpp::observable<>::create<T>(
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
RxCW::Maybe<T>	RxCW::Maybe<T>::defer(const std::function<RxCW::Maybe<T>()>& function)
{
	return Maybe<T>(rxcpp::observable<>::defer(
		[function]()
	{
		return *function()._observable;
	}
	));
}

template	<typename T>
RxCW::Maybe<T>	RxCW::Maybe<T>::just(const T& value)
{
	return Maybe<T>(rxcpp::observable<>::just<T>(value));
}

template	<typename T>
RxCW::Maybe<T>	RxCW::Maybe<T>::error(std::exception_ptr e)
{
	return Maybe<T>(rxcpp::observable<>::error<T>(e));
}

template	<typename T>
RxCW::Maybe<T>	RxCW::Maybe<T>::empty()
{
	return Maybe<T>(rxcpp::observable<>::empty<T>());
}

template	<typename T>
RxCW::Maybe<T>		RxCW::Maybe<T>::andThen(RxCW::Maybe<T>& other)
{
	return Maybe<T>(_observable->merge(*other._observable));
}

template	<typename T>
RxCW::Maybe<T>		RxCW::Maybe<T>::doOnSuccess(const SuccessFunction& onSuccess)
{
	return Maybe<T>(_observable->tap(
		[](T value){
			onSuccess(value);
		}
	));
}

template	<typename T>
RxCW::Maybe<T>		RxCW::Maybe<T>::doOnError(const ErrorFunction& onError)
{
	return Maybe<T>(_observable->tap(
		[onError](std::exception_ptr e)
		{
			onError(e);
		}
	));
}

template	<typename T>
RxCW::Maybe<T>		RxCW::Maybe<T>::doOnComplete(const CompleteFunction& onComplete)
{
	return Maybe<T>(_observable->tap(
		[](T)
		{
		},
		[onComplete](std::exception_ptr e)
		{
			onComplete();
		},
		[onComplete]()
		{
			onComplete();
		}
	));
}

template	<typename T>
RxCW::Single<bool>	RxCW::Maybe<T>::isEmpty()
{
	return Single<bool>(_observable->is_empty());
}

template	<typename T>
RxCW::Maybe<T>		RxCW::Maybe<T>::switchIfEmpty(Maybe<T>& other)
{
	return Maybe<T>(_observable->switch_if_empty(*other._observable));
}

template	<typename T>
RxCW::Single<T>		RxCW::Maybe<T>::toSingle()
{
	return Single<T>(_observable->switch_if_empty(*Single<T>.error(std::make_exception_ptr(std::logic_error("empty Single")))._observable));
}

template	<typename T>
RxCW::Maybe<T>		RxCW::Maybe<T>::observeOn(rxcpp::observe_on_one_worker coordination)
{
	return Maybe<T>(_observable->observe_on(coordination));
}

template	<typename T>
RxCW::Maybe<T>		RxCW::Maybe<T>::subscribeOn(rxcpp::synchronize_in_one_worker coordination)
{
	return Maybe<T>(_observable->subscribe_on(coordination));
}

template	<typename T>
void				RxCW::Maybe<T>::subscribe(const SuccessFunction& onSuccess, const ErrorFunction& onError, const CompleteFunction& onComplete)
{
	_observable->subscribe(
		[onSuccess](T value)
		{
			onSuccess(value);
		},
		[onError, onComplete](std::exception_ptr e)
		{
			onError(e);
			onComplete();
		},
		[onComplete]()
		{
			onComplete();
		}
	);
}

template	<typename T>
template	<typename R>
RxCW::Maybe<R>		RxCW::Maybe<T>::map(const std::function<R(T)>& function)
{
	return Maybe<R>(_observable->map(function));
}

template	<typename T>
template	<typename R>
RxCW::Maybe<R>		RxCW::Maybe<T>::flatMap(const std::function<Maybe<R>(T)>& function)
{
	return RxCW::Maybe<R>(_observable->flat_map([function](T v) {
		return *function(v)._observable;
	}));
}
