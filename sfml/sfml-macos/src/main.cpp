#include <SFML/Graphics.hpp>
#include <iostream>
#include "add.h"
#include <cmath>
#include <vector>

void drawArrow(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end) {
    // смещение нач. и кон. точкек на 20 пикселей (радиус вершин)
    start.x += 20;  
    start.y += 20;   
    end.x += 20;    
    end.y += 20;

    // вычисление направления и длины
    sf::Vector2f direction = end - start;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    float shorten_factor = 0.18f;  // уменьшить длину на n%
    
    // сдвиг нач. и кон. точки на n% от текущего положения
    start += direction * (shorten_factor / 2);
    end -= direction * (shorten_factor / 2);

    // линия
    sf::Vertex line[] = {
        sf::Vertex(start, sf::Color::White),
        sf::Vertex(end, sf::Color::White)
    };
    window.draw(line, 2, sf::Lines);

    // направление стрелки
    direction = end - start;  
    float angle = atan2(direction.y, direction.x);

    // размеры треугольника стрелки
    float arrowSize = 15.f;

    // создание треугольника для стрелки
    sf::ConvexShape arrowHead;
    arrowHead.setPointCount(3);
    arrowHead.setPoint(0, sf::Vector2f(0, 0));
    arrowHead.setPoint(1, sf::Vector2f(-arrowSize, arrowSize / 2));
    arrowHead.setPoint(2, sf::Vector2f(-arrowSize, -arrowSize / 2));
    arrowHead.setFillColor(sf::Color::White);

    // Поворот и позиционирование стрелки
    arrowHead.setRotation(angle * 180 / M_PI);  
    arrowHead.setPosition(end);

    window.draw(arrowHead);  // Отрисовка стрелки
}

int main()
{   
    int x, y; 

    // список ребер
    std::vector<std::vector<int>> edge_list = {
        {1, 5}, {1, 2}, {1, 3}, 
        {2, 1},
        {3, 2}, {3, 1},
        {4, 3}, {4, 5},
        {5, 3}, {5, 4}
    };

    // матрица смежности
    std::vector<std::vector<int>> matrix_adjacency = {
        {0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 1, 0, 1},
        {0, 0, 1, 1, 0}
    };

    // список смежности
    std::vector<std::vector<int>> list_adjacency = {
        {2, 3, 5},
        {1}, 
        {1, 2}, 
        {3, 5}, 
        {3, 4}
    };

    show_graph(edge_list, GraphType::EDGE_LIST);
    show_graph(matrix_adjacency, GraphType::ADJACENCY_MATRIX);
    show_graph(list_adjacency, GraphType::ADJACENCY_LIST);

    sf::RenderWindow window(sf::VideoMode(900, 700), "SFML Application");

    sf::Vector2f center(400, 300);  // центр
    float radius = 200;             // радиус окружности
    int num_vertices = 5;           // количество вершни многоугольника

    // создание круга
    sf::CircleShape shape;
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(2);
    circle.setOutlineColor(sf::Color::White);
    circle.setPosition(center.x - radius, center.y - radius);

    
    // массив для хранения вершин многоугольника
    sf::VertexArray polygon(sf::LinesStrip, num_vertices + 1);

    // массив для хранения маленьких кругов на вершинах
    std::vector<sf::CircleShape> vertex_circles;

    // массив для текста
    std::vector<sf::Text> vertex_labels;  

    // загрузка шрифта Arial 
    sf::Font font;
    if (!font.loadFromFile("/Users/redwolf/Documents/All/BFU/ОП/sfml/sfml-macos/src/arial.ttf")) {  
        std::cerr << "Ошибка загрузки шрифта" << std::endl;
        return -1;
    }

    for (int i = 0; i < num_vertices; i++) {
        float angle = 2 * M_PI * i / num_vertices;  // угол поворота для вершин многоугольника
        float x = center.x + radius * cos(angle);   // x вершины
        float y = center.y + radius * sin(angle);   // y вершины

        int r = 20;

        sf::CircleShape vertexCircle(r);            // радиус для вершин
        vertexCircle.setFillColor(sf::Color::Red);
        vertexCircle.setPosition(x - r, y - r);     // -r для совпадения с центром 

        vertex_circles.push_back(vertexCircle);

        polygon[i] = sf::Vertex(sf::Vector2f(x, y), sf::Color::Green);

        // текст с цифрой для каждой вершины
        sf::Text label;
        label.setFont(font);
        label.setString(std::to_string(i+1));       // цифра вершины
        label.setCharacterSize(25);                 // размер текста
        label.setFillColor(sf::Color::White);       // цвет текста
        label.setPosition(x - 8, y - 16);           // центровка цифр на глаз

        vertex_labels.push_back(label);
    }

    polygon[num_vertices] = polygon[0];  // замыкание пятиугольника
    

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(circle);    // круг
        window.draw(polygon);   // вписанный многоугольник

        // вершины c номерами внутри
        for (int i = 0; i < vertex_circles.size(); ++i) {
            window.draw(vertex_circles[i]);  
            window.draw(vertex_labels[i]);   
        }

        // соединение графа
        for (const auto& edge : edge_list) {
            x = edge[0] - 1;
            y = edge[1] - 1;
            drawArrow(window, vertex_circles[x].getPosition(), vertex_circles[y].getPosition());
        }

        window.display();
    }
}
