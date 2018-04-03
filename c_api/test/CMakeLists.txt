
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

function(add_gtest filepath)
  get_filename_component(filename ${filepath} NAME)

  string(REPLACE "_test.cc" "" name ${filename})

  add_executable(${name}_test ${name}_test.cc)
  add_dependencies(${name}_test gtest-target)

  target_link_libraries(${name}_test kiki_api ${GTEST_LIBRARIES})

  add_test(${name}_test ${name}_test)
endfunction()

file(GLOB test_source *_test.cc)

foreach(filename ${test_source})
  add_gtest(${filename})
endforeach(filename)
