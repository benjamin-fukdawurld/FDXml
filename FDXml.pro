#-------------------------------------------------
#
# Project created by QtCreator 2019-07-11T10:28:10
#
#-------------------------------------------------

TARGET = FDXml
TEMPLATE = lib
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../build/lib
MAKEFILE = ../build/makefiles/$${TARGET}
OBJECTS_DIR = ../build/obj/$${TARGET}

LIBS += -L../build/lib -lFDCore

INCLUDEPATH += include \
    ../FDSerialize/include \
    ../FDCore/include \
    ../thirdparty/

SOURCES += \
    src/Xml_utils.cpp \
    src/XmlValue.cpp \
    src/XmlAttribute.cpp \
    src/XmlNodeIterator.cpp \
    src/XmlAttributeIterator.cpp \
    src/XmlSerializer.cpp

HEADERS += \
    include/FDXml/FDXml.h \
    include/FDXml/Xml_array.h \
    include/FDXml/Xml_array_fwd.h \
    include/FDXml/Xml_fwd.h \
    include/FDXml/Xml_list.h \
    include/FDXml/Xml_list_fwd.h \
    include/FDXml/Xml_map.h \
    include/FDXml/Xml_map_fwd.h \
    include/FDXml/Xml_primitive.h \
    include/FDXml/Xml_primitive_fwd.h \
    include/FDXml/Xml_tuple.h \
    include/FDXml/Xml_tuple_fwd.h \
    include/FDXml/Xml_set.h \
    include/FDXml/Xml_set_fwd.h \
    include/FDXml/Xml_utils.h \
    include/FDXml/XmlSerializer.h \
    include/FDXml/XmlValue.h \
    include/FDXml/XmlAttribute.h \
    include/FDXml/XmlNodeIterator.h \
    include/FDXml/XmlAttributeIterator.h


unix {
    target.path = /usr/lib
    INSTALLS += target
}
