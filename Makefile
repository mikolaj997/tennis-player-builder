CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

TARGET = tennis-player-builder

SOURCES = src/main.cpp src/TennisPlayer.cpp src/TennisGame.cpp
HEADERS = $(wildcard include/*.h)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
