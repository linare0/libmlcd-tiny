#include <stdlib.h>
#include <limits.h>
#include "libmlcd-tiny.h"

mltSurface* mltCreateSurface(const unsigned int width,const unsigned int height) {
	mltSurface* surface = (mltSurface*)malloc(sizeof(mltSurface));
	surface->buffer = (unsigned char*)malloc(sizeof(unsigned char[width*height]));
	surface->width = width;
	surface->height = height;
	return surface;
}

mltResult mltClearSurface(mltSurface* const surface,const unsigned char color) {
	unsigned long bs = surface->width * surface->height;
	for(unsigned long i = 0;i < bs;i++) surface->buffer[i] = color;
	return MLT_SUCCESS;
}

mltResult mltDisposeSurface(mltSurface* const surface) {
	free(surface->buffer);
	free(surface);
	return MLT_SUCCESS;
}

mltResult mltPresentDevice(const mltSurface* const surface,const mltDevice* const device) {
	switch(device->type) {
		case MLT_DEVICE_RAW:
			return _mltPresentDevice_RAW(surface,device->ioWrite);
		case MLT_DEVICE_SSD1306:
			return _mltPresentDevice_SSD1306(surface,device->ioWrite);
		default:
			return MLT_FAIL;
	}
}

mltResult mltDrawPoint(mltSurface* const surface,const unsigned char color,const mltDrawOption options,const mltVector2D* const point) {
	if(point->x < 0 || point->y < 0 || point->x >= surface->width || point->y >= surface->height) return MLT_FAIL;
	if(options & MLT_DRAW_BLEND_ADD) {
		if((unsigned int)surface->buffer[(point->y)*(surface->width)+(point->x)] + (unsigned int)color > UCHAR_MAX)
			surface->buffer[(point->y)*(surface->width)+(point->x)] = UCHAR_MAX;
		else
			surface->buffer[(point->y)*(surface->width)+(point->x)] += color;
	} else if(options & MLT_DRAW_BLEND_OVERWRITE) {
		surface->buffer[(point->y)*(surface->width)+(point->x)] = color;
	} else {
		return MLT_FAIL;
	}
	return MLT_SUCCESS;
}
