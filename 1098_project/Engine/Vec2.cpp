#include "Vec2.h"


bool Math::vec2::operator==(const vec2& v)
{
    return { (x == v.x) && (y == v.y) };
}

bool Math::vec2::operator!=(const vec2& v)
{
    return !operator==(v);
}

Math::vec2 Math::vec2::operator+(const vec2& v) {
    return { x + v.x, y + v.y };
}

Math::vec2 Math::vec2::operator+(const vec2& v) const
{
    return { x + v.x, y + v.y };
}

Math::vec2& Math::vec2::operator+=(const vec2& v) {
    x += v.x;
    y += v.y;
    return *this;
}

Math::vec2& Math::vec2::operator+=(const ivec2& v)
{
    x += double(v.x);
    y += double(v.y);
    return *this;
}

Math::vec2 Math::vec2::operator-(const vec2& v)
{
    return { x - v.x, y - v.y };
}

Math::vec2 Math::vec2::operator-(const vec2& v) const
{
    return { x - v.x, y - v.y };
}

Math::vec2& Math::vec2::operator-=(const vec2& v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

Math::vec2& Math::vec2::operator-=(const ivec2& v)
{
    x -= double(v.x);
    y -= double(v.y);
    return *this;
}

Math::vec2 Math::vec2::operator*(double scale)
{
    return { x * scale, y * scale };
}

Math::vec2 Math::vec2::operator*(double scale) const
{
    return { x * scale, y * scale };
}

Math::vec2& Math::vec2::operator*=(double scale)
{
    x *= scale;
    y *= scale;
    return *this;
}

Math::vec2& Math::vec2::operator*=(const ivec2& v)
{
    x *= double(v.x);
    y *= double(v.y);
    return *this;
}



Math::vec2 Math::vec2::operator/(double divisor)
{
    return { x / divisor, y / divisor };
}

Math::vec2 Math::vec2::operator/(double divisor) const
{
    return { x / divisor, y / divisor };
}

Math::vec2& Math::vec2::operator/=(double divisor)
{
    x /= divisor;
    y /= divisor;
    return *this;
}

Math::vec2& Math::vec2::operator/=(const ivec2& v)
{
    x /= double(v.x);
    y /= double(v.y);
    return *this;
}

bool Math::operator==(const vec2& lv, const vec2& rv)
{
    return { (lv.x == rv.x) && (lv.y == rv.y) };
}

bool Math::operator!=(const vec2& lv, const vec2& rv)
{
    return !operator==(lv,rv);
}

Math::vec2 Math::operator*(double scale, const vec2& v)
{
    return { scale * v.x ,scale * v.y };
}

/*======================================================*/

bool Math::ivec2::operator==(const ivec2& v)
{
    return { (x == v.x) && (y == v.y) };
}

bool Math::ivec2::operator!=(const ivec2& v)
{
    return !operator==(v);
}

Math::ivec2 Math::ivec2::operator+(const ivec2& v) {
    return { x + v.x, y + v.y };
}

Math::ivec2 Math::ivec2::operator+(const ivec2& v) const
{
    return { x + v.x, y + v.y };
}

Math::ivec2& Math::ivec2::operator+=(const ivec2& v) {
    x += v.x;
    y += v.y;
    return *this;
}


Math::ivec2 Math::ivec2::operator-(const ivec2& v)
{
    return { x - v.x, y - v.y };
}

Math::ivec2 Math::ivec2::operator-(const ivec2& v) const
{
    return { x - v.x, y - v.y };
}

Math::ivec2& Math::ivec2::operator-=(const ivec2& v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}



Math::ivec2 Math::ivec2::operator*(int scale)
{
    return { x * scale, y * scale };
}

Math::ivec2 Math::ivec2::operator*(int scale) const
{
    return { x * scale, y * scale };
}

Math::ivec2& Math::ivec2::operator*=(int scale)
{
    x *= scale;
    y *= scale;
    return *this;
}


Math::ivec2 Math::ivec2::operator/(int divisor)
{
    return { x / divisor, y / divisor };
}

Math::ivec2 Math::ivec2::operator/(int divisor) const
{
    return { x / divisor, y / divisor };
}

Math::ivec2& Math::ivec2::operator/=(int divisor)
{
    x /= divisor;
    y /= divisor;
    return *this;
}


Math::vec2 Math::ivec2::operator*(double scale)
{
    return { x * scale, y * scale };
}

Math::vec2 Math::ivec2::operator*(double scale) const
{
    return { x * scale, y * scale };
}

Math::vec2 Math::ivec2::operator/(double divisor)
{
    return { x / divisor, y / divisor };
}

Math::vec2 Math::ivec2::operator/(double divisor) const
{
    return { x / divisor, y / divisor };
}

bool Math::operator==(const ivec2& lv, const ivec2& rv)
{
    return { (lv.x == rv.x) && (lv.y == rv.y) };
}

bool Math::operator!=(const ivec2& lv, const ivec2& rv)
{
    return !operator==(lv,rv);
}

Math::ivec2 Math::operator*(int scale, const ivec2& v)
{
    return { scale * v.x ,scale * v.y };
}

Math::vec2 Math::operator*(double scale, const ivec2& v)
{
    return { scale * v.x ,scale * v.y };
}
