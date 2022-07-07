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
 * File: Completable.cpp
 * Created: 8th February 2022 12:11:52 pm
 * Author: Paul Ribault (pribault.dev@gmail.com)
 * 
 * Last Modified: 8th February 2022 12:15:02 pm
 * Modified By: Paul Ribault (pribault.dev@gmail.com)
 */

#include "RxCW/Completable.h"

/*
**************
** includes **
**************
*/

/*
****************
** namespaces **
****************
*/

using namespace RxCW;

/*
********************************************************************************
************************************ METHODS ***********************************
********************************************************************************
*/

Completable::Completable(const rxcpp::observable<int>& observable) :
	_observable(new rxcpp::observable<int>(observable))
{
}

Completable::Completable(void)
{
}

Completable::~Completable(void)
{
}

Completable	Completable::create(const Handler& handler)
{
	return Completable(rxcpp::observable<>::create<int>(
		[handler](rxcpp::subscriber<int> subscriber)
		{
			handler(
				[subscriber]()
				{
					subscriber.on_next(1);
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

Completable	Completable::defer(const std::function<Completable()>& function)
{
	return Completable(rxcpp::observable<>::defer(
		[function]()
		{
			return *function()._observable;
		}
	));
}

Completable		Completable::complete()
{
	return Completable(rxcpp::observable<>::just<int>(1));
}

Completable		Completable::never()
{
	return Completable(rxcpp::observable<>::never<int>());
}

Completable		Completable::error(std::exception_ptr error)
{
	return Completable(rxcpp::observable<>::error<int>(error));
}

Completable		Completable::andThen(Completable& other)
{
	return Completable(_observable->ignore_elements()
		.concat(*other._observable));
}

Completable		Completable::repeat()
{
	return Completable(_observable->repeat());
}

Completable		Completable::repeat(size_t times)
{
	return Completable(_observable->repeat(times));
}

Completable		Completable::repeatUntil(const BooleanSupplier& supplier)
{
	return Completable(_observable->repeat()
		.take_while([supplier](int)
		{
			return !supplier();
		})
	);
}

Completable		Completable::doOnComplete(const CompleteFunction& onComplete)
{
	return Completable(_observable->tap(
		[](int){
			// 
		},
		[onComplete]()
		{
			onComplete();
		}
	));
}

Completable		Completable::doOnError(const ErrorFunction& onError)
{
	return Completable(_observable->tap(
		[onError](std::exception_ptr e)
		{
			onError(e);
		}
	));
}

Completable		Completable::doOnTerminate(const CompleteFunction& onTerminate)
{
	return Completable(_observable->tap(
		[](int){
			// 
		},
		[onTerminate](std::exception_ptr)
		{
			onTerminate();
		},
		[onTerminate]()
		{
			onTerminate();
		}
	));
}

Completable		Completable::observeOn(rxcpp::observe_on_one_worker coordination)
{
	return Completable(_observable->observe_on(coordination));
}

Completable		Completable::subscribeOn(rxcpp::synchronize_in_one_worker coordination)
{
	return Completable(_observable->subscribe_on(coordination));
}

void			Completable::subscribe()
{
	subscribe(
		[]() {},
		[](const std::exception_ptr&) {}
	);
}

void			Completable::subscribe(const CompleteFunction& onComplete)
{
	subscribe(
		onComplete,
		[](const std::exception_ptr&) {}
	);
}

void			Completable::subscribe(const ErrorFunction& onError)
{
	subscribe(
		[]() {},
		onError
	);
}

void			Completable::subscribe(const CompleteFunction& onComplete, const ErrorFunction& onError)
{
	_observable->subscribe(
		[](int)
		{
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
