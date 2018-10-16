#include "libmlcd-tiny.h"

mltResult _mltPresentDevice_RAW(const mltSurface* const surface,int (*ioWrite)(unsigned char data)) {
	unsigned long bs = surface->width * surface->height;
	for(unsigned long i = 0;i < bs;i++)
		if(ioWrite(surface->buffer[i]) < 0) return MLT_FAIL;
	return MLT_SUCCESS;
}
