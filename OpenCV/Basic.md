Mat - The Basic Image Container

No need to think about memory management with OpenCVs C++ interface.

two parts：

- the matrix header (containing information such as the size of the matrix, the method used for storing, at which address is the matrix stored, and so on) 
- a pointer to the matrix containing the pixel values

copy：

- use `=` or copy constructor to only copy the header (with reference counting)
- use cv::Mat::clone() and cv::Mat::copyTo() to copy the underlying matrix