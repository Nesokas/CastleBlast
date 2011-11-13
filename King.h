//
//  King.h
//  Project
//
//  Created by Inês on 11/11/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "cg/cg.h"
#include "Model.h"

namespace CastleBlast {
	class King : public cg::Entity, public cg::IDrawListener, public cg::IUpdateListener {
	private:
		Model* _king;
		cg::Vector3d _position;
		
	public:
		King();
		~King();
		
		void init();
		void draw();
		void update(unsigned long elapsed_millis);
		void placeKing(cg::Vector3d position);
	};
}