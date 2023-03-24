# CCI-Coding2-Final

#### Yan Wang 22019755 CC

https://user-images.githubusercontent.com/41440180/227395508-be2bea20-403e-43c2-bf3e-2a229dd28dce.MP4

### 

I have created an interactive audio-visual artwork using Openframeworks, incorporating the knowledge I have gained from this semester's classes on classes, inheritance, and the Maximilian library. The project has several key features:

Firstly, pressing the keys 1, 2, and 3 will switch between three black and white images that I have imported as processing materials. Using Openframeworks, I have traversed every pixel in the image to generate a two-dimensional rectangular array of particles.

```
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == '1') attachPtn(imageBili);
	else if (key == '2') attachPtn(imageGit);
	else if (key == '3') attachPtn(imageText);
	else if (key == 'r') resetPtn();
}

//--------------------------------------------------------------
void ofApp::attachPtn(ofImage img) {
	pixels = img.getPixels();

	//rectangle mode
	if (currCellMode == 0) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				int pxCol = floor(ofMap(j, 0, cols - 1, 0, img.getWidth() - 1));
				int pxRow = floor(ofMap(i, 0, rows - 1, 0, img.getHeight() - 1));
				ofColor pxColor = pixels.getColor(pxCol, pxRow);
        
        // Read the brightness value of each pixel. 
        // The lower the brightness, the more black the pixel is, and therefore a larger particle is drawn.
				float wT = ofMap(pxColor.getBrightness(), 0, 255, cellSize * 2, cellSize * .1);
				cells[i][j].resetWT(wT);
			}
		}
	} 
  //dot mode
  //........
}
```

Secondly, moving the mouse affects the movement of the particles. I have obtained the position of the mouse and passed it to the instantiated class object to add force to the particles and make them move.

Thirdly, moving the mouse changes the synthesized background music. I have used the Maximilian library and the triangle function to generate music. The mouse's x-position alters the frequency of the sound.

Lastly, pressing the R key will change the image generation mode between two different modes. The first mode generates rectangular particles with borders using the base class Cell, while the second mode generates circular particles using the subclass CellChild, which inherits all of the base class Cell's functions but only rewrites the shape of the particles in the display function.

Through this project, I have applied my understanding of classes, inheritance, and Maximilian library usage in creating an engaging and interactive artwork that responds to user input.
