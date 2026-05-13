file(REMOVE "${CMAKE_CURRENT_BINARY_DIR}/CTestTestfile.cmake")

if(NOT XAPP_MULTILANGUAGE)
  return()
endif()

if(DEFINED XAPP_TARGET_LANGUAGE AND NOT XAPP_TARGET_LANGUAGE STREQUAL "PYTHON_LANG")
  return()
endif()

if(CMAKE_C_FLAGS MATCHES "-fsanitize" OR CMAKE_CXX_FLAGS MATCHES "-fsanitize")
  message(STATUS "test/swig: skipping Python smoke test (sanitizer build)")
  return()
endif()

find_package(Python3 REQUIRED COMPONENTS Interpreter)

enable_testing()
add_test(
  NAME Smoke_test_xapp_sdk_python
  COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/smoke_test.py
)

set_tests_properties(Smoke_test_xapp_sdk_python PROPERTIES
  ENVIRONMENT "PYTHONPATH=${CMAKE_BINARY_DIR}/examples/xApp/python3"
  TIMEOUT 30
)
