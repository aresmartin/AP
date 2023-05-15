#include <stdio.h>
#include <stdlib.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>
    
int main(int argc, char **argv) {
    
    //invertirHorizontal(argc, argv);
    
        if (argc != 2) {
      printf("Error: Usage %s image_file_name\n", argv[0]);
      return EXIT_FAILURE;
    }

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
    
    IplImage* ImgDestino = cvCreateImage(cvSize(Img->width * 2, Img->height * 2), IPL_DEPTH_8U, 3);

    int fila, colum, i;
    int value = 0;
    int value2 = 0;
    int control = 0;
    int control2 = 0;
    
    //mostramos imagen orgininal en esquina izda. arriba
    for(fila = 0; fila < ImgDestino->height/2; fila ++){
        unsigned char * pImgOrigen = (unsigned char *) Img->imageData + (fila * Img->widthStep);
        unsigned char * pImgDestino = (unsigned char *) ImgDestino->imageData + (fila * ImgDestino->widthStep);
        
        for(colum = 0; colum < ImgDestino->widthStep/2; colum++){
            *pImgDestino++ = *pImgOrigen++;
            
        }
    }
    
    //mostramos imagen original en esquina derecha arriba (primera mitad arriba rojo)
    for(fila =  0; fila < ImgDestino->height/2; fila++){
        unsigned char * pImgOrigen = (unsigned char *) Img->imageData + (fila * Img->widthStep);
        unsigned char * pImgDestino = (unsigned char *) ImgDestino->imageData + ((fila * ImgDestino->widthStep) + ImgDestino->widthStep/2);    
       /* if(fila == Img->height/2){
            break;
        }*/  
        for(colum = ImgDestino->width/2; colum < ImgDestino->width; colum++){
            
            //azul
            *pImgDestino = 0;
            pImgDestino++;
            pImgOrigen++;
            //verde
            *pImgDestino = 0;
            pImgDestino++;
            pImgOrigen++;
            //rojo
            *pImgDestino = *pImgOrigen;
            pImgDestino++;
            pImgOrigen++;
            
        }
    }
                    //segunda mitad abajo azul
    for(fila =  0; fila < ImgDestino->height/2; fila++){
        unsigned char * pImgOrigen = (unsigned char *) Img->imageData + ((Img->height/2 + fila) * Img->widthStep);
        unsigned char * pImgDestino = (unsigned char *) ImgDestino->imageData + (((ImgDestino->height/4 + fila) * ImgDestino->widthStep) + ImgDestino->widthStep/2);    
        /*if(fila == Img->height){
            break;
        }*/
        for(colum = ImgDestino->width/2; colum < ImgDestino->width; colum++){
             //azul
            *pImgDestino = *pImgOrigen;
            pImgDestino++;
            pImgOrigen++;
            
            //verde
            *pImgDestino = 0;
            pImgDestino++;
            pImgOrigen++;
            //rojo
            *pImgDestino = 0;
            pImgDestino++;
            pImgOrigen++;
        }
    }
    
    //mostramos imagen original en esquina derecha abajo (parte de la derecha la colocamos en la izquierda)
    for(fila = ImgDestino->height/2; fila < ImgDestino->height; fila++){
        unsigned char * pImgOrigen = (unsigned char *) Img->imageData + ((value * Img->widthStep) + Img->widthStep/2);
        unsigned char * pImgDestino = (unsigned char *) ImgDestino->imageData + ((fila * ImgDestino->widthStep) + ImgDestino->widthStep/2);
        value++;
        for(colum = 0; colum < Img->widthStep/2; colum++){
            *pImgDestino++ = *pImgOrigen++;
        }
        
    }
    
               //parte de la izquierda la colocamos en la derecha
    for(fila = ImgDestino->height/2; fila < ImgDestino->height; fila++){
        unsigned char * pImgOrigen = (unsigned char *) Img->imageData + (control2 * Img->widthStep);
        unsigned char * pImgDestino = (unsigned char *) ImgDestino->imageData + ((fila * ImgDestino->widthStep) + ((ImgDestino->widthStep/2) + (Img->widthStep/2)));
        control2++;
        for(colum = Img->widthStep/2; colum < Img->widthStep; colum++){
            *pImgDestino++ = *pImgOrigen++;
        }
        
    }
    
    //value2 = Img->height;
    //mostramos imagen original en esquina izquierda abajo
    for(fila = ImgDestino->height/2; fila < ImgDestino->height; fila++){
        unsigned char * pImgOrigen = (unsigned char *) Img->imageData + (((Img->height - value2) * Img->widthStep)+ Img->widthStep -1);
        unsigned char * pImgDestino = (unsigned char *) ImgDestino->imageData + (fila * ImgDestino->widthStep);
        value2++;
        for(colum = 0; colum < ImgDestino->width/2; colum++){
            unsigned char rojo = *pImgOrigen--;
            unsigned char verde = *pImgOrigen--;
            unsigned char azul = *pImgOrigen--;

            *pImgDestino++ = azul;
            *pImgDestino++ = verde;
            *pImgDestino++ = rojo;
        }
    }

    //mostramos imagen orgininal en esquina izda. arriba
    while(1){
        int flag = 0;
        for(fila = 0; fila < ImgDestino->height/2; fila ++){
        unsigned char * pImgOrigen = (unsigned char *) Img->imageData + (fila * Img->widthStep);
        unsigned char * pImgDestino = (unsigned char *) ImgDestino->imageData + (fila * ImgDestino->widthStep);
        
        for(colum = 0; colum < ImgDestino->widthStep/2; colum++){
            if(*pImgDestino > 0){
                *pImgDestino = *pImgDestino -1;
                flag = 1;
            }
            pImgDestino++;
            
        }
    }
        cvNamedWindow("Imagen Destino", CV_WINDOW_AUTOSIZE);
        cvShowImage("Imagen Destino", ImgDestino);
        cvWaitKey(100);
        if(flag == 0){
            break;
        }
        
    }
    
         
    //Realizamos el fundido a negro
     /*while(1){         
         int flag = 0;         
         for(fila = 0; fila < ImgDestino->height; fila++){            
             unsigned char *pImgDestino = (unsigned char *) ImgDestino->imageData + ( fila * ImgDestino->widthStep );            
             for(colum = 0; colum < ImgDestino->widthStep; colum++){                
                 if(*pImgDestino > 0){
                            *pImgDestino = *pImgDestino - 1;
                            flag = 1;
                        }
                       pImgDestino ++;                                        
             }                                    
         }         
         cvNamedWindow("Imagen Destino", CV_WINDOW_AUTOSIZE);
         cvShowImage("Imagen Destino", ImgDestino);
         cvWaitKey(10);        
         if(flag == 0){
             break;
         }        
     }
     
     //Realizamos nuevamente el fundido a imagen original
     while(1){         
         int flag = 0;         
         for(fila = 0; fila < ImgDestino->height; fila++){            
             unsigned char *pImgDestino = (unsigned char *) ImgDestino->imageData + ( fila * ImgDestino->widthStep );
             unsigned char *pImgOrigen = (unsigned char *) Img->imageData + (fila * Img->widthStep);
             for(colum = 0; colum < ImgDestino->widthStep; colum++){                
                 if(*pImgDestino < *pImgOrigen){
                            *pImgDestino = *pImgDestino + 1;
                            flag = 1;
                        }
                       pImgDestino++; 
                       pImgOrigen++;
             }                                    
         }         
         cvNamedWindow("Imagen Destino", CV_WINDOW_AUTOSIZE);
         cvShowImage("Imagen Destino", ImgDestino);
         cvWaitKey(10);        
         if(flag == 0){
             break;
         }        
     }
         
     //Realizamos nuevamente el fundido a blanco
     while(1){         
         int flag = 0;         
         for(fila = 0; fila < ImgDestino->height; fila++){            
             unsigned char *pImgDestino = (unsigned char *) ImgDestino->imageData + ( fila * ImgDestino->widthStep );
             //unsigned char *pImgOrigen = (unsigned char *) Img->imageData + (fila * Img->widthStep);
             for(colum = 0; colum < ImgDestino->widthStep; colum++){                
                 if(*pImgDestino < 255){
                            *pImgDestino = *pImgDestino + 1;
                            flag = 1;
                        }
                       pImgDestino++; 
                       //pImgOrigen++;
             }                                    
         }         
         cvNamedWindow("Imagen Destino", CV_WINDOW_AUTOSIZE);
         cvShowImage("Imagen Destino", ImgDestino);
         cvWaitKey(10);        
         if(flag == 0){
             break;
         }        
     }*/
    
    
    
    
    // memory release for images before exiting the application
    cvReleaseImage(&Img);
    cvReleaseImage(&ImgDestino);  

    // Self-explanatory
    cvDestroyWindow(argv[1]);
    cvDestroyWindow("Imagen Destino");
    
    return EXIT_SUCCESS;  
} 
    /*for(fila = 0; fila < Img->height; fila++){
        
        unsigned char *pImg = (unsigned char *) Img->imageData + (fila * Img->widthStep);
        unsigned char *pImgDestino = (unsigned char *) ImgDestino->imageData + ( fila * (ImgDestino->widthStep));
        
        for(columna = 0; columna < Img->width; columna ++){
            
            *pImgDestino++ = *pImg++;
            
            *pImgDestino++ = 0;
             pImg++;
            
            *pImgDestino++ = 0;
            pImg++;
            
            
        }
    }
    
    for(fila = 0; fila < Img->height; fila++){
        
        unsigned char *pImg = (unsigned char *) Img->imageData + (fila * Img->widthStep);
        unsigned char *pImgDestino = (unsigned char *) ImgDestino->imageData + ( fila * (ImgDestino->widthStep));
        
        for(columna = 0; columna < Img->width; columna ++){
            
            
            *pImgDestino++ = 0;
             pImg++;
            
            *pImgDestino++ = *pImg++;
            
            *pImgDestino++ = 0;
            pImg++;
            
            
        }
    }
    
    for(fila = 0; fila < Img->height; fila++){
        
        unsigned char *pImg = (unsigned char *) Img->imageData + (fila * Img->widthStep);
        unsigned char *pImgDestino = (unsigned char *) ImgDestino->imageData + ( fila + Img->height * (ImgDestino->widthStep));
        
        for(columna = 0; columna < Img->width; columna ++){
            
            
            *pImgDestino++ = 0;
             pImg++;
            
            *pImgDestino++ = 0;
            pImg++;
            
            *pImgDestino++ = *pImg++;
            
            
        }
    }*/
          /*  //printf("%d %d ", sizeof(unsigned char), sizeof(Mypixel));
    int fila, columna;
    //width y height: pixeles
    //widthStep en bytes
    //pixel = 3 bytes (BGR)
    
    for(fila = 0; fila < Img->height/2; fila++){
        
        unsigned char *pImg = (unsigned char *) Img->imageData + (fila * Img->widthStep);
        unsigned char *pImgDestino = (unsigned char *) ImgDestino->imageData + ((ImgDestino->height/2 + fila) * (ImgDestino->widthStep ));
        
        for(columna = 0; columna < Img->widthStep; columna ++){
            
            *pImgDestino++ = *pImg++;
            
            
            
        }
    }
    
    for(fila = 0; fila < Img->height/2; fila++){
        
        unsigned char *pImg = (unsigned char *) Img->imageData + ((fila + Img->height/2) * Img->widthStep);
        unsigned char *pImgDestino = (unsigned char *) ImgDestino->imageData + ( fila * (ImgDestino->widthStep ));
        
        for(columna = 0; columna < Img->widthStep; columna ++){
            
            *pImgDestino++ = *pImg++;
            
            
            
        }
    }
    
     while(1){         
         int flag = 0;         
         for(fila = 0; fila < ImgDestino->height/2; fila++){            
             unsigned char *pImgDestino = (unsigned char *) ImgDestino->imageData + ((ImgDestino->height/2 + fila) * (ImgDestino->widthStep ));            
             for(columna = 0; columna < ImgDestino->widthStep; columna++){                
                 if(*pImgDestino > 0){
                            *pImgDestino = *pImgDestino - 1;
                            flag = 1;
                        }
                       pImgDestino ++;                                        
             }                                    
         }         
         cvNamedWindow("Imagen Destino", CV_WINDOW_AUTOSIZE);
         cvShowImage("Imagen Destino", ImgDestino);
         cvWaitKey(10);        
         if(flag == 0){
             break;
         }        
     }
    
    while(1){         
         int flag = 0;         
         for(fila = 0; fila < ImgDestino->height/2; fila++){            
            unsigned char *pImg = (unsigned char *) Img->imageData + ((fila + Img->height/2) * Img->widthStep);
            unsigned char *pImgDestino = (unsigned char *) ImgDestino->imageData + ( fila * (ImgDestino->widthStep ));             
             for(columna = 0; columna < ImgDestino->widthStep; columna++){                
                 if(*pImgDestino > 0){
                            *pImgDestino = *pImgDestino - 1;
                            flag = 1;
                        }
                       pImgDestino ++;                                        
             }                                    
         }         
         cvNamedWindow("Imagen Destino", CV_WINDOW_AUTOSIZE);
         cvShowImage("Imagen Destino", ImgDestino);
         cvWaitKey(10);        
         if(flag == 0){
             break;
         }        
     }
    
    while(1){
         
         int flag = 0;
         for(fila = 0; fila < Img->height/2; fila++){
             unsigned char *pImg = (unsigned char *) Img->imageData + ((fila + Img->height/2) * Img->widthStep);
             unsigned char *pImgDestino = (unsigned char *) ImgDestino->imageData + ( fila * (ImgDestino->widthStep ));
             for(columna = 0; columna < ImgDestino->widthStep; columna++){                
                 if(*pImgDestino < *pImg){

                            *pImgDestino = *pImgDestino + 1;
                            flag = 1;
                        }

                       pImgDestino ++;  
                       pImg++;                
             }
             
             
         }
         
         cvNamedWindow("Imagen Destino", CV_WINDOW_AUTOSIZE);
         cvShowImage("Imagen Destino", ImgDestino);
         cvWaitKey(100);
         if(flag == 0){
                        break;
                     } 
         
     }*/ 
    // crea y muestras las ventanas con las im genes
    
