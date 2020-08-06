#include <stdio.h>
#include "../include/Camera.h"

int setCamera(Camera *camera, const Point *eye, int resolution[2], int screen[2]){
	
	if (camera == NULL || eye == NULL || resolution == NULL || screen == NULL){
		return 0;
	}
	
	camera->eye = (*eye);
	camera->resolution[0] = resolution[0];
	camera->resolution[1] = resolution[1];
	camera->screen[0] = (double)screen[0];
	camera->screen[1] = (double)screen[1];
	HmatIdentity(camera->M);
	
	return 1;
}


int CameraConsoleDisplay(const Camera *camera, int return_line){
	/*
	double horizon;
	int resolution[2];
	Point eye;
	*/
	if (camera == NULL){
		return 0;
	}

	printf("eye:");
	PointConsoleDisplay(&camera->eye, 0);
	printf("resolution: %d %d\n", camera->resolution[0], camera->resolution[1]);
	
	return 1;
}


