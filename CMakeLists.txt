cmake_minimum_required(VERSION 3.9)
project(3DGraphicsCalculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(3DGraphicsCalculator wwgraphicscore/main.cpp wwgraphicscore/Drawer.cpp wwgraphicscore/Drawer.h wwgraphicscore/Screen.cpp wwgraphicscore/Screen.h wwmathcore/World.cpp wwmathcore/World.h wwdisplayobjects/Object.cpp wwdisplayobjects/Object.h wwmathcore/MVector.cpp wwmathcore/MVector.h wwmathcore/MMatrix.cpp wwmathcore/MMatrix.h wwdisplayobjects/Surface.cpp wwdisplayobjects/Surface.h wwmathcore/Polygon2D.cpp wwmathcore/Polygon2D.h wwgraphicscore/FontDrawer.cpp wwgraphicscore/FontDrawer.h)