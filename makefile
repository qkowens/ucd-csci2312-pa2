.SUFFIXES : .cc
.SUFFIXES : .c
.SUFFIXES : .cpp

INCDIR =
LIBDIR =

CC = g++

CXXFLAGS = -std=gnu++11

LIBS = -lm

OBJS = main.o Point.o Cluster.o ClusteringTests.o ErrorContext.o

TARGET = PointCluster

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBDIR) $(LIBS)

.cc.o:
	$(CC) -c $(CXXFLAGS) $(INCDIR) $<

.c.o:
	$(CC) -c $(CXXFLAGS) $(INCDIR) $<

.cpp.o:
	$(CC) -c $(CXXFLAGS) $(INCDIR) $<

clean:
	rm -f $(OBJS) $(TARGET) core



