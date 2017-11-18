set(
	EXAMPLES
		sample1
		sample2
		sample3
		sample4
		sample5
		exfilter
		xbstring
)
foreach(EXAMPLE ${EXAMPLES})
	add_executable(${EXAMPLE} ${EXAMPLE}.cpp)
	target_link_libraries(${EXAMPLE} xbase64_shared)
endforeach()
