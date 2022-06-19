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
 * File: main.cpp
 * Created: 8th February 2022 3:59:35 pm
 * Author: Paul Ribault (pribault.dev@gmail.com)
 * 
 * Last Modified: 12th February 2022 9:09:16 pm
 * Modified By: Paul Ribault (pribault.dev@gmail.com)
 */

/*
**************
** includes **
**************
*/

#include <Completable.h>

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

void	log(const std::string& pValue)
{
	std::cout << pValue << std::endl;
}

void	test_completable_defer()
{
	log("START\tCompletable defer test");
	Completable::defer([]() {
		log("creating Completable with defer function");
		return Completable::complete();
		//return Completable::error(std::exception_ptr());
	})
		.subscribe([]() {
			log("completed !");
		}, [](std::exception_ptr e) {
			log("error !");
		});
	log("END\tCompletable defer test");
	log("");
}

void	test_completable_create()
{
	log("START\tCompletable create test");
	Completable::create([](Completable::CompleteFunction onComplete, Completable::ErrorFunction onError)
	{
		log("creating Completable with create function");
		onComplete();
		//errorFunction(std::exception_ptr());
	})
		.subscribe([]() {
			log("completed !");
		}, [](std::exception_ptr e) {
			log("error !");
		});
	log("END\tCompletable create test");
	log("");
}

void	test_completable_andThen()
{
	log("START\tCompletable andThen test");
	Completable::defer([]() {
		log("creating Completable with defer function");
		return Completable::complete();
	})
		.andThen(Completable::defer([]() {
			log("andThen");
			return Completable::complete();
			//return Completable::error(std::exception_ptr());
		}))
		.subscribe([]() {
			log("completed !");
		}, [](std::exception_ptr e) {
			log("error !");
		});
	log("END\tCompletable andThen test");
	log("");
}

void	test_completable_tap()
{
	log("START\tCompletable andThen test");
	Completable::defer([]() {
		log("creating Completable with defer function");
		return Completable::complete();
		//return Completable::error(std::exception_ptr());
	})
		.doOnError([](std::exception_ptr e) {
			log("doOnError");
		})
		.doOnComplete([]() {
			log("doOnComplete");
		})
		.subscribe([]() {
			log("completed !");
		}, [](std::exception_ptr e) {
			log("error !");
		});
	log("END\tCompletable andThen test");
	log("");
}

int		main(int argc, char **argv)
{
	test_completable_defer();
	test_completable_create();
	test_completable_andThen();
	test_completable_tap();
	return 0;
}
