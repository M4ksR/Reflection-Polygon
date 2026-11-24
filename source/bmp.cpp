#include <cmath>

#include "bmp.hpp"

// Функция установки цвета пикселя
void setPixel(std::vector<std::vector<RGB>>& Image, int x, int y, RGB color) {
    if (0 <= y && y < Image.size() && 0 <= x && x < Image[0].size()) {
        Image[y][x] = color;
    }
}

// Функция отрисовки линии алгоритмом Брезенхема
void drawLine(std::vector<std::vector<RGB>>& Image, PixelPoint start, PixelPoint end, RGB color) {
    // Закрасим стартовую вершину а так же рассчитаем константы dx и dy
    setPixel(Image, start.x, start.y, color);
    int dx = std::abs(end.x - start.x);
    int dy = std::abs(end.y - start.y);
    
    // Определимся с направлением движения по X и по Y
    // -1 - справа налево
    // 0 - прямая
    // 1 - слева направо
    int sx = 0;
    if (end.x > start.x) sx = 1;
    else if (end.x < start.x) sx = -1;
    
    int sy = 0;
    if (end.y > start.y) sy = 1;
    else if (end.y < start.y) sy = -1;

    // Определяем какое Δ брать за 1 и далее действуем по алгоритму
    if (dx > dy) {
        int pk = 2 * dy - dx;
        int xk = start.x;
        int yk = start.y;

        for (int k = 0; k < dx; ++k) {
            if (pk < 0) {
                setPixel(Image, xk + sx, yk, color);
                pk += 2*dy;
                xk += sx;
            }
            else {
                setPixel(Image, xk + sx, yk + sy, color);
                pk += 2*dy - 2*dx;
                xk += sx;
                yk += sy;
            }
        }
    }
    else {
        int pk = 2 * dx - dy;
        int xk = start.x;
        int yk = start.y;

        for (int k = 0; k < dy; ++k) {
            if (pk < 0) {
                setPixel(Image, xk, yk + sy, color);
                pk += 2*dx;
                yk += sy;
            }
            else {
                setPixel(Image, xk + sx, yk + sy, color);
                pk += 2*dx - 2*dy;
                xk += sx;
                yk += sy;
            }
        }
    }
}

// Функция отрисовки многоугольника
void drawPolygon(std::vector<std::vector<RGB>>& Image,
                const std::vector<PixelPoint>& points, 
                RGB color) {
    // Берем пару соседних точек и соединяем их с помощью
    // функции drawLine (учитывая отрезок последняя_вершина - первая_вершина)
    for (int i1 = 0; i1 < points.size(); ++i1) {
        int i2 = (i1 + 1) % points.size();
        drawLine(Image, points[i1], points[i2], color);
    }
}

// Функция перевода 2D координат в координаты пикселей на экране
PixelPoint toScreen(const Point2D& point, const ClipRect& rect, int width, int height) {
    double x = std::lround((point.x - rect.xmin) * (width - 1) / (rect.xmax - rect.xmin));
    double y = std::lround((rect.ymax - point.y) * (height - 1) / (rect.ymax - rect.ymin));
    return {static_cast<int>(x), static_cast<int>(y)};
}

// Функция подсчета Little-Endian
void writeLittleEndian(std::ofstream& file, uint32_t value, int byteCount) {
    // Учитывая что в Little-Endian число записывается от меньшего разряда
    // к большему то будем сначала получать отдельные байты через &
    // а затем выполнять побитовый сдвиг для среза числа 
    for (int i = 0; i < byteCount; ++i) {
        uint8_t byte = value & 0xFF;
        value >>= 8;
        file.put(byte);
    }
}

// Функция сохранения пикселей в BMP файл
void saveBMP(const std::vector<std::vector<RGB>>& Image, const std::string& filename) {
    // Откроем выходной файл
    std::ofstream file(filename, std::ios::binary);
    if (!file) { return; }

    // Рассчитаем ширину и высоту
    int WIDTH = Image[0].size();
    int HEIGHT = Image.size();

    // Так же заранее определимся со следующими величинами
    int padding = (4 - (WIDTH * 3) % 4) % 4;
    int rowSize = WIDTH * 3 + padding;
    int pixelDataSize = rowSize * HEIGHT;
    int fileSize = 14 + 40 + pixelDataSize;

    // Запишем сигнатуру BMP файла
    file.put('B');
    file.put('M');

    // Запишем BITMAPFILEHEADER
    writeLittleEndian(file, fileSize, 4);
    writeLittleEndian(file, 0, 2);
    writeLittleEndian(file, 0, 2);
    writeLittleEndian(file, 54, 4);
    
    // Запишем BITMAPINFOHEADER
    writeLittleEndian(file, 40, 4);
    writeLittleEndian(file, WIDTH, 4);
    writeLittleEndian(file, HEIGHT, 4);
    writeLittleEndian(file, 1, 2);
    writeLittleEndian(file, 24, 2);
    writeLittleEndian(file, 0, 4);
    writeLittleEndian(file, pixelDataSize, 4);
    writeLittleEndian(file, 0, 4);
    writeLittleEndian(file, 0, 4);
    writeLittleEndian(file, 0, 4);
    writeLittleEndian(file, 0, 4);
    
    // Запишем пиксели проходясь по строкам внизу вверх
    for (int y = HEIGHT - 1; y >= 0; --y) {
        for (int x = 0; x < WIDTH; ++x) {
            file.put(Image[y][x].blue);
            file.put(Image[y][x].green);
            file.put(Image[y][x].red);
        }
        // Учтем padding
        for (int i = 0; i < padding; ++i) { file.put(0); }
    }
    file.close();
}
