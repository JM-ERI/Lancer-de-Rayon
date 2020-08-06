#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "../include/Parser.h"
#include "../include/Object.h"

#define MAX_PIXEL_SAMPLING 8888

typedef void (*fct_parcours_t)(xmlNodePtr);

int static camera_or_source(const char *node_name, int *index){
	int i;
	char *str[2] = {"Camera", "Source"};
	
	for (i = 0; i < 2; i++){
		if (!strcmp(node_name, str[i])){
			(*index) = TYPE_OBJECT_SIZE + i;
			return 1;
		}
	}
	return 0;
}


int static parse_couleur(xmlNodePtr node, Color *color){
	int i;
	
	char *string_values[3] = {"r", "g", "b"};
	unsigned char values[3];
	
	if (node == NULL || color == NULL){
		return 0;
	}
	
	for (i = 0; i < 3 && node != NULL; i++){
		if(strcmp((const char *)node->name, string_values[i]) || node->children == NULL || node->children->content == NULL){
			fprintf(stderr, "color r g b required and not found");
			return 0;
		}
		if (sscanf((const char *)node->children->content, "%hhu", &values[i]) != 1){
			fprintf(stderr, "color r g b required and not found or resolution <= 0");
			return 0;
		}
		
		node = node->next;
	}
	if (i != 3){
		return 0;
	}
	setColor(color, values[0], values[1], values[2]);
	/*printf("set %hhu %hhu %hhu fin \n\n", color[0], color[1], color[2]);*/
	return 1;
}

int static parse_point(xmlNodePtr node, Point *p){
	int i;
	
	char *string_values[3] = {"x", "y", "z"};
	double values[3];
	
	if (p == NULL || node == NULL){
		fprintf(stderr, "point x y z required and not found");
		return 0;
	}
	
	for (i = 0; i < 3 && node != NULL; i++){
		if(strcmp((const char *)node->name, string_values[i]) || node->children == NULL || node->children->content == NULL){
			fprintf(stderr, "point x y z required and not found\n");
			return 0;
		}
		if (sscanf((const char *)node->children->content, "%lf", &values[i]) != 1){
			fprintf(stderr, "point x y z required and not found : value %s\n", string_values[i]);
			return 0;
		}
		
		node = node->next;
	}
	if (i != 3){
		fprintf(stderr, "point x y z required and not found or resolution <= 0");
		return 0;
	}
	setPoint(p, values[0], values[1], values[2]);
	return 1;
}

int static parse_vecteur(xmlNodePtr node, Vecteur *p){
	int i;
	
	char *string_values[3] = {"x", "y", "z"};
	double values[3];
	
	if (p == NULL || node == NULL){
		fprintf(stderr, "point x y z required and not found");
		return 0;
	}
	
	for (i = 0; i < 3 && node != NULL; i++){
		if(strcmp((const char *)node->name, string_values[i]) || node->children == NULL || node->children->content == NULL){
			fprintf(stderr, "point x y z required and not found\n");
			return 0;
		}
		if (sscanf((const char *)node->children->content, "%lf", &values[i]) != 1){
			fprintf(stderr, "point x y z required and not found : value %s\n", string_values[i]);
			return 0;
		}
		
		node = node->next;
	}
	if (i != 3){
		fprintf(stderr, "point x y z required and not found or resolution <= 0");
		return 0;
	}
	setVecteur(p, values[0], values[1], values[2]);
	return 1;
}


/*******			SPECIFIC PARSE			*******/
int static parseCube(xmlNodePtr noeud, Scene *scene){
	double rayon;
	

	Color c;
	Point center;
	Cube cube;
	Object object;
	
	char *required_node[3] = {"center", "rayon", "couleur"};
	
	xmlNodePtr tmp;
	
	if (noeud == NULL || scene == NULL){
		return 0;
	}
	
	if (strcmp((const char *)noeud->name, required_node[0])){
		fprintf(stderr, "cube center required and was not found");
		return 0;
	}
	tmp = noeud->children;	/* center Point */
	if (tmp == NULL || !parse_point(tmp, &center)){
		return 0;
	}
	tmp = noeud->next;	/* rayon */
	if (strcmp((const char *)tmp->name, required_node[1])){
		fprintf(stderr, "cube rayon required and was not found");
		return 0;
	}
	if (tmp->children == NULL || tmp->children->content == NULL || sscanf((const char *)tmp->children->content, "%lf", &rayon) != 1){
		fprintf(stderr, "cube rayon required and was not found");
		return 0;
	}
	tmp = tmp->next;	/* couleur node*/
	if (tmp == NULL || strcmp((const char *)tmp->name, required_node[2])){
		fprintf(stderr, "cube couleur required and was not found");
		return 0;
	}

	if (!parse_couleur(tmp->children, &c)){
		return 0;
	}
	
	setCube(&cube, &center, &c, rayon);
	ObjectFromCube(&object, &cube);
	lst_Object_add_object(&scene->lst_object, &object);
	return 1;
}

int static parseRectangle(xmlNodePtr noeud, Scene *scene){
	
	Color col;
	Point center;
	Vecteur u;
	Vecteur v;
	double rayon;
	Rectangle rectangle;
	Object object;
	
	char *required_node[5] = {"center", "u", "v", "rayon", "couleur"};
	
	xmlNodePtr tmp;
	
	if (noeud == NULL || scene == NULL){
		return 0;
	}
	
	if (strcmp((const char *)noeud->name, required_node[0])){
		fprintf(stderr, "Rectangle center point required and was not found");
		return 0;
	}
	tmp = noeud->children;	/* Point center */
	if (tmp == NULL || !parse_point(tmp, &center)){
		return 0;
	}
    tmp = noeud->next;	/* Vecteur u */
	if (strcmp((const char *)tmp->name, required_node[1])){
		fprintf(stderr, "Rectangle first direction required and was not found");
		return 0;
	}
     tmp = tmp->children;
	if (tmp == NULL || !parse_vecteur(tmp, &u)){
		return 0;
	}
	tmp = noeud->next->next;	/* Vecteur v */
	if (strcmp((const char *)tmp->name, required_node[2])){
		fprintf(stderr, "Rectangle second direction required and was not found");
		return 0;
	}
    tmp = tmp->children;
	if (tmp == NULL || !parse_vecteur(tmp, &v)){
		return 0;
	}
	tmp = noeud->next->next->next;	/* double rayon */
	if (strcmp((const char *)tmp->name, required_node[3])){
		fprintf(stderr, "Rectangle rayon required and was not found");
		return 0;
	}

	if (tmp->children == NULL || tmp->children->content == NULL || sscanf((const char *)tmp->children->content, "%lf", &rayon) != 1){
		fprintf(stderr, "Rectangle rayon required and was not found");
		return 0;
	}

	tmp = tmp->next;	/* couleur node*/
	if (tmp == NULL || strcmp((const char *)tmp->name, required_node[4])){
		fprintf(stderr, "Rectangle couleur required and was not found");
		return 0;
	}

	if (!parse_couleur(tmp->children, &col)){
		return 0;
	}

	setRectangle(&rectangle, &center, &u, &v, rayon, &col);
	ObjectFromRectangle(&object, &rectangle);

	lst_Object_add_object(&scene->lst_object, &object);
	return 1;
}

int static parseSphere(xmlNodePtr noeud, Scene *scene){
	double rayon;
	

	Color c;
	Point center;
	Sphere sphere;
	Object object;
	
	char *required_node[3] = {"center", "rayon", "couleur"};
	
	xmlNodePtr tmp;
	
	if (noeud == NULL || scene == NULL){
		return 0;
	}
	
	/* parsing resolution of camera */
	if (strcmp((const char *)noeud->name, required_node[0])){
		fprintf(stderr, "Sphere center required and was not found");
		return 0;
	}
	tmp = noeud->children;	/* center Point */
	if (tmp == NULL || !parse_point(tmp, &center)){
		return 0;
	}
	tmp = noeud->next;	/* rayon */
	if (strcmp((const char *)tmp->name, required_node[1])){
		fprintf(stderr, "Sphere rayon required and was not found");
		return 0;
	}
	if (tmp->children == NULL || tmp->children->content == NULL || sscanf((const char *)tmp->children->content, "%lf", &rayon) != 1){
		fprintf(stderr, "Sphere rayon required and was not found");
		return 0;
	}
	tmp = tmp->next;	/* couleur node*/
	if (tmp == NULL || strcmp((const char *)tmp->name, required_node[2])){
		fprintf(stderr, "Sphere couleur required and was not found");
		return 0;
	}

	if (!parse_couleur(tmp->children, &c)){
		return 0;
	}
	
	setSphere(&sphere, &center, &c, rayon);
	ObjectFromSphere(&object, &sphere);
	
	lst_Object_add_object(&scene->lst_object, &object);
	return 1;
}

int static parseCylindre(xmlNodePtr noeud, Scene *scene){
	double rayon;
	
	Color c;
	Point p;
	Point q;
	Cylindre cylindre;
	Object object;
	
	char *required_node[4] = {"p", "q", "rayon", "couleur"};
	
	xmlNodePtr tmp;
	
	if (noeud == NULL || scene == NULL){
		return 0;
	}
	
	if (strcmp((const char *)noeud->name, required_node[0])){
		fprintf(stderr, "Cylindre first point required and was not found");
		return 0;
	}
	tmp = noeud->children;	/* center Point p*/
	if (tmp == NULL || !parse_point(tmp, &p)){
		return 0;
	}
    tmp = noeud->next;	/* center Point q*/
	if (strcmp((const char *)tmp->name, required_node[1])){
		fprintf(stderr, "Cylindre second point required and was not found");
		return 0;
	}
     tmp = tmp->children;
	if (tmp == NULL || !parse_point(tmp, &q)){
		return 0;
	}
	tmp = noeud->next->next;	/* rayon */
	if (strcmp((const char *)tmp->name, required_node[2])){
		fprintf(stderr, "Cylindre rayon required and was not found");
		return 0;
	}
	if (tmp->children == NULL || tmp->children->content == NULL || sscanf((const char *)tmp->children->content, "%lf", &rayon) != 1){
		fprintf(stderr, "Cylindre rayon required and was not found");
		return 0;
	}
	tmp = tmp->next;	/* couleur node*/
	if (tmp == NULL || strcmp((const char *)tmp->name, required_node[3])){
		fprintf(stderr, "Cylindre couleur required and was not found");
		return 0;
	}

	if (!parse_couleur(tmp->children, &c)){
		return 0;
	}

	setCylindre(&cylindre, &p, &q, &c, rayon);
	ObjectFromCylindre(&object, &cylindre);

	lst_Object_add_object(&scene->lst_object, &object);
	return 1;
}

int static parseTriangle(xmlNodePtr noeud, Scene *scene){
	
	Color color;
	Point a;
	Point b;
	Point c;
	Triangle triangle;
	Object object;
	
	char *required_node[4] = {"a", "b", "c", "couleur"};
	
	xmlNodePtr tmp;
	
	if (noeud == NULL || scene == NULL){
		return 0;
	}
	
	if (strcmp((const char *)noeud->name, required_node[0])){
		fprintf(stderr, "Triangle first point required and was not found");
		return 0;
	}
	tmp = noeud->children;	/* Point a */
	if (tmp == NULL || !parse_point(tmp, &a)){
		return 0;
	}
    tmp = noeud->next;	/* Point b */
	if (strcmp((const char *)tmp->name, required_node[1])){
		fprintf(stderr, "Triangle second point required and was not found");
		return 0;
	}
     tmp = tmp->children;
	if (tmp == NULL || !parse_point(tmp, &b)){
		return 0;
	}
	tmp = noeud->next->next;	/* Point c */
	if (strcmp((const char *)tmp->name, required_node[2])){
		fprintf(stderr, "Triangle third point required and was not found");
		return 0;
	}
	tmp = tmp->children;
	if (tmp == NULL || !parse_point(tmp, &c)){
		return 0;
	}
	tmp = noeud->next->next->next;	/* couleur node*/
	if (tmp == NULL || strcmp((const char *)tmp->name, required_node[3])){
		fprintf(stderr, "Triangle couleur required and was not found");
		return 0;
	}

	if (!parse_couleur(tmp->children, &color)){
		return 0;
	}

	setTriangle(&triangle, &a, &b, &c, &color);
	ObjectFromTriangle(&object, &triangle);

	lst_Object_add_object(&scene->lst_object, &object);
	return 1;
}

int static parseCamera(xmlNodePtr noeud, Scene *scene){
	int i;
	int j;
	int resolution[2]; /* width height */
	int screen[2];/* width height */
	int *index_to_fill;	

	char *required_node[3] = {"resolution", "screen", "eye"};
	char *required_name[2] = {"width", "height"};

	Point eye;
	
	xmlNodePtr tmp;
	
	if (noeud == NULL || scene == NULL){
		return 0;
	}
	/* parsing resolution of camera */
	if (strcmp((const char *)noeud->name, required_node[0])){
		fprintf(stderr, "Camera resolution required and was not found\n");
		return 0;
	}

	tmp = noeud->children;
	index_to_fill = resolution;
	/* parsing eye of camera */
	for (i = 0; i < 2; i++){
		for (j = 0; j < 2 && tmp != NULL; j++){
			if(strcmp((const char *)tmp->name, required_name[j]) || tmp->children == NULL || tmp->children->content == NULL){
				fprintf(stderr, "resolution width height required and was not found\n");
				return 0;
			}
			if (sscanf((const char *)tmp->children->content, "%d", &index_to_fill[j]) != 1 || index_to_fill[j] < 0){
				fprintf(stderr, "%s width height required and was not found or value <  0 \nerror name: %s content: %s\n", required_node[i], (const char *)tmp->name, (const char *)tmp->children->content);
				return 0;
			}
			
			tmp = tmp->next;
		}
		index_to_fill = screen;
		tmp = noeud->next->children;
	}
	if (i != 2 || noeud->next == NULL || (tmp = noeud->next->next) == NULL){
		fprintf(stderr, "missing <eye> tag\n");
		return 0;
	}
	
	if (tmp == NULL || strcmp((const char *)tmp->name, required_node[i])){
		fprintf(stderr, "Camera eye required and was not found");
		return 0;
	}
	if (!parse_point(tmp->children, &eye)){
		return 0;
	}
	
	setCamera(&scene->camera, &eye, resolution, screen);
	return 1;
}

int static parseSource(xmlNodePtr noeud, Scene *scene){
	double intensity;
	Point p;
	Source src;
	xmlNodePtr tmp;
	
	tmp = noeud;
	if (tmp == NULL || scene == NULL){
		return 0;
	}
	if (noeud == NULL || !parse_point(tmp, &p)){
		return 0;
	}
	tmp = tmp->next->next->next;
	/*printf("%s\n", (const char *)tmp->content);*/
	if(strcmp((const char *)tmp->name, "intensity")){
		fprintf(stderr, "Source intensity required in Source and not found\n");
		return 0;
	}
	if (tmp->children == NULL || 	tmp->children->content == NULL || sscanf((const char *)tmp->children->content, "%lf", &intensity) != 1 || intensity < 0){
		fprintf(stderr, "Source intensity value required and not found  or < 0 \n");
		return 0;
	}
		
	noeud = noeud->next;
	setSource(&src, &p, intensity);
	add_source(&scene->sources, &src);
	return 1;
}

int parse_XML_scene(const char *input_path, Scene *scene) {
	int object_index;	/* which parser to use */
	char * object_name;
	
	int (*all_parser[TYPE_OBJECT_SIZE + 2])(xmlNodePtr noeud, Scene *scene) = {NULL, parseCube, parseCylindre, parseRectangle
																		 , parseSphere, parseTriangle, parseCamera, parseSource};
	
	xmlDocPtr doc;
    xmlNodePtr racine;
    xmlNodePtr noeud;
    
    /* Ouverture du document */
    xmlKeepBlanksDefault(0); /* Ignore les noeuds texte composant la mise en forme */
    doc = xmlParseFile(input_path);
    if (doc == NULL) {
        fprintf(stderr, "Document XML invalide\n");
        return 0;
    }
    /* Récupération de la racine */
    racine = xmlDocGetRootElement(doc);
    if (racine == NULL) {
        fprintf(stderr, "Document XML vierge\n");
        xmlFreeDoc(doc);
		xmlCleanupParser();
        return 0;
    }
    if(racine == NULL || strcmp((char *)racine->name, "Scene")){
		printf("le xml ne commence pas par SCENE : %s\n", (const char *)racine->name);
		return 0;
	}
	
	for (noeud = racine->children; noeud != NULL; noeud = noeud->next){
		if (noeud == NULL){
			fprintf(stderr, "Invalid XML\n");
			return 0;
		}
		/* à retirer et merge avec 1er if */
		if(noeud->type != XML_ELEMENT_NODE){
			fprintf(stderr, "Bad constitution name:%s type:%d\n", (char *)noeud->name, noeud->type);
			return 0;
		}
		object_name = (char *)noeud->name;
		if (object_name == NULL){
			fprintf(stderr, "fail cast xml node name\n");
			return 0;
		}
		
		object_index = string_to_TYPE_OBJECT(object_name);
		if (object_index == UNKNOW && !camera_or_source(object_name, &object_index)){
			return 0;
		}
		
		if (!all_parser[object_index](noeud->children, scene)){
			fprintf(stderr, "fail parsing\n");
			return 0;
		}
	}
	
	xmlFreeDoc(doc);
	xmlCleanupParser();
	
	printf("Successful read Scene !\n");
	return 1;
}

void lray_help(){
	char help_message[512] = {"help : lray show a scene specified by a a xml file\n\
Options	: -n nb -> the level of scene\n\
	      1: single ray tracing\n\
	      2: interactive ray tracing\n\
	      3: recursive interactive ray tracing\n\n\
	  -ps nb -> pixel sampling\n\
	      number of rays launched per pixel\n\n\
	  -i scene.xml  the scene to input\n\n\
	  -o output_image (optional for -n = 2 or 3) export the scene in a png image without print it in a window\n\n\
	  -t timer the scene calculation\n"};
				 
	printf("%s", help_message);
}

void lray_usage(){
	printf("usage: lray -n [1|2|3] [-ps NB if n=3] -i <my_scene.xml> [-o <image name>] [-t timer the scene calculation]\n");
}

int double_arg(char c, int arg){
	if (arg){
		fprintf(stderr, "double use of argument: %c\n", c);
	}
	return arg;
}

int parse_args(int argc, char *argv[], Option *options){
	char wait_s_arg;
	char opt_n;
	char opt_i;
	char opt_o;
	char opt_p;
	int opt;

	if (argv == NULL || options == NULL){
		return 0;
	}
	
	wait_s_arg = opt_n = opt_i = opt_o = opt_p = 0;
	options->level = 0;
	options->timer_on_compute_scene = 0;
	options->pixel_sampling = -1;
	options->input_path = options->output_path = NULL;
	
	while((opt = getopt(argc, argv, "+n:i:o:ps:t")) != -1){
		switch (opt){
			case 'h':
				return 0;
			case 't':
				options->timer_on_compute_scene = 1;
				break;
			case 'n':
				if (double_arg('n', opt_n)){
					return 0;
				}
				opt_n = 1;
				options->level = atoi(optarg);
				if (options->level <= 0 || options->level > 3){
					return 0;
				}
				break;
			case 'i':
				if (double_arg('i', opt_i)){
					return 0;
				}
				opt_i = 1;
				/*strcpy(options->input_path, optarg);*/
				options->input_path = optarg;
				break;
			case 'o':
				if (double_arg('o', opt_o)){
					return 0;
				}
				opt_o = 1;
				/*strcpy(options->output_path, optarg);*/
				options->output_path = optarg;
				break;
			case 'p':
				if (double_arg('p', opt_p)){
					return 0;
				}
				opt_p = 1;
				wait_s_arg = 1;
				break;
			case 's':
				if (wait_s_arg != 1 || options->level != 3){
					fprintf(stderr, "ps argument error\n");
					return 0;
				}
				options->pixel_sampling = atoi(optarg);
				wait_s_arg = 0;
				if (options->pixel_sampling < 0 || options->pixel_sampling > MAX_PIXEL_SAMPLING){
					return 0;
				}
				break;
			default:
				printf("unknow arg: %c\n", opt);
				wait_s_arg = 0;
				return 0;
		}	
		if (wait_s_arg && opt != 'p'){
			return 0;
		}
	}
	
	if (options->level == 0 || (options->level == 3 && options->pixel_sampling == -1)
		|| (options->level == 1 && options->output_path == NULL)){
		return 0;
	}
	return options->input_path != NULL;
}
