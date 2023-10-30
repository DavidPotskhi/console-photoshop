cmake_minimum_required(VERSION 3.21)
project(project_photoshop)

set(CMAKE_CXX_STANDARD 23)

add_executable(project_photoshop main.cpp bitmap.cpp bitmap.h command_line_parser.cpp command_line_parser.h base_filter.h crop_filter.cpp crop_filter.h filter_pipeline_maker.cpp filter_pipeline_maker.h grayscale.cpp grayscale.h negative.cpp negative.h sharpening.cpp sharpening.h edge_detection.cpp edge_detection.h blur.cpp blur.h application.cpp application.h app_exceptions.h)
