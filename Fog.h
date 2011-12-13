//
//  Fog.h
//  Project
//
//  Created by Inês on 10/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef FOG_H
#define FOG_H

#include "cg/cg.h"

namespace CastleBlast {
	class Fog : public cg::Entity, public cg::IDrawListener {
	public:
		Fog();
		~Fog();
		
		void init();
		void draw();
		double _red, _green, _blue;
		GLfloat _start, _end;
		void setLevel(int level);
		
	private:
		GLfloat _fogColor[4];
		GLfloat _density;
	};
}

#endif