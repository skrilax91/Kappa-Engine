# Kappa-Engine
Game engine

Kappa-Engine is a game engine that we have created for this project. It is a C++ library that uses SFML for the graphical part and Asio for the network part. It is cross-platform and can be used on Windows, Linux and Mac OS.
You can find our Kappa-Engine documentation [here](http://docs.kappa-engine.the-devix.com)

## Installation

### Conan

Conan is used to manage this library. You can find the library on [GitHub](https://github.com/conan-io)
You can also find the documentation [here](https://docs.conan.io)

You can create a local conan repository to install the library. You can find the documentation [here](https://docs.conan.io/en/latest/reference/commands/creator/create.html)
```bash
conan create . kappa/stable
```


### Development

For development, you can use the `conanfile.py` file in the root of the repository. It will install all the dependencies and build the library.
You need to have Conan installed on your machine.  
You can find the documentation [here](https://docs.conan.io/en/latest/installation.html)
generate the build files with CMake and build the library.
```bash
mkdir build && cd build
conan install .. --build=missing -s build_type=Debug
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
cmake --build .
```


#### CLion

You can use CLion to develop the library. 
In order to do so, you need to install the Conan plugin. You can find the documentation [here](https://plugins.jetbrains.com/plugin/8575-conan)
After you need to change your default build profile with "Visual Studio" as toolchain. You can find the documentation [here](https://docs.conan.io/en/latest/integrations/build_system/cmake/cmake_generator.html#visual-studio)
And select "Visual Studio 17 2022" as generator. You can find the documentation [here](https://docs.conan.io/en/latest/integrations/build_system/cmake/cmake_generator.html#visual-studio)
The Build directory MUST be set to `build` in the CMake options.

![Screenshot_27](https://user-images.githubusercontent.com/6585219/216644812-121d6113-85b0-4d7d-b441-ced12b90e3cd.png)

Next you need to install the dependencies. (You need to set build type to Debug)
```bash
mkdir build && cd build
conan install .. -s build_type=Debug --build=missing
```
This will install all the dependencies and generate all FindXXX.cmake files in the build directory.

After that you can open the project in CLion and build it.

Made by : L??o Brossard, Jessica Ebely, S??bastien Lamard, Dylan Akpinar and Quentin Capelle