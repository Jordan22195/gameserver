# Compiler and flags
CXX = g++
CXXFLAGS = -lcurl -std=c++17 

# Source files
SRCS = gameServer.cpp item.cpp inventory.cpp dropTable.cpp entity.cpp resourceEntity.cpp combatEntity.cpp \
craftingEntity.cpp player.cpp zone.cpp
HEADERS = timeKeeping.h databaseInterface.h
INCLUDE = -I/usr/local/lib/aws-sdk-cpp/generated/src/aws-cpp-sdk-dynamodb/include -I/usr/local/include


# Output binary
TARGET = gameServer

# Compile and link
$(TARGET): $(HEADERS) $(SRCS) 
	$(CXX)  $(INCLUDE) $(SRCS) -o $(TARGET) $(CXXFLAGS) 
# Clean
clean:
	rm -f $(TARGET)

.PHONY: clean