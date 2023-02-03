# Kappa-Engine
Game engine

Kappa-Engine is a game engine that we have created for this project. It is a C++ library that uses SFML for the graphical part and Asio for the network part. It is cross-platform and can be used on Windows, Linux and Mac OS.

## Installation

### Conan

Conan is used to manage this library. You can find the library on [GitHub]()
You can also find the documentation [here]()

You can create a local conan repository to install the library. You can find the documentation [here](https://docs.conan.io/en/latest/reference/commands/creator/create.html)
```bash
conan create . kappa/stable
```


### Development

For development, you can use the `conanfile.py` file in the root of the repository. It will install all the dependencies and build the library.
You need to have Conan installed on your machine.  
You can find the documentation [here](https://docs.conan.io/en/latest/installation.html)

#### CLion

You can use CLion to develop the library. 
In order to do so, you need to install the Conan plugin. You can find the documentation [here](https://plugins.jetbrains.com/plugin/8575-conan)
After you need to change your default build profile with "Visual Studio" as toolchain. You can find the documentation [here](https://docs.conan.io/en/latest/integrations/build_system/cmake/cmake_generator.html#visual-studio)
And select "Visual Studio 17 2022" as generator. You can find the documentation [here](https://docs.conan.io/en/latest/integrations/build_system/cmake/cmake_generator.html#visual-studio)
The Build directory MUST be set to `build` in the CMake options.

Next you need to install the dependencies.
```bash
mkdir build && cd build
conan install ..
```
This will install all the dependencies and generate all FindXXX.cmake files in the build directory.

After that you can open the project in CLion and build it.