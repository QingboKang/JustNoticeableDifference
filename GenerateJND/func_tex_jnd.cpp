#include "func_tex_jnd.h"

#include <time.h>
time_t t1, t2;


Mat filter2( float fKernel[], Mat matin)
{
    Mat matout = Mat(matin.rows, matin.cols, CV_32FC1);

    Mat kernel = (Mat_<float>(5, 5) << fKernel[0], fKernel[1], fKernel[2], fKernel[3], fKernel[4],
        fKernel[5], fKernel[6], fKernel[7], fKernel[8], fKernel[9],
        fKernel[10], fKernel[11], fKernel[12], fKernel[13], fKernel[14],
        fKernel[15], fKernel[16], fKernel[17], fKernel[18], fKernel[19],
        fKernel[20], fKernel[21], fKernel[22], fKernel[23], fKernel[24] );

    filter2D( matin, matout, -1, kernel, cvPoint(-1, -1), 0, BORDER_CONSTANT); 

    return matout;
}

Mat func_tex_jnd(Mat matin)
{
    // initialize all kernels
    float G1[] = { 0, 0, 0, 0, 0, 
        1./16, 3./16, 8./16, 3./16, 1./16,
        0, 0, 0, 0, 0,
        -1./16, -3./16, -8./16, -3./16, -1./16,
        0, 0, 0, 0, 0 };
    float G2[] = { 0, 0, 0, 0, 0, 
        0, 8./16, 3./16, 0, 0,
        1./16, 3./16, 0, -3./16, -1./16,
        0, 0, -3./16, -8./16, 0,
        0, 0, -1./16, 0, 0 };
    float G3[] = { 0, 0, 1./16, 0, 0, 
        0, 0, 3./16, 8./16, 0,
        -1./16, -3./16, 0, 3./16, 1./16,
        0, -8./16, -3./16, 0, 0,
        0, 0, -1./16, 0, 0 };
    float G4[] = { 0, 1./16, 0, -1./16, 0, 
        0, 3./16, 0, -3./16, 0,
        0, 8./16, 0, -8./16, 0,
        0, 3./16, 0, -3./16, 0,
        0, 1./16, 0, -1./16, 0 };

    // Convert the matin to the 32-floating point Mat
    Mat matin_32F = Mat( matin.rows, matin.cols, CV_32FC1 );
    matin.convertTo(matin_32F, CV_32FC1);

    // filtering
    t1 = clock();
    Mat mat_1 = abs( filter2( G1, matin_32F ) );
    Mat mat_2 = abs( filter2( G2, matin_32F ) );
    Mat mat_3 = abs( filter2( G3, matin_32F ) );
    Mat mat_4 = abs( filter2( G4, matin_32F ) );
    t2 = clock();
    printf("four filter2: %d ms\n", (t2 - t1));

    // mat size
    int iMatCols = matin_32F.cols;
    int iMatRows = matin_32F.rows;

    // find the maximum mat of the four filtering result
    t1 = clock();
    Mat mat_max12 = Mat(iMatRows, iMatCols, CV_32FC1);
    Mat mat_max123 = Mat(iMatRows, iMatCols, CV_32FC1);
    Mat maxgard = Mat(iMatRows, iMatCols, CV_32FC1);
    max( mat_1, mat_2, mat_max12 );
    max( mat_max12, mat_3, mat_max123 );
    max( mat_max123, mat_4, maxgard );

    t2 = clock();
    printf("find maximum: %d ms\n", (t2 - t1));

    Mat mat_bglum = func_bg_lum(matin_32F);
    Mat matout_32F = Mat( iMatRows, iMatCols, CV_32FC1 );

    // constant
    float LANDA = 0.5;

    // fill the data of the output mat
    for(int r = 0; r < iMatRows; r++)
    {
        float* pfbglum = mat_bglum.ptr<float>(r);
        float* pfmaxgrad = maxgard.ptr<float>(r);
        float* pfoutMat = matout_32F.ptr<float>(r);

        for( int c = 0; c < iMatCols; c++ )
        {
            int ibglum = (int)pfbglum[c];
            float falpha = 0.0001 * ibglum + 0.115;
            float fbeta = LANDA - 0.01 * ibglum;
            float fmaxgrad = pfmaxgrad[c];

            float fmatout = fmaxgrad * falpha + fbeta;
            pfoutMat[c] = fmatout;
        }
    }

    // release all mats
    matin_32F.release();
    mat_1.release();
    mat_2.release();
    mat_3.release();
    mat_4.release();

    mat_max12.release();
    mat_max123.release();
    maxgard.release();
    mat_bglum.release();

    return matout_32F;
}
