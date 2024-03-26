#include <iostream>
#include <cmath>
#include <GLFW/glfw3.h>

using namespace std;

// Объявляем глобальную переменную для хранения угла поворота
float rotationAngle = 0.0f;
float x, y;
float scale = 1.0f;

void rotateClockwise(float& x, float& y, float angle)
{
    float radians = angle * (3.14 / 180.0f); // Переводим угол в радианы
    float newX = x * cos(radians) - y * sin(radians);
    float newY = x * sin(radians) + y * cos(radians);
    x = newX;
    y = newY;
    rotationAngle += angle; // Обновляем значение угла поворота
}

void reflectXEqualsY(float& x, float& y)
{
    float deltaX = x - y;
    x = y + deltaX;
    y = x + deltaX;
}

void DrawShape(float x, float y, float rotationAngle)
{
    // Размеры фигуры
    float size = 0.4f * scale;

    // Переводим угол поворота в радианы
    float radians = rotationAngle * (3.14 / 180.0f);

    // Поворачиваем координаты фигуры
    float rotatedX = x * cos(radians) - y * sin(radians);
    float rotatedY = x * sin(radians) + y * cos(radians);

    // Рисуем фигуру с учетом поворота
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(rotatedX - size, rotatedY);
    glVertex2f(rotatedX, rotatedY + size);

    glVertex2f(rotatedX, rotatedY + size);
    glVertex2f(rotatedX + size, rotatedY);

    // Рисуем ромб
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(rotatedX - size, rotatedY);
    glVertex2f(rotatedX, rotatedY + size);

    glVertex2f(rotatedX, rotatedY + size);
    glVertex2f(rotatedX + size, rotatedY);

    glVertex2f(rotatedX + size, rotatedY);
    glVertex2f(rotatedX, rotatedY - size);

    glVertex2f(rotatedX, rotatedY - size);
    glVertex2f(rotatedX - size, rotatedY);

    // Отрисовка крестовины
    glVertex2f(rotatedX, rotatedY + size);
    glVertex2f(rotatedX, rotatedY - size);

    glVertex2f(rotatedX + size, rotatedY);
    glVertex2f(rotatedX - size, rotatedY);

    // Отрисовка звезды
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
    // Изменяем масштаб фигуры
    float scaleFactor = 1.1f;
    if (yoffset > 0)
        scale *= scaleFactor;
    else
        scale /= scaleFactor;

    DrawShape(x, y, rotationAngle); // Перерисовываем фигуру с новыми размерами
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
    // Отражение относительно оси OX
    else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        y *= -1;
        DrawShape(x, y, rotationAngle);
    }
    // Отражение относительно оси OY
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
    // Добавим обработку клавиш I и O для поворота фигуры
    else if (key == GLFW_KEY_I && action == GLFW_PRESS)
    {
        rotationAngle -= 1.0f; // Поворот против часовой стрелки на 1 градус
        DrawShape(x, y, rotationAngle);
    }
    else if (key == GLFW_KEY_O && action == GLFW_PRESS)
    {
        rotationAngle += 1.0f; // Поворот по часовой стрелке на 1 градус
        DrawShape(x, y, rotationAngle);
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
    cout << "Введите координаты центра фигуры\n";
    cin >> x >> y;

    /* Цикл до закрытия окна */
    while (!glfwWindowShouldClose(window))
    {
        /* Отрисовка здесь */
        glClear(GL_COLOR_BUFFER_BIT);

        // Рисуем координатную плоскость с сеткой
        drawAxesWithGrid();

        // Рисуем фигуру
        DrawShape(x, y, rotationAngle);

        /* Переключение переднего и заднего буферов */
        glfwSwapBuffers(window);

        /* Проверка событий и их обработка */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}