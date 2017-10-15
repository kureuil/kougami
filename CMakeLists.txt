cmake_minimum_required(VERSION 2.8.7)
project(kougami CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++14")

set(SRCS
  inc/clang.hpp

  src/clang/Cursor.cpp
  src/clang/CursorKind.cpp
  src/clang/File.cpp
  src/clang/Index.cpp
  src/clang/SourceLocation.cpp
  src/clang/SourceRange.cpp
  src/clang/String.cpp
  src/clang/TranslationUnit.cpp
  src/clang/Type.cpp
  src/clang/Visitor.cpp

  inc/kougami.hpp

  src/kougami/Error.cpp
  src/kougami/LinterVisitor.cpp
  src/kougami/linters/IdentifierCase.cpp
  src/kougami/linters/MacroCase.cpp
  src/kougami/linters/NoMultilineMacro.cpp
  src/kougami/linters/MacroLocation.cpp
  src/kougami/linters/TypedefName.cpp
  src/kougami/linters/TypedefLocation.cpp
  src/kougami/linters/NoStructCopy.cpp
  src/kougami/linters/GlobalVarLocation.cpp
  src/kougami/linters/ArgumentCount.cpp
  src/kougami/linters/FunctionCount.cpp
  src/kougami/linters/FunctionLength.cpp
  src/kougami/linters/BreakAfterControl.cpp
  src/kougami/linters/NoSpaceAfterUnary.cpp
  src/kougami/linters/SpaceAroundBinary.cpp

  src/main.cpp
)

add_executable(${PROJECT_NAME} ${SRCS})
target_include_directories(${PROJECT_NAME} PRIVATE inc/)
target_link_libraries(${PROJECT_NAME} clang)
