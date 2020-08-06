/**
 * \file Scene_generator.h
 * \brief a scene generator that can be imported into the lray program
 * \author Jean-Manuel ERIALC - Hadjer Djerroumi
 * \version 0.1
 * \date 11 juin 2020
 *
 * a scene generator that can be imported into the lray program
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <time.h>

#include "include/Hmat.h"
#include "include/Color.h"
#include "include/Vecteur.h"
#include "include/Point.h"
#include "include/Sphere.h"
#include "include/Cube.h"
#include "include/Cylindre.h"
#include "include/Triangle.h"
#include "include/Rectangle.h"

#define MAX(a,b)((a) < (b) ? (b) : (a))
#define MAX_X 100
#define MAX_Y 100
#define MAX_Z 200
#define DEFAULT_RADIUS 3
#define MAX_RADIUS 9
#define NB_OBJECT_TYPE 5
#define COLOR_MIN 50
#define LIGHT 14
#define MIN_WIDTH 100
#define MIN_HEIGHT 100

#define SPHERE_TAG 1		/*!< bit tag representing a sphere */
#define CUBE_TAG 2			/*!< bit tag representing a cube */
#define CYLINDRE_TAG 4		/*!< bit tag representing a cylinder */
#define TRIANGLE_TAG 8		/*!< bit tag representing a triangle */
#define RECTANGLE_TAG 16	/*!< bit tag representing a rectangle */

#define ALL_OBJECT (~((unsigned int)0))

/**
 * \struct lst_obj
 * \brief a list of objects to generate
 *
 * a list of objects to generate
 * 
 * 
 */
typedef struct _object{
	int radius;				 /*!< the radius of the object */
	Point center;			 /*!< the center */
	struct _object *suivant; /*!< pointer to the next node */
}node, *lst_obj;

/**
 * \struct Scene_info
 * \brief all parameters desired by the user when generating the scene
 *
 * all parameters desired by the user when generating the scene
 * 
 */
typedef struct{
	unsigned int kind_of_object;	/*!< all kind of object */
	int tabulation_nb;				/*!< the number of times we need to tab (useful when creating the xml scene) */
	int nb_object;					/*!< the number of objects to be generated */
	int width;						/*!< the width of the scene when it will be exported in a image */
	int height;						/*!< the height of the scene when it will be exported in a image */
	lst_obj lst;					/*!< the list of objects to write in the file representing the scene */
	FILE *output_file;				/*!< the output file containing the scene */
}Scene_info;

/**################### LST ################### **/

int static add_object(lst_obj *lst, const Point *p, int radius){
	lst_obj tmp;
	
	if (lst == NULL || p == NULL){
		return -1;
	}
	
	tmp = (*lst);
	(*lst) = (node *)malloc(sizeof(node));

	if ((*lst) == NULL){
		return 0;
	}
	(*lst)->center = (*p);
	(*lst)->radius = radius;
	(*lst)->suivant = tmp;
	
	return 1;
}

void static lst_obj_free(lst_obj *lst){
	lst_obj tmp;
	lst_obj suiv;
	if (lst == NULL || (*lst) == NULL){
		return;
	}
	tmp = (*lst)->suivant;
	free(*lst);
	for (;tmp != NULL;){
		suiv = tmp;
		tmp = tmp->suivant;
		free(suiv);
	}
	(*lst) = NULL;
}

/**################### LST END ################### **/


/**################### WRITE SCENE IN XML ################### **/

/**
 * write tabulation to have a pretty XML
 */
void static write_tabulation(const Scene_info *scene_info){
	int i;	 
	for (i = 0; i < scene_info->tabulation_nb; i++){
		fprintf(scene_info->output_file, "\t");
	}
}

/**
 * write two tag <width>value</width>
 * 				 <height>value</height>
 */
void static write_width_height(Scene_info *scene_info, int width, int height){
	int i;
	char text[2][16] = {"width", "height"}; 
	int value[2] = {width, height};
	
	scene_info->tabulation_nb++;
	for (i = 0; i < 2; i++){
		write_tabulation(scene_info);
		fprintf(scene_info->output_file, "<%s>%d</%s>\n", text[i], value[i],text[i]);
	}
	scene_info->tabulation_nb--;
}

/**
 * write three tag <x>value</x>
 * 				   <y>value</y>
 * 				   <z>value</z>
 */
void static write_x_y_z(Scene_info *scene_info, int x, int y, int z){
	int i;
	char text[3][2] = {"x", "y", "z"}; 
	int value[3] = {x, y, z};
	
	scene_info->tabulation_nb++;
	for (i = 0; i < 3; i++){
		write_tabulation(scene_info);
		fprintf(scene_info->output_file, "<%c>%d</%c>\n", text[i][0], value[i],text[i][0]);
	}
	scene_info->tabulation_nb--;
}

/**
 * write a tag <width>
 *
 */
void static write_tag(Scene_info *scene_info, const char *tag, int keep_tabulation){
	
	if (tag[0] != '/'){
		scene_info->tabulation_nb++;
	}
	write_tabulation(scene_info);
	fprintf(scene_info->output_file, "<%s>\n", tag);
	if (keep_tabulation){
		return;
	}
	scene_info->tabulation_nb--;
}

/**
 * write a Color tag
 * 
 * <Couleur>
 * 		<r>r_value</r>
 * 		<g>g_value</g>
 * 		<b>b_value</b>
 * </Couleur>
 */
void static write_Color(Scene_info *scene_info, const Color color){
	int i;
	char text[3][2] = {"r", "g", "b"}; 
	int value[3] = {color.r, color.g, color.b};
	 
	write_tag(scene_info, "couleur", 1);
	scene_info->tabulation_nb++;
	for (i = 0; i < 3; i++){
		write_tabulation(scene_info);
		fprintf(scene_info->output_file, "<%c>%d</%c>\n", text[i][0], value[i],text[i][0]);
	}
	scene_info->tabulation_nb--;
	write_tag(scene_info, "/couleur", 0);
}

/**
 * write a tag <string>value</string>
 */
void static write_single_value(Scene_info *scene_info, const char* text, int value, int keep_tabulation){
	write_tabulation(scene_info);
	fprintf(scene_info->output_file, "<%s>%d</%s>\n", text, value, text);
	if (keep_tabulation){
		return;
	}
	scene_info->tabulation_nb--;
}
/**################### WRITE SCENE IN XML ################### **/

/**	#################### RANDOMIZE OBJECT #################### **/

/** create a random_XXX **/

void static random_Color(Color *color) {
	int light;
	int tmp_r;
	int tmp_g;
	int tmp_b;

	color->r = (rand() % 256);
	color->g = (rand() % 256);
	color->b = (rand() % 256);
	light = LIGHT;
	tmp_r = (255 - color->r) * light + color->r;
	tmp_g = (255 - color->g) * light + color->g;
	tmp_b = (255 - color->b) * light + color->b;

	if (tmp_r > 255 || tmp_g > 255 || tmp_b > 255){
		return;
	}
	
	color->r = tmp_r;
	color->g = tmp_g;
	color->b = tmp_b;
}

void static random_Point(Point *point, double rayon) {
	double maxi;

	do{
		point->x = (rand() % (2 * MAX_X)) - MAX_X;
		point->y = (rand() % (2 * MAX_Y)) - MAX_Y;
		point->z = -(rand() % MAX_Z) - rayon;

		maxi = MAX(point->x, point->y);

	}while (!(point->z < -50 || (maxi < 25)));
}

void static randomize_Sphere(Scene_info *scene_info, Sphere *sphere){
	random_Color(&sphere->color);
	
	sphere->rayon = (rand() % (MAX_RADIUS + 10)) + 1;
	random_Point(&sphere->center, sphere->rayon);
}

void static randomize_Cube(Scene_info *scene_info, Cube *cube){
	random_Color(&cube->color);
	
	cube->rayon = (rand() % (MAX_RADIUS + 5)) + 1;
	random_Point(&cube->center, cube->rayon);
}

void static randomize_Cylindre(Scene_info *scene_info, Cylindre *cylindre){
	double distance;
	random_Color(&cylindre->color);
	do
	{
		cylindre->rayon = (rand() % MAX_RADIUS) + 1;
		random_Point(&cylindre->P, cylindre->rayon);
		random_Point(&cylindre->Q, cylindre->rayon);
		PointDistance(&cylindre->P, &cylindre->Q, &distance);
	} while (distance < cylindre->rayon || distance > 7 * cylindre->rayon);
	
}

void static randomize_Triangle(Scene_info *scene_info, Triangle *triangle){
	random_Color(&triangle->color);

	random_Point(&triangle->A, MAX_RADIUS);
	random_Point(&triangle->B, MAX_RADIUS);
	random_Point(&triangle->C, MAX_RADIUS);
}

void static randomize_Rectangle(Scene_info *scene_info, Rectangle *rectangle){
	random_Color(&rectangle->color);

	rectangle->rayon = (rand() % MAX_RADIUS) + 1;
	
	random_Point(&rectangle->center, rectangle->rayon);

	rectangle->u.x = (rand() % (2 * MAX_X)) - MAX_X;
	rectangle->u.y = (rand() % (2 * MAX_Y)) - MAX_Y;
	rectangle->u.z = -(rand() % MAX_Z);

	rectangle->v.x = (rand() % (2 * MAX_X)) - MAX_X;
	rectangle->v.y = (rand() % (2 * MAX_Y)) - MAX_Y;
	rectangle->v.z = -(rand() % MAX_Z);
}

/**	#################### END RANDOMIZE OBJECT #################### **/

/** #################### GENERATE OBJECT	  #################### **/
/** #################### CREATE A OBJECT THAT DO NOT INTERFERE WITH OTHERS OBJECT #################### **/
void static generateSphere(Scene_info *scene_info, int rayon, const Color color, const Point *center){
	write_tag(scene_info, "Sphere", 1);
	write_tag(scene_info, "center", 1);
	write_x_y_z(scene_info, center->x, center->y, center->z);
	write_tag(scene_info, "/center", 1);
	write_single_value(scene_info, "rayon", rayon, 0);
	write_Color(scene_info, color);
	write_tag(scene_info, "/Sphere", 0);
}

void static generateCube(Scene_info *scene_info, int rayon, const Color color, const Point *center){
	write_tag(scene_info, "Cube", 1);
	write_tag(scene_info, "center", 1);
	write_x_y_z(scene_info, center->x, center->y, center->z);
	write_tag(scene_info, "/center", 1);
	write_single_value(scene_info, "rayon", rayon, 0);
	write_Color(scene_info, color);
	write_tag(scene_info, "/Cube", 0);
}

void static generateCylindre(Scene_info *scene_info, int rayon, const Color color, const Point *p_q){
	const Point *p = &p_q[0];
	const Point *q = &p_q[1];
	
	write_tag(scene_info, "Cylindre", 1);
	write_tag(scene_info, "p", 1);
	write_x_y_z(scene_info, p->x, p->y, p->z);
	write_tag(scene_info, "/p", 0);
	write_tag(scene_info, "q", 1);
	write_x_y_z(scene_info, q->x, q->y, q->z);
	write_tag(scene_info, "/q", 1);
	write_single_value(scene_info, "rayon", rayon, 0);
	write_Color(scene_info, color);
	write_tag(scene_info, "/Cylindre", 0);
}

void static generateRectangle(Scene_info *scene_info, int rayon, const Color color, const Point *center_u_v){
	const Point *center = &center_u_v[0];
	const Point *u = &center_u_v[1];
	const Point *v = &center_u_v[2];
	write_tag(scene_info, "Rectangle", 1);
	write_tag(scene_info, "center", 1);
	write_x_y_z(scene_info, center->x, center->y, center->z);
	write_tag(scene_info, "/center", 0);
	write_tag(scene_info, "u", 1);
	write_x_y_z(scene_info, u->x, u->y, u->z);
	write_tag(scene_info, "/u", 0);
	write_tag(scene_info, "v", 1);
	write_x_y_z(scene_info, v->x, v->y, v->z);
	write_tag(scene_info, "/v", 1);
	write_single_value(scene_info, "rayon", rayon, 0);
	write_Color(scene_info, color);
	write_tag(scene_info, "/Rectangle", 0);
}

void static generateTriangle(Scene_info *scene_info, int rayon, const Color color, const Point *A_B_C){
	const Point *A = &A_B_C[0];
	const Point *B = &A_B_C[1];
	const Point *C = &A_B_C[2];
	write_tag(scene_info, "Triangle", 1);
	write_tag(scene_info, "a", 1);
	write_x_y_z(scene_info, A->x, A->y, A->z);
	write_tag(scene_info, "/a", 0);
	write_tag(scene_info, "b", 1);
	write_x_y_z(scene_info, B->x, B->y, B->z);
	write_tag(scene_info, "/b", 0);
	write_tag(scene_info, "c", 1);
	write_x_y_z(scene_info, C->x, C->y, C->z);
	write_tag(scene_info, "/c", 0);
	write_Color(scene_info, color);
	write_tag(scene_info, "/Triangle", 0);
}

void static generate_camera(Scene_info *scene_info , int resolution_width, int resolution_height, int screen_width, int screen_height, Point *eye){
	
	write_tag(scene_info, "Camera", 1);
	write_tag(scene_info, "resolution", 1);
	write_width_height(scene_info, resolution_width, resolution_height);
	write_tag(scene_info, "/resolution", 0);
	write_tag(scene_info, "screen", 1);
	write_width_height(scene_info, screen_width, screen_height);
	write_tag(scene_info, "/screen", 0);
	write_tag(scene_info, "eye", 1);
	write_x_y_z(scene_info, eye->x, eye->y, eye->z);
	write_tag(scene_info, "/eye", 0);
	write_tag(scene_info, "/Camera", 0);
	
}

void static generate_Source(Scene_info *scene_info , int x, int y, int z, int intensity){
	write_tag(scene_info, "Source", 1);
	write_x_y_z(scene_info, x, y, z);
	scene_info->tabulation_nb++;
	write_single_value(scene_info, "intensity", intensity, 0);
	write_tag(scene_info, "/Source", 0);
	
}
/** #################### END GENERATE OBJECT	  #################### **/

void default_Camera(Scene_info *scene_info){
	Point eye = {0, 0, 50};
	generate_camera(scene_info, scene_info->width, scene_info->height, 50, 50, &eye);
}

void default_Source(Scene_info *scene_info){
	int intensity;
	double z;
	int maxi = MAX(MAX_X, MAX_Y);
	
	intensity = 11000000;
	z = 0.;
	generate_Source(scene_info, maxi, maxi, z, intensity);
	generate_Source(scene_info, -maxi, maxi, z, intensity);
	generate_Source(scene_info, maxi, -maxi, z, intensity);
	generate_Source(scene_info, -maxi, -maxi, z, intensity);
	generate_Source(scene_info, 0., 0., 0, intensity);
	z = -MAX_Z / 2.;
	generate_Source(scene_info, maxi, maxi, z, intensity);
	generate_Source(scene_info, -maxi, maxi, z, intensity);
	generate_Source(scene_info, maxi, -maxi, z, intensity);
	generate_Source(scene_info, -maxi, -maxi, z, intensity);


}

int static intersection(Scene_info *scene_info, const Point *p, int p_radius){
	int biggest_radius;
	double distance;
	lst_obj tmp;
	
	for (tmp = scene_info->lst; tmp != NULL; tmp = tmp->suivant){
		PointDistance(&tmp->center, p, &distance);
		biggest_radius = MAX(tmp->radius, p_radius);
		if (distance < 7 * biggest_radius){
			/*
			PointConsoleDisplay(p, 1);
			printf("%lf distance\n", distance);
			*/
			return 1;
		}
	}
	return 0;
}

int static set_object_type(Scene_info *scene_info){
	unsigned int type;
	unsigned int object_tag;
	for (; ;){
		type = rand() % NB_OBJECT_TYPE;
		object_tag = (unsigned int)1 << type;
		if ((scene_info->kind_of_object & object_tag) == object_tag){
			/* printf("type: %d tag: %d\n", type, object_tag); */
			return type;
		}
	}
}

void static Sphere_args(Scene_info *scene_info, int *radius, Point *p, Color *color, void *element){
	Sphere *sphere;
	
	sphere = (Sphere *)element;
	randomize_Sphere(scene_info, sphere);
	p[0] = sphere->center;
	(*radius) = sphere->rayon;
	(*color) = sphere->color;
}

void static Cube_args(Scene_info *scene_info, int *radius, Point *p, Color *color, void *element){
	Cube *cube;
	
	cube = (Cube *)element;
	randomize_Cube(scene_info, cube);
	p[0] = cube->center;
	(*radius) = cube->rayon;
	(*color) = cube->color;
}

void static Triangle_args(Scene_info *scene_info, int *radius, Point *p, Color *color, void *element){
	Triangle *triangle;
	
	triangle = (Triangle *)element;
	randomize_Triangle(scene_info, triangle);
	(*radius) = MAX_RADIUS;
	(*color) = triangle->color;
	p[0] = triangle->A;
	p[1] = triangle->B;
	p[2] = triangle->C;
}

void static Rectangle_args(Scene_info *scene_info, int *radius, Point *p, Color *color, void *element){
	Rectangle *rectangle;
	
	rectangle = (Rectangle *)element;
	randomize_Rectangle(scene_info, rectangle);
	(*radius) = rectangle->rayon;
	(*color) = rectangle->color;
	p[0] = rectangle->center;
	setPoint(&p[1], rectangle->u.x, rectangle->u.y, rectangle->u.z);
	setPoint(&p[2], rectangle->v.x, rectangle->v.y, rectangle->v.z);
}

void static Cylindre_args(Scene_info *scene_info, int *radius, Point *p, Color *color, void *element){
	Cylindre *cylindre;
	
	cylindre = (Cylindre *)element;
	randomize_Cylindre(scene_info, cylindre);
	(*radius) = cylindre->rayon;
	(*color) = cylindre->color;
	p[0] = cylindre->P;
	p[1] = cylindre->Q;
}

void static random_scene(Scene_info *scene_info){
	Color color;
	int i;
	int radius;
	int object_type;
	int max_recursion;
	int recursion;
	Sphere sphere;
	Cube cube;
	Cylindre cylindre;
	Triangle triangle;
	Rectangle rectangle;
	Point points[3];
	void *objects[NB_OBJECT_TYPE] = {(void *)&sphere, (void *)&cube, (void *)&cylindre, (void *)&triangle, (void *)&rectangle};
	void (*generate_object[NB_OBJECT_TYPE])(Scene_info *, int , const Color , const Point *) = {generateSphere, generateCube, generateCylindre, generateTriangle, generateRectangle};
	void (*get_args[NB_OBJECT_TYPE])(Scene_info *, int *, Point *, Color *, void *) = {Sphere_args, Cube_args, Cylindre_args, Triangle_args, Rectangle_args};

	recursion = 0;
	max_recursion = scene_info->width * scene_info->height * 10;
	
	for (i = 0; i < scene_info->nb_object;){
		object_type = set_object_type(scene_info);
		/* printf("object_type:%d\n", object_type); */
		get_args[object_type](scene_info, &radius, points, &color, objects[object_type]);
		if (recursion > max_recursion){
			fprintf(stderr, "only %d object generated\n", i);
			return;
		}
		if (intersection(scene_info, points, radius)){
			recursion++;
			continue;
		}
		add_object(&scene_info->lst, points, radius);
		generate_object[object_type](scene_info, radius, color, points);
		recursion = 0;
		i++;
	}
	printf("all objects have been successfully created\n");
}

void static generate_scene(Scene_info *scene_info){
	scene_info->tabulation_nb = 0;
	scene_info->lst = NULL;
	fprintf(scene_info->output_file, "<Scene>\n");
	default_Camera(scene_info);
	default_Source(scene_info);
	random_scene(scene_info);
	fprintf(scene_info->output_file, "</Scene>\n");	
}

int static double_arg(char c, int arg){
	if (arg){
		fprintf(stderr, "double use of argument: %c\n", c);
	}
	return arg;
}

int static object_to_generate(Scene_info *scene_info, char *all_object){
	unsigned int i;
	char *object;
	char str_object[NB_OBJECT_TYPE][12] = {"sphere", "cube", "cylindre", "triangle", "rectangle"};
	object = all_object;
	while((object = strtok(object, ",")) != NULL){
		/*printf("%s\n", object);*/
		for (i = 0; i < NB_OBJECT_TYPE; i++){
			if (!strcmp(object, str_object[i])){
				scene_info->kind_of_object |= ((unsigned int)1 << i);
				printf("object %d\n", scene_info->kind_of_object);
				break; 
			}
		}
		if (i == NB_OBJECT_TYPE){
			fprintf(stderr, "unrecognized object %s\n", object);
			return 0;
		}
		object = NULL;
	}
	return 1;
}

/**
 * \fn int parse_args(int argc, char *argv[], Scene_info *scene_info)
 * \brief parse all arguments on the command line and create a scene_info with all the options specified 
 *
 * \param argc number of arguments of the command line
 * \param argv all parameters
 * \param scene_info the scene_info to create
 */
int static parse_args(int argc, char *argv[], Scene_info *scene_info){
	char opt_n;
	char opt_o;
	char opt_p;
	int opt;

	if (argc < 3){
		return 0;
	}
	
	scene_info->width = atoi(argv[1]);
	scene_info->height = atoi(argv[2]);
	scene_info->output_file = NULL;
	scene_info->nb_object = scene_info->kind_of_object = 0;
	
	if (scene_info->width < MIN_WIDTH || scene_info->height < MIN_HEIGHT){
		return 0;
	}
	opt_n = opt_o = opt_p = 0;
	
	while((opt = getopt(argc, argv, "n:o:p:ah")) != -1){
		switch (opt){
			case 'h':
				return 0;
			case 'a':
				if (double_arg('p', opt_p)){ /* -a is all object cannot have -p and -a*/
					return 0;
				}
				opt_p = 1;
				scene_info->kind_of_object = ALL_OBJECT;
				break;
			case 'n':
				if (double_arg('n', opt_n)){
					return 0;
				}
				opt_n = 1;
				scene_info->nb_object = atoi(optarg);
				break;
			case 'p':
				if (double_arg('p', opt_p)){
					return 0;
				}
				opt_p = 1;
				if(!object_to_generate(scene_info, optarg)){
					return 0;
				}
				break;
			case 'o':
				if (double_arg('o', opt_o)){
					return 0;
				}
				opt_o = 1;
				scene_info->output_file = fopen(optarg, "w");
				break;
			default:
				printf("unknow arg: %c\n", opt);
				return 0;
		}	
	}
	
	if (!scene_info->kind_of_object){
		scene_info->kind_of_object = ~((unsigned int)0);
	}

	return scene_info->output_file != NULL
		   && opt_n
		   && scene_info->width > 0
		   && scene_info->height > 0
		   && scene_info->nb_object > 0
		   && scene_info->kind_of_object != 0;
}

/**
 * \fn void static free_scene_info(Scene_info *scene_info)
 * \brief frees the memory allocated by the scene_info
 *
 * \param scene_info the scene_info to release
 */
void static free_scene_info(Scene_info *scene_info){
	fclose(scene_info->output_file);
	lst_obj_free(&scene_info->lst);
}


int main(int argc, char *argv[]){
	
	Scene_info scene_info;
	
	srand(time(NULL));
	if(!parse_args(argc, argv, &scene_info)){
		fprintf(stderr, "Usage: generator width height [-p specify objects to generate e.g -p cube,cylindre,rectangle,sphere,triangle] [-a generate all typed of object] -n nb_object -o output_file\n");
		return 1;
	};
	generate_scene(&scene_info);
	free_scene_info(&scene_info);
	return 0;
}
