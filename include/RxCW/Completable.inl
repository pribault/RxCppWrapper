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
 * File: Completable.inl
 * Created: 26th June 2022 9:00:38 pm
 * Author: Paul Ribault (pribault.dev@gmail.com)
 * 
 * Last Modified: 26th June 2022 9:01:15 pm
 * Modified By: Paul Ribault (pribault.dev@gmail.com)
 */

/*
**************
** includes **
**************
*/

// RxCW
#include <RxCW/Maybe.h>
#include <RxCW/Observable.h>
#include <RxCW/Single.h>

/*
********************************************************************************
************************************ METHODS ***********************************
********************************************************************************
*/

template	<typename T>
RxCW::Single<T>	RxCW::Completable::andThen(const RxCW::Single<T>& other)
{
	return RxCW::Single<T>(_observable->flat_map([other](int) {
		return *other._observable;
	}));
}

template	<typename T>
RxCW::Maybe<T>	RxCW::Completable::andThen(const RxCW::Maybe<T>& other)
{
	return RxCW::Maybe<T>(_observable->flat_map([other](int) {
		return *other._observable;
	}));
}

template	<typename T>
RxCW::Observable<T>	RxCW::Completable::andThen(const RxCW::Observable<T>& other)
{
	return RxCW::Observable<T>(_observable->flat_map([other](int) {
		return *other._observable;
	}));
}

template	<typename ... Args>
RxCW::Completable	RxCW::Completable::merge(Args ... completables)
{
	return RxCW::Completable(
		_observable->merge((*completables._observable)...)
			.reduce(
				1,
				[](int, int)
				{
					return 1;
				},
				[](int)
				{
					return 1;
				}
			)
	);
}

template	<typename ... Args>
RxCW::Completable	RxCW::Completable::concat(Args ... completables)
{
	return RxCW::Completable(
		_observable->concat((*completables._observable)...)
			.reduce(
				1,
				[](int, int)
				{
					return 1;
				},
				[](int)
				{
					return 1;
				}
			)
	);
}
