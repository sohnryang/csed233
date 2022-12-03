add_executable(pa3 pa3.cpp avl.cpp bst.cpp closed_hash_function.cpp closed_hash_table.cpp open_hash_function.cpp open_hash_table.cpp sort.cpp tree.cpp utils.cpp)
target_include_directories(pa3 PRIVATE "${DATA_STRUCTURE_INCLUDE}")
target_compile_options(pa3 PRIVATE "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,leak>")
target_link_options(pa3 PRIVATE "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,leak>")
target_link_libraries(pa3 PRIVATE Deque)
add_executable(pa3_eval evaluate.cpp)
set(PA3_SRC_DIR "${CMAKE_BINARY_DIR}/pa3_src")
file(MAKE_DIRECTORY "${PA3_SRC_DIR}")
add_custom_target(pa3_src ALL
  COMMAND "${TOOLS_DIR}/expand_header.py" -I "${DATA_STRUCTURE_INCLUDE}" -o "${PA3_SRC_DIR}/utils.h" "${CMAKE_CURRENT_SOURCE_DIR}/utils.h"
  COMMAND "${TOOLS_DIR}/expand_header.py" -I "${DATA_STRUCTURE_INCLUDE}" -o "${PA3_SRC_DIR}/closed_hash_table.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/closed_hash_table.cpp"
  COMMAND "${TOOLS_DIR}/expand_header.py" -I "${DATA_STRUCTURE_INCLUDE}" -o "${PA3_SRC_DIR}/open_hash_function.h" "${CMAKE_CURRENT_SOURCE_DIR}/open_hash_function.h"
  COMMAND "${TOOLS_DIR}/expand_header.py" -I "${DATA_STRUCTURE_INCLUDE}" -o "${PA3_SRC_DIR}/utils.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/utils.cpp"
  COMMAND "${TOOLS_DIR}/expand_header.py" -I "${DATA_STRUCTURE_INCLUDE}" -o "${PA3_SRC_DIR}/closed_hash_table.h" "${CMAKE_CURRENT_SOURCE_DIR}/closed_hash_table.h"
  COMMAND "${TOOLS_DIR}/expand_header.py" -I "${DATA_STRUCTURE_INCLUDE}" -o "${PA3_SRC_DIR}/open_hash_table.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/open_hash_table.cpp"
  COMMAND "${TOOLS_DIR}/expand_header.py" -I "${DATA_STRUCTURE_INCLUDE}" -o "${PA3_SRC_DIR}/tree.h" "${CMAKE_CURRENT_SOURCE_DIR}/tree.h"
  COMMAND "${TOOLS_DIR}/expand_header.py" -I "${DATA_STRUCTURE_INCLUDE}" -o "${PA3_SRC_DIR}/sort.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/sort.cpp"
  COMMAND "${TOOLS_DIR}/expand_header.py" -I "${DATA_STRUCTURE_INCLUDE}" -o "${PA3_SRC_DIR}/avl.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/avl.cpp"
  COMMAND "${TOOLS_DIR}/expand_header.py" -I "${DATA_STRUCTURE_INCLUDE}" -o "${PA3_SRC_DIR}/tree.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/tree.cpp"
  COMMAND "${TOOLS_DIR}/expand_header.py" -I "${DATA_STRUCTURE_INCLUDE}" -o "${PA3_SRC_DIR}/bst.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/bst.cpp"
  COMMAND "${TOOLS_DIR}/expand_header.py" -I "${DATA_STRUCTURE_INCLUDE}" -o "${PA3_SRC_DIR}/bst.h" "${CMAKE_CURRENT_SOURCE_DIR}/bst.h"
  COMMAND "${TOOLS_DIR}/expand_header.py" -I "${DATA_STRUCTURE_INCLUDE}" -o "${PA3_SRC_DIR}/closed_hash_function.h" "${CMAKE_CURRENT_SOURCE_DIR}/closed_hash_function.h"
  COMMAND "${TOOLS_DIR}/expand_header.py" -I "${DATA_STRUCTURE_INCLUDE}" -o "${PA3_SRC_DIR}/avl.h" "${CMAKE_CURRENT_SOURCE_DIR}/avl.h"
  COMMAND "${TOOLS_DIR}/expand_header.py" -I "${DATA_STRUCTURE_INCLUDE}" -o "${PA3_SRC_DIR}/open_hash_table.h" "${CMAKE_CURRENT_SOURCE_DIR}/open_hash_table.h"
  COMMAND "${TOOLS_DIR}/expand_header.py" -I "${DATA_STRUCTURE_INCLUDE}" -o "${PA3_SRC_DIR}/pa3.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/pa3.cpp"
  COMMAND "${TOOLS_DIR}/expand_header.py" -I "${DATA_STRUCTURE_INCLUDE}" -o "${PA3_SRC_DIR}/sort.h" "${CMAKE_CURRENT_SOURCE_DIR}/sort.h"
  COMMAND "${TOOLS_DIR}/expand_header.py" -I "${DATA_STRUCTURE_INCLUDE}" -o "${PA3_SRC_DIR}/closed_hash_function.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/closed_hash_function.cpp"
  COMMAND "${TOOLS_DIR}/expand_header.py" -I "${DATA_STRUCTURE_INCLUDE}" -o "${PA3_SRC_DIR}/open_hash_function.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/open_hash_function.cpp"
)

pa_test(pa3 1 "\"[('insertion',17), ('insertion',20), ('insertion',2), ('insertion',21), ('insertion',4), ('quickSort',NULL)]\"" "17 20 2 21 4\n17 2 20 21 4\n17 2 4 21 20\n4 2 17 21 20\n2 4 17 21 20\n2 4 17 20 21")
pa_test(pa3 1 "\"[('insertion',5), ('insertion',6), ('insertion',4), ('insertion',3), ('insertion',2), ('insertion',1), ('quickSort',NULL)]\"" "5 6 4 3 2 1\n5 4 6 3 2 1\n5 4 3 6 2 1\n5 4 3 2 6 1\n5 4 3 2 1 6\n1 4 3 2 5 6\n1 2 3 4 5 6")
pa_test(pa3 2 "\"[('insertion',56), ('insertion',42), ('insertion',20), ('insertion',17), ('insertion',13), ('insertion',28), ('insertion',14), ('mergeSort',NULL)]\"" "56 42 20 17 13 28 14\n42 56 20 17 13 28 14\n42 56 17 20 13 28 14\n17 20 42 56 13 28 14\n17 20 42 56 13 28 14\n17 20 42 56 13 14 28\n13 14 17 20 28 42 56")
pa_test(pa3 2 "\"[('insertion',6), ('insertion',5), ('insertion',4), ('insertion',3), ('insertion',2), ('insertion',1), ('mergeSort',NULL)]\"" "6 5 4 3 2 1\n5 6 4 3 2 1\n4 5 6 3 2 1\n4 5 6 2 3 1\n4 5 6 1 2 3\n1 2 3 4 5 6")
pa_test(pa3 3 "\"[('insertion',4), ('insertion',6), ('insertion',6), ('insertion',7), ('deletion',7)]\"" "0\n0\n-1\n0\n0\n4 6\n4 6")
pa_test(pa3 3 "\"[('insertion',4), ('insertion',2), ('insertion',10), ('insertion',9), ('insertion',15), ('insertion',1), ('deletion',1), ('deletion',4), ('deletion',10)]\"" "0\n0\n0\n0\n0\n0\n0\n0\n0\n9 2 15\n2 9 15")
pa_test(pa3 4 "\"[('insertion',4), ('insertion',6), ('insertion',0), ('deletion',7)]\"" "0\n0\n0\n-1\n4 0 6\n0 4 6")
pa_test(pa3 4 "\"[('insertion',4), ('insertion',2), ('insertion',10), ('insertion',9), ('insertion',15), ('insertion',5), ('insertion',0), ('deletion',4), ('insertion',10)]\"" "0\n0\n0\n0\n0\n0\n0\n0\n-1\n9 2 0 5 10 15\n0 2 5 9 10 15")
pa_test(pa3 5 "\"[('M',4), ('insert',32615), ('insert',315), ('insert',6468), ('insert',94833)]\"" "0: 6468\n1: 32615, 315\n2: empty\n3: 94833")
pa_test(pa3 5 "\"[('M',4), ('insert',32615), ('insert',315), ('insert',6468), ('insert',94833), ('delete',32615), ('delete',6468)]\"" "0: empty\n1: 315\n2: empty\n3: 94833")
pa_test(pa3 5 "\"[('M',4), ('insert',32615), ('insert',315), ('insert',6468), ('insert',94833), ('delete',32615), ('delete',6468), ('insert',22)]\"" "0: 22\n1: 315\n2: empty\n3: 94833")
pa_test(pa3 6 "\"[('n',4), ('r',2), ('insert',15), ('insert',2), ('insert',3)]\"" "0: 15\n1: 3\n2: empty\n3: 2")
pa_test(pa3 6 "\"[('n',4), ('r',2), ('insert',15), ('insert',2), ('insert',3), ('delete',2), ('delete',3)]\"" "0: 15\n1: deleted\n2: empty\n3: deleted")
pa_test(pa3 6 "\"[('n',4), ('r',2), ('insert',15), ('insert',2), ('insert',3), ('delete',2), ('delete',3), ('insert',4)]\"" "0: 15\n1: deleted\n2: 4\n3: deleted")

pa_test(pa3 3 "\"[('insertion',4), ('insertion',6), ('insertion',0), ('deletion',7)]\"" "0\n0\n0\n-1\n4 0 6\n0 4 6")
