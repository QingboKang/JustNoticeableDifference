#include "func_lum_jnd.h"

double* lum_jnd( int iT0, float fGamma )
{
    double* pdBg_jnd = (double*)malloc( sizeof(double) * 256 );

    for(int k = 0; k < 256; k++)
    {
        int lum = k - 1;
        if( lum < 127)
        {
            pdBg_jnd[k] = iT0 * (1- sqrt( (float)(lum + 1)/127)) + 3;
        }
        else
        {
            pdBg_jnd[k] = fGamma * (lum - 126) + 3;
        }
    }

    return pdBg_jnd;
}

Mat func_lum_jnd( Mat matin )
{
    // Convert the matin to the 32-floating point Mat
    Mat matin_32F = Mat( matin.rows, matin.cols, CV_32FC1 );
    matin.convertTo(matin_32F, CV_32FC1);

    // mat size
    int iMatCols = matin_32F.cols;
    int iMatRows = matin_32F.rows;

    // Get the average background luminance of the image
    Mat mat_bglum = func_bg_lum(matin_32F);

    double * pdbg_jnd = lum_jnd( 17, 3./128 );

    // output mat
    Mat matout = Mat(iMatRows, iMatCols, CV_32FC1);

    for(int r = 0; r < iMatRows; r++)
    {
        float* pfMatbglum = mat_bglum.ptr<float>(r);
        float* pfMatout = matout.ptr<float>(r);

        for( int c = 0; c < iMatCols; c++ )
        {
            float fbg_lum = pfMatbglum[c];
            pfMatout[c] = pdbg_jnd[(int) (fbg_lum ) ];
        }
    }

    // release all mats
    matin_32F.release();
    mat_bglum.release();
    free(pdbg_jnd);

    return matout;
}