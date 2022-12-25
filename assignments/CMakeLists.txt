function(pa_test binary task input result)
  add_test(NAME "Task${task}.Input[${input}]" COMMAND bash -c "cd ${CMAKE_BINARY_DIR} && rm submit.txt 2>&1 > /dev/null; ./${binary} ${task} ${input} && cat submit.txt")
  set_tests_properties("Task${task}.Input[${input}]" PROPERTIES PASS_REGULAR_EXPRESSION "${result}")
endfunction()

add_subdirectory(pa1)
add_subdirectory(pa2)
add_subdirectory(pa3)
add_subdirectory(pa4)
