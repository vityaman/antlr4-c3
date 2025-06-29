from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.build import check_min_cppstd


class antlr4_c3Recipe(ConanFile):
    name = "antlr4-c3"
    version = "3.0.0"
    package_type = "library"

    license = "MIT"
    author = "Mike Lischke mike@lischke-online.de"
    url = "https://github.com/mike-lischke/antlr4-c3/tree/main/ports/cpp"
    description = "This is a port of the antlr4-c3 library to C++"
    topics = "antlr",

    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    exports_sources = "CMakeLists.txt", "src/*", "include/*"

    def validate(self):
        check_min_cppstd(self, "20")

    def requirements(self):
        self.requires("antlr4/4.13.1")
        self.requires("antlr4-cppruntime/4.13.1")

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["antlr4-c3"]
