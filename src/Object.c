#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../include/Object.h"
#include "../include/Hmat.h"

void static compute_diffuse_reflection_coeff(Object * object){
	object->diffuse_reflection_coeff[0] = object->color.r / 255.;
	object->diffuse_reflection_coeff[1] = object->color.g / 255.;
	object->diffuse_reflection_coeff[2] = object->color.b / 255.;
}

void static compute_specular_reflection_coeff(Object *object, float spec){
	/** default value **/
	object->specular_reflection_coeff[0] = object->specular_reflection_coeff[1] = object->specular_reflection_coeff[2] = spec;
}

int translate(Object *obj, const Vecteur *v){
	Hmat translateMatrix;
	Hmat Md;
	Hmat Mi;
	if(obj == NULL || v == NULL){
		return 0;
	}
	/* Md */
	Hmat_translation_Vecteur(translateMatrix, v);
	Hmat_x_Hmat(obj->Md, translateMatrix, Md);
	memcpy(obj->Md, Md, sizeof(Hmat));
	/* Mi */
	Hmat_translation_Hmatxyz(translateMatrix, -v->x, -v->y, -v->z);
	Hmat_x_Hmat(obj->Mi, translateMatrix, Mi);
	memcpy(obj->Mi, Mi, sizeof(Hmat));

	return 1;
}

int rescale(Object *obj, double a, double b, double c){
	if(obj == NULL){
		return 0;
	}
	Hmat Hd;
	Hmat Hi;
	Hmat Hn;
	Hmat Md;
	Hmat Mi;
	Hmat Mn;
	Homothetie(Hd, a, b, c);
	Homothetie(Hi, 1./a, 1./b, 1./c);
	Homothetie(Hn, b*c, a*c, a*b);
	/* Md */
	Hmat_x_Hmat(obj->Md, Hd, Md);
	memcpy(obj->Md, Md, sizeof(Hmat));
	/* Mi */
	Hmat_x_Hmat(Hi, obj->Mi, Mi);
	memcpy(obj->Mi, Mi, sizeof(Hmat));
	/* Mn */
	Hmat_x_Hmat(obj->Mn, Hn, Mn);
	memcpy(obj->Mn, Mn, sizeof(Hmat));
	return 1;
}

int rotate_x(Object *obj, const Vecteur *u, const Vecteur *v){
	if(VecteurIsZero(u) || VecteurIsZero(v)){
		return 0;
	}
	double cos;
	double sin;
	Hmat rotate;
	Hmat rotate_inverse;
	Hmat Md;
	Hmat Mi;
	Hmat Mn;
	if(obj == NULL || u == NULL || v == NULL){
		return 0;
	}
	Cosinus(u, v, &cos);
	Sinus(u, v, &sin);
	HmatIdentity(rotate);
	HmatIdentity(rotate_inverse);
	rotate[A11] = rotate[A22] = rotate_inverse[A11] = rotate_inverse[A22] = cos;
	rotate[A12] = rotate_inverse[A21] = -sin;
	rotate[A21] = rotate_inverse[A12] = sin;
	/* Md */
	Hmat_x_Hmat(obj->Md, rotate, Md);
	memcpy(obj->Md, Md, sizeof(Hmat));
	/* Mi */
	Hmat_x_Hmat(rotate_inverse ,obj->Mi, Mi);
	memcpy(obj->Mi, Mi, sizeof(Hmat));
	/* Mn */
	Hmat_x_Hmat(obj->Mn, rotate, Mn);
	memcpy(obj->Mn, Mn, sizeof(Hmat));
	return 1;
}

int rotate_y(Object *obj, const Vecteur *u, const Vecteur *v){
	if(VecteurIsZero(u) || VecteurIsZero(v)){
		return 0;
	}
	double cos;
	double sin;
	Hmat rotate;
	Hmat rotate_inverse;
	Hmat Md;
	Hmat Mi;
	Hmat Mn;
	if(obj == NULL || u == NULL || v == NULL){
		return 0;
	}
	if(!Cosinus(u, v, &cos) || !Sinus(u, v, &sin)){
		return 0;
	}
	HmatIdentity(rotate);
	HmatIdentity(rotate_inverse);
	rotate[A00] = rotate[A22] = rotate_inverse[A00] = rotate_inverse[A22] = cos;
	rotate[A02] = rotate_inverse[A20] = sin;
	rotate[A20] = rotate_inverse[A02] = -sin;
	/* Md */
	Hmat_x_Hmat(obj->Md, rotate, Md);
	memcpy(obj->Md, Md, sizeof(Hmat));
	/* Mi */
	Hmat_x_Hmat(rotate_inverse ,obj->Mi, Mi);
	memcpy(obj->Mi, Mi, sizeof(Hmat));
	/* Mn */
	Hmat_x_Hmat(obj->Mn, rotate, Mn);
	memcpy(obj->Mn, Mn, sizeof(Hmat));
	return 1;
}

int rotate_z(Object *obj, const Vecteur *u, const Vecteur *v){
	if(VecteurIsZero(u) || VecteurIsZero(v)){
		return 0;
	}
	double cos;
	double sin;
	Hmat rotate;
	Hmat rotate_inverse;
	Hmat Md;
	Hmat Mi;
	Hmat Mn;
	if(obj == NULL || u == NULL || v == NULL){
		return 0;
	}
	if(!Cosinus(u, v, &cos) || !Sinus(u, v, &sin)){
		return 0;
	}
	HmatIdentity(rotate);
	HmatIdentity(rotate_inverse);
	rotate[A00] = rotate[A11] = rotate_inverse[A00] = rotate_inverse[A11] = cos;
	rotate[A01] = rotate_inverse[A10] = -sin;
	rotate[A10] = rotate_inverse[A01] = sin;
	/* Md */
	Hmat_x_Hmat(obj->Md, rotate, Md);
	memcpy(obj->Md, Md, sizeof(Hmat));
	/* Mi */
	Hmat_x_Hmat(rotate_inverse ,obj->Mi, Mi);
	memcpy(obj->Mi, Mi, sizeof(Hmat));
	/* Mn */
	Hmat_x_Hmat(obj->Mn, rotate, Mn);
	memcpy(obj->Mn, Mn, sizeof(Hmat));
	return 1;
}

int ObjectFromCube(Object *object, const Cube *cube){
	double r;	
	Vecteur translationVector;
	
	if (object == NULL || cube == NULL){
		return 0;
	}
	
	r  = cube->rayon;
    setVecteur(&translationVector, cube->center.x, cube->center.y, cube->center.z);

	object->canonique = CUBE;
	object->shininess = 200;
	ColorCopy(&object->color, &cube->color);

    object->rayon_inter = rayon_inter_Cube;

    HmatIdentity(object->Md);
    HmatIdentity(object->Mi);
    HmatIdentity(object->Mn);
    translate(object, &translationVector);
    rescale(object, r, r, r);
  
    compute_diffuse_reflection_coeff(object);
    compute_specular_reflection_coeff(object, 1.);
	
	return 1;
}

int ObjectFromCylindre(Object *object, const Cylindre *cylindre){
	double r1;
	double r2;
	Point center;
	Vecteur translationVector;
	Vecteur u;
    Vecteur v;
    Vecteur v_x;
    
	if (object == NULL || cylindre == NULL){
		return 0;
	}

	object->shininess = 50;
	
	r1  = cylindre->rayon;
	PointCenter(&center, &cylindre->P, &cylindre->Q);
	PointDistance(&cylindre->P, &center, &r2);
	setVecteur(&translationVector, center.x, center.y, center.z);

	object->canonique = CYLINDRE;
	ColorCopy(&object->color, &cylindre->color);
    object->rayon_inter = rayon_inter_Cylindre;

    HmatIdentity(object->Md);
    HmatIdentity(object->Mi);
    HmatIdentity(object->Mn);
    translate(object, &translationVector);
    setVecteur(&u, 0., 0., 1.);  /* vecteur du cylindre canonique */ 
    VecteurOfPoints(&v, &center, &cylindre->Q); /* vecteur equivalent dans l'objet */

    setVecteur(&v_x, 0., v.y, v.z);
    rotate_x(object, &u, &v_x);
    Hmat_x_Vec(object->Md, &u);
    rotate_y(object, &u, &v);
    rescale(object, r1, r1, r2);
    
	compute_diffuse_reflection_coeff(object);
    compute_specular_reflection_coeff(object, .8);

	return 1;
}

int ObjectFromSphere(Object *object, const Sphere *sphere){
	double r;
	Vecteur translationVector;
	
	if (object == NULL || sphere == NULL){
		return 0;
	}
	
	object->shininess = 60;
	
	r  = sphere->rayon;
	setVecteur(&translationVector, sphere->center.x, sphere->center.y, sphere->center.z);
	object->canonique = SPHERE;
	ColorCopy(&object->color, &sphere->color);

    object->rayon_inter = rayon_inter_Sphere;

    HmatIdentity(object->Md);
    HmatIdentity(object->Mi);
    HmatIdentity(object->Mn);
    translate(object, &translationVector);
    rescale(object, r, r, r);

    compute_diffuse_reflection_coeff(object);
    compute_specular_reflection_coeff(object, .6);

	return 1;
}

int ObjectFromRectangle(Object *object, const Rectangle *rectangle){
	double a;
	double b;

	Point A;
	Point B;
	Point C;
	Point D;
	Vecteur translationVector;
	Vecteur normalize_u;
	Vecteur normalize_v;
    Vecteur u;
    Vecteur v;
    Vecteur t1;
    Vecteur t2;
    Vecteur z1;
    Vecteur z2;	
    Vecteur v_x;
    
	if (object == NULL || rectangle == NULL){
		return 0;
	}

	object->shininess = 100;
	
	VecteurCopy(&normalize_u, &rectangle->u);
	VecteurCopy(&normalize_v, &rectangle->v);
	VecteurNormalize(&normalize_u);
	VecteurNormalize(&normalize_v);
	setVecteur(&translationVector, rectangle->center.x, rectangle->center.y, rectangle->center.z);
	setPoint(&A, rectangle->center.x + rectangle->rayon * normalize_u.x, 
				 rectangle->center.y + rectangle->rayon * normalize_u.y,
				 rectangle->center.z + rectangle->rayon * normalize_u.z);
	setPoint(&B, rectangle->center.x + rectangle->rayon * normalize_v.x, 
				 rectangle->center.y + rectangle->rayon * normalize_v.y,
				 rectangle->center.z + rectangle->rayon * normalize_v.z);	
	setPoint(&C, rectangle->center.x - rectangle->rayon * normalize_u.x, 
				 rectangle->center.y - rectangle->rayon * normalize_u.y,
				 rectangle->center.z - rectangle->rayon * normalize_u.z);
	setPoint(&D, rectangle->center.x - rectangle->rayon * normalize_v.x, 
				 rectangle->center.y - rectangle->rayon * normalize_v.y,
				 rectangle->center.z - rectangle->rayon * normalize_v.z);
	
	PointDistance(&A, &B, &a);
	PointDistance(&B, &C, &b);


	object->canonique = RECTANGLE;
	ColorCopy(&object->color, &rectangle->color);

    object->rayon_inter = rayon_inter_Square;

    HmatIdentity(object->Md);
    HmatIdentity(object->Mi);
    HmatIdentity(object->Mn);

    translate(object, &translationVector);
    setVecteur(&u, 0., 0., 1.);  /* normale du carré canonique */ 
    VecteurProd_vec(&rectangle->u, &rectangle->v, &v); /* normale du rectangle */
    setVecteur(&t1, 1., 1., 0.); /* angle du carré canonique */
    setVecteur(&t2, -1., 1., 0.);
    VecteurOfPoints(&z1, &rectangle->center, &A); /* angle equivalent du rectangle */
    VecteurOfPoints(&z2, &rectangle->center, &B); 
    /* rotation autour x et y (z est initule pour retrouver le plan) */
    setVecteur(&v_x, 0., v.y, v.z);
    rotate_x(object, &u, &v_x);
    Hmat_x_Vec(object->Md, &u);
    Hmat_x_Vec(object->Md, &t1);
    Hmat_x_Vec(object->Md, &t2);
    rotate_y(object, &u, &v);
    /*probleme avec la rotation autour de z
    Hmat_x_Vec(object->Md, &t1);
    Hmat_x_Vec(object->Md, &t2);
    if(VecteurAnglesEquals(&t1, &t2, &z1, &z2)){
    	rotate_z(object, &t1, &z1);
    	return 1;
    }
    rotate_z(object, &t2, &z1);*/

    rescale(object, a, b, 1.);	
	compute_diffuse_reflection_coeff(object);
    compute_specular_reflection_coeff(object, 1.);
	
	return 1;
}

int ObjectFromTriangle(Object *object, const Triangle *triangle){
	Vecteur translationVector;
	Vecteur AB;
	Vecteur AC;
	Vecteur u;
	Vecteur v;
	Vecteur v_x;
	if (object == NULL || triangle == NULL){
		return 0;
	}
	
	object->shininess = 100;
	Point center; 
	PointBarycentre(&triangle->A, &triangle->B, &triangle->C, &center);
    setVecteur(&translationVector, center.x, center.y, center.z);

	object->canonique = TRIANGLE;
	ColorCopy(&object->color, &triangle->color);

    object->rayon_inter = rayon_inter_Triangle;

    HmatIdentity(object->Md);
    HmatIdentity(object->Mi);
    HmatIdentity(object->Mn);
    translate(object, &translationVector);
    VecteurOfPoints(&AB, &triangle->A, &triangle->B);
    VecteurOfPoints(&AC, &triangle->A, &triangle->C);
    setVecteur(&u, 0., 0., 1.);  /* normale du triangle canonique */ 
    VecteurProd_vec(&AB, &AC, &v); /* normale du triangle */
    /* rotation autour x et y (z est initule pour retrouver le plan) */
    setVecteur(&v_x, 0., v.y, v.z);
    rotate_x(object, &u, &v_x);

    rotate_y(object, &u, &v);
    rescale(object, 15., 15., 1.);
    
	compute_diffuse_reflection_coeff(object);
    compute_specular_reflection_coeff(object, 1.);

	return 1;
}

void ObjectCopy(Object *dest, const Object *src){
	if (src == NULL || dest == NULL){
		return;
	}
	memcpy(dest, src, sizeof(Object));
}

TYPE_OBJECT string_to_TYPE_OBJECT(char *object_name){
	int i;
	char * allObjects[TYPE_OBJECT_SIZE] = {"", "Cube", "Cylindre", "Rectangle", "Sphere", "Triangle"};
	
	if(object_name == NULL){
		return UNKNOW;
	}

	for (i = 1; i < TYPE_OBJECT_SIZE; i++){
		if(!strcmp(allObjects[i], object_name)){
			return i;
		}
	}

	return UNKNOW;
}
