cmake_minimum_required (VERSION 3.20)

project(db_proxy_client)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#set(CMAKE_VERBOSE_MAKEFILE on)

include (precompile)
include (project)
include (fetch_content)

fetch_content(thirdparty https://github.com/nearmeng/thirdparty.git master)
fetch_content(common https://github.com/nearmeng/common.git master)
fetch_content(db_proxy_proto https://github.com/nearmeng/db_proxy_proto.git master)

init_project()

pre_project(db_proxy_client STATIC)

add_project()

post_project()

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries (${TARGET_NAME}
    mango::common
    mango::db_proxy_proto
	3rd::hiredis
)