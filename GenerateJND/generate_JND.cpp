#include "generate_JND.h"

Mat GenerateJND(Mat matin)
{
    // lum_jnd mat
    Mat matlumjnd = func_lum_jnd(matin);

    // tex_jnd mat
    Mat mattexjnd = func_tex_jnd(matin);

    // output JND mat  in the range (0, 1)
    Mat matJND = Mat( matin.rows, matin.cols, CV_32FC1);

    for(int r = 0; r < matin.rows; r++)
    {
        float* pfMatlumjnd = matlumjnd.ptr<float>(r);
        float* pfMattexjnd = mattexjnd.ptr<float>(r);
        float* pfMatJND = matJND.ptr<float>(r);

        for( int c = 0; c < matin.cols; c++ )
        {
            float flumjnd = pfMatlumjnd[c];
            float ftexjnd = pfMattexjnd[c];

            float fJND = 2 * (ftexjnd + 3) + flumjnd;
            pfMatJND[c] = fJND;
        }
    }

    // normalize the JND mat [0.0, 1.0]
    normalize(matJND, matJND, 1.0, 0.0, NORM_MINMAX);

    matlumjnd.release();
    mattexjnd.release();

    return matJND;
// 
//     for(int r = 0; r < matJND.rows; r++)
//     {
//         float* pfMatJND = matJND.ptr<float>(r);
// 
//         for( int c = 0; c < matJND.cols; c++ )
//         {
//             float fTemp = pfMatJND[c];
//             int k;
//         }
//     }
// 
}