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
