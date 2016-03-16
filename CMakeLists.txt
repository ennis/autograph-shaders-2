cmake_minimum_required(VERSION 2.8.8)
project(AutographShaders)

message(STATUS "Looking for LLVM in ${LLVM_DIR}")

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)
set(CMAKE_CXX_STANDARD 11)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "Using ClangConfig.cmake in: ${CLANG_DIR}")

# Set your project compile flags.
# E.g. if using the C++ header files
# you will need to enable C++11 support
# for your compiler.

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
include_directories(${CLANG_INCLUDE_DIRS})
add_definitions(${CLANG_DEFINITIONS})

file(GLOB SOURCES
	src/*.cpp)

file(GLOB HEADERS
	src/*.hpp)

# Now build our tools
add_executable(agfxc ${SOURCES})

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(LLVM_LIBRARIES support core irreader)

set(CLANG_LIBRARIES 
	clangBasic 
	clangLex 
	clangParse 
	clangAST 
	clangCodeGen
	clangDynamicASTMatchers 
	clangASTMatchers 
	clangSema 
	clangAnalysis 
	clangEdit 
	clangRewrite 
	clangDriver 
	clangRewriteFrontend 
	clangFrontend 
	clangFrontendTool 
	clangToolingCore 
	clangTooling 
	clangIndex)

# Link against LLVM libraries
target_link_libraries(agfxc ${LLVM_LIBRARIES} ${CLANG_LIBRARIES})