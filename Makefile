# Compiler and flags
CXX = g++
CXXFLAGS = -lcurl -std=c++17 

# Source files
SRCS = gameServer.cpp item.cpp inventory.cpp dropTable.cpp entity.cpp resourceEntity.cpp combatEntity.cpp \
craftingEntity.cpp player.cpp zone.cpp
HEADERS = timeKeeping.h databaseInterface.h


# Output binary
TARGET = gameServer

# Compile and link
$(TARGET): $(HEADERS) $(SRCS) 
	$(CXX)  $(SRCS) -o $(TARGET) $(CXXFLAGS)

# Clean
clean:
	rm -f $(TARGET)

.PHONY: clean