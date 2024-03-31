#include <iostream>
#include <GLFW/glfw3.h>

using namespace std;

float x, y;
float rotationAngle = 0.0;

void DrawShape(float x, float y)
{
    // ������ ������ � ������ �������� � ��������
    glPushMatrix();
    glTranslatef(x, y, 0.0f); // ����������� � ��������� �����
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f); // ������� ������������ ��� Z

    // ������ ����
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(x - 0.5, y);
    glVertex2f(x, y + 0.5);

    glVertex2f(x, y + 0.5);
    glVertex2f(x + 0.5, y);

    glVertex2f(x + 0.5, y);
    glVertex2f(x, y - 0.5);

    glVertex2f(x, y - 0.5);
    glVertex2f(x - 0.5, y);

    // ��������� ����������
    glVertex2f(x, y + 0.5);
    glVertex2f(x, y - 0.5);

    glVertex2f(x + 0.5, y);
    glVertex2f(x - 0.5, y);

    // ��������� ������
    glVertex2f(x - 0.5, y);
    glVertex2f(x - 0.1, y + 0.1);

    glVertex2f(x - 0.1, y + 0.1);
    glVertex2f(x, y + 0.5);

    glVertex2f(x, y + 0.5);
    glVertex2f(x + 0.1, y + 0.1);

    glVertex2f(x + 0.1, y + 0.1);
    glVertex2f(x + 0.5, y);

    glVertex2f(x + 0.5, y);
    glVertex2f(x + 0.1, y - 0.1);

    glVertex2f(x + 0.1, y - 0.1);
    glVertex2f(x, y - 0.5);

    glVertex2f(x, y - 0.5);
    glVertex2f(x - 0.1, y - 0.1);

    glVertex2f(x - 0.1, y - 0.1);
    glVertex2f(x - 0.5, y);
    glEnd();
    glPopMatrix;
}

//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    // �������� ������� ������
//    if (yoffset > 0)
//        scale += 0.1f; // ����������� ������� �� 0.1 ��� ������������� �����
//    else
//        scale -= 0.1f; // ��������� ������� �� 0.1 ��� ������������� ����
//
//    // ������� �� ����� ���� ������ 0.1
//    if (scale < 0.1f)
//        scale = 0.1f;
//
//    // �������������� ����
//    glfwPostEmptyEvent();
//}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        y += 0.1f; // ��������� ������� ������� ��� ��������� ���������
    }
    else if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        x += 0.1f; // ��������� ������� ������� ��� ��������� ���������
    }
    else if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        y -= 0.1f; // ��������� ������� ������� ��� ��������� ���������
    }
    else if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        x -= 0.1f; // ��������� ������� ������� ��� ��������� ���������
    }
    else if (key == GLFW_KEY_U && action == GLFW_PRESS)
    {
        rotationAngle += 5.0f; // ������� ������ ������� ������� �� 5 ��������
    }
    else if (key == GLFW_KEY_I && action == GLFW_PRESS)
    {
        rotationAngle -= 5.0f; // ������� �� ������� ������� �� 5 ��������
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
    GLFWwindow* window = glfwCreateWindow(900, 900, "Grafic", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* ��������� �������� ��������� ��� ���� */
    glfwMakeContextCurrent(window);

    // ������������� ������� ��������� ������ ��� ������� ������
    glfwSetKeyCallback(window, keyCallback);

    // ������ ����� ������
    cout << "������� ���������� ������ ������\n";
    cin >> x >> y;

    /* ���� �� �������� ���� */
    while (!glfwWindowShouldClose(window))
    {
        /* ��������� ����� */
        glClear(GL_COLOR_BUFFER_BIT);

        // ������ ������������ ��������� � ������
        drawAxesWithGrid();

        // ��������� ������� �������
        glPushMatrix();

        // ������������ ������
        //glScalef(scale, scale, 1.0f);

        // ���������� ������
        glTranslatef(x, y, 0.0f);

        // ������ ������ � ������ ������ � ��������
        DrawShape(x, y);

        // ��������������� ���������� �������
        glPopMatrix();

        /* ������������ ��������� � ������� ������� */
        glfwSwapBuffers(window);

        /* �������� ������� � �� ��������� */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}