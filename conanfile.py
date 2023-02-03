from os.path import join

from conans import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain
from conan.tools.files import copy


class KappaEngineConan(ConanFile):
    name = "KappaEngine"
    version = "0.1"

    license = "<Put the package license here>"
    author = "Leo Brossard leo.brossard@epitech.eu"
    url = "https://github.com/skrilax91/Kappa-Engine"
    description = "C++ Game engine using ECS architecture"
    topics = ("Game", "CPP", "Engine")

    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    generators = "CMakeDeps"

    exports_sources = "CMakeLists.txt", "src/*", "include/*"

    def requirements(self):
        self.requires("sfml/2.5.1")
        self.requires("asio/1.24.0")

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
        copy(self, "*.h", join(self.source_folder, "include"), join(self.package_folder, "include"))
        copy(self, "*.hpp", join(self.source_folder, "include"), join(self.package_folder, "include"))
        copy(self, "*.lib", self.build_folder, join(self.package_folder, "lib"))
        copy(self, "*.dll", self.build_folder, join(self.package_folder, "bin"))
        copy(self, "*.so", self.build_folder, join(self.package_folder, "lib"))
        copy(self, "*.dylib", self.build_folder, join(self.package_folder, "lib"))
        copy(self, "*.a", self.build_folder, join(self.package_folder, "lib"))

    def package_info(self):
        self.cpp_info.libs = ["KappaEngine"]
