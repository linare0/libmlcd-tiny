#ifndef LIBMLCD_TINY_H
#define LIBMLCD_TINY_H

#define MLT_DEVICE_SSD1306	0x0002
#define MLT_DEVICE_RAW	0x0001
#define MLT_SUCCESS	0x0001
#define MLT_FAIL	0x0002
#define MLT_DRAW_BLEND_ADD	0x0001
#define MLT_DRAW_BLEND_OVERWRITE	0x0002

typedef int mltResult;
typedef unsigned int mltDeviceType;
typedef unsigned int mltDrawOption;

typedef struct {
	unsigned int height;
	unsigned int width;
	unsigned char* buffer;
} mltSurface;

typedef struct {
	unsigned int x;
	unsigned int y;
} mltVector2D;

typedef struct {
	mltDeviceType type;
	int (*ioWrite)(unsigned char data);
} mltDevice;

mltSurface* mltCreateSurface(const unsigned int width,const unsigned int height);
mltResult mltClearSurface(mltSurface* const surface, const unsigned char color);
mltResult mltDisposeSurface(mltSurface* const surface);
mltResult mltPresentDevice(const mltSurface* const surface,const mltDevice* const device);

mltResult mltDrawPoint(mltSurface* const surface,const unsigned char color,const mltDrawOption options,const mltVector2D* const point);
mltResult mltDrawLine(mltSurface* const surface,const unsigned char color,const mltDrawOption options,const mltVector2D* const p1,const mltVector2D* const p2);

#endif
