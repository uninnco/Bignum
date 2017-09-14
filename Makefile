# 头文件
INCLUDE =include/

# 源文件
SRC     =src/

# 测试文件
TEST    =test/

# 说明文档
DOC     =doc/

# 编译选项
CXXFLAGS= -Wall -g

# 头文件
INC_FLAGS = -I $(INCLUDE)

# 连接选项
#LDFLAGS = -lcpptest

# 目标文件
OBJ     =$(TEST)bignum.o $(TEST)bignum_test.o 
##$(TEST)bignum.o 

all: bignum.o bignum_test.o bignum_test  astyle doxygen

# 编译
bignum.o:$(SRC)bignum.cpp
	g++ -c $(CXXFLAGS)  -o $(TEST)$@ $<  -std=c++11
bignum_test.o:$(TEST)bignum_test.cpp  
	g++ -c $(CXXFLAGS) -o $(TEST)$@ $< -std=c++11
bignum_test:$(OBJ)
	$(CXX) $(CXXFLAGS) $(INC_FLAGS) -o $(TEST)$@ $(OBJ) $(LDFLAGS) 



##:.$(SRC)bignum.cpp
##	g++ $(CXXFLAGS) -c -o $(TEST)$@ $<

# 静态代码检测
cppcheck:
	cppcheck --enable=all $(SRC) $(INCLUDE)

# 测试
#cpptest:
#	$(TEST)string_test > $(TEST)test.html

# TODO 覆盖率测试

# TODO 代码统计

# 清空
clean:
	rm -f $(TEST)string_test.o
	rm -f $(TEST)string_test
	rm -f $(TEST)*.html
	rm -f $(DOC)html/*.*

# 格式化
astyle:
	astyle -A8 $(INCLUDE)*.h $(SRC)*.cpp

# 生成文档
doxygen:
	doxygen

