CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = leaderboard
SRCS = main.cpp leaderboard.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe *.o

.PHONY: all clean
