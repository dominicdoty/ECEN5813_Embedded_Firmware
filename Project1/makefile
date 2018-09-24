CC := gcc
CFLAGS := -Wall
SRCPATH := src
BUILDPATH := build
INCPATH := include
TARGET := P1_Memtester

SRCEXT := c
SRC := $(shell find $(SRCPATH) -type f -name *.$(SRCEXT))
OBJ := $(patsubst $(SRCPATH)/%, $(BUILDPATH)/%, $(SRC:.$(SRCEXT)=.o))


$(TARGET):$(OBJ)
	$(CC) $^ -o $@ $(LIB)

$(BUILDPATH)/%.o:$(SRCPATH)/%.$(SRCEXT)
	mkdir -p build
	$(CC) $(CFLAGS) -I $(INCPATH) -c -o $@ $<

.PHONY:clean

clean:
	$(RM) -r $(BUILDPATH) $(TARGET)

#add automatic test compilation and execution here later
