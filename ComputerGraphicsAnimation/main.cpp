#include <iostream>
#include <GLFW/glfw3.h>

using namespace std;

float x, y;
float rotationAngle = 0.0;

void DrawShape(float x, float y)
{
    // Рисуем фигуру с учетом масштаба и поворота
    glPushMatrix();
    glTranslatef(x, y, 0.0f); // Перемещение в указанную точку
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f); // Поворот относительно оси Z

    // Рисуем ромб
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

    // Отрсиовка крестовины
    glVertex2f(x, y + 0.5);
    glVertex2f(x, y - 0.5);

    glVertex2f(x + 0.5, y);
    glVertex2f(x - 0.5, y);

    // Отрисовка звезды
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
//    // Изменяем масштаб фигуры
//    if (yoffset > 0)
//        scale += 0.1f; // Увеличиваем масштаб на 0.1 при прокручивании вверх
//    else
//        scale -= 0.1f; // Уменьшаем масштаб на 0.1 при прокручивании вниз
//
//    // Масштаб не может быть меньше 0.1
//    if (scale < 0.1f)
//        scale = 0.1f;
//
//    // Перерисовываем окно
//    glfwPostEmptyEvent();
//}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        y += 0.1f; // Учитываем текущий масштаб при изменении координат
    }
    else if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        x += 0.1f; // Учитываем текущий масштаб при изменении координат
    }
    else if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        y -= 0.1f; // Учитываем текущий масштаб при изменении координат
    }
    else if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        x -= 0.1f; // Учитываем текущий масштаб при изменении координат
    }
    else if (key == GLFW_KEY_U && action == GLFW_PRESS)
    {
        rotationAngle += 5.0f; // Поворот против часовой стрелки на 5 градусов
    }
    else if (key == GLFW_KEY_I && action == GLFW_PRESS)
    {
        rotationAngle -= 5.0f; // Поворот по часовой стрелке на 5 градусов
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
    GLFWwindow* window = glfwCreateWindow(900, 900, "Grafic", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Установка текущего контекста для окна */
    glfwMakeContextCurrent(window);

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

        // Сохраняем текущую матрицу
        glPushMatrix();

        // Масштабируем фигуру
        //glScalef(scale, scale, 1.0f);

        // Перемещаем фигуру
        glTranslatef(x, y, 0.0f);

        // Рисуем фигуру с учетом сдвига и масштаба
        DrawShape(x, y);

        // Восстанавливаем предыдущую матрицу
        glPopMatrix();

        /* Переключение переднего и заднего буферов */
        glfwSwapBuffers(window);

        /* Проверка событий и их обработка */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}