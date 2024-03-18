#include <iostream>
#include <GLFW/glfw3.h>

using namespace std;

float x, y;

void DrawShape(float x, float y)
{
    // Рисуем ромб
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

    // Отрсиовка крестовины
    glVertex2f(x, y + 0.4);
    glVertex2f(x, y - 0.4);

    glVertex2f(x + 0.4, y);
    glVertex2f(x - 0.4, y);

    // Отрисовка звезды
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
    // Изменяем масштаб фигуры относительно её текущего центра
    float scaleFactor = 1.1f;
    x = x + (xoffset - 450) * 0.002f * scaleFactor;
    y = y - (yoffset - 450) * 0.002f * scaleFactor;
    DrawShape(x, y); // Перерисовываем фигуру с новыми размерами
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
    // Отражение относительно оси OX
    else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        y *= -1;
        DrawShape(x, y);
    }
    // Отражение относительно оси OY
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

// Рисуем координатную плоскость с сеткой
void drawAxesWithGrid()
{
    // Рисуем сетку
    glColor3f(0.5f, 0.5f, 0.5f); // Серый цвет для сетки
    glBegin(GL_LINES);
    // Рисуем горизонтальные линии сетки
    for (float y = -1.0f; y <= 1.0f; y += 0.1f)
    {
        glVertex2f(-1.0f, y);
        glVertex2f(1.0f, y);
    }
    // Рисуем вертикальные линии сетки
    for (float x = -1.0f; x <= 1.0f; x += 0.1f)
    {
        glVertex2f(x, -1.0f);
        glVertex2f(x, 1.0f);
    }
    glEnd();

    // Рисуем оси координат
    glBegin(GL_LINES);
    // Ось X (красный)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    // Ось Y (зеленый)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.0f, -1.0f);
    glVertex2f(0.0f, 1.0f);
    glEnd();
}

int main(void)
{
    setlocale(LC_ALL, "Russian");

    /* Инициализация библиотеки GLFW */
    if (!glfwInit())
        return -1;

    /* Создание окна и его контекста OpenGL */
    GLFWwindow* window = glfwCreateWindow(900, 900, "Tetris", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Установка текущего контекста для окна */
    glfwMakeContextCurrent(window);
    
    // Прокурчивание колеса мыши
    glfwSetScrollCallback(window, scroll_callback);

    // Устанавливаем функцию обратного вызова для нажатия клавиш
    glfwSetKeyCallback(window, keyCallback);

    // Вводим центр фигуры
    //cout << "Введите координаты центра фигуры\n";
    //cin >> x >> y;

    /* Цикл до закрытия окна */
    while (!glfwWindowShouldClose(window))
    {
        /* Отрисовка здесь */
        glClear(GL_COLOR_BUFFER_BIT);

        // Рисуем координатную плоскость с сеткой
        drawAxesWithGrid();

        // Рисуем фигуру
        DrawShape(0, 0);

        /* Переключение переднего и заднего буферов */
        glfwSwapBuffers(window);

        /* Проверка событий и их обработка */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}