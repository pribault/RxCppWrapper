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
 * File: AsyncFile.cpp
 * Created: 6th June 2022 1:44:59 pm
 * Author: Paul Ribault (pribault.dev@gmail.com)
 * 
 * Last Modified: 6th June 2022 1:45:00 pm
 * Modified By: Paul Ribault (pribault.dev@gmail.com)
 */

#include "RxCW/AsyncFile.h"

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

AsyncFile::AsyncFile(void)
	: _closed(false)
	, _readBufferSize(DEFAULT_READ_BUFFER_SIZE)
	, _paused(true)
	, _readEnded(false)
	, _writeEnded(false)
	, _writeQueueSize(DEFAULT_WRITE_QUEUE_SIZE)
	, _writeQueueFull(false)
{
}

AsyncFile::AsyncFile(const std::string& fileName, const std::string& mode)
	: AsyncFile()
{
	_file = std::fopen(fileName.c_str(), mode.c_str());
}

AsyncFile::~AsyncFile(void)
{
	if (!_closed)
		std::fclose(_file);
}

void		AsyncFile::exceptionHandler(const StreamBase<std::string>::ErrorFunction& handler)
{
	_errorHandler = handler;
}

void		AsyncFile::endHandler(const ReadStream<std::string>::EndFunction& handler)
{
	_endHandler = handler;
}

void		AsyncFile::handler(const ReadStream<std::string>::DataFunction& handler)
{
	_dataHandler = handler;
}

void		AsyncFile::pause()
{
	if (!_paused)
	{
		_paused = true;
	}
}

void		AsyncFile::resume()
{
	if (_paused)
	{
		_paused = false;
		rxInternalRead()
			.observeOn(rxcpp::observe_on_new_thread())
			.repeatUntil([this]() {
				return _paused || _readEnded;
			})
			.subscribe(
				[]()
				{
				},
				[this](std::exception_ptr e)
				{
					_paused = true;
				});
	}
}

void		AsyncFile::drainHandler(const WriteStream<std::string>::DrainFunction& handler)
{
	_drainHandler = handler;
}

void		AsyncFile::end()
{
	if (!_writeEnded)
	{
		_writeEnded = true;
		_closed = true;
		std::fclose(_file);
	}
}

void		AsyncFile::write(const std::string& data)
{
	_writeQueue.push_back(data);

	if (_writeQueue.size() >= _writeQueueSize)
		_writeQueueFull = true;

	rxInternalWrite()
		.observeOn(rxcpp::observe_on_new_thread())
		.repeatUntil([this]()
			{
				return _writeQueue.empty();
			})
		.subscribe(
			[]()
			{
			},
			[this](std::exception_ptr e)
			{
			});
}

void		AsyncFile::setWriteQueueMaxSize(size_t size)
{
	if (!size)
		throw std::invalid_argument("size must be greater than 0");

	_writeQueueSize = size;

	if (_writeQueue.size() >= _writeQueueSize)
		_writeQueueFull = true;
}

bool		AsyncFile::writeQueueFull()
{
	return _writeQueueFull;
}

Completable	AsyncFile::rxInternalRead()
{
	return Completable::create([this](Completable::CompleteFunction onComplete, Completable::ErrorFunction onError) {
		std::string	buffer;

		buffer.resize(_readBufferSize);
		size_t	result = std::fread(&buffer[0], 1, _readBufferSize, _file);
		if (result > 0)
		{
			buffer.resize(result);
			_dataHandler(buffer);
			onComplete();
		}
		else if (result == 0)
		{
			_readEnded = true;
			_endHandler();
			onComplete();
		}
		else
		{
			onError(std::make_exception_ptr(std::runtime_error("Error " + std::to_string(result) + " while reading file")));
		}
	});
}

Completable	AsyncFile::rxInternalWrite()
{
	return Completable::create([this](Completable::CompleteFunction onComplete, Completable::ErrorFunction onError)
	{
		if (!_writeQueue.empty())
		{
			std::string	data = _writeQueue.front();
			_writeQueue.pop_front();
			if (!data.empty())
			{
				size_t	result = std::fwrite(&data[0], 1, data.size(), _file);
				if (result > 0)
				{
					if (result < data.size())
					{
						_writeQueue.push_front(data.substr(result));
					}
				}
				else
				{
					onError(std::make_exception_ptr(std::runtime_error("Error " + std::to_string(result) + " while writing file")));
					return ;
				}
			}
		}

		if (_writeQueueFull)
		{
			if (_writeQueueSize == 1)
			{
				if (_writeQueue.empty())
				{
					_writeQueueFull = false;
					_drainHandler();
				}
			}
			else
			{
				if (_writeQueue.size() < _writeQueueSize / 2)
				{
					_writeQueueFull = false;
					_drainHandler();
				}
			}
		}

		onComplete();
	});
}
