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
 * Created: 8th February 2022 3:59:46 pm
 * Author: Paul Ribault (pribault.dev@gmail.com)
 * 
 * Last Modified: 13th February 2022 3:47:25 pm
 * Modified By: Paul Ribault (pribault.dev@gmail.com)
 */

/*
**************
** includes **
**************
*/

#include <RxCW/Single.h>

#include <string>

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
	std::cout << "[thread " << std::this_thread::get_id() << "] " << pValue << std::endl;
}

int		main(int argc, char **argv)
{
	Single<int>::just(42)
		.ignoreElement()
		.subscribe([]() {
			log("complete !");
		}, [](const std::exception_ptr& e) {
			log("error !");
		});
	Single<int>::just(42)
		.map<float>([](int value) {
			return 66.6666f;
		})
		.flatMap<int>([](float value) {
			return Single<int>::just(-12);
		})
		.subscribeOn(rxcpp::synchronize_new_thread())
		.subscribe([](int value) {
			log("value: " + std::to_string(value));
		}, [](const std::exception_ptr& e) {
			log("error !");
		}, []() {
			log("complete !");
			exit(0);
		});
		while (true)
			;
	return 0;
}
