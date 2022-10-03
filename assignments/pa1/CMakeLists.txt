add_executable(pa1 pa1.cpp utils.cpp)
target_include_directories(pa1 PRIVATE "${DATA_STRUCTURE_INCLUDE}")
target_link_libraries(pa1 PRIVATE Deque PRIVATE DoubleLinkedList)
add_executable(pa1_eval evaluate.cpp)
