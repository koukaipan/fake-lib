#include <stdio.h>
#include <errno.h>
#include <dlfcn.h>

void* dlopen_wrapper()
{
	void *handle;

	handle = dlopen("./encode_true.so", RTLD_NOW);
	if (handle == NULL) {
		printf("error loading encode_true.so (%s)\n", dlerror());
		return NULL;
	}

	return handle;
}

void* find_real_encode(void *handle, const char* fn_name)
{
	void* fn_ptr;

	fn_ptr = dlsym(handle, fn_name);
	if (fn_ptr == NULL) {
		printf("error finding symbol: %s (%s)\n", fn_name, dlerror());
		return NULL;
	}

	return fn_ptr;
}

int encode(double v)
{
	void* handle;
	int (*real_encode)(double v) = NULL;
	int ret;

	handle = dlopen_wrapper();
	printf("this is a fake encode1, and now I'm trying to find the true one\n");
	real_encode = find_real_encode(handle, __func__);
	if (real_encode == NULL) {
		printf("cannot find real encode()\n");
		return -EFAULT;
	}

	ret = real_encode(v);
	dlclose(handle);

	return ret;
}

int encode2(double v)
{
	void* handle;
	int (*real_encode)(double v) = NULL;
	int ret;

	handle = dlopen_wrapper();
	printf("this is a fake encode2, and now I'm trying to find the true one\n");
	real_encode = find_real_encode(handle, __func__);
	if (real_encode == NULL) {
		printf("cannot find real encode()\n");
		return -EFAULT;
	}

	ret = real_encode(v);
	dlclose(handle);

	return ret;
}
