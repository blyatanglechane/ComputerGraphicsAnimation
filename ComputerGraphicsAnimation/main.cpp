#include <iostream>
#include <cmath>
#include <GLFW/glfw3.h>

using namespace std;

// ��������� ���������� ���������� ��� �������� ���� ��������
float rotationAngle = 0.0f;
float x, y;
float scale = 1.0f;

void rotateClockwise(float& x, float& y, float angle)
{
    float radians = angle * (3.14 / 180.0f); // ��������� ���� � �������
    float newX = x * cos(radians) - y * sin(radians);
    float newY = x * sin(radians) + y * cos(radians);
    x = newX;
    y = newY;
    rotationAngle += angle; // ��������� �������� ���� ��������
}

void reflectXEqualsY(float& x, float& y)
{
    float deltaX = x - y;
    x = y + deltaX;
    y = x + deltaX;
}

void DrawShape(float x, float y, float rotationAngle)
{
    // ������� ������
    float size = 0.4f * scale;

    // ��������� ���� �������� � �������
    float radians = rotationAngle * (3.14 / 180.0f);

    // ������������ ���������� ������
    float rotatedX = x * cos(radians) - y * sin(radians);
    float rotatedY = x * sin(radians) + y * cos(radians);

    // ������ ������ � ������ ��������
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(rotatedX - size, rotatedY);
    glVertex2f(rotatedX, rotatedY + size);

    glVertex2f(rotatedX, rotatedY + size);
    glVertex2f(rotatedX + size, rotatedY);

    // ������ ����
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(rotatedX - size, rotatedY);
    glVertex2f(rotatedX, rotatedY + size);

    glVertex2f(rotatedX, rotatedY + size);
    glVertex2f(rotatedX + size, rotatedY);

    glVertex2f(rotatedX + size, rotatedY);
    glVertex2f(rotatedX, rotatedY - size);

    glVertex2f(rotatedX, rotatedY - size);
    glVertex2f(rotatedX - size, rotatedY);

    // ��������� ����������
    glVertex2f(rotatedX, rotatedY + size);
    glVertex2f(rotatedX, rotatedY - size);

    glVertex2f(rotatedX + size, rotatedY);
    glVertex2f(rotatedX - size, rotatedY);

    // ��������� ������
    glVertex2f(rotatedX - size, rotatedY);
    glVertex2f(rotatedX - size * 0.25, rotatedY + size * 0.25);

    glVertex2f(rotatedX - size * 0.25, rotatedY + size * 0.25);
    glVertex2f(rotatedX, rotatedY + size);

    glVertex2f(rotatedX, rotatedY + size);
    glVertex2f(rotatedX + size * 0.25, rotatedY + size * 0.25);

    glVertex2f(rotatedX + size * 0.25, rotatedY + size * 0.25);
    glVertex2f(rotatedX + size, rotatedY);

    glVertex2f(rotatedX + size, rotatedY);
    glVertex2f(rotatedX + size * 0.25, rotatedY - size * 0.25);

    glVertex2f(rotatedX + size * 0.25, rotatedY - size * 0.25);
    glVertex2f(rotatedX, rotatedY - size);

    glVertex2f(rotatedX, rotatedY - size);
    glVertex2f(rotatedX - size * 0.25, rotatedY - size * 0.25);

    glVertex2f(rotatedX - size * 0.25, rotatedY - size * 0.25);
    glVertex2f(rotatedX - size, rotatedY);
    glEnd();
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    // �������� ������� ������
    float scaleFactor = 1.1f;
    if (yoffset > 0)
        scale *= scaleFactor;
    else
        scale /= scaleFactor;

    DrawShape(x, y, rotationAngle); // �������������� ������ � ������ ���������
}


/// <summary>
/// /
/// </summary>
/// <param name="window"></param>
/// <param name="key"></param>
/// <param name="scancode"></param>
/// <param name="action"></param>
/// <param name="mods"></param>

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        y += 0.1f / scale;
        DrawShape(x, y, rotationAngle);
    }
    else if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        x += 0.1f / scale;
        DrawShape(x, y, rotationAngle);
    }
    else if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        y -= 0.1f / scale;
        DrawShape(x, y, rotationAngle);
    }
    else if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        x -= 0.1f / scale;
        DrawShape(x, y, rotationAngle);
    }
    // ��������� ������������ ��� OX
    else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        y *= -1;
        DrawShape(x, y, rotationAngle);
    }
    // ��������� ������������ ��� OY
    else if (key == GLFW_KEY_E && action == GLFW_PRESS)
    {
        x *= -1;
        DrawShape(x, y, rotationAngle);
    }
    else if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
        reflectXEqualsY(x, y);
        DrawShape(x, y, rotationAngle);
    }
    // ������� ��������� ������ I � O ��� �������� ������
    else if (key == GLFW_KEY_I && action == GLFW_PRESS)
    {
        rotationAngle -= 1.0f; // ������� ������ ������� ������� �� 1 ������
        DrawShape(x, y, rotationAngle);
    }
    else if (key == GLFW_KEY_O && action == GLFW_PRESS)
    {
        rotationAngle += 1.0f; // ������� �� ������� ������� �� 1 ������
        DrawShape(x, y, rotationAngle);
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
    cout << "������� ���������� ������ ������\n";
    cin >> x >> y;

    /* ���� �� �������� ���� */
    while (!glfwWindowShouldClose(window))
    {
        /* ��������� ����� */
        glClear(GL_COLOR_BUFFER_BIT);

        // ������ ������������ ��������� � ������
        drawAxesWithGrid();

        // ������ ������
        DrawShape(x, y, rotationAngle);

        /* ������������ ��������� � ������� ������� */
        glfwSwapBuffers(window);

        /* �������� ������� � �� ��������� */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}