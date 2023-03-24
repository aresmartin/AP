#include <stdio.h>
#include <stdlib.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>

int main(int argc, char **argv) {

    if (argc != 2) {
        printf("Error: Usage %s image_file_name\n", argv[0]);
        return EXIT_FAILURE;
    }

    //CV_LOAD_IMAGE_COLOR = 1 forces the resultant IplImage to be colour.
    //CV_LOAD_IMAGE_GRAYSCALE = 0 forces a greyscale IplImage.
    //CV_LOAD_IMAGE_UNCHANGED = -1
    IplImage* Img = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);

    // Always check if the program can find the image file
    if (!Img) {
        printf("Error: file %s not found\n", argv[1]);
        return EXIT_FAILURE;
    }

    // a visualization window is created with title: image file name
    cvNamedWindow(argv[1],  CV_WINDOW_AUTOSIZE);
    // Img is shown in 'image' window
    cvShowImage(argv[1], Img);
    cvWaitKey(0);

    // Crea la imagen para la componete azul
    IplImage* ImgInfSup = cvCreateImage(cvSize(Img->width, Img->height), IPL_DEPTH_8U, 3);

    int fila, columna;

    for (fila = 0; fila < Img->height/2; fila++) {

        int mitadImg = (ImgInfSup->height)/2;
        unsigned char *pImg = (unsigned char *) Img->imageData + fila * Img->widthStep;
        unsigned char *pImgInfSup = (unsigned char *) ImgInfSup->imageData  + (fila + mitadImg) * ImgInfSup->widthStep;    

        for (columna = 0; columna < Img->width; columna++) {

            //Imagen BLUE
            *pImgInfSup++ = *pImg++;
            *pImgInfSup++ = *pImg++;
            *pImgInfSup++ = *pImg++;       
        }
    }
    
    for (fila = 0; fila < Img->height/2; fila++) {

        int mitadImg = ImgInfSup->height/2;
        unsigned char *pImg = (unsigned char *) Img->imageData + (fila + mitadImg) * Img->widthStep;
        unsigned char *pImgInfSup = (unsigned char *) ImgInfSup->imageData  + fila  * ImgInfSup->widthStep;    

        for (columna = 0; columna < Img->width; columna++) {

            //Imagen BLUE
            *pImgInfSup++ = *pImg++;
            *pImgInfSup++ = *pImg++;
            *pImgInfSup++ = *pImg++;       
        }
    }
    
    

    // crea y muestras las ventanas con las im genes
    cvNamedWindow("Imagen Superior Inferior", CV_WINDOW_AUTOSIZE);
    cvShowImage("Imagen Superior Inferior", ImgInfSup);

    cvWaitKey(0);

    // memory release for images before exiting the application
    cvReleaseImage(&Img);
    cvReleaseImage(&ImgInfSup);

    // Self-explanatory
    cvDestroyWindow(argv[1]);
    cvDestroyWindow("Imagen Superior Inferior");

    return EXIT_SUCCESS;
}