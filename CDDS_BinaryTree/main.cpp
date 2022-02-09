#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"
#include "BinaryTree.h"
#include "TreeNode.h"

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    //initialize binary tree
    BinaryTree<int> binaryTree = BinaryTree<int>();
    TreeNode<int>* selectedNode = nullptr;
    int valueBoxValue = 0;
    bool valueBoxEditMode = false;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, GUI_TEXT_ALIGN_CENTER);

        if (GuiValueBox(Rectangle{ 10, 10, 125, 30 }, NULL, &valueBoxValue, 0, 100, valueBoxEditMode)) valueBoxEditMode = !valueBoxEditMode;

        if (GuiButton(Rectangle{ 145, 10, 125, 30 }, GuiIconText(RICON_OK_TICK, "Insert")))
        {
            // Implement the code to insert valueBoxValue into your binary tree here! 
            binaryTree.insert(valueBoxValue);
            selectedNode = binaryTree.find(valueBoxValue);
        }

        if (GuiButton(Rectangle{ 145, 50, 125, 30 }, GuiIconText(RICON_CROSS, "Remove")))
        {
            // Implement the code to remove the node with value = valueBoxValue from your binary tree here! 
            binaryTree.remove(valueBoxValue);
        }

        // draw the binary tree
        binaryTree.draw(selectedNode);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}