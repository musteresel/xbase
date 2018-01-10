add_executable(
	tests
		main.cpp
		test_date.cpp
		test_exp.cpp
		test_index.cpp
		test_lfile.cpp
		test_lock.cpp
)
target_link_libraries(
	tests
		gtest
		xbase64_static
)

add_custom_target(check COMMAND ./tests)
