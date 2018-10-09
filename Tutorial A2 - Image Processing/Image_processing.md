

1. # Camera, and Image Processing

   Author : Amrutavarsh Kinagi

   Contact: askinagi@connect.ust.hk 

   Author : Morris Tseng

   Contact: mtseng@connect.ust.hk 

   ## Camera - Ov7725

   ov7725 is one of the camera modules used by the Smart Car Sub Team, where it can output picture with various size and in various colour formats. 

   The camera configuration is passed by a communication protocol called SCCB (similar to I2C), and it has also been included inside the camera library.

   Due to the limited memory size and computation power of STM32F1, the default image size is set to be 80 * 60.

   In this library, three colour formats are provided(RGB565 and grey scale). You are also suggested to implement your own method with the raw data in RGB565 or grey scale.

   ### Presetting

   ### Camera Initialization 

   Initialize the camera to RGB or GreyScale

   ```C
   uint8_t cameraInit(ImageType outputType);
   ```

   ImageType:
   RGBColour, GreyScale

   ### Usage

   1. Check whether the image is ready to receive in FIFO buffer

   ```C
   uint8_t camera_ready(void);
   ```

   1. Receive image from the external FIFO buffer into image[row][col] or colourImage[][] depending on ImageType
      The image receive from the camera is stored in an extern uint8_t array "image(colourImage)".

   ```C
   uint8_t camera_receive_frame(void);
   ```

   1. Printing the image

   ```C
   void camera_copy(void);
   
   void camera_print(uint8_t x, uint8_t y);
   
   u8 camera_printing_done(void);
   ```

   - camera_copy will copy the pixels in image[][]/colorImage[][] to the buffer for printing
   - camera_print will print out the buffer to the tft, x and y are the coordinates in the tft (0,0 as the left top corner)
   - the program will continue to run after calling camera_print, however printing will still be ongoing until `camera_printing_done()` return 1;
     - do not attempt to print anything to the tft (using tft_prints/tft_update) until camera printing is done or it will result in errors

   ## Image Processing

   Image Processing and the usage of magnetic sensors are two vital parts in the Smart Car sub-team and the racing robot in the internal competition.  Since is is mandatory that the car be fully automated, we will give you a quick and brief guide to it. 

   ### Before Image Processing

   Since the camera image is stored in pixels in a 2d array, it is important to know the concept and implementations of arrays.

   #### Review on Arrays

   ```C
   #include <stdio.h>
   #define SIZE 180
   
   //passing an array to a function is like pass by reference, not pass by value
   void print_array(int A[], int size){}
   
   int main(){ 
   int myArry[SIZE]; //create an array which has the size 180 and stores int data
   myArry[0] = 1; //assign value to the array
   print_array(myArry, SIZE);
   for(int i=0; i<size; i++){
   //traverse
   }
   return 0;
   }
   ```

   #### Multi-dimensional array

   Here is a 2D array with width 5 and height 3

   [0,0] | [0,1] | [0,2] | [0,3] | [0,4] 
   ----- | ----- | ----- | ----- | ----- 
   [1,0] | [1,1] | [1,2] | [1,3] | [1,4]
   
   [2,0] | [2,1] | [2,2] | [2,3] | [2,4] 

   ```C
   #include <stdio.h>
   #define WIDTH 5
   #define HEIGHT 3
   void print_array(int A[][WIDTH], int height){
   for(int i=0; i<height; i++){
   for(int j=0; j<WIDTH; j++){
   printf("%d ",A[i][j]);
   }
   printf("\n");
   }
   }
   int main(){
   int myArray[HEIGHT][WIDTH];
   for(int i=0; i<HEIGHT; i++){
   for(int j=0; j<WIDTH; j++){
   myArray[i][j] = WIDTH*i+j;
   }
   }
   print_array(myArray, HEIGHT);
   }
   
   ```

   Output

   ```
   0 1 2 3 4 
   5 6 7 8 9 
   10 11 12 13 14 
   ```



   ### Image Processing

   #### 1. Image Type (Colored, Grayscale or Black&White)

   **Colored**

   <img width="480" alt="colored" src="https://user-images.githubusercontent.com/32810188/44947015-2f9d3180-ae39-11e8-854a-a32387a246ef.png">

   **GrayScale**

   <img width="480" alt="greyscale" src="https://user-images.githubusercontent.com/32810188/44947020-404da780-ae39-11e8-8c8b-f1113f03550c.png">

   Please note that the images are rendered instead of taking in reality, so the image shown here may not fully represent the real image that you will be getting.

   ##### Pros and Cons

   - Colored: (colors are stored as RGB in the MCU)
   - Pros: Contains lot of details
   - Cons: Hard to control
   - GreyScale: (range from 0 ~ 255, which black = 0 and white = 255)  **Recommended**
   - Pros: Easier to control(compares to Colored image), able to use gradient to differentiate features
   - Cons: 
   - Black & White: (represented by 1 and 0, which black = 1 and white = 0)
   - Pros: Easiest to control
   - Cons: Hard to adjust thresholding for the image, having less information

   These pros and cons are just a means to guide you. However, these rules aren't set in stone. It is general that for image processing, we would usually choose greyscale or black&white images to analyze as they provide adequate information in order to handle the dynamics of the car. The use of Colored image may provide more information but it is upto you to determine if the extra information available is of any substantial benefit.

   #### 2. Brightness & Intensity

   Apart from color choices, the brightness and the intensity of the image captured also affect the quality of the image you obtain, which in turn affect the ability to extract good data from it.

   **Low Intensity**

   <img width="480" alt="lowintense" src="https://user-images.githubusercontent.com/32810188/44949429-b49d4080-ae63-11e8-902e-17e64f7caf88.png">

   **Medium Intensity**

   <img width="480" alt="mediumintense" src="https://user-images.githubusercontent.com/32810188/44949432-b961f480-ae63-11e8-8896-d919740a78bd.png">

   **High Intensity**

   <img width="480" alt="highintense" src="https://user-images.githubusercontent.com/32810188/44949434-bbc44e80-ae63-11e8-8e68-152058dd8f3a.png">

   If you do not find the proper intensity, your image might contains noise that would deter you from processing the information accurately. It is important that the program you write is able to adjust the brightness and intensity based on different lighting conditions as it is against the rules to flash your program during the competition.

   ## Convolution of image

   #### Introduce to kernel

   A kernel is a square matrix that specifies spatial weights of various pixels in an image. Different image processing have different kernels.

   <img width="480" alt="wrxle" src="https://user-images.githubusercontent.com/32810188/45767787-afb2fc00-bc6d-11e8-81a5-29ba95f1c94a.png">

   #### Convolution Process

   Convolution of a matrix involves laying a matrix over another and then calculating the weighted sum of all pixel values.In this example, it is using an 3x3 kernel for convolution. If the input image is a mxn array, then the ouput array should be (m-2)x(n-2).

   <img width="480" height="360" src="https://user-images.githubusercontent.com/32810188/45766774-f6ebbd80-bc6a-11e8-9aed-c7f57fe57159.JPG">

   105*(0)+102*(-1)+100*(0)+103*(0)... = 89

   More examples:

   <img width="480" height="360" src="https://user-images.githubusercontent.com/32810188/45768526-bb9fbd80-bc6f-11e8-9d93-120bb90f9175.gif">

   ## Application for convolution - Feature Dectection

   Here are some images that have gone through the convolution.

   ![](https://i.imgur.com/T17jDCz.png)



   Convolutions can extended to further detect other vital features of the track. Another key term to keep in mind is **Gradient**.




   ![](https://i.imgur.com/AbQLWej.png)



   Usually image generated might contain noise and will have to be **filtered/ smoothened** to prevent it from affecting the image analysis. 



   ![](https://i.imgur.com/v9DjmbP.png)

   Use of a median filter to improve an image severely corrupted by defective pixels



   **Points to remember:**

   1. Real life situations largely vary from digital replicated simulations. Application of algorithms should thus be geared to tackle the blemishes you would face.
   2. Analyse features and algorithms from a mathematical and physical perspective. 
   3. Keep the program robust in order to tackle the worst cases possible. 
   4. Tuning the physical properties of the car is allowed and remains essential for ensuring the car runs according to plan.
   5. As images are stored in the form of matrices, keep in mind the run time of your program during feature extraction or **path planning.**
