#include "generate_JND.h"

// Convert JND mat(CV_32FC1) to image(CV_8UC1) and save this image
int convertJND2Img( Mat matJND, char* strFilePath )
{
    Mat matJNDImage( matJND.rows, matJND.cols, CV_8UC1 );

    for(int r = 0; r < matJND.rows; r++)
    {
        float* pfMatJND = matJND.ptr<float>(r);
        uchar* pucMatJNDImage = matJNDImage.ptr<uchar>(r);

        for( int c = 0; c < matJND.cols; c++ )
        {
            float fTemp = pfMatJND[c];
            
            int iTemp = fTemp * 255;

            pucMatJNDImage[c] = iTemp;
        }
    }

    imwrite( strFilePath, matJNDImage);

    matJNDImage.release();

    return 0;
}

int main()
{
    Mat matin = imread("y.png", CV_LOAD_IMAGE_GRAYSCALE);

    Mat matJND;
 //   for( int i = 0; i < 1000; i++ )
  //  {
        matJND = GenerateJND(matin);

 //   }
    
    
    convertJND2Img( matJND, "y_jnd.png" );
   

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

    waitKey(0);

    return 0;
}