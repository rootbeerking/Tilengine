/*
* Tilengine - The 2D retro graphics engine with raster effects
* Copyright (C) 2015-2019 Marc Palacios Domenech <mailto:megamarc@hotmail.com>
* All rights reserved
*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/.
* */

#ifndef _ENGINE_H
#define _ENGINE_H

#include "Tilengine.h"
#include "Sprite.h"
#include "Layer.h"
#include "Animation.h"
#include "Bitmap.h"
#include "Blitters.h"

/* motor */
typedef struct Engine
{
	uint32_t	header;			/* object signature to identify as engine context */
	uint8_t*	priority;		/* buffer receiving tiles with priority */
	uint16_t*	collision;		/* buffer with sprite coverage IDs for per-pixel collision */
	uint8_t*	tmpindex;		/* buffer for intermediate scanline output  */
	int			numsprites;		/* number of sprites */
	Sprite*		sprites;		/* pointer to sprite buffer */
	int			numlayers;		/* number of layers */
	Layer*		layers;			/* pointer to layer buffer */
	int			numanimations;	/* number of animations */
	Animation*	animations;		/* pointer to animation buffer */
	bool		dopriority;		/* there is some data in "priority" buffer that need blitting */
	TLN_Error	error;			/* last error code */
	TLN_LogLevel log_level;		/* logging level */

	uint32_t	bgcolor;		/* background color */
	TLN_Bitmap	bgbitmap;		/* background bitmap */
	TLN_Palette	bgpalette;		/* background bitmap palette */
	ScanBlitPtr	blit_fast;		/* blitter for background bitmap */
	uint8_t*	blend_table;	/* current blending table */
	void		(*raster)(int);	/* raster callback */
	void		(*frame)(int);	/* frame callback */
	int line;					/* current scanline */

	int first_sprite;			/* first sprite in list, none = -1 */
	int last_sprite;			/* last sprite in list, none = -1 */
	int sprite_mask_top;		/* top scanline for sprite masking */
	int sprite_mask_bottom;		/* bottom scanline for sprite masking */

	struct
	{
		int		width;
		int		height;
		int		pitch;
		uint8_t*	data;
	}
	framebuffer;
}
Engine;

extern Engine* engine;

extern void tln_trace(TLN_LogLevel log_level, const char* format, ...);

#define GetFramebufferLine(line) \
	(engine->framebuffer.data + (line*engine->framebuffer.pitch))

#endif
