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
 * File: WriteStream.inl
 * Created: 29th May 2022 7:54:46 pm
 * Author: Paul Ribault (pribault.dev@gmail.com)
 * 
 * Last Modified: 29th May 2022 7:54:48 pm
 * Modified By: Paul Ribault (pribault.dev@gmail.com)
 */

/*
**************
** includes **
**************
*/

/*
********************************************************************************
************************************ METHODS ***********************************
********************************************************************************
*/

template	<typename T>
RxCW::WriteStream<T>::WriteStream(void)
{
}

template	<typename T>
RxCW::WriteStream<T>::~WriteStream(void)
{
}

template	<typename T>
RxCW::Completable	RxCW::WriteStream<T>::rxEnd()
{
	return Completable::create([this](Completable::CompleteFunction onComplete, Completable::ErrorFunction onError)
	{
		try
		{
			this->end();
		}
		catch (const std::exception& e)
		{
			onError(std::make_exception_ptr(e));
			return;
		}
		onComplete();
	});
}

template	<typename T>
RxCW::Completable		RxCW::WriteStream<T>::rxWrite(const T& data)
{
	return Completable::create([this, data](Completable::CompleteFunction onComplete, Completable::ErrorFunction onError)
	{
		try
		{
			this->write(data);
		}
		catch (const std::exception& e)
		{
			onError(std::make_exception_ptr(e));
			return;
		}
		onComplete();
	});
}
