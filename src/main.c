#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <g3x.h>

#include "../include/Point.h"
#include "../include/Camera.h"
#include "../include/Vecteur.h"
#include "../include/Image.h"
#include "../include/Parser.h"
#include "../include/Image.h"
#include "../include/Object.h"
#include "../include/Lst_Object.h"
#include "../include/Png_Output.h"
#include "../include/Scene.h"
#include "../include/Window.h"
#include "../include/Light.h"
#include "../include/Option.h"

int main(int argc, char* argv[]) {
	Option options;
	Scene scene;

	if(!parse_args(argc, argv, &options)){
		lray_usage();
		lray_help();
		return 1;
	}

	if(!createScene(&scene, &options)){
		fprintf(stderr, "fail to create scene\n");
		return 1;
	}

	if (want_fast_output_scene(&options)){
		computeScene(&scene);
		outputScene(&scene, options.output_path);
	}
	else{
		openWindow(&scene, &options);
	}
	freeScene(&scene);
	return 0;
}
