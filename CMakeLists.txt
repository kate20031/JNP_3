cmake_minimum_required(VERSION 3.22)
project(jnp3)

set(CMAKE_CXX_STANDARD 17)

add_executable(jnp3 moneybag.cc moneybag.h moneybag_example.cc)
