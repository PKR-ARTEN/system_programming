CC=gcc

TARGET = my_shell
OBJECTS = extern_variables.o my_shell.o print_prompt.o m_ls.o get_command.o m_mkdir.o m_cat.o m_cd.o get_path.o m_rm.o

all : $(TARGET)

$(TARGET) : $(OBJECTS)
			  $(CC) -o $@ $^

clean :
	rm *.o my_shell
