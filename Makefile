# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17

# Source files
SRCS = gameServer.cpp item.cpp inventory.cpp dropTable.cpp entity.cpp resourceEntity.cpp combatEntity.cpp \
craftingEntity.cpp player.cpp zone.cpp
HEADERS = timeKeeping.h


# Output binary
TARGET = gameServer

# Compile and link
$(TARGET): $(HEADERS) $(SRCS) 
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Clean
clean:
	rm -f $(TARGET)

.PHONY: clean