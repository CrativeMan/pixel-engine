CXX            := -c++
CXXFLAGS       := -pedantic-errors -Wall -Wextra -Werror
LDFLAGS        := -L/usr/lib -lstdc++ -lm -lGL -lGLEW -lglfw -limgui
BUILD          := ./build
OBJ_DIR        := $(BUILD)/objects
APP_DIR        := $(BUILD)/bin
TARGET         := main
INCLUDE        := -I/home/$(USER)/dev/cpp/pixel-engine/src
SRC            := $(shell find . -name "*.cpp" | sort -k 1nr | cut -f2-)

OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)
DEPENDENCIES \
         := $(OBJECTS:.o=.d)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)

-include $(DEPENDENCIES)

.PHONY: all build clean debug release info

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: TARGET := debug
debug: all

release: CXXFLAGS += -O2
release: TARGET := release
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*

info:
	@echo "[*] Application dir: ${APP_DIR}     "
	@echo "[*] Object dir:      ${OBJ_DIR}     "
	@echo "[*] Sources:         ${SRC}         "
	@echo "[*] Objects:         ${OBJECTS}     "
	@echo "[*] Dependencies:    ${DEPENDENCIES}"
