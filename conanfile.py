from conans import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout


class KappaEngineConan(ConanFile):
    name = "KappaEngine"
    version = "0.1"

    license = "<Put the package license here>"
    author = "Leo Brossard leo.brossard@epitech.eu"
    url = "https://github.com/skrilax91/Kappa-Engine"
    description = "C++ Game engine using ECS architecture"
    topics = ("Game", "CPP", "Engine")

    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    generators = "CMakeDeps"

    exports_sources = "CMakeLists.txt", "src/*", "include/*"
    build_requires = "cmake/3.24.0"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def requirements(self):
        self.requires("sfml/2.5.1")
        self.requires("asio/1.24.0")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        self.run("cmake --version")
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        self.copy("*.h", dst="include", src="include")
        self.copy("*.hpp", dst="include", src="include")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["KappaEngine"]
