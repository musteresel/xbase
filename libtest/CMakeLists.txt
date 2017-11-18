set(
	LIBTESTS
		indextst
		exptest
		locktest
		testdate
		lfiletst
)
foreach(LIBTEST ${LIBTESTS})
	add_executable(${LIBTEST}_shared ${LIBTEST}.cpp)
	add_executable(${LIBTEST}_static ${LIBTEST}.cpp)
	target_link_libraries(${LIBTEST}_shared xbase64_shared)
	target_link_libraries(${LIBTEST}_static xbase64_static)
endforeach()
