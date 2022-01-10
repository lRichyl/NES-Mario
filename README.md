# NES Mario
This is a clone of the original Mario for the NES, it's made only for educational purposes. All the sounds and images used belong to Nintendo.

# How the level editor works.
First select an object from the left, then you can choose a layer on which you want to place it using the scrollwheel, the layer number shows on then top right corner of the screen. The layers are drawn in ascending order, which means that layer 0 is first, so it can be used for background objects. Layer 2 is different because it the one in which collision are checked and the player and any dynamic object should be placed here. If Mario is placed in the layer 0, you won't be able to move him, same with enemies, they just won't update. Layers 1 and 3 are just to give more control over the depth of the level. 

For the **item blocks** you can select which object will appear when it is hit by mario with the keys Q and E. Currently you can select between fire flower and mushroom.

To place an object press the mouse left button, and the right mouse button to remove them. The layer where the object was placed needs to be selected in order to remove it.

To go between play mode and the level editor press SPACE.
Controlls:
- Move mario with the arrows.
- Jump with B.

Here's a brief video showing a small level. https://www.youtube.com/watch?v=I0_fCcebxfc


![mario_editor_fire_flower](https://user-images.githubusercontent.com/66743720/148846638-9f39d839-f70f-4806-b190-6cb646bf6575.PNG)

![mario_editor_mushroom](https://user-images.githubusercontent.com/66743720/148846660-3dc5e638-20bf-45c0-be9b-533ecdf2f135.PNG)

![mario_editor_level](https://user-images.githubusercontent.com/66743720/148846670-0aa2853d-7ed8-4ce7-9976-6cb008094be8.PNG)
