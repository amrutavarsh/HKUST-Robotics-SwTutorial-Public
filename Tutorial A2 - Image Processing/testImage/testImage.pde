PImage testImage;
void setup(){
  size(640,480);
  testImage = loadImage("0036.bmp");
}

int location(int x, int y){
    return x+y*width; //<>//
}

float RGBtoGreyScale(PImage img, int location){
  float greyScale = 0;
  float r = red(img.pixels[location]);
  float g = green(img.pixels[location]);
  float b = blue(img.pixels[location]);
  greyScale = (r*299 + g*587 + b*114 + 500) / 1000;
  return greyScale;
}

void draw(){
  image(testImage, 0, 0);
  loadPixels();
  float threshold = 128;
  for(int i=0; i<width; i++){
    for(int j=0; j<height; j++){
      float greyScaleValue = RGBtoGreyScale(testImage, location(i,j));
      //hint: float nextGreyScaleValue = RGBtoGreyScale(testImage, location(i+1,j));
      
      //implement your ode here
      //objective: mark the edges
      
      /*
      print function:
      pixels[location(i,j)] = color(255,0,0);
      pixels[location(i,j)] = color(greyScaleValue);(range from 0 to 255)  
      */
    }
  }
  updatePixels();
}
