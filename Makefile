CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

TARGET = tennis-player-builder

SOURCES = src/main.cpp src/TennisPlayer.cpp src/TennisGame.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)