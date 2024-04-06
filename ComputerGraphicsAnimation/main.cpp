#include <iostream>
#include <GLFW/glfw3.h>

using namespace std;

float x, y; // ��� ��������� �����
float centerX, centerY; // ��� ��������� ������ ������
float rotationAngle = 0.0;
float scale = 1.0f;
float initialCenterX, initialCenterY;

void reflectXEqualsY(float& x, float& y)
{
    float temp = x;
    x = y;
    y = temp;
}

void DrawShape()
{
    /* ������� ������*/
    float size = 0.1f / scale;

    /* ������ ������ � ������ �������� � ��������*/
    glPushMatrix();
    glTranslatef(centerX, centerY, 0.0f); // ����������� � ��������� �����
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f); // ������� ������������ ��� Z

    /* ������ ����*/
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(centerX - 0.25 - size, centerY);
    glVertex2f(centerX, centerY + 0.25 + size);

    glVertex2f(centerX, centerY + 0.25 + size);
    glVertex2f(centerX + 0.25 + size, centerY);

    glVertex2f(centerX + 0.25 + size, centerY);
    glVertex2f(centerX, centerY - 0.25 - size);

    glVertex2f(centerX, centerY - 0.25 - size);
    glVertex2f(centerX - 0.25 - size, centerY);

    /* ��������� ����������*/
    glVertex2f(centerX, centerY + 0.25 + size);
    glVertex2f(centerX, centerY - 0.25 - size);

    glVertex2f(centerX + 0.25 + size, centerY);
    glVertex2f(centerX - 0.25 - size, centerY);

    /*  ��������� ������*/
    glVertex2f(centerX - 0.25 - size, centerY);
    glVertex2f(centerX - 0.05 - size * 0.25, centerY + 0.05 + size * 0.25);

    glVertex2f(centerX - 0.05 - size * 0.25, centerY + 0.05 + size * 0.25);
    glVertex2f(centerX, centerY + 0.25 + size);

    glVertex2f(centerX, centerY + 0.25 + size);
    glVertex2f(centerX + 0.05 + size * 0.25, centerY + 0.05 + size * 0.25);

    glVertex2f(centerX + 0.05 + size * 0.25, centerY + 0.05 + size * 0.25);
    glVertex2f(centerX + 0.25 + size, centerY);

    glVertex2f(centerX + 0.25 + size, centerY);
    glVertex2f(centerX + 0.05 + size * 0.25, centerY - 0.05 - size * 0.25);

    glVertex2f(centerX + 0.05 + size * 0.25, centerY - 0.05 - size * 0.25);
    glVertex2f(centerX, centerY - 0.25 - size);

    glVertex2f(centerX, centerY - 0.25 - size);
    glVertex2f(centerX - 0.05 - size * 0.25, centerY - 0.05 - size * 0.25);

    glVertex2f(centerX - 0.05 - size * 0.25, centerY - 0.05 - size * 0.25);
    glVertex2f(centerX - 0.25 - size, centerY);
    glEnd();
    glPopMatrix();
}

void resetShape()
{
    centerX = 0;
    centerY = 0;
    x = initialCenterX;
    y = initialCenterY;
    rotationAngle = 0.0f;
    scale = 1.0f;
    DrawShape();
}

void rotateAroundPoint(float angle, float pointX, float pointY)
{
    glPushMatrix();
    glTranslatef(pointX, pointY, 0.0f); // ������� ������� ��������� � ����� (pointX, pointY)
    glRotatef(angle, 0.0f, 0.0f, 1.0f); // ������������ ������� ���������
    glTranslatef(-pointX, -pointY, 0.0f); // ���������� ������� ��������� � �������� ���������
    glPopMatrix();
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    // �������� ������� ������
    float scaleFactor = 1.1f;
    if (yoffset > 0)
        scale *= scaleFactor;
    else
        scale /= scaleFactor;

    DrawShape(); // �������������� ������ � ������ ���������
}

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
        rotationAngle += 45.0f; // ������� ������ ������� ������� �� 5 ��������
    }
    else if (key == GLFW_KEY_I && action == GLFW_PRESS)
    {
        rotationAngle -= 45.0f; // ������� �� ������� ������� �� 5 ��������
    }
    // ��������� ������������ ��� OX
    else if (key == GLFW_KEY_Z && action == GLFW_PRESS)
    {
        y *= -1;
    }
    // ��������� ������������ ��� OY
    else if (key == GLFW_KEY_X && action == GLFW_PRESS)
    {
        x *= -1;
    }
    // ��������� ������������ ������ Y = X
    else if (key == GLFW_KEY_C && action == GLFW_PRESS)
    {
        reflectXEqualsY(x, y);
    }
    // ������� �� �������� ���� ������������ ������������ �����, ����������� � ���� ���������� ���������.
    else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        // ����������� � ������������ ���� � ���������� �����
        cout << "������� ���� ��������: ";
        cin >> rotationAngle;
        cout << "������� ���������� ����� �������� (x y): ";
        cin >> centerX >> centerY;

        // ������������ ������ ������������ �������� �����
        rotateAroundPoint(rotationAngle, centerX, centerY);
    }
    // ������� ������ � �������� ���������
    else if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
    {
        // ������� ������ � �������� ���������
        resetShape();
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

    // ������������� ������� ��������� ������ ��� ��������� ������ ����
    glfwSetScrollCallback(window, scroll_callback);

    // ������������� ������� ��������� ������ ��� ������� ������
    glfwSetKeyCallback(window, keyCallback);

    // ������ ����� ������
    cout << "������� ���������� ������ ������\n";
    cin >> x >> y;

    initialCenterX = x;
    initialCenterY = y;
    /* ���� �� �������� ���� */
    while (!glfwWindowShouldClose(window))
    {
        /* ��������� ����� */
        glClear(GL_COLOR_BUFFER_BIT);

        // ������ ������������ ��������� � ������
        drawAxesWithGrid();

        // ��������� ������� �������
        glPushMatrix();

        // ���������� ������
        glTranslatef(x, y, 0.0f);

        // ������ ������ � ������ ������ � ��������
        DrawShape();

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
