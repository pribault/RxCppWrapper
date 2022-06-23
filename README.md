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

## Contributing and feedbacks

This wrapper misses a lot of methods for now, don't hesitate to contribute or to open an issue if you want to add any useful method or class.
