#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "../include/Scene.h"
#include "../include/Image.h"
#include "../include/Parser.h"
#define LEVEL_MAX 3
#define M_PI 3.14159265358979323846
#define NBR_RAYONS 9
#define ELEMENTS {3, 3, 1, 1, 3, 1, 5, 1, 1, 3, 5, 3, 1, 5, 3, 5, 5, 5}

void Scene_init(Scene *scene){
	if (scene == NULL){
		return;
	}
	memset(scene, 0, sizeof(Scene));
}

int createScene(Scene *scene, const Option *options){
	if (scene == NULL || options == NULL || options->input_path == NULL){
		return 0;
	}
	
	Scene_init(scene);
	if(!parse_XML_scene(options->input_path, scene)){
		return 0;
	}
	scene->pixel_sampling = options->pixel_sampling;
	scene->level = options->level;
	scene->timer_on_compute_scene = options->timer_on_compute_scene;
	scene->count_rayon = 0;
	scene->reflection_level = 0;
	return 1;
}

void freeScene(Scene *scene){
	if (scene == NULL){
		return;
	}
	/*for_each_Source(scene->sources,  SourceConsoleDisplay);*/
	lst_Object_free(&scene->lst_object);
	free_lst_Source(&scene->sources);
	freeImage(scene->output_image);
	scene->lst_object = NULL;
	scene->output_image = NULL;
}

static int blinn_phong(Color *res, const Scene *scene, const Object *object, const Vecteur *u, const Point *X, const Vecteur *N){
	if(res == NULL || scene == NULL || u == NULL || X == NULL || N == NULL){
		return 0;
	}
	double coef;
	double intensity = 0.;       /* sum of intensities */
	double module2 = 0.;        /* sum of X.S² */
	double diffuse_component = 0.;  /* sum of diffuse_component*/
	double specular_component = 0.; /* sum of specular_component*/
	double ps1; /* XS² before normalisation */
	double ps2; /* N.I I = normalize(XS) */		
	double ps3; /* N.H */
	double ps4; /* R.I reflected * light */
	Vecteur XS; /* illumination vector */
	Vecteur SX; /* inverse of XS */
    Vecteur H;  /* half vector */
    Vecteur R; /* Reflected vector */
	lst_Source sources;  /* linked list of sources */
	for (sources = scene->sources; sources != NULL; sources = sources->suivant){
		if(scene->level == 3 && !delta(&sources->src, X, scene->lst_object)){
			continue;
		}
		ps1 = 0.; ps2 = 0.; ps3 = 0.; ps4 = 0.;
		VecteurOfPoints(&XS, X, &sources->src.p);
		VecteurProd_scal(&XS, &XS, &ps1);
		VecteurNormalize(&XS);
		VecteurProd_scal(N, &XS, &ps2);
		VecteurHalf(&XS, u, &H);
		setVecteur(&SX, -XS.x, -XS.y, -XS.z);
	    VecteurReflected(&SX, N, &R);
    	VecteurProd_scal(&R, &SX, &ps4); /* dot product R.I for Phong model */
    	VecteurNormalize(&R);
		VecteurProd_scal(N, &H, &ps3);
		if(ps2 < 0.) ps2 = 0.;
		if(ps3 < 0.) ps3 = 0.;
		if(ps4 < 0.) ps4 = 0.; 
		intensity += sources->src.intensity;
		module2 += ps1;
		diffuse_component  += ps2;
		specular_component += pow(ps3, object->shininess); /* or ps4 for Phong model */
	}
	if(intensity == 0. || module2 == 0.) {
		setColor(res, 0, 0, 0);
		return 1;
	}
	coef = intensity / (4. * M_PI * module2);
	double r = object->diffuse_reflection_coeff[0] * diffuse_component + object->specular_reflection_coeff[0] * specular_component;
	double g = object->diffuse_reflection_coeff[1] * diffuse_component + object->specular_reflection_coeff[1] * specular_component;
	double b = object->diffuse_reflection_coeff[2] * diffuse_component + object->specular_reflection_coeff[2] * specular_component;
	Color_from_double(res, coef * r, coef * g, coef * b);

	return 1;
}

static int reflexion(Color *color_of_pixel, Scene *scene, Point *A, Vecteur *u, Object *object, int n){
	if(color_of_pixel == NULL || scene == NULL || A == NULL || u == NULL){
		return 0;
	}
	if(n == -1){
		return 1;
	}
	lst_Object tmp;    /* linked list of objects */
	lst_Object closest_object;

	double distance;
	double last_inter = DBL_MAX;

	Point B;
	Point I;
	Point X;
	Point closest_X;

	Vecteur v;
	Vecteur N_tmp;
	Vecteur N;
	Vecteur closest_N;
	Vecteur R;

	Color first_color;
	ColorCopy(&first_color, color_of_pixel);

	closest_object = NULL;

	for (tmp = scene->lst_object; (tmp != NULL && &tmp->obj != object); tmp = tmp->suivant){
		Hmat_x_Point(tmp->obj.Mi, A, &B);
		Hmat_x_Vecteur(tmp->obj.Mi, u, &v);	
		VecteurNormalize(&v);
		if (tmp->obj.rayon_inter(&B, &v, &I, &N_tmp)){
			Hmat_x_Point(tmp->obj.Md, &I, &X);
			Hmat_x_Vecteur(tmp->obj.Mn, &N_tmp, &N);
			PointDistance(A, &X, &distance);
			if(distance < last_inter){
				last_inter = distance;
				closest_object = tmp;
				closest_X = X;
				closest_N = N;
			}
		}
	}

	if (closest_object == NULL){
		return 1;
	}
	VecteurNormalize(&closest_N);
	if(!blinn_phong(color_of_pixel, scene, &closest_object->obj, u, &closest_X, &closest_N)){
		return 0;
	}
    VecteurReflected(u, &closest_N, &R);
    VecteurNormalize(&R);
	reflexion(color_of_pixel, scene, &closest_X, &R, &closest_object->obj, n-1);
	if(object == NULL){
		return 1;
	}
	double r = (double)first_color.r + (double)color_of_pixel->r;
	double g = (double)first_color.g + (double)color_of_pixel->g;
	double b = (double)first_color.b + (double)color_of_pixel->b;
	Color_from_double(color_of_pixel, r, g, b);
    return 1;
}

static int computeScene1(Scene *scene){
	int row;
	int col;
	double pixel_hight;
	double pixel_width;
	double middle_screen_width;
	double middle_screen_hight;
	double last_inter;
	double distance;
	
	Color font;
	Color color_of_pixel;
	
	Point A;  /* the center of the pixel */
	Point I;  /* the intersection point of canonique object */
	Point B;  /* the transformed point of A */
	Point P; /* the top left point of the pixel */
	Point X;  /* the intersection point of object */

	Vecteur u; /* canonique vector */
	Vecteur v; /* the transformed vector of u */
	Vecteur N;
	
	Image *image;
	lst_Object tmp;    /* linked list of objects */
	lst_Object closest_object;    /* linked list of objects */
	
	setColor(&font, 10, 2, 20);

	if (scene->output_image == NULL){
		scene->output_image = newImage(scene->camera.resolution[0], scene->camera.resolution[1]);
	}
	
	image = scene->output_image;
	closest_object = NULL;
	
	if (image == NULL){
		return 0;
	}

	pixel_width = (double)scene->camera.screen[0] / scene->camera.resolution[0];
	pixel_hight = (double)scene->camera.screen[1] / scene->camera.resolution[1];
	middle_screen_width = -(scene->camera.screen[0] / 2.);
	middle_screen_hight = -(scene->camera.screen[1] / 2.);
	for(row = 0; row < scene->camera.resolution[1]; row++){
		for(col = 0; col < scene->camera.resolution[0]; col++){
			setPoint(&P, middle_screen_width + col * pixel_width, middle_screen_hight + row * pixel_hight, 0.);
			setPoint(&A, P.x + pixel_width/2., P.y + pixel_hight/2., 0.);
			VecteurOfPoints(&u, &scene->camera.eye, &A);
			VecteurNormalize(&u);
			ColorCopy(&color_of_pixel, &font);
			last_inter = DBL_MAX;
			for (tmp = scene->lst_object; tmp != NULL; tmp = tmp->suivant){
			    Hmat_x_Point(tmp->obj.Mi, &A, &B);
				Hmat_x_Vecteur(tmp->obj.Mi, &u, &v);
				VecteurNormalize(&v);
				if (tmp->obj.rayon_inter(&B, &v, &I, &N)){
					Hmat_x_Point(tmp->obj.Md, &I, &X);
					PointDistance(&A, &X, &distance);
					if(distance < last_inter){
						last_inter = distance;
						closest_object = tmp;
					}
				}
			}
			if (closest_object != NULL){
				ColorCopy(&color_of_pixel, &closest_object->obj.color);
			}
			ImageSetPixel(image, &color_of_pixel, image->h - row - 1,  col);
			closest_object = NULL;
        }
    }
	
	
    return 1;
}

static int computeScene2(Scene *scene){
	int row;
	int col;
	double pixel_hight;
	double pixel_width;
	double middle_screen_width;
	double middle_screen_hight;
	double a;
	double b;
	Color color_of_pixel;
	Color font;
	
	Point A;  /* the random point inside of the pixel */
	Point A_tmp; /* A befor transformation by the camera matrx */
	Point P; /* the top left point of the pixel */

	Vecteur u; /* canonique vector */
	
	Image *image;

	int tab[2 * NBR_RAYONS] = ELEMENTS;
	
	if (scene == NULL){
		return 0;
	}
	
	setColor(&font, 10, 2, 20);

	if (scene->output_image == NULL){
		scene->output_image = newImage(scene->camera.resolution[0], scene->camera.resolution[1]);
	}
	
	image = scene->output_image;
	
	if (image == NULL){
		return 0;
	}

	pixel_width = (double)scene->camera.screen[0] / scene->camera.resolution[0];
	pixel_hight = (double)scene->camera.screen[1] / scene->camera.resolution[1];
	middle_screen_width = -(scene->camera.screen[0] / 2.);
	middle_screen_hight = -(scene->camera.screen[1] / 2.);
	/**/
	for(row = 0; row < scene->camera.resolution[1]; row++){
		for(col = 0; col < scene->camera.resolution[0]; col++){
			setPoint(&P, middle_screen_width + col * pixel_width, middle_screen_hight + row * pixel_hight, 0.);
			a = (double) tab[2 * scene->count_rayon];
			b = (double) tab[2 * scene->count_rayon + 1];
			setPoint(&A_tmp, P.x + a * pixel_width/6., P.y + b * pixel_hight/6., 0.);
			Vecteur u_tmp;
			VecteurOfPoints(&u_tmp, &scene->camera.eye, &A_tmp);
			
			Hmat_x_Point(scene->camera.M, &A_tmp, &A);
			Hmat_x_Vecteur(scene->camera.M, &u_tmp, &u);
			VecteurNormalize(&u);

			ColorCopy(&color_of_pixel, &font);
			reflexion(&color_of_pixel, scene, &A, &u, NULL, scene->reflection_level);
			ImageSetPixel(image, &color_of_pixel, image->h - row - 1,  col);
        }
    }
	/**/
	
    return 1;
}

static int computeScene3(Scene *scene){
	int row;
	int col;
	int i;
	double pixel_height;
	double pixel_width;
	double middle_screen_width;
	double middle_screen_height;
	double r;
	double g;
	double b;
	
	Color color_of_pixel;
	Color font;
	
	Point A_tmp;
	Point A;
	Point P; /* the top left point of the pixel */

	Vecteur u_tmp; /* canonique vector */
	Vecteur u;

	
	Image *image;

	setColor(&font, 10, 2, 20);

	if (scene->output_image == NULL){
		scene->output_image = newImage(scene->camera.resolution[0], scene->camera.resolution[1]);
	}
	
	image = scene->output_image;
	
	if (image == NULL){
		return 0;
	}
	
	pixel_width = (double)scene->camera.screen[0] / scene->camera.resolution[0];
	pixel_height = (double)scene->camera.screen[1] / scene->camera.resolution[1];
	middle_screen_width = -(scene->camera.screen[0] / 2.);
	middle_screen_height = -(scene->camera.screen[1] / 2.);

	for(row = 0; row < scene->camera.resolution[1]; row++){
		for(col = 0; col < scene->camera.resolution[0]; col++){
			setPoint(&P, middle_screen_width + col * pixel_width, middle_screen_height + row * pixel_height, 0.);
			r = 0.; g = 0.; b = 0.;
			for(i = 0; i < scene->pixel_sampling; i++){
			double random_x = (rand() / (double)RAND_MAX) * pixel_width;
			double random_y = (rand() / (double)RAND_MAX) * pixel_height;
			setPoint(&A_tmp, P.x + random_x, P.y + random_y, 0.);
			VecteurOfPoints(&u_tmp, &scene->camera.eye, &A_tmp);
			
			Hmat_x_Point(scene->camera.M, &A_tmp, &A);
			Hmat_x_Vecteur(scene->camera.M, &u_tmp, &u);
			VecteurNormalize(&u);

            ColorCopy(&color_of_pixel, &font);
            reflexion(&color_of_pixel, scene, &A, &u, NULL, scene->reflection_level);

			r += (double)color_of_pixel.r;
			g += (double)color_of_pixel.g;
			b += (double)color_of_pixel.b;
		}
			Color_from_double(&color_of_pixel, r/scene->pixel_sampling, g/scene->pixel_sampling, b/scene->pixel_sampling);
			ImageSetPixel(image, &color_of_pixel, image->h - row - 1,  col);
        }
    }
	
	
    return 1;
}

int computeScene(Scene *scene){
	int status;
	clock_t begin;
	clock_t end;
	int (*level_ray[LEVEL_MAX])(Scene *) = {computeScene1, computeScene2, computeScene3};
	if (scene->timer_on_compute_scene){
		begin = clock();
		status = level_ray[scene->level - 1](scene);
		end = clock();
		fprintf(stderr, "computed in %ld ms\n", (end -  begin) * 1000 / CLOCKS_PER_SEC);
		return status;
	}
	return level_ray[scene->level - 1](scene);
}

int outputScene(const Scene *scene, const char *output_file){
	if (output_file == NULL || scene == NULL || scene->output_image == NULL){
		return 0;
	}
	writeImagePNG(scene->output_image, output_file);
    printf("Sucessul Output scene\n");
	return 1;
}
