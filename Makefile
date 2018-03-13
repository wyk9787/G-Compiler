# Copied from http://www.partow.net/programming/makefile/idx.html

CXX       	 := clang++
CXXFLAGS 	   := -std=c++14
LDFLAGS      := -L/usr/lib -lstdc++ -lm
BUILD        := ./build
OBJ_DIR      := $(BUILD)/objects
APP_DIR      := $(BUILD)/apps
SRC_DIR      := ./src
LEX_OUTPUT   := $(SRC_DIR)/scanner.yy.cpp
BISON_OUTPUT := $(SRC_DIR)/parser.yy.cpp
BISON_AUX    := $(SRC_DIR)/location.hh $(SRC_DIR)/parser.yy.hpp $(SRC_DIR)/position.hh $(SRC_DIR)/stack.hh
TEST_DIR     := ./test
TARGET       := compiler
INCLUDE      := -Iinclude/ -Isrc/
CORE         := $(SRC_DIR)/compiler.cpp $(SRC_DIR)/expression.cpp $(SRC_DIR)/interpreter.cpp $(SRC_DIR)/parser_driver.cpp $(SRC_DIR)/type.cpp
SRC          := $(BISON_OUTPUT) $(LEX_OUTPUT) $(CORE)

all: build $(APP_DIR)/$(TARGET)

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS)

$(LEX_OUTPUT) : $(SRC_DIR)/scanner.l
	flex  -o $@ $<

$(BISON_OUTPUT) : $(SRC_DIR)/parser.yy
	bison -o $@ $<

.PHONY: all test build clean debug release

test:
	$(TEST_DIR)/test.sh

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rf $(OBJ_DIR)/*
	-@rm -rf $(APP_DIR)/*
	-@rm -rf ${BISON_OUTPUT} ${BISON_AUX}
	-@rm -rf ${LEX_OUTPUT}
