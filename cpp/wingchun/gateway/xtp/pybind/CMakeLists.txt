PROJECT(pyxtp)
if(WIN32)
    SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)
endif()
PYBIND11_ADD_MODULE(xtp SHARED "gateway_ext.cpp")
TARGET_LINK_LIBRARIES(xtp PRIVATE xtp_md xtp_td)

