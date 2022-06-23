# RxCppWrapper

[![GitHub license](https://img.shields.io/github/license/pribault/RxCppWrapper)](https://github.com/pribault/RxCppWrapper/blob/master/LICENSE)
[![Maintenance](https://img.shields.io/badge/Maintained%3F-yes-green.svg)](https://github.com/pribault/RxCppWrapper/graphs/commit-activity)
![](https://img.shields.io/badge/C%2B%2B-17-blue)

Because rxcpp is a powerful reactive library but can be hardly understandable because of the methods weak typing, I wanted to bring with this wrapper strong typed classes and methods with some useful objects from rxjava like Completable, Single, Maybe and readctive streams.

Because the original is better than the copy when it comes to explain reactive philosophy and mechanisms, I recommend you to take a look at the ReactiveX universe and related repos:

https://reactivex.io/intro.html

https://reactivex.io/

https://github.com/ReactiveX/RxJava

https://github.com/ReactiveX/RxCpp

## Documentation

The doxygen documentation can be found at: https://pribault.github.io/RxCppWrapper/index.html

## Dependencies

This library uses the following dependencies:

- vcpkg
- Doxygen (optional)

### Vcpkg

Using Vcpkg, you have to install the following packages in order to build the RxCppWrapper library:

- rxcpp

## Getting started

### Cmake

```sh
python scripts/cmake.py
```

### Generate documentation

```sh
python scripts/genDoc.py
```

### A quick exemple

This little exemple demonstrates a simple file existence checking, opening and writing.

```cpp
#include <RxCW/AsyncFile.h>
#include <RxCW/FileSystem.h>

using namespace RxCW;

void	log(const std::string& pValue)
{
	std::time_t t_c = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << std::put_time(std::localtime(&t_c), "%H:%M:%S") << " - [thread " << std::this_thread::get_id() << "] : " << pValue << std::endl;
}

int		main(int argc, char **argv)
{
	log("===== START =====");

	FileSystem::rxExists("hello_world.txt")
		.flatMapCompletable([](bool exists)
		{
			log("file exists: " + std::to_string(exists));

			return FileSystem::rxOpen("hello_world.txt", "w")
				.flatMapCompletable([](AsyncFile* file)
				{
					log("file created and ready for writing !");

					return file->rxWrite("Hello world!")
						.doOnComplete([file]()
						{
							log("wrote some data");
						})
						.doOnTerminate([file]()
						{
							log("closing file");
							delete file;
						});
				});
		})
		.doOnComplete([]()
		{
			log("ended without error!");
		})
		.doOnError([](std::exception_ptr)
		{
			log("ended with an error!");
		})
		.doOnTerminate([]()
		{
			log("===== END =====");
			exit(0);
		})
		.subscribe();
	while (true)
		;
	return 0;
}
```

outputs:

```
21:42:42 - [thread 35128] : ===== START =====
21:42:42 - [thread 35128] : file exists: 1
21:42:42 - [thread 35128] : file created and ready for writing !
21:42:42 - [thread 35128] : wrote some data
21:42:42 - [thread 35128] : closing file
21:42:42 - [thread 35128] : ended without error!
21:42:42 - [thread 35128] : ===== END =====
```

One of the main interests of the reactive approach here is to have a powerfull asynchronous code that stays human friendly, and less prone to errors than standard c++.

## Contributing and feedbacks

This wrapper misses a lot of methods for now, don't hesitate to contribute or to open an issue if you want to add any useful method or class.
