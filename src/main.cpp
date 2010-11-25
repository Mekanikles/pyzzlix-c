#include "stdlib.h"
#include "stdio.h"


#include "GL/glfw.h"



int main(int argc, char** argv)
{
    fprintf(stderr, "Running pyzzlix!\n");


    glfwInit();

    glfwOpenWindow(640, 480, 0, 0, 0, 0, 0, 0, GLFW_WINDOW);

    int done = false;
    while(!done)
    {
        done = (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS);


        glfwSwapBuffers();
    }
    
    glfwTerminate();

    return 0;
}
