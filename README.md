# Lancer-de-Rayon
Maîtriser le lancer de rayons simple dans une scène hiérarchisée

# Lray
lray show a scene specified by a a xml file<br>
<b>usage: lray -n [1|2|3] [-ps NB if n=3] -i <my_scene.xml> [-o ] [-t timer the scene calculation]</b><br>
  Options : <b><i>-n nb</i></b> the level of scene <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>1:</b> single ray tracing<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>2:</b> interactive ray tracing<br> 
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>3:</b> recursive interactive ray tracing <br>
<b><i>-ps \<nb\></i></b> pixel sampling
number of rays launched per pixel<br>
<b><i>-i <scene.xml></i></b> the scene to create<br>
<b><i>-o <output_image></i></b> (optional for -n = 2 or 3) export the scene in a png image without print it in a window<br>
<b><i>-t</i></b> timer on scene calculation<p>

# Generator
The xml file representing the scene can be generated randomly with the executable <i> generator <i><br>
<b>usage : ./bin/generator <w> <h> [-p <type of objects eg . sphere,rectangle>] -n <number_of_objects> -o <output_file.xml></b><br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b><i> w <nb\></i></b> width of the final scene<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b><i> h <nb\></i></b> height of the final scene<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b><i>-p <type of objects></i></b> all objects wanted seperated by a comma e.g -p cube,cylindre,rectangle,sphere,triangle<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b><i>-n <number of objects></i></b>the number of objects to generate<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b><i>-o <output_file.xml></i></b> the name of the scene's file (with .xml extension)<p>

# Build
In order to build the whole project you have to install the libG3x library by running the <i>install.sh</i> script and use the command <code> make</code><br>
To build the generator of random scene you have to use the command : <code>make generator</code>

# Examples
![level2_ref_2](https://user-images.githubusercontent.com/60750434/89584366-40802a00-d83c-11ea-89e4-8764478f4848.png)
![cube1](https://user-images.githubusercontent.com/60750434/89584389-4d048280-d83c-11ea-8c44-71535e857b76.png)
![Exemple1_Random_100](https://user-images.githubusercontent.com/60750434/89584443-5f7ebc00-d83c-11ea-8cb3-e356113e20c7.png)

# Authors

Jean-Manuel ERIALC -- Hadjer DJERROUMI
