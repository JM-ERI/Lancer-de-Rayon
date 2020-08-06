#include <stddef.h>
#include "../include/Window.h"
#include "../include/Point.h"
#include "../include/Camera.h"
#include "../include/Image.h"
#include <g3x.h>

#define KEY_CAMERA_UP 'o'
#define KEY_CAMERA_DOWN 'l'
#define KEY_CAMERA_LEFT 'k'
#define KEY_CAMERA_RIGHT 'm'
#define KEY_CAMERA_ZOOM 'p'
#define KEY_CAMERA_UNZOOM 'i'
#define KEY_SAVE_SCENE 's'
#define MOVE_STEP 2
#define MARGE 50

#define MAX_LRAY 9

#ifndef MIN
	#define MIN(a,b) (((a)<(b))?(a):(b))
#endif

#ifndef MAX
	#define MAX(a,b) (((a)<(b))?(b):(a))
#endif

/*G3Xcamera *cam;*/
bool render_progressive = false;
char changed = 0;
static Scene *s;
static Option *args;
/**/Image *progressive_computed_image;/**/

/*
void mouse_callback(G3Xpoint p){
	printf("appel mouse\n");
	if (g3x_GetClic(p)){
		g3x_GetMousePosition(p);
		printf("clic en %f %f %f", p[0], p[0], p[2]);
	}
	printf("\n");
}
*/


static void translate_camera(double x, double y, double z){
	Hmat translateMatrix;
	Hmat M;
	Vecteur translationVector;
	setVecteur(&translationVector, x, y , z);
	Hmat_translation_Vecteur(translateMatrix, &translationVector);
	Hmat_x_Hmat(s->camera.M, translateMatrix, M);
	memcpy(s->camera.M, M, sizeof(Hmat));
	changed = 1;
	s->count_rayon = 0;
}

static int rotate_camera_y(int signe){

	double cos;
	double sin;
	Hmat rotate;
	Hmat rotate_inverse;
	Hmat M;

	Vecteur u;
	Vecteur v;
	setVecteur(&u, 0., 1., 0.);
	setVecteur(&v, 0., .97, .03);
	if(!Cosinus(&u, &v, &cos) || !Sinus(&u, &v, &sin)){
		return 0;
	}

	HmatIdentity(rotate);
	HmatIdentity(rotate_inverse);
	rotate[A00] = rotate[A22] = rotate_inverse[A00] = rotate_inverse[A22] = cos;
	rotate[A02] = rotate_inverse[A20] = sin;
	rotate[A20] = rotate_inverse[A02] = -sin;

	if(signe == -1){
		Hmat_x_Hmat(s->camera.M, rotate_inverse, M);
	}else{
		Hmat_x_Hmat(s->camera.M, rotate, M);
	}
	memcpy(s->camera.M, M, sizeof(Hmat));
	changed = 1;
	s->count_rayon = 0;
	return 1;
}

static int rotate_camera_x(int signe){

	double cos;
	double sin;
	Hmat rotate;
	Hmat rotate_inverse;
	Hmat M;

	Vecteur u;
	Vecteur v;
	setVecteur(&u, 0., 1., 0.);
	setVecteur(&v, 0., .97, .03);
	if(!Cosinus(&u, &v, &cos) || !Sinus(&u, &v, &sin)){
		return 0;
	}

	HmatIdentity(rotate);
	HmatIdentity(rotate_inverse);
	rotate[A11] = rotate[A22] = rotate_inverse[A11] = rotate_inverse[A22] = cos;
	rotate[A12] = rotate_inverse[A21] = -sin;
	rotate[A21] = rotate_inverse[A12] = sin;

	if(signe == -1){
		Hmat_x_Hmat(s->camera.M, rotate_inverse, M);
	}else{
		Hmat_x_Hmat(s->camera.M, rotate, M);
	}
	memcpy(s->camera.M, M, sizeof(Hmat));
	changed = 1;
	s->count_rayon = 0;
	return 1;
}

static void left_callback(){	
	rotate_camera_y(1);
}

static void right_callback(){
	rotate_camera_y(-1);
}

static void up_callback(){
	rotate_camera_x(-1);
}

static void down_callback(){
	rotate_camera_x(1);
}

static void zoom_callback(){
	translate_camera(0., 0., -MOVE_STEP);
}

static void unzoom_callback(){
	translate_camera(0., 0., MOVE_STEP);
}

static void save_scene_callback(){
	printf("saving file in %s\n", args->output_path);
	outputScene(s, args->output_path);
}

static void reflection_down(){
	s->reflection_level = MAX(0, s->reflection_level - 1);
	changed = 1;
}

static void reflection_plus(){
	s->reflection_level = MIN(3, s->reflection_level + 1);
	changed = 1;
}

void init(){
}

void quit(){
	freeScene(s);
	freeImage(progressive_computed_image);
	s = NULL;
}

void draw_level2(){
	glDrawPixels(s->output_image->w, s->output_image->h, GL_RGB, GL_UNSIGNED_BYTE, s->output_image->data);
	if (!s->count_rayon) s->count_rayon++;
}

void anim_level2(){
	Image *tmp;					/* temporary variable for swap */
	/*Image *image_to_display;	 */

	if(!changed){
		if (render_progressive && s->count_rayon < MAX_LRAY){
			/*printf("not changed progressive\n");*/
			tmp = s->output_image;
			s->output_image = progressive_computed_image;
			computeScene(s);
			progressiveRay(s->count_rayon, progressive_computed_image, progressive_computed_image, tmp); /* fais normalement le moyennage */
			/*printf("%p %p %p\n", s->output_image, progressive_computed_image, tmp);*/
			progressive_computed_image = tmp;
			/*s->output_image = progressive_computed_image;*/
			cpyImage(progressive_computed_image, s->output_image);
			/*glDrawPixels(s->output_image->w, s->output_image->h, GL_RGB, GL_UNSIGNED_BYTE, s->output_image->data);*/
			/*printf("%p %p %p\n\n", s->output_image, progressive_computed_image, tmp);*/
			s->count_rayon++;
			/*g3x_Show();*/
		}
		else{
			cpyImage(progressive_computed_image, s->output_image);
			/*glDrawPixels(s->output_image->w, s->output_image->h, GL_RGB, GL_UNSIGNED_BYTE, s->output_image->data);
			printf("not changed\n");*/
		}
		return;
	}
	/*printf("changed\n");*/
	computeScene(s);
	cpyImage(progressive_computed_image, s->output_image);
	/*glDrawPixels(s->output_image->w, s->output_image->h, GL_RGB, GL_UNSIGNED_BYTE, s->output_image->data);*/
	changed = 0;

	/* fait tout le rendu progressif, parcontre ça ne prend pas en compte les autres touches sur lesquelles tu pourrais appuyer pendant le rendu */
	/* la solution 2 serait de faire un rendu progressif à chaque appui de touche */
	/*
	if (render_progressive){
		g3x_Show();
	}
	*/
}

void draw_level3(){
	if(!changed){
		glDrawPixels(s->output_image->w, s->output_image->h, GL_RGB, GL_UNSIGNED_BYTE, s->output_image->data);
	}
	computeScene(s);
	glDrawPixels(s->output_image->w, s->output_image->h, GL_RGB, GL_UNSIGNED_BYTE, s->output_image->data);
	changed = 0;
}

void anim_level3(){
		;
}

void static generate_default_option(){
	void (*draw_function)(void);
	void (*anim_function)(void);
	
	draw_function = NULL;
	anim_function = NULL;
	g3x_SetKeyAction(KEY_CAMERA_LEFT, left_callback, "deplacement gauche de la camera");
	g3x_SetKeyAction(KEY_CAMERA_RIGHT, right_callback, "deplacement droit de la camera");
	g3x_SetKeyAction(KEY_CAMERA_UP, up_callback, "deplacement haut de la camera");
	g3x_SetKeyAction(KEY_CAMERA_DOWN, down_callback, "deplacement bas de la camera");
	g3x_SetKeyAction(KEY_CAMERA_ZOOM, zoom_callback, "zoom de la camera");
	g3x_SetKeyAction(KEY_CAMERA_UNZOOM, unzoom_callback, "de-zoom de la camera");
	g3x_SetKeyAction('-', reflection_down, "diminue la reflection des objets");	
	g3x_SetKeyAction('+', reflection_plus, "augmente la reflection des objets");	
	g3x_SetKeyAction('=', reflection_plus, "augmente la reflection des objets");	
	g3x_SetKeyAction(KEY_SAVE_SCENE, save_scene_callback, "sauvegarde de la scene en png");	
	g3x_SetKeyAction(KEY_SAVE_SCENE, save_scene_callback, "sauvegarde de la scene en png");	
	if (s->level == 2){
	/**/g3x_CreateSwitch("progress.", &render_progressive, "enable/disable progressive render");/**/
		draw_function = draw_level2;
		anim_function = anim_level2;
	}
	else{
		draw_function = draw_level3;
		anim_function = anim_level3;
	}
	
	g3x_SetInitFunction(init);
	g3x_SetExitFunction(quit);
	g3x_SetDrawFunction(draw_function);
	g3x_SetAnimFunction(anim_function);
	
	if (s->level == 2){
		g3x_Continue();
		g3x_SetRefreshFreq(3);
	}
}

void openWindow(Scene* scene, Option *options){
	char default_output[16] = {"scene"};
	if (scene == NULL || options == NULL){
		return;
	}
	g3x_InitWindow("Scene", scene->camera.resolution[0] + MARGE, scene->camera.resolution[1]);
	
	s = scene;
	args = options;
	args->output_path = default_output;
	
	computeScene(s);
	s->count_rayon = 1;
	progressive_computed_image = cloneImage(s->output_image);
	if (progressive_computed_image == NULL){
		fprintf(stderr, "allocation error\n");
		return;
	}
	
	generate_default_option();
	
	g3x_MainStart();
}
