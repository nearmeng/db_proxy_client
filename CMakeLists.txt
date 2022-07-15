cmake_minimum_required (VERSION 3.20)

project(db_proxy_client)

include (FetchContent)
FetchContent_Declare(cmake_tool GIT_REPOSITORY https://github.com/nearmeng/cmake_tools.git GIT_TAG master)
FetchContent_MakeAvailable(cmake_tool)

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