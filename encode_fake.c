#include <stdio.h>
#include <errno.h>
#include <dlfcn.h>

void* find_real_encode()
{
	void* handle;
	void* fn_ptr;

	handle = dlopen("./encode_true.so", RTLD_NOW);
	if (handle == NULL) {
		printf("error loading encode_true.so\n");
		return NULL;
	}

	fn_ptr = dlsym(handle, "encode");
	if (fn_ptr == NULL) {
		printf("error finding symbol: encode\n");
		return NULL;
	}

	return fn_ptr;
}

int encode(double v)
{
	static int (*real_encode)(double v) = NULL;
	int ret;

	if (real_encode == NULL) {
		printf("this is a fake encode, and now I'm trying to find the true one\n");
		real_encode = find_real_encode();
		if (real_encode == NULL) {
			printf("cannot find real encode()\n");
			return -EFAULT;
		}
	}

	ret = real_encode(v);

	return ret;
}
