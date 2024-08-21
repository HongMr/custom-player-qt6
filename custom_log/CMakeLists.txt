#添加编译
set(CUSTOM_LOG_SOURCES
        custom_log.cpp
        custom_log.h
)

#设置当前头文件路径
set(CUSTOM_LOG_INCLUDE_DIR 
	${CMAKE_CURRENT_SOURCE_DIR}
	# 这个字符串相当于对变量CUSTOM_LOG_INCLUDE_DIR的描述说明，不能省略，但可以自己随便定义,只有添加了这个描述SUB_INCLUDE_DIR变量才能被上层CMakeLists.txt调用！！！
	CACHE INTERNAL "custom_log include dir"
)

#生成静态库
add_library(custom_log ${CUSTOM_LOG_SOURCES}
    )
