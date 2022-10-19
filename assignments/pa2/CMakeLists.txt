add_executable(pa2 pa2.cpp utils.cpp heap.cpp tree.cpp)
target_include_directories(pa2 PRIVATE "${DATA_STRUCTURE_INCLUDE}")
target_link_libraries(pa2 PRIVATE PriorityQueue PRIVATE Deque)
target_compile_options(pa2 PRIVATE "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,leak>")
target_link_options(pa2 PRIVATE "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,leak>")
add_executable(pa2_eval evaluate.cpp)
set(PA2_SRC_DIR "${CMAKE_BINARY_DIR}/pa2_src")
file(MAKE_DIRECTORY "${PA2_SRC_DIR}")
add_custom_target(pa2_src ALL
  COMMAND "${TOOLS_DIR}/expand_header.py" -I "${DATA_STRUCTURE_INCLUDE}" -o "${PA2_SRC_DIR}/pa2.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/pa2.cpp"
  COMMAND "${TOOLS_DIR}/expand_header.py" -I "${DATA_STRUCTURE_INCLUDE}" -o "${PA2_SRC_DIR}/heap.h" "${CMAKE_CURRENT_SOURCE_DIR}/heap.h"
  COMMAND "${TOOLS_DIR}/expand_header.py" -I "${DATA_STRUCTURE_INCLUDE}" -o "${PA2_SRC_DIR}/heap.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/heap.cpp"
  COMMAND "${TOOLS_DIR}/expand_header.py" -I "${DATA_STRUCTURE_INCLUDE}" -o "${PA2_SRC_DIR}/tree.h" "${CMAKE_CURRENT_SOURCE_DIR}/tree.h"
  COMMAND "${TOOLS_DIR}/expand_header.py" -I "${DATA_STRUCTURE_INCLUDE}" -o "${PA2_SRC_DIR}/tree.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/tree.cpp"
)

function(pa2_test task input result)
  add_test(NAME "Task${task}.Input[${input}]" COMMAND bash -c "cd ${CMAKE_BINARY_DIR} && rm submit.txt 2>&1 > /dev/null; ./pa2 ${task} ${input} && cat submit.txt")
  set_tests_properties("Task${task}.Input[${input}]" PROPERTIES PASS_REGULAR_EXPRESSION "${result}")
endfunction()

pa2_test(2 "\"1(2)(3)\" \"preorder\"" "1 2 3")
pa2_test(2 "\"1(2()(4))(3()(5))\" \"postorder\"" "4 2 5 3 1")
pa2_test(2 "\"4(2(3)(1))(6(5))\" \"preorder\"" "4 2 3 1 6 5")
pa2_test(2 "\"4(2(3)(1))(6(5))\" \"inorder\"" "3 2 1 4 5 6")
pa2_test(2 "\"4(2(3)(1))(6(5))\" \"postorder\"" "3 1 2 5 6 4")
pa2_test(3 "\"1(2)(3)\" 2" "1 0")
pa2_test(3 "\"1(2(3(4)))(5)\" 3" "2 1")
pa2_test(3 "\"1(2(3(4)))(5)\" 6" "error")
pa2_test(4 "\"1(2)(3)\" \"proper\"" "True")
pa2_test(4 "\"1(2(4)(5))(3(6))\" \"proper\"" "False")
pa2_test(4 "\"1(2)(3)\" \"full\"" "True")
pa2_test(4 "\"1(2(4)(5))(3()(7))\" \"full\"" "False")
pa2_test(4 "\"1(2)(3)\" \"complete\"" "True")
pa2_test(4 "\"1(2(4)(5))(3(6))\" \"complete\"" "True")
pa2_test(4 "\"1(2()(4))(3(6))\" \"complete\"" "False")
pa2_test(5 "\"[('insert',5),('insert',-3),('insert',2)]\"" "-3 5 2")
pa2_test(5 "\"[('insert',4),('insert',-2),('insert',9),('insert',10),('insert',15),('insert',-25)]\"" "-25 4 -2 10 15 9")
pa2_test(5 "\"[('insert',28),('insert',9),('insert',27),('insert',10),('insert',3),('insert',45)]\"" "3 9 27 28 10 45")
pa2_test(6 "\"[('insert',5),('insert',-3),('insert',22),('delMin',NULL)]\"" "5 22")
pa2_test(6 "\"[('insert',28),('insert',9),('insert',27),('insert',10),('insert',3),('insert',45),('delMin',NULL)]\"" "9 10 27 28 45")
pa2_test(6 "\"[('insert',28),('insert',9),('insert',27),('insert',10),('insert',3),('insert',45),('delMin',NULL),('insert',22)]\"" "9 10 22 28 45 27")
pa2_test(6 "\"[('insert',3),('insert',7),('insert',6),('insert',25),('delMin',NULL),('insert',12),('delete', 2),('insert',-1),('delMin',NULL)]\"" "6 7 12")
