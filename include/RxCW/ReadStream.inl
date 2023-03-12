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
 * File: ReadStream.inl
 * Created: 29th May 2022 7:54:32 pm
 * Author: Paul Ribault (pribault.dev@gmail.com)
 * 
 * Last Modified: 29th May 2022 7:54:34 pm
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
RxCW::ReadStream<T>::ReadStream(void)
{
}

template	<typename T>
RxCW::ReadStream<T>::~ReadStream(void)
{
}

template	<typename T>
RxCW::Completable	RxCW::ReadStream<T>::rxPipeTo(WriteStream<T>& writeStream)
{
	return Completable::create([this, &writeStream](Completable::CompleteFunction onComplete, Completable::ErrorFunction onError)
	{
		writeStream.drainHandler([this]()
		{
			this->resume();
		});
		this->handler([this, &writeStream](const T& data)
		{
			writeStream.write(data);
			if (writeStream.writeQueueFull())
				this->pause();
		});
		this->endHandler([&writeStream, onComplete]()
		{
			writeStream.end();
			onComplete();
		});
		this->exceptionHandler([onError](std::exception_ptr exception)
		{
			onError(exception);
		});
		writeStream.exceptionHandler([onError](std::exception_ptr exception)
		{
			onError(exception);
		});
		this->resume();
	});
}
