#include <dlfcn.h>
#include <mach-o/dyld.h>


void listImages(void)
{
	//列出所有mach-o镜像
	uint32_t i;
	uint32_t ic = _dyld_image_count();

	printf("Got %d images\n", ic);
	for (int i = 0; i < ic; ++i)
	{
		printf("%d: %p\t%s\t(slide: %p)\n", 
			i,
			_dyld_get_image_header(i),
			_dyld_get_image_name(i),
			_dyld_get_image_slide(i));
	}
}

void add_callback(const struct mach_header *mh, intptr_t vmaddr_slide)
{
	//通过dyld的回掉机制，我们可以得到枚举出二进制的所有镜像的同样功能
	Dl_info info;
	dladdr(mh, &info);
	printf("Callback invoked for image: %p %s (slide: %p)\n", 
		mh, info.dli_fname, vmaddr_slide);
}

int main(int argc, char const *argv[])
{
	//  调用listImage 可以通过_dyld 系列函数
	listImages();

	// 此外还可以注册添加镜像时的回掉函数，这个回掉函数会对此时已有的镜像调用
	_dyld_register_func_for_add_image(add_callback);

	return 0;
}