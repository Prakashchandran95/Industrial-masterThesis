TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp
LIBS += -L/usr/local/lib -lopencv_imgproc -lopencv_core -lopencv_highgui  -lopencv_imgcodecs
LIBS += -L/usr/local/lib -lopencv_dnn -lopencv_ml -lopencv_features2d -lopencv_flann
LIBS += -L/usr/local/lib -lopencv_objdetect -lopencv_photo -lopencv_shape -lopencv_stitching
LIBS += -L/usr/local/lib -lopencv_superres -lopencv_videoio -lopencv_video
