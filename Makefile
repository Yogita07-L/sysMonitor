# The name of final program
TARGET = monitor

# The command to build the program
$(TARGET): src/main.cpp src/sysUptime.cpp
	g++-13 -I include/ src/main.cpp src/sysUptime.cpp -o $(TARGET)

# A rule to delete the program so it can rebuild from scratch
clean:
	rm -f $(TARGET)