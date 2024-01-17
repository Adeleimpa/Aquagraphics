How to run code ? (assuming you have everything to use OpenGL)

I run it on Ubuntu.
OpenGL version string: 4.0 (Compatibility profile) Mesa 22.2.5
Cmake version 3.22.1

1. Download code on your computer
3. Open terminal window in folder 'Code' of Aquagraphics
4. Remove 'build' folder
5. mkdir build
6. cd build
7. cmake ..
8. cd ..

Once you've done that you can you compile and run like that:
9. cmake —build build
10. cd waterRendering
11. ./waterRendering


Commands in the app:
- Press c to move the camera around the scene
- Press space bar to make a droplet fall onto the surface
- Use the arrows to move in the scene
- Press W to visualize the wires of the mesh