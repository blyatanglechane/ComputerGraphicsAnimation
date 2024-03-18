#include <iostream>
#include <GLFW/glfw3.h>

using namespace std;

float x, y;

void DrawShape(float x, float y)
{
    // ������ ����
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(x - 0.4, y);
    glVertex2f(x, y + 0.4);

    glVertex2f(x, y + 0.4);
    glVertex2f(x + 0.4, y);

    glVertex2f(x + 0.4, y);
    glVertex2f(x, y - 0.4);

    glVertex2f(x, y - 0.4);
    glVertex2f(x - 0.4, y);

    // ��������� ����������
    glVertex2f(x, y + 0.4);
    glVertex2f(x, y - 0.4);

    glVertex2f(x + 0.4, y);
    glVertex2f(x - 0.4, y);

    // ��������� ������
    glVertex2f(x - 0.4, y);
    glVertex2f(x - 0.1, y + 0.1);

    glVertex2f(x - 0.1, y + 0.1);
    glVertex2f(x, y + 0.4);

    glVertex2f(x, y + 0.4);
    glVertex2f(x + 0.1, y + 0.1);

    glVertex2f(x + 0.1, y + 0.1);
    glVertex2f(x + 0.4, y);

    glVertex2f(x + 0.4, y);
    glVertex2f(x + 0.1, y - 0.1);

    glVertex2f(x + 0.1, y - 0.1);
    glVertex2f(x, y - 0.4);

    glVertex2f(x, y - 0.4);
    glVertex2f(x - 0.1, y - 0.1);

    glVertex2f(x - 0.1, y - 0.1);
    glVertex2f(x - 0.4, y);
    glEnd();
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    // �������� ������� ������ ������������ � �������� ������
    float scaleFactor = 1.1f;
    x = x + (xoffset - 450) * 0.002f * scaleFactor;
    y = y - (yoffset - 450) * 0.002f * scaleFactor;
    DrawShape(x, y); // �������������� ������ � ������ ���������
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        y += 0.1f;
        DrawShape(x, y);
    }
    else if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        x += 0.1f;
        DrawShape(x, y);
    }
    else if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        y -= 0.1f;
        DrawShape(x, y);
    }
    else if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        x -= 0.1f;
        DrawShape(x, y);
    }
    // ��������� ������������ ��� OX
    else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        y *= -1;
        DrawShape(x, y);
    }
    // ��������� ������������ ��� OY
    else if (key == GLFW_KEY_E && action == GLFW_PRESS)
    {
        x *= -1;
        DrawShape(x, y);
    }
    else if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
        float x_new = y;
        float y_new = x;
        DrawShape(x_new, y_new);
    }
}

// ������ ������������ ��������� � ������
void drawAxesWithGrid()
{
    // ������ �����
    glColor3f(0.5f, 0.5f, 0.5f); // ����� ���� ��� �����
    glBegin(GL_LINES);
    // ������ �������������� ����� �����
    for (float y = -1.0f; y <= 1.0f; y += 0.1f)
    {
        glVertex2f(-1.0f, y);
        glVertex2f(1.0f, y);
    }
    // ������ ������������ ����� �����
    for (float x = -1.0f; x <= 1.0f; x += 0.1f)
    {
        glVertex2f(x, -1.0f);
        glVertex2f(x, 1.0f);
    }
    glEnd();

    // ������ ��� ���������
    glBegin(GL_LINES);
    // ��� X (�������)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    // ��� Y (�������)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.0f, -1.0f);
    glVertex2f(0.0f, 1.0f);
    glEnd();
}

int main(void)
{
    setlocale(LC_ALL, "Russian");

    /* ������������� ���������� GLFW */
    if (!glfwInit())
        return -1;

    /* �������� ���� � ��� ��������� OpenGL */
    GLFWwindow* window = glfwCreateWindow(900, 900, "Tetris", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* ��������� �������� ��������� ��� ���� */
    glfwMakeContextCurrent(window);
    
    // ������������� ������ ����
    glfwSetScrollCallback(window, scroll_callback);

    // ������������� ������� ��������� ������ ��� ������� ������
    glfwSetKeyCallback(window, keyCallback);

    // ������ ����� ������
    //cout << "������� ���������� ������ ������\n";
    //cin >> x >> y;

    /* ���� �� �������� ���� */
    while (!glfwWindowShouldClose(window))
    {
        /* ��������� ����� */
        glClear(GL_COLOR_BUFFER_BIT);

        // ������ ������������ ��������� � ������
        drawAxesWithGrid();

        // ������ ������
        DrawShape(0, 0);

        /* ������������ ��������� � ������� ������� */
        glfwSwapBuffers(window);

        /* �������� ������� � �� ��������� */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}