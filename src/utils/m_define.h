#ifndef __M_DEFINE_H__
#define __M_DEFINE_H__

#include "../_morisa.h"

MORISA_NAMESPACE_BEGIN

typedef  unsigned int shape_choice;

#define SHAPE_CUBE						0x01
#define SHAPE_QUAD						0x02
#define SHAPE_PLANE						0x03

// vertex attibute
typedef  unsigned int vertex_attribute;

#define	VA_POSITION						0x01
#define	VA_NORMAL						0x02
#define	VA_POSITION_NORMAL				0x03
#define	VA_TEXCOORD						0x04 
#define	VA_POSITION_TEXCOORD			0x05
#define	VA_POSITION_NORMAL_TEXCOORD 	0x07


MORISA_NAMESPACE_END
#endif