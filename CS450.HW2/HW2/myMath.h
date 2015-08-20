#if !defined(MYMATH_H)

#define PI 3.1415

union v3f
{
    struct
    {
        GLfloat x, y, z;
    };
    struct
    {
        GLfloat r, g, b;
    };
    struct
    {
        GLfloat width, height, length;
    };
    GLfloat pos[3];
};

inline v3f operator+(v3f A, v3f B)
{
    v3f Result;

    Result.x = A.x + B.x;
    Result.y = A.y + B.y;
    Result.z = A.z + B.z;

    return Result;
}

inline v3f & operator+=(v3f &A, v3f B)
{
    A = A + B;
    
    return A;
}

#define MYMATH_H
#endif
