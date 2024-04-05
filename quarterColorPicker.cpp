/**
 * @file quarterColorPicker.cpp
 * @description Implements the QuarterColorPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "quarterColorPicker.h"

QuarterColorPicker::QuarterColorPicker(PNG& inputimg, unsigned char b_amount)
{
    referenceimg = inputimg;
    brightamount = b_amount;
}

/**
 * Picks the color for pixel (x, y).
 *
 * Using the private reference image, scale each dimension by half
 * and tile the smaller image in a 2 x 2 grid over the original dimensions
 * of the image, and return the pixel at the appropriate coordinate from
 * the tiled image, brightened on each R/G/B channel by the required amount.
 * 
 * The value of each pixel in the scaled image will be a bilinear interpolation
 * of a 2x2 pixel region from the original image, with each of the R/G/B/A channels
 * processed individually. Interpolate over the x-axis before the y-axis.
 * Truncate any fractional values on the R/G/B channels. Brighten each color channel
 * as the final step.
 * 
 * @pre referenceimg width and height are both even
 */
RGBAPixel QuarterColorPicker::operator()(PixelPoint p) {
    int originalX = (p.x % (referenceimg.width() / 2)) * 2;
    int originalY = (p.y % (referenceimg.height() / 2)) * 2;

    RGBAPixel* topLeft = referenceimg.getPixel(originalX, originalY);
    RGBAPixel* topRight = referenceimg.getPixel(originalX + 1, originalY);
    RGBAPixel* bottomLeft = referenceimg.getPixel(originalX, originalY + 1);
    RGBAPixel* bottomRight = referenceimg.getPixel(originalX + 1, originalY + 1);

    unsigned int avgR = min(255, (topLeft->r + topRight->r + bottomLeft->r + bottomRight->r) / 4 + brightamount);
    unsigned int avgG = min(255, (topLeft->g + topRight->g + bottomLeft->g + bottomRight->g) / 4 + brightamount);
    unsigned int avgB = min(255, (topLeft->b + topRight->b + bottomLeft->b + bottomRight->b) / 4 + brightamount);
    unsigned int avgA = (topLeft->a + topRight->a + bottomLeft->a + bottomRight->a) / 4;


    RGBAPixel newPixel(avgR, avgG, avgB, avgA);

    return newPixel;
}



/**
 * Add your private QuarterColorPicker function implementations below
 */
