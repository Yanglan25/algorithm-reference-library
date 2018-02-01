CC=gcc
LDFLAGS=$(shell python3-config --ldflags) -lcfitsio
EXT_SUFFIX=$(shell python3-config --extension-suffix) $(LDFLAGS)

all:
	gcc $(BUILD_LIB)/ffi_demo$(EXT_SUFFIX) $(LDFLAGS) -o ffi_demo
	gcc $(BUILD_LIB)/ical_demo$(EXT_SUFFIX) $(LDFLAGS) -o ical_demo
	gcc $(BUILD_LIB)/timg_starpu$(EXT_SUFFIX) $(LDFLAGS) -L$(HOME)/.local/starpu/lib -L$(HOME)/arch/ia64-gcc/lib -lstarpu-1.2 -o timg_starpu

clean:
	rm -rf build ffi_demo ical_demo timg_starpu
