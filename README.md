# Harris-corner-detection
Implemented Harris corner detection algorithm
The steps followed are:
1. Read the source image
2. convert to gray scale image
3. find x and y derivatives of gray scale image using sobel function
4. computed attributes of covariance matrix to compute Harris corner response
5. apply gaussian blur to the attributes
6. using the attributes calculated harris corner response = det(M) - k*tr(M)*tr(M)
7. saved the harris corner response in the destination image
8. normalized the image
9. circled the points with response greater than a threshold
