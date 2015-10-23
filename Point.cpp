//
// Created by Nick on 9/20/2015.
//
#include "Point.h"
#include <cmath>
#include "assert.h"
#include <stdlib.h>

using namespace std;

namespace Clustering {
            //Constructors
    Point::Point(int d) {
        if (d == 0)
            dim = 2;
        else
            dim = d;
        values = new double[dim];
        for (int n = 0; n < dim; n++)
            setValue(n+1, 0);
    }
    Point::Point(int d, double *points) {

        if (d == 0)
            dim = 2;
        dim = d;
        values = new double[dim];
        for(int n = 0; n < dim; n++)
            setValue(n+1, *(points+n));

    }

        //Big3
    Point::Point(const Point &p)
        {
            dim = p.getDims();
            for (int n = 0; n < dim; n++)
                setValue(n+1, p.getValue(n+1));
    }
    Point &Point::operator=(const Point &rhs) {
        assert(dim == rhs.getDims());
        bool equal = true;
        for (int n = 0; n < rhs.getDims(); n++)
            if (getValue(n+1) != rhs.getValue(n+1))
                equal = false;
        if (equal)
            return *this;
        else {
            for (int n = 0; n < dim; n++)
                values[n] = rhs.values[n];
        }
        return *this;
    }
    Point::~Point() {
        if(values != nullptr)
            delete[] values;
    }

    //Accessors/Mutators
    void Point::setValue(int d, double v) {
        values[d-1] = v;
    }

    double Point::getValue(int d) const {
        return values[d - 1];
    }

    //Functions
    double Point::distanceTo(const Point &p) const {
        int size = p.getDims();
        int sum;

        for (int n = 0; n < size; n++) {
            double diff = values[n] - p.values[n];
            sum += diff * diff;
        }
        return sqrt(sum);
    }
    //Operators
    const Point Point:: operator/(double i) const
    {
        Point temp(dim);
        assert(i > 0);
        for(int n =0; n < dim; n++)
            temp.setValue(n+1,(values[n]/i));
        return temp;
    }
    const Point Point:: operator *(double i) const
    {
        Point temp(dim);

        for(int n =0; n < dim; n++)
            temp.setValue(n+1, (values[n]*i));
        return temp;
    }
    Point &Point:: operator /=(double i)
    {
        assert(i > 0);
        for(int n =0; n < dim; n++)
            values[n] = values[n]/i;
        return *this;
    }
    Point &Point:: operator *=(double i)
    {
        for(int n =0; n < dim; n++)
            values[n] = values[n]*i;
        return *this;
    }
    //Friend Operators
    const Point operator+(const Point & lhs, const Point &rhs)
    {
        Point temp(rhs.getDims());
        assert(rhs.getDims() == rhs.getDims());
        for(int n =0; n < rhs.getDims(); n++)
            temp.setValue(n+1,(lhs.getValue(n+1)+rhs.getValue(n+1)));
        return temp;
    }
    const Point operator-(const Point & lhs, const Point &rhs)
    {
        Point temp(rhs.getDims());
        assert(rhs.getDims() == rhs.getDims());
        for(int n =0; n < rhs.getDims(); n++)
            temp.setValue(n+1,(lhs.getValue(n+1)-rhs.getValue(n+1)));
        return temp;
    }
    Point &operator+=(Point & rhs, const Point &lhs)
    {
        rhs = rhs +lhs;
        return rhs;
    }
    Point &operator-=(Point & rhs, const Point &lhs)
    {
        rhs = rhs -lhs;
        return rhs;
    }

    bool operator==(const Point &lhs, const Point &rhs) {
        if (lhs.getDims() != rhs.getDims()) {
            return false;
        }
        for (int n = 0; n < lhs.getDims(); n++) {
            if (lhs.getValue(n+1) != rhs.getValue(n+1)) {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const Point &lhs, const Point &rhs) {
        if(!(lhs == rhs))
            return true;
        return false;
    }
    bool operator <(const Point &lhs, const Point &rhs)
    {
        assert(lhs.getDims() == rhs.getDims());
        if(lhs == rhs)
            return false;

        for(int n = 0; n < rhs.getDims();)
        {
            if(lhs.getValue(n) > rhs.getValue(n))
                return false;
            if(lhs.getValue(n) == rhs.getValue(n)) {
                n++;
            }
            if(lhs.getValue(n) < rhs.getValue(n))
                return true;

        }

    }
    bool operator <=(const Point &lhs, const Point &rhs)
    {
        assert(lhs.getDims() == rhs.getDims());
        if(lhs == rhs)
            return true;

        for(int n = 0; n < rhs.getDims();)
        {
            if(lhs.getValue(n) > rhs.getValue(n))
                return false;
            if(lhs.getValue(n) == rhs.getValue(n))
                n++;
            if(lhs.getValue(n) < rhs.getValue(n))
                return true;
        }
    }
    bool operator >(const Point &lhs, const Point &rhs)
    {
        assert(lhs.getDims() == rhs.getDims());
        if(!(lhs <= rhs))
            return true;
        return false;

    }
    bool operator >=(const Point &lhs, const Point &rhs)
    {
        if(lhs == rhs)
            return true;
        assert(lhs.getDims() == rhs.getDims());
        if(!(lhs < rhs))
            return true;
        return false;

    }

    std::ostream &operator<<(std::ostream &os, const Point &p) {
        for (int n = 0; n < p.getDims(); n++)
            if (n != p.getDims() - 1)
                os << p.getValue(n+1) << ",";
            else
                os << p.getValue(n+1);
        return os;
    }
    std::istream &operator>>(std::istream &is, Point &p)
    {
        string value;
        double dval;
        while(!is.eof()) {
            for (int n = 0; n < p.getDims(); n++)
            {
                getline(is,value,',');
                dval = atof(value.c_str());
                p.setValue(n+1, dval);
            }
        }
        return is;
    }
}
