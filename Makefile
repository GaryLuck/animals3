CC = cl
CFLAGS = /W4 /D_CRT_SECURE_NO_WARNINGS /nologo /Zi

TARGET = animals_c.exe
SRCS = main.c game.c storage.c
OBJS = $(SRCS:.c=.obj)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) /Fe$(TARGET) $(OBJS)

.c.obj:
	$(CC) $(CFLAGS) /c $<

clean:
	-del $(TARGET) $(OBJS) *.pdb *.ilk

.PHONY: all clean
