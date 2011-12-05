//
//  Camera.cpp
//  Project
//
//  Created by In�s on 10/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "CannonCamera.h"
namespace CastleBlast {
	
	CannonCamera::CannonCamera(Cannon *cannon) : Entity("CANNON_CAMERA") 
	{
		_cannon = cannon;
	}
	CannonCamera::~CannonCamera() {
	}


	void CannonCamera::init() {
		cg::tWindowInfo win = cg::Manager::instance()->getApp()->getWindowInfo();
		_winWidth = win.width;
		_winHeight = win.height;
		_orientation.setRotationDeg(0,cg::Vector3d::ny);
		_eye.set(0,0,0);
		_center.set(0,0,0);
		_eyeInc.set(0,5,0);
		//_centerInc.set(0,5,0);
		_up.set(0,1,0);
		_front.set(1,0,0);
		_right.set(0,0,1);
		_isRoll = false;
		_scale = 150.0f;
		
		_cameraSpeed = cg::Properties::instance()->getInt("CAMERA_SPEED");
		/* Initialize camera position */
		_q.setRotationDeg(90,_up);
		_front = apply(_q,_front);
		_right = apply(_q,_right);
		_q.setRotationDeg(15, _right);
		_front = apply(_q,_front);
	}
	void CannonCamera::draw() 
	{
		_center = -_front * _scale;
		_cannonPos = _cannon->getPosition();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(65, _winWidth/(double)_winHeight, 1, 500);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(_eye[0]+_cannonPos[0], _eye[1]+_cannonPos[1]+5, _eye[2]+_cannonPos[2],
			_center[0]+_cannonPos[0], _center[1]+_cannonPos[1]+5, _center[2]+_cannonPos[2],
			_up[0], _up[1], _up[2]);
		std::cout << _cannonPos << std::endl;
	}

	void CannonCamera::update(unsigned long elapsed_millis)
	{
		if (cg::KeyBuffer::instance()->isKeyDown('a')) {
			_eyeInc[0] -= _cameraSpeed*_front[2];
			_eyeInc[2] += _cameraSpeed*_front[0];
			_centerInc[0] -= _cameraSpeed*_front[2];
			_centerInc[2] += _cameraSpeed*_front[0];
		}
		if (cg::KeyBuffer::instance()->isKeyDown('d')) {
			_eyeInc[0] += _cameraSpeed*_front[2];
			_eyeInc[2] -= _cameraSpeed*_front[0];
			_centerInc[0] += _cameraSpeed*_front[2];
			_centerInc[2] -= _cameraSpeed*_front[0];
		}
		if (cg::KeyBuffer::instance()->isKeyDown('w')) {
			_eyeInc[0] -= _cameraSpeed*_front[0];
			_eyeInc[2] -= _cameraSpeed*_front[2];
			_centerInc[0] -= _cameraSpeed*_front[0];
			_centerInc[2] -= _cameraSpeed*_front[2];
		}
		if (cg::KeyBuffer::instance()->isKeyDown('s')) {
			_eyeInc[0] += _cameraSpeed*_front[0];
			_eyeInc[2] += _cameraSpeed*_front[2];
			_centerInc[0] += _cameraSpeed*_front[0];
			_centerInc[2] += _cameraSpeed*_front[2];
		}
	}

#if !defined(GLUT_WHEEL_UP)
# define GLUT_WHEEL_UP 3
# define GLUT_WHEEL_DOWN 4
#endif

	void CannonCamera::onMouse(int button, int state, int x, int y)
	{
		_isRoll = (button == GLUT_RIGHT_BUTTON);
		_lastMousePosition.set(x,y);
		if (state == GLUT_UP) {
			if (button == GLUT_WHEEL_UP)
				_scale -= 0.5f;

			else if (button == GLUT_WHEEL_DOWN)
				_scale += 0.5f;
		}
	}

	void CannonCamera::onMouseMotion(int x, int y)
	{	
		double anglex = (_lastMousePosition[0] - x) / (double)5;
			_q.setRotationDeg(anglex,_up);
			_front = apply(_q,_front);
			_right = apply(_q,_right);
		double angley = (y - _lastMousePosition[1]) / (double)5;
			_q.setRotationDeg(angley, _right);
			_front = apply(_q,_front);
		_lastMousePosition.set(x,y);
	}

	void CannonCamera::onMousePassiveMotion(int x, int y)
	{

	}
	void CannonCamera::onReshape(int width, int height) 
	{
		_winWidth = width;
		_winHeight = height;
	}
}