# ImageFilter

ImageFilter is a C library that applies transformation to images like negative, rotate, blur, etc.

* **Easy:** Say what transformation you want on what image and apply!
* **Flexible:** You can mix transformations.
* **Clear:** You know exactly what's going on.

## Examples

```c
  source = charger_image_pgm("vache_positive.png");
  destination = negatif(source);
  sauver_image_pgm("vache_negative.png", destination);
  destination = rotation_droite(source, 90);
  sauver_image_pgm("vache_rotate.png", destination);
```

This example applies successively a negative transformation and a rotation.

The original image is:
![alt tag](https://github.com/afissegalaad/ImageFilter/blob/master/images/vache_positive.png)

## Installation

Include the library in your C code:

## License

ImageFilter is made under the terms of the MIT license.