set(DATA_STRUCTURE_INCLUDE "${PROJECT_SOURCE_DIR}/data_structures" PARENT_SCOPE)

add_library(DoubleLinkedList INTERFACE)
target_sources(DoubleLinkedList INTERFACE double_linked_list.h)
target_include_directories(DoubleLinkedList INTERFACE "${DATA_STRUCTURE_INCLUDE}")

add_library(Deque INTERFACE)
target_sources(Deque INTERFACE deque.h)
target_include_directories(Deque INTERFACE "${DATA_STRUCTURE_INCLUDE}")

add_library(KAryTree INTERFACE)
target_sources(KAryTree INTERFACE kary_tree.h)
target_include_directories(KAryTree INTERFACE "${DATA_STRUCTURE_INCLUDE}")

add_library(Bitmask INTERFACE)
target_sources(Bitmask INTERFACE bitmask.h)
target_include_directories(Bitmask INTERFACE "${DATA_STRUCTURE_INCLUDE}")

add_library(PriorityQueue INTERFACE)
target_sources(PriorityQueue INTERFACE priority_queue.h)
target_include_directories(PriorityQueue INTERFACE "${DATA_STRUCTURE_INCLUDE}")

enable_testing()
add_compile_options("$<$<CONFIG:DEBUG>:-fno-omit-frame-pointer>")
add_compile_options("$<$<CONFIG:DEBUG>:-fsanitize=address>")
add_link_options("$<$<CONFIG:DEBUG>:-fsanitize=address>")

add_executable(tests tests.cpp)
target_include_directories(tests PRIVATE "${DATA_STRUCTURE_INCLUDE}")
target_link_libraries(tests PRIVATE GTest::gtest_main PRIVATE DoubleLinkedList PRIVATE Deque PRIVATE PriorityQueue PRIVATE Bitmask)
target_compile_options(tests PRIVATE "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,leak>")
target_link_options(tests PRIVATE "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,leak>")
include(GoogleTest)
gtest_discover_tests(tests)

add_executable(list_fuzz list_fuzz.cpp)
target_include_directories(list_fuzz PRIVATE "${DATA_STRUCTURE_INCLUDE}")
target_link_libraries(list_fuzz PRIVATE DoubleLinkedList)
target_compile_options(list_fuzz PRIVATE "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,fuzzer>")
target_link_options(list_fuzz PRIVATE "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,fuzzer>")

add_executable(deque_fuzz deque_fuzz.cpp)
target_include_directories(deque_fuzz PRIVATE "${DATA_STRUCTURE_INCLUDE}")
target_link_libraries(deque_fuzz PRIVATE Deque)
target_compile_options(deque_fuzz PRIVATE "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,fuzzer>")
target_link_options(deque_fuzz PRIVATE "$<$<C_COMPILER_ID:Clang>:-fsanitize=address,fuzzer>")
