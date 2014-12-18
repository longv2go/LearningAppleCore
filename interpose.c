// 编译为动态库，并且强制加载
// cc -dynamiclib 1.c -o libMTrace.dylib -Wall
// DYLD_INSERT_LIBRARIES=libMTrace.dylib ls

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <malloc/malloc.h>

typedef struct interpose_s
{
	void *new_func;
	void *orig_func;
} interpose_t;

// 我们的原型，要求有原型的原因是要将其放在下面的interposing_functions中
void *my_malloc(int size);
void my_free(void *);


static const interpose_t interposing_functions [] __attribute__ ((section("__DATA, __interpose"))) = {
		{(void *)my_free, (void *)free },
		{(void *)my_malloc, (void *)malloc },
	};

// 在最新的10.10 clang 6.0 中默认如果没有引用 interposing_functions那么，不会连接到动态库中，所以添加了一个test函数只是为了，把interposing_functions编译进入到动态库中
// 可以通过 pagestuff libMTrace.dylib -a 查看macho文件中的section信息等
void test()
{
	printf("%p\n", &interposing_functions);
}

void *my_malloc(int size)
{
	//调用原来的malloc()
	void *returned = malloc(size);

	//调用malloc_printf()的原因是真是的printf内部会调用malloc
	malloc_printf("+ %p %d\n", returned, size);
	return returned;
}

void my_free(void *addr)
{
	malloc_printf(" - %p\n", addr);
	free(addr);
}
