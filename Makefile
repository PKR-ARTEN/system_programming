CC=gcc

TARGET = my_shell
OBJECTS = my_shell.o print_prompt.o m_ls.o get_command.o m_mkdir.o

all : $(TARGET)

$(TARGET) : $(OBJECTS)
			  $(CC) -o $@ $^

clean :
	rm *.o my_shell
