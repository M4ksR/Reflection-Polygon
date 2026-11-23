#include "clipping.hpp"

bool isInside(const Point2D& point, const ClipRect& rect, ClipEdge edge) {
    switch (edge) {
        case ClipEdge::Left: 
            return point.x >= rect.xmin;

        case ClipEdge::Right: 
            return point.x <= rect.xmax;

        case ClipEdge::Bottom: 
            return point.y >= rect.ymin;

        case ClipEdge::Top: 
            return point.y <= rect.ymax;
    }
}

Point2D findIntersection(const Point2D& p1, const Point2D& p2, const ClipRect& rect, ClipEdge edge) {
    double x;
    double y;
    double t;
    
    switch (edge) {
        case ClipEdge::Left:
            t = (rect.xmin - p1.x) / (p2.x - p1.x);
            y = p1.y + t * (p2.y - p1.y);
            return {rect.xmin, y};

        case ClipEdge::Right:
            t = (rect.xmax - p1.x) / (p2.x - p1.x);
            y = p1.y + t * (p2.y - p1.y);
            return {rect.xmax, y};

        case ClipEdge::Bottom:
            t = (rect.ymin - p1.y) / (p2.y - p1.y);
            x = p1.x + t * (p2.x - p1.x);
            return {x, rect.ymin};

        case ClipEdge::Top:
            t = (rect.ymax - p1.y) / (p2.y - p1.y);
            x = p1.x + t * (p2.x - p1.x);
            return {x, rect.ymax};
    }
}

std::vector<Point2D> clipPolygon(const std::vector<Point2D>& polygon, const ClipRect& rect) {
    std::vector<Point2D> result = polygon;
    std::vector<ClipEdge> edges = {ClipEdge::Left, ClipEdge::Right, ClipEdge::Bottom, ClipEdge::Top};
    
    for (const auto& edge : edges) {
        std::vector<Point2D> input = result;
        result.clear();

        if (input.empty()) {
            return result;
        }
        
        Point2D prev = input[input.size() - 1];
        
        for (const auto& curr : input) {
            bool prevInside = isInside(prev, rect, edge);
            bool currInside = isInside(curr, rect, edge);

            if (prevInside && currInside) {
                result.push_back(curr);
            }
            else if (prevInside) {
                Point2D intersection = findIntersection(prev, curr, rect, edge);
                result.push_back(intersection);
            }
            else if (currInside) {
                Point2D intersection = findIntersection(prev, curr, rect, edge);
                result.push_back(intersection);
                result.push_back(curr);
            }

            prev = curr;
        }
    }

    return result;
}
