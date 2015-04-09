
#include "func_bg_lum.h"


Mat func_bg_lum(Mat matin)
{
    // kernel data
    float k[25] = { 1./ 32, 1./ 32, 1./ 32, 1./ 32, 1./ 32, 
        1./ 32, 2./ 32, 2./ 32, 2./ 32, 1./ 32,
        1./ 32, 2./ 32, 0, 2./ 32, 1./ 32,
        1./ 32, 2./ 32, 2./ 32, 2./ 32, 1./ 32,
        1./ 32, 1./ 32, 1./ 32, 1./ 32, 1./ 32 };

    Mat kernel = Mat(5, 5, CV_32FC1, k);

    Mat matout = Mat(matin.rows, matin.cols, CV_32FC1);
    filter2D( matin, matout, -1, kernel, cvPoint(-1, -1), 0, BORDER_CONSTANT); 

    return matout;
}