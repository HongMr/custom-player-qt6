#添加编译
set(MESSAGE_QUEUE_SOURCES
        message_queue.cpp
        message_queue.h

)

#设置当前头文件路径
set(MESSAGE_QUEUE_INCLUDE_DIR 
	${CMAKE_CURRENT_SOURCE_DIR}
	# 这个字符串相当于对变量CUSTOM_LOG_INCLUDE_DIR的描述说明，不能省略，但可以自己随便定义,只有添加了这个描述SUB_INCLUDE_DIR变量才能被上层CMakeLists.txt调用！！！
	CACHE INTERNAL "message queue include dir"
)

#生成静态库
add_library(message_queue ${MESSAGE_QUEUE_SOURCES}
    )
