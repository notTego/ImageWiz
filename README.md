# ImageWiz

ImageWiz is a program designed to process images. It accepts the following commands: LOAD, SELECT, SELECT ALL, ROTATE, SAVE, APPLY, and EXIT.

## Decision Making with `int main()`

The main function employs a `switch-case` conditional to improve code readability and maintain a cleaner appearance. Normally, `switch-case` works with numerical values, but since commands are entered as strings, implementing a decision-based program might seem challenging, requiring multiple "if" statements and potentially making the code harder to follow. However, a unique integer code is assigned to each string using string hashing (see `hash.c`). After assigning each command its unique hash, these hashes are compiled and tagged with suggestive names in an enum to enhance comprehension.

## Storing Pixel Values (color_values.h)

Pixel values are stored as a matrix of arrays. A struct is used, containing a pointer to an array of unsigned chars. Each element in the matrix represents an array with a length of either 1 or 3, depending on the image type.

## LOAD

The LOAD command takes a string as a parameter, opens the file with the specified name, and parses its content. This process retrieves data from the file, including image type, file type, dimensions, and more.

## SELECT

The SELECT command allows you to choose a rectangular area within the loaded image. It requires two points: the top-left corner and the bottom-right corner, specified by their coordinates. SELECT ALL is a special case that uses (0,0) and (width, height) as the default rectangular area delimiters. It shares a function with SELECT, detecting whether integers or the string "ALL" are provided after SELECT and executing the appropriate instructions.

## ROTATE (Partial Implementation)

The ROTATE feature is partially implemented and works in two cases:
1. When the entire image is selected, it attempts to rotate it 90 degrees clockwise by transposing the matrix and flipping its elements around the vertical axis.
2. When a square selection has been previously made, it follows a similar method of element-by-element manipulation using an auxiliary variable.

## SAVE

The SAVE command allows you to save the image matrix to a file with an optional format parameter (e.g., "ascii" for ASCII format). It accepts a maximum of two strings: the file name and the format.

## APPLY (Partial Implementation)

The APPLY command applies convolution between the loaded image's matrix and a specified kernel. Different APPLY options are implemented using string hashing to facilitate the use of a `switch-case` statement.

## EXIT

The EXIT command frees all the memory allocated during the process and terminates the program.