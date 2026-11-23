#pragma once

#include <cstdint>
#include <fstream>
#include <vector>

#include "clipping.hpp"
#include "structs.hpp"

void setPixel(std::vector<std::vector<RGB>>& Image, int x, int y, RGB color);

void drawLine(std::vector<std::vector<RGB>>& Image, PixelPoint start, PixelPoint end, RGB color);

void drawPolygon(std::vector<std::vector<RGB>>& Image,
                std::vector<PixelPoint>& points, 
                RGB color);             

PixelPoint toScreen(const Point2D& point, const ClipRect& rect, int width, int height);

void writeLittleEndian(std::ofstream& file, uint32_t value, int byteCount);

void saveBMP(const std::vector<std::vector<RGB>>& Image, const std::string& filename);
