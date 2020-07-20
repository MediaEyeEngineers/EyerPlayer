#ifndef	EYER_LIB_MATH_H
#define	EYER_LIB_MATH_H

namespace Eyer {

    class EyerRand
    {
    public:
        int static Rand(int x);
    };

    class EyerMat;
    class EyerMat4x1;
    class EyerMat3x1;
    class EyerMat2x1;
    class EyerMat4x4;

    typedef EyerMat4x1 EyerVec4;
    typedef EyerMat3x1 EyerVec3;
    typedef EyerMat2x1 EyerVec2;

    class EyerMat
    {
    public:
        int row = 0;
        int col = 0;
        float * * mat = nullptr;

    private:
        void init(int row, int col);
        void output();

    public:
        EyerMat(int row = 0, int col = 0);
        EyerMat(const EyerMat &m);

        ~EyerMat();

        EyerMat & operator = (const EyerMat &m);
        EyerMat operator * (const EyerMat &m);
        EyerMat operator * (const float a);
        EyerMat operator + (const EyerMat &m);
        EyerMat operator - (const EyerMat &m);

        /**
         * 矩阵转置
         * @return
         */
        EyerMat operator ~ ();

        /**
         * 矩阵求逆
         * @return
         */
        // SvMat operator ! ();
        int Print();

        /**
         * 当你想要从 Mat 中拷贝出矩阵的 float 数组的时候，你应该先后调用 GetMatLen() 和 GetMat(),GetMatLen() 将告诉你你需要多大的空间来存放这个数组
         * @return 你需要的空间大小
         */
        int GetMatLen();

        /**
         * GetMat 将把数组拷贝到你分配的空间内，当 matBuffer == NULL 的时候，函数将内部 malloc 一个空间，但是这样外部其实无法知道数组的长度。
         * @param matBuffer 你想要拷贝的地方
         * @return 返回数组
         */ 
        float * GetMat(float * matBuffer = nullptr);
    };

    class EyerMat4x4 : public EyerMat
    {
    public:
        EyerMat4x4();
        ~EyerMat4x4();

        EyerMat4x4(const EyerMat & mat);

        EyerMat4x4 & operator = (const EyerMat &m);

        int SetScale(float x, float y, float z);
        int SetTrans(float x, float y, float z);
        int SetPerspective(float fov, float aspect, float near, float far);
        int SetOrtho(float l, float r, float t, float b, float near, float far);

        int SetRotate(float x, float y, float z, float a);

        int SetRotateX(float a);
        int SetRotateY(float a);
        int SetRotateZ(float a);
    };


    class EyerMat4x1 : public EyerMat
    {
    public:
        EyerMat4x1();
        ~EyerMat4x1();

        EyerMat4x1(float x, float y, float z, float w);

        float x();
        float y();
        float z();
        float w();

        int SetX(float x);
        int SetY(float y);
        int SetZ(float z);
        int SetW(float w);

        float x1();
        float y1();
        float x2();
        float y2();

        int SetXY1(float x, float y);
        int SetXY2(float x, float y);

        float Norm();
    };

    class EyerMat3x1 : public EyerMat
    {
    public:
        EyerMat3x1();
        ~EyerMat3x1();

        float x();
        float y();
        float z();

        int SetX(float x);
        int SetY(float y);
        int SetZ(float z);

        float Norm();
    };

    class EyerMat2x1 : public EyerMat
    {
    public:
        EyerMat2x1(float x, float y);
        EyerMat2x1();

        EyerMat2x1(const EyerMat & m);

        ~EyerMat2x1();

        float x();
        float y();

        int SetX(float x);
        int SetY(float y);

        float Norm();
    };
}

#endif