#ifndef RAYTRACEENGINE_H
#define RAYTRACEENGINE_H
#include <iostream>
#include <cmath>
#include <vector>

/*
This class defines the namespace and operator overloading functions for the raytracing object.

*/

namespace raytrace
{
    template <typename T>
    class Vector
    {
    public:
        Vector(T x, T y, T z) : x_pos(x), y_pos(y), z_pos(z) {}
        Vector(T n) : x_pos(n), y_pos(n), z_pos(n) {}
        Vector() : x_pos(0), y_pos(0), z_pos(0) {}
        /*
    -- Getter Functions --
    */

        T get_x() const { return x_pos; }
        T get_y() const { return y_pos; }
        T get_z() const { return z_pos; }

        /*

-- Operator Overloading

    */
        //Scalar multiplication
        Vector<T> operator*(const T& d) const { return Vector<T>(x_pos * d, y_pos * d, z_pos * d); }
        Vector<T> operator*(const Vector<T>& v) const { return Vector<T>(x_pos * v.x_pos, y_pos * v.y_pos, z_pos * v.z_pos); }
        Vector<T> operator/(const T& d) const { return Vector<T>(x_pos / d, y_pos / d, z_pos / d); }
        Vector<T> operator+(const Vector<T>& v) const { return Vector<T>(x_pos + v.x_pos, y_pos + v.y_pos, z_pos + v.z_pos); }
        Vector<T> operator-(const Vector<T>& v) const { return Vector<T>(x_pos - v.x_pos, y_pos - v.y_pos, z_pos - v.z_pos); }
      
        T& operator[](int i) {
            try {
                if (i == 0) return x_pos;
                if (i == 1) return y_pos;
                if (i == 2) return z_pos;
                throw std::out_of_range("Invalid Index");
            }
            catch (const std::out_of_range& e)
            {
                std::cerr << "Caught an out_of_range exception: " << e.what() << '\n';
                }
            // Consider throwing an exception here or handling it however you prefer
        }
        friend inline std::ostream& operator<<(std::ostream& os, Vector<T> a)
        {
            os << a.x_pos << " " << a.y_pos << " " << a.z_pos << std::endl;
            return os;
        }
        friend inline std::istream& operator>>(std::istream& is, Vector<T> a)
        {
            is >> a.x_pos >> a.y_pos >> a.z_pos;
            return is;
        }
        Vector<T>& operator+=(const Vector<T>& v)
        {
            x_pos += v.x_pos;
            y_pos += v.y_pos;
            z_pos += v.z_pos;
            return *this;
        
        }
        /*
----------- FORMULAS ----------------------------

        */
        T dot_product(Vector<T> a)
        {
            return x_pos * a.x_pos + y_pos * a.y_pos + z_pos * a.z_pos;
        }
        Vector<T> cross_product(Vector<T> a) { return Vector<T>((y_pos * a.z_pos - z_pos * a.y_pos), (z_pos * a.x_pos - x_pos * a.z_pos), (x_pos * a.y_pos - y_pos * a.x_pos)); }
        //2X2 Matrix
        T magnitude() const
        {
            return sqrt(x_pos * x_pos + y_pos * y_pos + z_pos * z_pos);
        }
        Vector<T>& normalize()
        {
            T inverse = 1 / magnitude();
            x_pos *= inverse;
            y_pos *= inverse;
            z_pos *= inverse;
            return *this;
        }
        inline Vector<T> unit_vector()
        {
            T d = this->magnitude();
            return *this / d;
        }

        //Taking dot-product of the vector itself to get squared length
        T squared_length() const
        {
            return x_pos * x_pos + y_pos * y_pos + z_pos * z_pos;
        }
    private:
        T x_pos,
            y_pos,
            z_pos;
    };
} // namespace raytrace

//Typedefs
typedef raytrace::Vector<float> vecfloat;
typedef raytrace::Vector<int> vecint;
typedef raytrace::Vector<double> vecdouble;

#endif